#include "world.h"


#define MAP_WIDTH 40
#define MAP_HEIGHT 30

int map[MAP_HEIGHT][MAP_WIDTH];


void CreateMap(void)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            map[y][x] = 0;
        }
    }

    // Horizontal path
    for (int x = 0; x < MAP_WIDTH; x++)
    {
        map[15][x] = 1;
        map[16][x] = 1;
    }

    // Vertical path
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        map[y][19] = 1;
        map[y][20] = 1;
    }

    // Water lake
    for (int y = 5; y < 12; y++)
    {
        for (int x = 5; x < 13; x++)
        {
            map[y][x] = 2;
        }
    }

    // Second water area
    for (int y = 20; y < 26; y++)
    {
        for (int x = 28; x < 37; x++)
        {
            map[y][x] = 2;
        }
    }

    // Forest 1
    for (int y = 2; y < 6; y++)
    {
        for (int x = 25; x < 30; x++)
        {
            map[y][x] = 3;
        }
    }

    // Forest 2
    for (int y = 20; y < 25; y++)
    {
        for (int x = 5; x < 10; x++)
        {
            map[y][x] = 3;
        }
    }
}


// =========================
// CHECK TILE WALKABILITY
// =========================

bool IsTileWalkable(int tile)
{
    return tile == 0 || tile == 1;
}

void DrawMap(void)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            int tile = map[y][x];


            // Grass

            if (tile == 0)
            {
                DrawRectangle(
                    x * TILE_SIZE,
                    y * TILE_SIZE,
                    TILE_SIZE,
                    TILE_SIZE,
                    GREEN
                );
            }


            // Path

            else if (tile == 1)
            {
                DrawRectangle(
                    x * TILE_SIZE,
                    y * TILE_SIZE,
                    TILE_SIZE,
                    TILE_SIZE,
                    BEIGE
                );
            }


            // Water

            else if (tile == 2)
            {
                DrawRectangle(
                    x * TILE_SIZE,
                    y * TILE_SIZE,
                    TILE_SIZE,
                    TILE_SIZE,
                    BLUE
                );
            }


            // Tree

            else if (tile == 3)
            {
                DrawRectangle(
                    x * TILE_SIZE,
                    y * TILE_SIZE,
                    TILE_SIZE,
                    TILE_SIZE,
                    GREEN
                );

                DrawRectangle(
                    x * TILE_SIZE + 15,
                    y * TILE_SIZE + 20,
                    10,
                    20,
                    BROWN
                );

                DrawCircle(
                    x * TILE_SIZE + TILE_SIZE / 2,
                    y * TILE_SIZE + 18,
                    18,
                    DARKGREEN
                );
            }


            // Tile border

            DrawRectangleLines(
                x * TILE_SIZE,
                y * TILE_SIZE,
                TILE_SIZE,
                TILE_SIZE,
                DARKGREEN
            );
        }
    }
}

