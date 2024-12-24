#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cstdint>

// Define the GameSettings struct
struct GameSettings {
    uint8_t PlayerCount;
    uint16_t MaxHandSize;
    uint16_t MaxLibrarySize;
    uint16_t MaxGraveyardSize;
    uint16_t MaxExileZoneSize;
    uint16_t MaxBattlefieldSize;
    uint16_t MaxAttachments;
};

// Function declarations
void SetGameSettings(GameSettings &gamesettings);

#endif // FUNCTIONS_H
