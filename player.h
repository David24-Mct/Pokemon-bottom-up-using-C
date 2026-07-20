#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

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
// PLAYER FUNCTIONS
// =========================

void DrawPlayer(Player player);

#endif