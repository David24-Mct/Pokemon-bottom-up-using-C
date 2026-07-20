#include "npc.h"

void DrawNPC(NPC npc)
{
    // NPC body

    DrawRectangle(
        (int)npc.position.x,
        (int)npc.position.y,
        npc.size,
        npc.size,
        BLACK
    );


    // NPC head

    DrawCircle(
        (int)npc.position.x + npc.size / 2,
        (int)npc.position.y - 10,
        10,
        BEIGE
    );


    // NPC name

    DrawText(
        npc.name,
        (int)npc.position.x - 10,
        (int)npc.position.y - 35,
        16,
        WHITE
    );
}


int FindNearbyNPC(
    Player player,
    NPC npcs[],
    int npcCount
)
{
    Rectangle playerRect =
    {
        player.position.x,
        player.position.y,
        player.size,
        player.size
    };


    for (int i = 0; i < npcCount; i++)
    {
        Rectangle interactionArea =
        {
            npcs[i].position.x - 20,
            npcs[i].position.y - 20,
            npcs[i].size + 40,
            npcs[i].size + 40
        };


        if (
            CheckCollisionRecs(
                playerRect,
                interactionArea
            )
        )
        {
            return i;
        }
    }


    return -1;
}