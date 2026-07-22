#include <stdio.h>
#include <string.h>

#include "battle.h"
#include "moves.h"

// =========================
// INTERNAL BATTLE STATE
// =========================

typedef enum
{
    BSTATE_MAIN_MENU,     // Attack / Run choice, shown first
    BSTATE_MOVE_SELECT,   // player is picking a move from the 2x2 grid
    BSTATE_MESSAGE        // stepping through the results of the turn

} BattleSubState;

static Team *playerTeam;
static Team *npcTeam;

static BattleSubState subState;

static int menuCursor;    // 0 = Attack, 1 = Run

static int cursorRow;
static int cursorCol;

#define MAX_MESSAGES 6
static char messageQueue[MAX_MESSAGES][96];
static int messageCount;
static int messageIndex;

static bool battleEnded;   // set true once a team has no Pokemon left


// =========================
// HELPERS
// =========================

static void QueueMessage(const char *text)
{
    if (messageCount < MAX_MESSAGES)
    {
        strncpy(messageQueue[messageCount], text, 95);
        messageQueue[messageCount][95] = '\0';
        messageCount++;
    }
}

static int FindNextAlive(Team *team)
{
    for (int i = 0; i < 3; i++)
    {
        if (!team->pokemon[i].fainted)
        {
            return i;
        }
    }

    return -1;
}

// Real level-50 damage formula, without a type-effectiveness multiplier.
static int CalculateDamage(Pokemon *attacker, Pokemon *defender, Move move)
{
    int damage =
        ((2 * attacker->level / 5 + 2) * move.power * attacker->attack / defender->defense) / 50 + 2;

    return damage;
}


// =========================
// TURN RESOLUTION
// =========================

static void ResolveTurn(int playerMoveId)
{
    messageCount = 0;
    messageIndex = 0;
    battleEnded = false;

    Pokemon *playerActive = &playerTeam->pokemon[playerTeam->activeIndex];
    Pokemon *npcActive    = &npcTeam->pokemon[npcTeam->activeIndex];

    int npcMoveId = npcActive->moveIds[GetRandomValue(0, 3)];

    Move playerMove = moveTable[playerMoveId];
    Move npcMove    = moveTable[npcMoveId];

    bool playerProtected = false;
    bool npcProtected = false;

    // Higher Speed moves first; player wins ties.
    bool playerFirst = playerActive->speed >= npcActive->speed;

    for (int turn = 0; turn < 2; turn++)
    {
        bool isPlayerTurn = (turn == 0) ? playerFirst : !playerFirst;

        Pokemon *attacker = isPlayerTurn ? playerActive : npcActive;
        Pokemon *defender = isPlayerTurn ? npcActive : playerActive;
        Move move         = isPlayerTurn ? playerMove : npcMove;

        bool *defenderProtected = isPlayerTurn ? &npcProtected : &playerProtected;

        // Fainted earlier this same turn -- cannot act.
        if (attacker->fainted)
        {
            continue;
        }

        char msg[96];

        if (move.isStatus)
        {
            if (isPlayerTurn) playerProtected = true; else npcProtected = true;

            snprintf(msg, sizeof(msg), "%s used %s!", attacker->name, move.name);
            QueueMessage(msg);
            continue;
        }

        if (*defenderProtected)
        {
            snprintf(msg, sizeof(msg), "%s protected itself!", defender->name);
            QueueMessage(msg);
            continue;
        }

        int damage = CalculateDamage(attacker, defender, move);
        defender->hp -= damage;
        if (defender->hp < 0) defender->hp = 0;

        snprintf(msg, sizeof(msg), "%s used %s!", attacker->name, move.name);
        QueueMessage(msg);

        snprintf(msg, sizeof(msg), "%s took %d damage!", defender->name, damage);
        QueueMessage(msg);

        if (defender->hp == 0)
        {
            defender->fainted = true;

            snprintf(msg, sizeof(msg), "%s fainted!", defender->name);
            QueueMessage(msg);

            Team *defTeam = isPlayerTurn ? npcTeam : playerTeam;
            int nextIndex = FindNextAlive(defTeam);

            if (nextIndex == -1)
            {
                battleEnded = true;

                if (isPlayerTurn)
                {
                    QueueMessage("NPC: Oh, you are good, nice job!");
                }
                else
                {
                    QueueMessage("NPC: Well, we all have to lose sometimes. Better luck next time!");
                }

                break;
            }
            else
            {
                defTeam->activeIndex = nextIndex;

                if (defTeam == playerTeam)
                {
                    snprintf(msg, sizeof(msg), "Go, %s!", defTeam->pokemon[nextIndex].name);
                }
                else
                {
                    snprintf(msg, sizeof(msg), "NPC sent out %s!", defTeam->pokemon[nextIndex].name);
                }

                QueueMessage(msg);
            }
        }
    }
}


