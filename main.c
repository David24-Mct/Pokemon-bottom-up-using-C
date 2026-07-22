#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define TILE_SIZE 40
#define MAP_WIDTH 40
#define MAP_HEIGHT 30

#include "battle.h"

// =========================
// PLAYER DIRECTION
// =========================

typedef enum
{
    DIRECTION_DOWN,
    DIRECTION_UP,
    DIRECTION_LEFT,
    DIRECTION_RIGHT

} Direction;


// =========================
// DIALOGUE STATE
// =========================

typedef enum
{
    DIALOGUE_CLOSED,
    DIALOGUE_ACTIVE,
    DIALOGUE_CONFIRM_BATTLE

} DialogueState;


// =========================
// PLAYER STRUCTURE
// =========================

typedef struct
{
    Vector2 position;

    float speed;

    int size;

    Direction direction;

} Player;


// =========================
// NPC STRUCTURE
// =========================

typedef struct
{
    Vector2 position;

    int size;

} NPC;

typedef enum
{
    GAME_OVERWORLD,
    GAME_BATTLE
} GameState;
// =========================
// MAP
// =========================

// 0 = Grass
// 1 = Path
// 2 = Water
// 3 = Tree

int map[MAP_HEIGHT][MAP_WIDTH];


// =========================
// DIALOGUE DATA
// =========================

const char *dialogueLines[] =
{
    "Welcome to Monster Realms!",

    "This world is full of mystery.",

    "There are many places waiting to be explored.",

    "You should begin your adventure soon.",

    "Good luck, young trainer!"
};


#define TOTAL_DIALOGUE_LINES 5


// =========================
// CREATE MAP
// =========================

void CreateMap(void)
{
    // Fill map with grass

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            map[y][x] = 0;
        }
    }


    // Horizontal path

    for (int x = 0; x < MAP_WIDTH; x++)
    {
        map[15][x] = 1;
        map[16][x] = 1;
    }


    // Vertical path

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        map[y][19] = 1;
        map[y][20] = 1;
    }


    // Water lake

    for (int y = 5; y < 12; y++)
    {
        for (int x = 5; x < 13; x++)
        {
            map[y][x] = 2;
        }
    }


    // Second water area

    for (int y = 20; y < 26; y++)
    {
        for (int x = 28; x < 37; x++)
        {
            map[y][x] = 2;
        }
    }


    // Forest 1

    for (int y = 2; y < 6; y++)
    {
        for (int x = 25; x < 30; x++)
        {
            map[y][x] = 3;
        }
    }


    // Forest 2

    for (int y = 20; y < 25; y++)
    {
        for (int x = 5; x < 10; x++)
        {
            map[y][x] = 3;
        }
    }
}


// =========================
// TILE WALKABILITY
// =========================

bool IsTileWalkable(int tile)
{
    if (tile == 0)
    {
        return true;
    }


    if (tile == 1)
    {
        return true;
    }


    return false;
}


// =========================
// PLAYER COLLISION
// =========================

bool CanMoveTo(
    Player player,
    NPC npc,
    float newX,
    float newY
)
{
    int leftTile =
        newX / TILE_SIZE;


    int rightTile =
        (newX + player.size - 1)
        / TILE_SIZE;


    int topTile =
        newY / TILE_SIZE;


    int bottomTile =
        (newY + player.size - 1)
        / TILE_SIZE;


    // World boundaries

    if (
        leftTile < 0 ||
        rightTile >= MAP_WIDTH ||
        topTile < 0 ||
        bottomTile >= MAP_HEIGHT
    )
    {
        return false;
    }


    // Tile collision

    if (
        !IsTileWalkable(
            map[topTile][leftTile]
        )
    )
    {
        return false;
    }


    if (
        !IsTileWalkable(
            map[topTile][rightTile]
        )
    )
    {
        return false;
    }


    if (
        !IsTileWalkable(
            map[bottomTile][leftTile]
        )
    )
    {
        return false;
    }


    if (
        !IsTileWalkable(
            map[bottomTile][rightTile]
        )
    )
    {
        return false;
    }


    // Player rectangle

    Rectangle playerRect =
    {
        newX,
        newY,
        player.size,
        player.size
    };


    // NPC rectangle

    Rectangle npcRect =
    {
        npc.position.x,
        npc.position.y,
        npc.size,
        npc.size
    };


    // NPC collision

    if (
        CheckCollisionRecs(
            playerRect,
            npcRect
        )
    )
    {
        return false;
    }


    return true;
}


// =========================
// NPC INTERACTION
// =========================

