#ifndef NPC_H
#define NPC_H

#include "raylib.h"
#include "player.h"

typedef struct
{
    Vector2 position;

    int size;

    const char *name;

    const char **dialogue;

    int dialogueLineCount;

} NPC;

void DrawNPC(NPC npc);

int FindNearbyNPC(
    Player player,
    NPC npcs[],
    int npcCount
);

#endif