// Fleeing counts as an automatic loss -- reuses the exact same
// battleEnded + message flow as a real defeat.
static void ResolveRun(void)
{
    messageCount = 0;
    messageIndex = 0;
    battleEnded = true;

    QueueMessage("You ran from the battle!");
    QueueMessage("NPC: Well, we all have to lose sometimes. Better luck next time!");
}


// =========================
// INIT
// =========================

void InitBattle(Team *pTeam, Team *nTeam)
{
    playerTeam = pTeam;
    npcTeam = nTeam;

    for (int i = 0; i < 3; i++)
    {
        playerTeam->pokemon[i].hp = playerTeam->pokemon[i].maxHp;
        playerTeam->pokemon[i].fainted = false;

        npcTeam->pokemon[i].hp = npcTeam->pokemon[i].maxHp;
        npcTeam->pokemon[i].fainted = false;
    }

    playerTeam->activeIndex = 0;
    npcTeam->activeIndex = 0;

    subState = BSTATE_MAIN_MENU;
    menuCursor = 0;
    cursorRow = 0;
    cursorCol = 0;

    messageCount = 0;
    messageIndex = 0;

    battleEnded = false;
}


// =========================
// UPDATE
// =========================

bool UpdateBattle(void)
{
    switch (subState)
    {
        case BSTATE_MAIN_MENU:
        {
            if (IsKeyPressed(KEY_DOWN) && menuCursor == 0) menuCursor = 1;
            if (IsKeyPressed(KEY_UP)   && menuCursor == 1) menuCursor = 0;

            if (IsKeyPressed(KEY_ENTER))
            {
                if (menuCursor == 0) // Attack
                {
                    subState = BSTATE_MOVE_SELECT;
                    cursorRow = 0;
                    cursorCol = 0;
                }
                else // Run
                {
                    ResolveRun();
                    subState = BSTATE_MESSAGE;
                }
            }

            break;
        }

        case BSTATE_MOVE_SELECT:
        {
            if (IsKeyPressed(KEY_RIGHT) && cursorCol == 0) cursorCol = 1;
            if (IsKeyPressed(KEY_LEFT)  && cursorCol == 1) cursorCol = 0;
            if (IsKeyPressed(KEY_DOWN)  && cursorRow == 0) cursorRow = 1;
            if (IsKeyPressed(KEY_UP)    && cursorRow == 1) cursorRow = 0;

            if (IsKeyPressed(KEY_ENTER))
            {
                int moveSlot = cursorRow * 2 + cursorCol;

                Pokemon *playerActive = &playerTeam->pokemon[playerTeam->activeIndex];
                int playerMoveId = playerActive->moveIds[moveSlot];

                ResolveTurn(playerMoveId);

                subState = BSTATE_MESSAGE;
            }

            break;
        }

        case BSTATE_MESSAGE:
        {
            if (IsKeyPressed(KEY_E))
            {
                messageIndex++;

                if (messageIndex >= messageCount)
                {
                    if (battleEnded)
                    {
                        return true;
                    }

                    subState = BSTATE_MAIN_MENU;
                    menuCursor = 0;
                }
            }

            break;
        }
    }

    return false;
}