bool IsNearNPC(
    Player player,
    NPC npc
)
{
    Rectangle playerRect =
    {
        player.position.x,
        player.position.y,
        player.size,
        player.size
    };


    Rectangle interactionArea =
    {
        npc.position.x - 20,
        npc.position.y - 20,
        npc.size + 40,
        npc.size + 40
    };


    return CheckCollisionRecs(
        playerRect,
        interactionArea
    );
}


// =========================
// DRAW MAP
// =========================

void DrawMap(void)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            int tile =
                map[y][x];


            // Grass

            if (tile == 0)
            {
                DrawRectangle(
                    x * TILE_SIZE,
                    y * TILE_SIZE,
                    TILE_SIZE,
                    TILE_SIZE,
                    GREEN
                );
            }


            // Path

            else if (tile == 1)
            {
                DrawRectangle(
                    x * TILE_SIZE,
                    y * TILE_SIZE,
                    TILE_SIZE,
                    TILE_SIZE,
                    BEIGE
                );
            }


            // Water

            else if (tile == 2)
            {
                DrawRectangle(
                    x * TILE_SIZE,
                    y * TILE_SIZE,
                    TILE_SIZE,
                    TILE_SIZE,
                    BLUE
                );
            }


            // Trees

            else if (tile == 3)
            {
                DrawRectangle(
                    x * TILE_SIZE,
                    y * TILE_SIZE,
                    TILE_SIZE,
                    TILE_SIZE,
                    GREEN
                );


                DrawRectangle(
                    x * TILE_SIZE + 15,
                    y * TILE_SIZE + 20,
                    10,
                    20,
                    BROWN
                );


                DrawCircle(
                    x * TILE_SIZE +
                    TILE_SIZE / 2,

                    y * TILE_SIZE + 18,

                    18,

                    DARKGREEN
                );
            }


            // Tile border

            DrawRectangleLines(
                x * TILE_SIZE,
                y * TILE_SIZE,
                TILE_SIZE,
                TILE_SIZE,
                DARKGREEN
            );
        }
    }
}


// =========================
// DRAW PLAYER
// =========================

void DrawPlayer(
    Player player
)
{
    Color playerColor =
        DARKBLUE;


    if (
        player.direction ==
        DIRECTION_UP
    )
    {
        playerColor =
            RED;
    }


    else if (
        player.direction ==
        DIRECTION_DOWN
    )
    {
        playerColor =
            GREEN;
    }


    else if (
        player.direction ==
        DIRECTION_LEFT
    )
    {
        playerColor =
            YELLOW;
    }


    else if (
        player.direction ==
        DIRECTION_RIGHT
    )
    {
        playerColor =
            PURPLE;
    }


    // Player body

    DrawRectangle(
        player.position.x,
        player.position.y,
        player.size,
        player.size,
        playerColor
    );


    // Direction arrow

    if (
        player.direction ==
        DIRECTION_UP
    )
    {
        DrawTriangle(
            (Vector2)
            {
                player.position.x +
                player.size / 2,

                player.position.y - 10
            },

            (Vector2)
            {
                player.position.x + 5,

                player.position.y
            },

            (Vector2)
            {
                player.position.x +
                player.size - 5,

                player.position.y
            },

            WHITE
        );
    }


    else if (
        player.direction ==
        DIRECTION_DOWN
    )
    {
        DrawTriangle(
            (Vector2)
            {
                player.position.x + 5,

                player.position.y +
                player.size
            },

            (Vector2)
            {
                player.position.x +
                player.size - 5,

                player.position.y +
                player.size
            },

            (Vector2)
            {
                player.position.x +
                player.size / 2,

                player.position.y +
                player.size + 10
            },

            WHITE
        );
    }


    else if (
        player.direction ==
        DIRECTION_LEFT
    )
    {
        DrawTriangle(
            (Vector2)
            {
                player.position.x - 10,

                player.position.y +
                player.size / 2
            },

            (Vector2)
            {
                player.position.x,

                player.position.y + 5
            },

            (Vector2)
            {
                player.position.x,

                player.position.y +
                player.size - 5
            },

            WHITE
        );
    }


    else if (
        player.direction ==
        DIRECTION_RIGHT
    )
    {
        DrawTriangle(
            (Vector2)
            {
                player.position.x +
                player.size + 10,

                player.position.y +
                player.size / 2
            },

            (Vector2)
            {
                player.position.x +
                player.size,

                player.position.y + 5
            },

            (Vector2)
            {
                player.position.x +
                player.size,

                player.position.y +
                player.size - 5
            },

            WHITE
        );
    }
}


// =========================
// DRAW NPC
// =========================

