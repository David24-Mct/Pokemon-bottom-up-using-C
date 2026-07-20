#ifndef GAME_H
#define GAME_H


#include "player.h"
#include "npc.h"

void UpdatePlayerMovement(
    Player *player,
    NPC npcs[],
    int npcCount
);

bool CanMoveTo(
    Player player,
    NPC npcs[],
    int npcCount,
    float newX,
    float newY
);

#endif