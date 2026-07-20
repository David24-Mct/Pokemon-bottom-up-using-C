#include "raylib.h"
#include "player.h"
#include "npc.h"
#include "world.h"
#include "dialogue.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define TILE_SIZE 40
#define MAP_WIDTH 40
#define MAP_HEIGHT 30

#define MAX_NPCS 3




// =========================
// NPC DIALOGUE
// =========================

const char *elderDialogue[] =
{
    "Welcome to our village!",
    "The forest ahead is dangerous.",
    "Many trainers have disappeared there.",
    "Be careful on your journey."
};

const char *scientistDialogue[] =
{
    "Ah! A new adventurer!",
    "I am studying the creatures of this world.",
    "There is still so much we do not know.",
    "Perhaps you can help me someday."
};

const char *travellerDialogue[] =
{
    "Hey there, traveller!",
    "The road ahead is long.",
    "You should explore every area you find.",
    "You never know what you might discover."
};





// =========================
// CHECK PLAYER MOVEMENT
// =========================

bool CanMoveTo(
    Player player,
    NPC npcs[],
    int npcCount,
    float newX,
    float newY
)
{
    int leftTile =
        (int)newX / TILE_SIZE;

    int rightTile =
        (int)(newX + player.size - 1) / TILE_SIZE;

    int topTile =
        (int)newY / TILE_SIZE;

    int bottomTile =
        (int)(newY + player.size - 1) / TILE_SIZE;


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

    if (!IsTileWalkable(map[topTile][leftTile]))
        return false;

    if (!IsTileWalkable(map[topTile][rightTile]))
        return false;

    if (!IsTileWalkable(map[bottomTile][leftTile]))
        return false;

    if (!IsTileWalkable(map[bottomTile][rightTile]))
        return false;


    // Player rectangle

    Rectangle playerRect =
    {
        newX,
        newY,
        player.size,
        player.size
    };


    // NPC collision

    for (int i = 0; i < npcCount; i++)
    {
        Rectangle npcRect =
        {
            npcs[i].position.x,
            npcs[i].position.y,
            npcs[i].size,
            npcs[i].size
        };

        if (
            CheckCollisionRecs(
                playerRect,
                npcRect
            )
        )
        {
            return false;
        }
    }

    return true;
}



// =========================
// DRAW DIALOGUE BOX
// =========================



// =========================
// MAIN
// =========================

int main(void)
{
    InitWindow(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        "Monster Realms"
    );

    SetTargetFPS(60);

    CreateMap();


    // =========================
    // PLAYER
    // =========================

    Player player =
    {
        .position = { 760, 540 },
        .speed = 5.0f,
        .size = 30,
        .direction = DIRECTION_DOWN
    };


    // =========================
    // NPCS
    // =========================

    NPC npcs[MAX_NPCS];


    npcs[0] =
    (NPC)
    {
        .position = { 820, 540 },
        .size = 30,
        .name = "Elder",
        .dialogue = elderDialogue,
        .dialogueLineCount = 4
    };


    npcs[1] =
    (NPC)
    {
        .position = { 1200, 600 },
        .size = 30,
        .name = "Scientist",
        .dialogue = scientistDialogue,
        .dialogueLineCount = 4
    };


    npcs[2] =
    (NPC)
    {
        .position = { 500, 900 },
        .size = 30,
        .name = "Traveller",
        .dialogue = travellerDialogue,
        .dialogueLineCount = 4
    };


    // =========================
    // DIALOGUE SYSTEM
    // =========================

    DialogueState dialogueState =
        DIALOGUE_CLOSED;

    int currentDialogueLine =
        0;

    int activeNPC =
        -1;


    // =========================
    // CAMERA
    // =========================

    Camera2D camera =
    {
        0
    };


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

        if (
            IsKeyPressed(KEY_E)
        )
        {
            if (
                dialogueState ==
                DIALOGUE_CLOSED
            )
            {
                int nearbyNPC =
                    FindNearbyNPC(
                        player,
                        npcs,
                        MAX_NPCS
                    );


                if (
                    nearbyNPC != -1
                )
                {
                    activeNPC =
                        nearbyNPC;

                    currentDialogueLine =
                        0;

                    dialogueState =
                        DIALOGUE_ACTIVE;
                }
            }


            else if (
                dialogueState ==
                DIALOGUE_ACTIVE
            )
            {
                currentDialogueLine++;


                if (
                    currentDialogueLine >=
                    npcs[activeNPC].dialogueLineCount
                )
                {
                    dialogueState =
                        DIALOGUE_CLOSED;

                    currentDialogueLine =
                        0;

                    activeNPC =
                        -1;
                }
            }
        }


        // =========================
        // PLAYER MOVEMENT
        // =========================

        if (
            dialogueState ==
            DIALOGUE_CLOSED
        )
        {
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
                        npcs,
                        MAX_NPCS,
                        newX,
                        player.position.y
                    )
                )
                {
                    player.position.x =
                        newX;
                }
            }


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
                        npcs,
                        MAX_NPCS,
                        newX,
                        player.position.y
                    )
                )
                {
                    player.position.x =
                        newX;
                }
            }


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
                        npcs,
                        MAX_NPCS,
                        player.position.x,
                        newY
                    )
                )
                {
                    player.position.y =
                        newY;
                }
            }


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
                        npcs,
                        MAX_NPCS,
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

        BeginDrawing();

        ClearBackground(BLACK);


        BeginMode2D(camera);

        DrawMap();


        for (
            int i = 0;
            i < MAX_NPCS;
            i++
        )
        {
            DrawNPC(npcs[i]);
        }


        DrawPlayer(player);


        EndMode2D();


        if (
            dialogueState ==
            DIALOGUE_ACTIVE
        )
        {
            DrawDialogueBox(
                npcs[activeNPC],
                currentDialogueLine
            );
        }


        EndDrawing();
    }


    CloseWindow();

    return 0;
}