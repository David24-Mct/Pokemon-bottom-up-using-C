#include "player_data.h"

void CreatePlayer(Player *player)
{
    *player =
        (Player)
        {
            .position = { 760, 540 },
            .speed = 5.0f,
            .size = 30,
            .direction = DIRECTION_DOWN
        };
}