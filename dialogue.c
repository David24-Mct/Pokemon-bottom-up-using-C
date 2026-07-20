#include "dialogue.h"
#include "npc.h"


void DrawDialogueBox(
    NPC npc,
    int currentLine
)
{
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
        npc.name,
        75,
        455,
        20,
        YELLOW
    );


    DrawText(
        npc.dialogue[currentLine],
        75,
        490,
        24,
        WHITE
    );


    if (
        currentLine <
        npc.dialogueLineCount - 1
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
