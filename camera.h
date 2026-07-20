#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"
#include "player.h"

void InitializeCamera(
    Camera2D *camera,
    Player player,
    int screenWidth,
    int screenHeight
);

void UpdateGameCamera(
    Camera2D *camera,
    Player player
);

#endif