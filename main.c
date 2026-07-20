#include "raylib.h"
#include "player.h"
#include "npc.h"
#include "world.h"
#include "dialogue.h"
#include "game.h"
#include "camera.h"
#include "config.h"
#include "npc_data.h"
#include "player_data.h"
#include "game_state.h"
#include "pause.h"


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

  Player player;

CreatePlayer(&player);

    // =========================
    // NPCS
    // =========================

    NPC npcs[MAX_NPCS];


    CreateNPCs(npcs);


    // =========================
    // DIALOGUE SYSTEM
    // =========================

   GameState gameState =
    GAME_PLAYING;

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


InitializeCamera(
    &camera,
    player,
    SCREEN_WIDTH,
    SCREEN_HEIGHT
);

    // =========================
    // GAME LOOP
    // =========================

    while (
        !WindowShouldClose()
    )

    {


     UpdatePauseMenu
     (
    &gameState
);

        // =========================
        // DIALOGUE
        // =========================

        UpdateDialogue(
    &gameState,
    &activeNPC,
    &currentDialogueLine,
    player,
    npcs,
    MAX_NPCS
);

        // =========================
        // PLAYER MOVEMENT
        // =========================

        if (
            gameState ==
            GAME_PLAYING
        )
        {
            UpdatePlayerMovement(
                &player,
                npcs,
                MAX_NPCS
            );
        }


        // =========================
        // UPDATE CAMERA
        // =========================
           UpdateGameCamera(
               &camera,
               player
            );

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
            gameState ==
            GAME_DIALOGUE
        )
        {
            DrawDialogueBox(
                npcs[activeNPC],
                currentDialogueLine
            );
        }

        if (gameState == GAME_PAUSED)
{
    DrawPauseMenu();
}


        EndDrawing();
    }


    CloseWindow();


    return 0;
}