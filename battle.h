#ifndef BATTLE_H
#define BATTLE_H

#include "raylib.h"
#include "pokemon.h"

// Call once, right when the player enters GAME_BATTLE, to reset both
// teams to full health and start a fresh battle.
void InitBattle(Team *playerTeamPtr, Team *npcTeamPtr);

// Call every frame while gameState == GAME_BATTLE.
// Returns true the moment the battle has concluded (win or lose) and the
// final message has been dismissed -- main.c should switch back to
// GAME_OVERWORLD when this returns true.
bool UpdateBattle(void);

void DrawBattle(void);

#endif