void DrawNPC(
    NPC npc
)
{
    // NPC body

    DrawRectangle(
        npc.position.x,
        npc.position.y,
        npc.size,
        npc.size,
        BLACK
    );


    // NPC head

    DrawCircle(
        npc.position.x +
        npc.size / 2,

        npc.position.y - 10,

        10,

        BEIGE
    );


    // NPC label

    DrawText(
        "NPC",

        npc.position.x - 5,

        npc.position.y - 35,

        20,

        WHITE
    );
}


// =========================
// DRAW DIALOGUE BOX
// =========================

void DrawDialogueBox(
    int currentLine
)
{
    // Dialogue background

    DrawRectangle(
        50,
        430,
        700,
        120,
        BLACK
    );


    // Dialogue border

    DrawRectangleLines(
        50,
        430,
        700,
        120,
        WHITE
    );


    // NPC name

    DrawText(
        "NPC:",

        75,
        455,

        20,

        YELLOW
    );


    // Current dialogue line

    DrawText(
        dialogueLines[currentLine],

        75,
        490,

        24,

        WHITE
    );


    // Instruction

    if (
        currentLine <
        TOTAL_DIALOGUE_LINES - 1
    )
    {
        DrawText(
            "Press E to continue",

            550,
            525,

            16,

            LIGHTGRAY
        );
    }


    else
    {
        DrawText(
            "Press E to finish",

            550,
            525,

            16,

            LIGHTGRAY
        );
    }
}


// =========================
// DRAW BATTLE CONFIRM BOX
// =========================

void DrawBattleConfirmBox(
    int confirmCursor
)
{
    // Same box position/style as the dialogue box, for visual consistency

    DrawRectangle(
        50,
        430,
        700,
        120,
        BLACK
    );

    DrawRectangleLines(
        50,
        430,
        700,
        120,
        WHITE
    );

    DrawText(
        "NPC:",

        75,
        455,

        20,

        YELLOW
    );

    DrawText(
        "Do you want to battle?",

        75,
        490,

        24,

        WHITE
    );

    const char *options[2] = { "Yes", "No" };

    for (int i = 0; i < 2; i++)
    {
        bool selected = (confirmCursor == i);

        DrawText(
            selected ? ">" : " ",
            600,
            460 + i * 30,
            20,
            selected ? YELLOW : WHITE
        );

        DrawText(
            options[i],
            620,
            460 + i * 30,
            20,
            selected ? YELLOW : WHITE
        );
    }
}


// =========================
// MAIN
// =========================

