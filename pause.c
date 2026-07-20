#include "pause.h"
#include "raylib.h"


// =========================
// UPDATE PAUSE MENU
// =========================

void UpdatePauseMenu(
    GameState *gameState
)
{
    if (IsKeyPressed(KEY_P))
    {
        if (*gameState == GAME_PLAYING)
        {
            *gameState = GAME_PAUSED;
        }
        else if (*gameState == GAME_PAUSED)
        {
            *gameState = GAME_PLAYING;
        }
    }
}


// =========================
// DRAW PAUSE MENU
// =========================

void DrawPauseMenu(void)
{
    DrawRectangle(
        0,
        0,
        GetScreenWidth(),
        GetScreenHeight(),
        Fade(BLACK, 0.6f)
    );

    DrawText(
        "GAME PAUSED",
        GetScreenWidth() / 2 - 120,
        200,
        40,
        WHITE
    );

    DrawText(
        "Press P to resume",
        GetScreenWidth() / 2 - 130,
        270,
        20,
        WHITE
    );
}