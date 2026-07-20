#include "npc_data.h"


// =========================
// ELDER DIALOGUE
// =========================

const char *elderDialogue[] =
{
    "Welcome to our village!",
    "The forest ahead is dangerous.",
    "Many trainers have disappeared there.",
    "Be careful on your journey."
};


// =========================
// SCIENTIST DIALOGUE
// =========================

const char *scientistDialogue[] =
{
    "Ah! A new adventurer!",
    "I am studying the creatures of this world.",
    "There is still so much we do not know.",
    "Perhaps you can help me someday."
};


// =========================
// TRAVELLER DIALOGUE
// =========================

const char *travellerDialogue[] =
{
    "Hey there, traveller!",
    "The road ahead is long.",
    "You should explore every area you find.",
    "You never know what you might discover."
};


// =========================
// CREATE NPCS
// =========================

void CreateNPCs(
    NPC npcs[]
)
{
    npcs[0] =
        (NPC)
        {
            .position = { 820, 540 },
            .size = 30,
            .name = "Elder",
            .dialogue = elderDialogue,
            .dialogueLineCount = 4
        };


    npcs[1] =
        (NPC)
        {
            .position = { 1200, 600 },
            .size = 30,
            .name = "Scientist",
            .dialogue = scientistDialogue,
            .dialogueLineCount = 4
        };


    npcs[2] =
        (NPC)
        {
            .position = { 500, 900 },
            .size = 30,
            .name = "Traveller",
            .dialogue = travellerDialogue,
            .dialogueLineCount = 4
        };
}