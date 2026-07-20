
#include "game_state.h"

#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "npc.h"

typedef enum
{
    DIALOGUE_CLOSED,
    DIALOGUE_ACTIVE

} DialogueState;


void DrawDialogueBox(
    NPC npc,
    int currentLine
);


void UpdateDialogue(
    GameState *gameState,
    int *activeNPC,
    int *currentDialogueLine,
    Player player,
    NPC npcs[],
    int npcCount
);

#endif