#ifndef POKEMON_H
#define POKEMON_H

#include "raylib.h"

// =========================
// POKEMON TYPE
// =========================

typedef enum
{
    TYPE_NORMAL,
    TYPE_FIRE,
    TYPE_WATER,
    TYPE_GRASS,
    TYPE_FLYING,
    TYPE_POISON,
    TYPE_GROUND

} PokemonType;


// =========================
// POKEMON STRUCTURE
// =========================

typedef struct
{
    char name[32];

    int level;

    int hp;
    int maxHp;

    int attack;
    int defense;
    int speed;

    PokemonType pokeType;

    int moveIds[4];

    Color spriteColor;

    bool fainted;

} Pokemon;


// =========================
// TEAM STRUCTURE
// =========================

typedef struct
{
    Pokemon pokemon[3];

    int activeIndex;

} Team;


Team CreatePlayerTeam(void);
Team CreateNPCTeam(void);

#endif