
#include "camera.h"


// =========================
// INITIALIZE CAMERA
// =========================

void InitializeCamera(
    Camera2D *camera,
    Player player,
    int screenWidth,
    int screenHeight
)
{
    camera->target =
        (Vector2)
        {
            player.position.x +
                player.size / 2,

            player.position.y +
                player.size / 2
        };


    camera->offset =
        (Vector2)
        {
            screenWidth / 2,
            screenHeight / 2
        };


    camera->rotation =
        0.0f;


    camera->zoom =
        1.0f;
}


// =========================
// UPDATE CAMERA
// =========================

void UpdateGameCamera(
    Camera2D *camera,
    Player player
)
{
    camera->target =
        (Vector2)
        {
            player.position.x +
                player.size / 2,

            player.position.y +
                player.size / 2
        };
}