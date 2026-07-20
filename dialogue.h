#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "npc.h"


// =========================
// DIALOGUE STATE
// =========================

typedef enum
{
    DIALOGUE_CLOSED,
    DIALOGUE_ACTIVE

} DialogueState;


// =========================
// DRAW DIALOGUE BOX
// =========================

void DrawDialogueBox(
    NPC npc,
    int currentLine
);

#endif