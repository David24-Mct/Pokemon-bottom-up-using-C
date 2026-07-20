#include "player.h"

// =========================
// DRAW PLAYER
// =========================

void DrawPlayer(Player player)
{
    Color playerColor;

    if (player.direction == DIRECTION_DOWN)
    {
        playerColor = BLUE;
    }
    else if (player.direction == DIRECTION_UP)
    {
        playerColor = RED;
    }
    else if (player.direction == DIRECTION_LEFT)
    {
        playerColor = GREEN;
    }
    else
    {
        playerColor = PURPLE;
    }

    // Player body

    DrawRectangle(
        (int)player.position.x,
        (int)player.position.y,
        player.size,
        player.size,
        playerColor
    );


    // Direction arrow

    if (player.direction == DIRECTION_DOWN)
    {
        DrawTriangle(
            (Vector2)
            {
                player.position.x + player.size / 2,
                player.position.y + player.size + 10
            },

            (Vector2)
            {
                player.position.x + 5,
                player.position.y + player.size
            },

            (Vector2)
            {
                player.position.x + player.size - 5,
                player.position.y + player.size
            },

            WHITE
        );
    }

    else if (player.direction == DIRECTION_UP)
    {
        DrawTriangle(
            (Vector2)
            {
                player.position.x + player.size / 2,
                player.position.y - 10
            },

            (Vector2)
            {
                player.position.x + 5,
                player.position.y
            },

            (Vector2)
            {
                player.position.x + player.size - 5,
                player.position.y
            },

            WHITE
        );
    }

    else if (player.direction == DIRECTION_LEFT)
    {
        DrawTriangle(
            (Vector2)
            {
                player.position.x - 10,
                player.position.y + player.size / 2
            },

            (Vector2)
            {
                player.position.x,
                player.position.y + 5
            },

            (Vector2)
            {
                player.position.x,
                player.position.y + player.size - 5
            },

            WHITE
        );
    }

    else if (player.direction == DIRECTION_RIGHT)
    {
        DrawTriangle(
            (Vector2)
            {
                player.position.x + player.size + 10,
                player.position.y + player.size / 2
            },

            (Vector2)
            {
                player.position.x + player.size,
                player.position.y + 5
            },

            (Vector2)
            {
                player.position.x + player.size,
                player.position.y + player.size - 5
            },

            WHITE
        );
    }
}