#include <string.h>

#include "pokemon.h"
#include "moves.h"

// =========================
// SPECIES FACTORIES
// =========================
// Stats are calculated with the real level-50 stat formula using each
// species' actual base stats:
//
//   stat = floor(2 * base * level / 100) + 5
//   HP   = floor(2 * base * level / 100) + level + 10
//
// This keeps the numbers "game accurate" even though we skip IVs/EVs.

static Pokemon CreateVenusaur(void)
{
    Pokemon p = { 0 };

    strcpy(p.name, "Venusaur");

    p.level  = 50;
    p.maxHp  = 140;
    p.hp     = p.maxHp;
    p.attack = 105;
    p.defense = 105;
    p.speed  = 85;

    p.pokeType = TYPE_GRASS;

    p.moveIds[0] = MOVE_SOLAR_BEAM;
    p.moveIds[1] = MOVE_GIGA_DRAIN;
    p.moveIds[2] = MOVE_SLUDGE_BOMB;
    p.moveIds[3] = MOVE_EARTH_POWER;

    p.spriteColor = GREEN;
    p.fainted = false;

    return p;
}

static Pokemon CreateCharizard(void)
{
    Pokemon p = { 0 };

    strcpy(p.name, "Charizard");

    p.level  = 50;
    p.maxHp  = 138;
    p.hp     = p.maxHp;
    p.attack = 114;
    p.defense = 90;
    p.speed  = 105;

    p.pokeType = TYPE_FIRE;

    p.moveIds[0] = MOVE_FLAMETHROWER;
    p.moveIds[1] = MOVE_AIR_SLASH;
    p.moveIds[2] = MOVE_FLY;
    p.moveIds[3] = MOVE_SOLAR_BEAM;

    p.spriteColor = RED;
    p.fainted = false;

    return p;
}

static Pokemon CreateBlastoise(void)
{
    Pokemon p = { 0 };

    strcpy(p.name, "Blastoise");

    p.level  = 50;
    p.maxHp  = 139;
    p.hp     = p.maxHp;
    p.attack = 90;
    p.defense = 110;
    p.speed  = 83;

    p.pokeType = TYPE_WATER;

    p.moveIds[0] = MOVE_SURF;
    p.moveIds[1] = MOVE_TAKE_DOWN;
    p.moveIds[2] = MOVE_HYPER_BEAM;
    p.moveIds[3] = MOVE_PROTECT;

    p.spriteColor = BLUE;
    p.fainted = false;

    return p;
}


// =========================
// TEAM FACTORIES
// =========================
// Both trainers run the identical roster and move sets.

Team CreatePlayerTeam(void)
{
    Team t;

    t.pokemon[0] = CreateVenusaur();
    t.pokemon[1] = CreateCharizard();
    t.pokemon[2] = CreateBlastoise();

    t.activeIndex = 0;

    return t;
}

Team CreateNPCTeam(void)
{
    return CreatePlayerTeam();
}