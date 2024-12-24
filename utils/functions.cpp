#include <cstdint>
#include <iostream>
#include "functions.h"
#include "utils.h"




struct GameSettings{
    uint8_t PlayerCount;
    uint16_t MaxHandSize;
    uint16_t MaxLibrarySize;
    uint16_t MaxGraveyardSize;
    uint16_t MaxExileZoneSize;
    uint16_t MaxBattlefieldSize;
    uint16_t MaxAttachments;

};

void SetGameSettings(struct GameSettings & gamesettings) {
    gamesettings.PlayerCount = ObtainUInt8("Input PlayerCount: ");
    gamesettings.MaxHandSize = ObtainUInt8("Input MaxHandSize: ");
    gamesettings.MaxLibrarySize = NULL;
    gamesettings.MaxGraveyardSize = ObtainUInt16("Input MaxGraveyardSize: ");
    gamesettings.MaxExileZoneSize = ObtainUInt16("Input MaxExileZoneSize: ");

    gamesettings.MaxBattlefieldSize = ObtainUInt16("Input MaxBattlefieldSize: ");
    gamesettings.MaxAttachments = ObtainUInt8("Input MaxAttachments: ");
}