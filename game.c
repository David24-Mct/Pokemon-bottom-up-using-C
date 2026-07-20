#include "game.h"
#include "world.h"


// =========================
// CHECK PLAYER MOVEMENT
// =========================

bool CanMoveTo(
    Player player,
    NPC npcs[],
    int npcCount,
    float newX,
    float newY
)
{
    int leftTile =
        (int)newX / TILE_SIZE;

    int rightTile =
        (int)(newX + player.size - 1) / TILE_SIZE;

    int topTile =
        (int)newY / TILE_SIZE;

    int bottomTile =
        (int)(newY + player.size - 1) / TILE_SIZE;


    // World boundaries

    if (
        leftTile < 0 ||
        rightTile >= MAP_WIDTH ||
        topTile < 0 ||
        bottomTile >= MAP_HEIGHT
    )
    {
        return false;
    }


    // Tile collision

    if (!IsTileWalkable(map[topTile][leftTile]))
        return false;

    if (!IsTileWalkable(map[topTile][rightTile]))
        return false;

    if (!IsTileWalkable(map[bottomTile][leftTile]))
        return false;

    if (!IsTileWalkable(map[bottomTile][rightTile]))
        return false;


    // Player rectangle

    Rectangle playerRect =
    {
        newX,
        newY,
        player.size,
        player.size
    };


    // NPC collision

    for (int i = 0; i < npcCount; i++)
    {
        Rectangle npcRect =
        {
            npcs[i].position.x,
            npcs[i].position.y,
            npcs[i].size,
            npcs[i].size
        };


        if (
            CheckCollisionRecs(
                playerRect,
                npcRect
            )
        )
        {
            return false;
        }
    }


    return true;
}


// =========================
// PLAYER MOVEMENT
// =========================

void UpdatePlayerMovement(
    Player *player,
    NPC npcs[],
    int npcCount
)
{
    if (IsKeyDown(KEY_RIGHT))
    {
        player->direction =
            DIRECTION_RIGHT;

        float newX =
            player->position.x +
            player->speed;


        if (
            CanMoveTo(
                *player,
                npcs,
                npcCount,
                newX,
                player->position.y
            )
        )
        {
            player->position.x =
                newX;
        }
    }


    else if (IsKeyDown(KEY_LEFT))
    {
        player->direction =
            DIRECTION_LEFT;

        float newX =
            player->position.x -
            player->speed;


        if (
            CanMoveTo(
                *player,
                npcs,
                npcCount,
                newX,
                player->position.y
            )
        )
        {
            player->position.x =
                newX;
        }
    }


    else if (IsKeyDown(KEY_UP))
    {
        player->direction =
            DIRECTION_UP;

        float newY =
            player->position.y -
            player->speed;


        if (
            CanMoveTo(
                *player,
                npcs,
                npcCount,
                player->position.x,
                newY
            )
        )
        {
            player->position.y =
                newY;
        }
    }


    else if (IsKeyDown(KEY_DOWN))
    {
        player->direction =
            DIRECTION_DOWN;

        float newY =
            player->position.y +
            player->speed;


        if (
            CanMoveTo(
                *player,
                npcs,
                npcCount,
                player->position.x,
                newY
            )
        )
        {
            player->position.y =
                newY;
        }
    }
}