#include "menu.h"
#include "game_state.h"
#include "raylib.h"


// =========================
// UPDATE MENU
// =========================

void UpdateMenu(
    GameState *gameState
)
{
    if (IsKeyPressed(KEY_ENTER))
    {
        *gameState =
            GAME_PLAYING;
    }
}


// =========================
// DRAW MENU
// =========================

void DrawMenu(void)
{
    ClearBackground(BLACK);

    DrawText(
        "MONSTER REALMS",
        GetScreenWidth() / 2 - 180,
        180,
        40,
        WHITE
    );

    DrawText(
        "PRESS ENTER TO START",
        GetScreenWidth() / 2 - 150,
        280,
        20,
        WHITE
    );
}