int main(void)
{
    // Create window

    InitWindow(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        "Monster Realms"
    );


    SetTargetFPS(60);


    // Create map

    CreateMap();


    // =========================
    // CREATE PLAYER
    // =========================

    Player player;


    player.position.x =
        760;


    player.position.y =
        540;


    player.speed =
        5.0f;


    player.size =
        30;


    player.direction =
        DIRECTION_DOWN;


    // =========================
    // CREATE NPC
    // =========================

    NPC npc;


    npc.position.x =
        820;


    npc.position.y =
        540;


    npc.size =
        30;


    // =========================
    // DIALOGUE SYSTEM
    // =========================

    DialogueState dialogueState =
        DIALOGUE_CLOSED;

    GameState gameState = GAME_OVERWORLD;
    int currentDialogueLine =
        0;

    int battleConfirmCursor = 0;   // 0 = Yes, 1 = No

    // =========================
    // BATTLE TEAMS
    // =========================

    Team playerTeam = CreatePlayerTeam();
    Team npcTeam = CreateNPCTeam();


    // =========================
    // CREATE CAMERA
    // =========================

    Camera2D camera =
        { 0 };


    camera.target =
        (Vector2)
        {
            player.position.x +
            player.size / 2,

            player.position.y +
            player.size / 2
        };


    camera.offset =
        (Vector2)
        {
            SCREEN_WIDTH / 2,

            SCREEN_HEIGHT / 2
        };


    camera.rotation =
        0.0f;


    camera.zoom =
        1.0f;


    // =========================
    // GAME LOOP
    // =========================

    while (
        !WindowShouldClose()
    )
    {
        // =========================
        // DIALOGUE INPUT
        // =========================
        // Only runs in the overworld -- otherwise pressing E to advance a
        // battle message would also fire this and reopen the NPC chat
        // on top of the battle screen.

        if (
            gameState == GAME_OVERWORLD &&
            IsKeyPressed(KEY_E)
        )
        {
            // Start conversation

            if (
                dialogueState ==
                DIALOGUE_CLOSED
            )
            {
                if (
                    IsNearNPC(
                        player,
                        npc
                    )
                )
                {
                    dialogueState =
                        DIALOGUE_ACTIVE;


                    currentDialogueLine =
                        0;
                }
            }


            // Continue conversation

            else if (
                dialogueState ==
                DIALOGUE_ACTIVE
            )
            {
                currentDialogueLine++;


                // Conversation finished -- instead of jumping straight
                // into battle, ask the player first.

                if (
                    currentDialogueLine >=
                    TOTAL_DIALOGUE_LINES
                )
                {
                    dialogueState =
                        DIALOGUE_CONFIRM_BATTLE;

                    battleConfirmCursor = 0;

                    currentDialogueLine =
                        0;
                }
            }
        }

        // =========================
        // BATTLE CONFIRM INPUT
        // =========================
        // "Do you want to battle?" -- Yes/No prompt shown after the
        // intro conversation finishes.

        if (
            gameState == GAME_OVERWORLD &&
            dialogueState == DIALOGUE_CONFIRM_BATTLE
        )
        {
            if (IsKeyPressed(KEY_DOWN) && battleConfirmCursor == 0) battleConfirmCursor = 1;
            if (IsKeyPressed(KEY_UP)   && battleConfirmCursor == 1) battleConfirmCursor = 0;

            if (IsKeyPressed(KEY_ENTER))
            {
                dialogueState = DIALOGUE_CLOSED;

                if (battleConfirmCursor == 0) // Yes
                {
                    InitBattle(&playerTeam, &npcTeam);
                    gameState = GAME_BATTLE;
                }
                // No -- just closes the dialogue, no battle starts
            }
        }
        if (IsKeyPressed(KEY_B))
        {
            if (gameState == GAME_OVERWORLD)
            {
                InitBattle(&playerTeam, &npcTeam);
                gameState = GAME_BATTLE;
            }
        }

        // =========================
        // PLAYER MOVEMENT
        // =========================

        // Player cannot move during dialogue

        if (
            dialogueState ==
            DIALOGUE_CLOSED
        )
        {
            // Move right

            if (
                IsKeyDown(KEY_RIGHT)
            )
            {
                player.direction =
                    DIRECTION_RIGHT;


                float newX =
                    player.position.x +
                    player.speed;


                if (
                    CanMoveTo(
                        player,
                        npc,
                        newX,
                        player.position.y
                    )
                )
                {
                    player.position.x =
                        newX;
                }
            }


            // Move left

            else if (
                IsKeyDown(KEY_LEFT)
            )
            {
                player.direction =
                    DIRECTION_LEFT;


                float newX =
                    player.position.x -
                    player.speed;


                if (
                    CanMoveTo(
                        player,
                        npc,
                        newX,
                        player.position.y
                    )
                )
                {
                    player.position.x =
                        newX;
                }
            }


            // Move up

            else if (
                IsKeyDown(KEY_UP)
            )
            {
                player.direction =
                    DIRECTION_UP;


                float newY =
                    player.position.y -
                    player.speed;


                if (
                    CanMoveTo(
                        player,
                        npc,
                        player.position.x,
                        newY
                    )
                )
                {
                    player.position.y =
                        newY;
                }
            }


            // Move down

            else if (
                IsKeyDown(KEY_DOWN)
            )
            {
                player.direction =
                    DIRECTION_DOWN;


                float newY =
                    player.position.y +
                    player.speed;


                if (
                    CanMoveTo(
                        player,
                        npc,
                        player.position.x,
                        newY
                    )
                )
                {
                    player.position.y =
                        newY;
                }
            }
        }


        // =========================
        // UPDATE CAMERA
        // =========================

        camera.target =
            (Vector2)
            {
                player.position.x +
                player.size / 2,

                player.position.y +
                player.size / 2
            };


        // =========================
        // DRAW
        // =========================

        if (gameState == GAME_OVERWORLD)
                {
                BeginMode2D(camera);

                DrawMap();
                DrawNPC(npc);
                DrawPlayer(player);

                EndMode2D();
            }
            else if (gameState == GAME_BATTLE)
            {
                if (UpdateBattle())
                {
                    gameState = GAME_OVERWORLD;
                }

                DrawBattle();
            }


        // Dialogue UI

        if (
            dialogueState ==
            DIALOGUE_ACTIVE
        )
        {
            DrawDialogueBox(
                currentDialogueLine
            );
        }
        else if (dialogueState == DIALOGUE_CONFIRM_BATTLE)
        {
            DrawBattleConfirmBox(battleConfirmCursor);
        }


        EndDrawing();
    }


    // Close window

    CloseWindow();


    return 0;
}