// =========================
// DRAW HELPERS
// =========================

static void DrawPokemonBlock(Pokemon *poke, int x, int y)
{
    // HP bar background
    DrawRectangle(x, y - 24, 120, 12, BLACK);

    float hpRatio = (float)poke->hp / (float)poke->maxHp;
    Color hpColor = (hpRatio > 0.5f) ? GREEN : (hpRatio > 0.2f) ? YELLOW : RED;

    DrawRectangle(x + 2, y - 22, (int)(116 * hpRatio), 8, hpColor);
    DrawRectangleLines(x, y - 24, 120, 12, WHITE);

    // Name / HP text
    char label[48];
    snprintf(label, sizeof(label), "%s  %d/%d", poke->name, poke->hp, poke->maxHp);
    DrawText(label, x, y - 44, 16, WHITE);

    // Sprite block (colored per species)
    if (!poke->fainted)
    {
        DrawRectangle(x, y, 60, 60, poke->spriteColor);
        DrawRectangleLines(x, y, 60, 60, WHITE);
    }
    else
    {
        DrawRectangleLines(x, y, 60, 60, GRAY);
        DrawText("FAINTED", x, y + 22, 12, GRAY);
    }
}

static void DrawMessageBox(const char *text)
{
    DrawRectangle(50, 430, 700, 120, BLACK);
    DrawRectangleLines(50, 430, 700, 120, WHITE);

    DrawText(text, 75, 470, 24, WHITE);
    DrawText("Press E to continue", 550, 525, 16, LIGHTGRAY);
}

static void DrawMainMenu(void)
{
    DrawRectangle(50, 430, 220, 120, BLACK);
    DrawRectangleLines(50, 430, 220, 120, WHITE);

    const char *options[2] = { "Attack", "Run" };

    for (int i = 0; i < 2; i++)
    {
        bool selected = (menuCursor == i);

        DrawText(selected ? ">" : " ", 65, 455 + i * 40, 24,
            selected ? YELLOW : WHITE);

        DrawText(options[i], 90, 455 + i * 40, 24,
            selected ? YELLOW : WHITE);
    }
}

static void DrawMoveGrid(void)
{
    Pokemon *playerActive = &playerTeam->pokemon[playerTeam->activeIndex];

    DrawRectangle(50, 430, 700, 120, BLACK);
    DrawRectangleLines(50, 430, 700, 120, WHITE);

    int cellWidth = 340;
    int cellHeight = 50;
    int startX = 60;
    int startY = 440;

    for (int row = 0; row < 2; row++)
    {
        for (int col = 0; col < 2; col++)
        {
            int slot = row * 2 + col;
            Move move = moveTable[playerActive->moveIds[slot]];

            int cellX = startX + col * cellWidth;
            int cellY = startY + row * cellHeight;

            bool selected = (row == cursorRow && col == cursorCol);

            DrawRectangleLines(cellX, cellY, cellWidth - 10, cellHeight - 10,
                selected ? YELLOW : GRAY);

            DrawText(move.name, cellX + 10, cellY + 12, 20,
                selected ? YELLOW : WHITE);
        }
    }
}


// =========================
// DRAW
// =========================

void DrawBattle(void)
{
    DrawRectangle(0, 0, 800, 600, DARKGRAY);

    Pokemon *playerActive = &playerTeam->pokemon[playerTeam->activeIndex];
    Pokemon *npcActive    = &npcTeam->pokemon[npcTeam->activeIndex];

    DrawPokemonBlock(npcActive, 560, 120);
    DrawPokemonBlock(playerActive, 100, 300);

    if (subState == BSTATE_MAIN_MENU)
    {
        DrawMainMenu();
    }
    else if (subState == BSTATE_MOVE_SELECT)
    {
        DrawMoveGrid();
    }
    else if (subState == BSTATE_MESSAGE)
    {
        DrawMessageBox(messageQueue[messageIndex]);
    }
}