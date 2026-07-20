#ifndef WORLD_H
#define WORLD_H

#include "raylib.h"
#include <stdbool.h>

#define TILE_SIZE 40
#define MAP_WIDTH 40
#define MAP_HEIGHT 30

extern int map[MAP_HEIGHT][MAP_WIDTH];

void CreateMap(void);

bool IsTileWalkable(int tile);

void DrawMap(void);

#endif