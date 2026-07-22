#ifndef MOVES_H
#define MOVES_H

#include "pokemon.h"

// =========================
// MOVE IDENTIFIERS
// =========================

typedef enum
{
    MOVE_SURF,
    MOVE_TAKE_DOWN,
    MOVE_HYPER_BEAM,
    MOVE_PROTECT,

    MOVE_FLAMETHROWER,
    MOVE_AIR_SLASH,
    MOVE_FLY,

    MOVE_SOLAR_BEAM,
    MOVE_GIGA_DRAIN,
    MOVE_SLUDGE_BOMB,
    MOVE_EARTH_POWER,

    TOTAL_MOVES

} MoveId;


// =========================
// MOVE STRUCTURE
// =========================

typedef struct
{
    char name[32];

    int power;

    PokemonType moveType;

    bool isStatus;   // true = does not deal damage (e.g. Protect)

} Move;


extern const Move moveTable[TOTAL_MOVES];

#endif