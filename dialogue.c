#include "dialogue.h"
#include "game_state.h"
#include "raylib.h"


// =========================
// DRAW DIALOGUE BOX
// =========================

void DrawDialogueBox(
    NPC npc,
    int currentLine
)
{
    DrawRectangle(
        50,
        450,
        700,
        120,
        BLACK
    );

    DrawRectangleLines(
        50,
        450,
        700,
        120,
        WHITE
    );

    DrawText(
        npc.name,
        70,
        465,
        20,
        YELLOW
    );

    DrawText(
        npc.dialogue[currentLine],
        70,
        500,
        20,
        WHITE
    );

    DrawText(
        "Press E to continue",
        520,
        540,
        16,
        GRAY
    );
}


// =========================
// UPDATE DIALOGUE
// =========================

void UpdateDialogue(
    GameState *gameState,
    int *activeNPC,
    int *currentDialogueLine,
    Player player,
    NPC npcs[],
    int npcCount
)
{
    if (!IsKeyPressed(KEY_E))
    {
        return;
    }


    // =========================
    // START DIALOGUE
    // =========================

    if (
        *gameState ==
        GAME_PLAYING
    )
    {
        int nearbyNPC =
            FindNearbyNPC(
                player,
                npcs,
                npcCount
            );


        if (
            nearbyNPC != -1
        )
        {
            *activeNPC =
                nearbyNPC;

            *currentDialogueLine =
                0;

            *gameState =
                GAME_DIALOGUE;
        }
    }


    // =========================
    // ADVANCE DIALOGUE
    // =========================

    else if (
        *gameState ==
        GAME_DIALOGUE
    )
    {
        (*currentDialogueLine)++;


        if (
            *currentDialogueLine >=
            npcs[*activeNPC].dialogueLineCount
        )
        {
            *gameState =
                GAME_PLAYING;

            *currentDialogueLine =
                0;

            *activeNPC =
                -1;
        }
    }
}