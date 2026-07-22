#include "moves.h"

// =========================
// MOVE TABLE
// =========================
// Real base power values from the games.
// Type effectiveness is intentionally not applied in damage calculation
// (see battle.c) to keep the combat math simple and readable.

const Move moveTable[TOTAL_MOVES] =
{
    [MOVE_SURF]         = { "Surf",         90,  TYPE_WATER,  false },
    [MOVE_TAKE_DOWN]    = { "Take Down",    90,  TYPE_NORMAL, false },
    [MOVE_HYPER_BEAM]   = { "Hyper Beam",   150, TYPE_NORMAL, false },
    [MOVE_PROTECT]      = { "Protect",      0,   TYPE_NORMAL, true  },

    [MOVE_FLAMETHROWER] = { "Flamethrower", 90,  TYPE_FIRE,   false },
    [MOVE_AIR_SLASH]    = { "Air Slash",    75,  TYPE_FLYING, false },
    [MOVE_FLY]          = { "Fly",          90,  TYPE_FLYING, false },

    [MOVE_SOLAR_BEAM]   = { "Solar Beam",   120, TYPE_GRASS,  false },
    [MOVE_GIGA_DRAIN]   = { "Giga Drain",   75,  TYPE_GRASS,  false },
    [MOVE_SLUDGE_BOMB]  = { "Sludge Bomb",  90,  TYPE_POISON, false },
    [MOVE_EARTH_POWER]  = { "Earth Power",  90,  TYPE_GROUND, false },
};