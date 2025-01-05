// GameState.h
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <string>
#include <optional>

// GameSettings struct
struct GameSettings {
    uint8_t PlayerCount;
    uint16_t MaxHandSize;
    uint16_t MaxLibrarySize;
    uint16_t MaxGraveyardSize;
    uint16_t MaxExileZoneSize;
    uint16_t MaxBattlefieldSize;
    uint16_t MaxAttachments;
};

// Enum for game phases
enum class GamePhase : uint8_t {
    Setup = 0,
    MainPhase1,
    Combat,
    MainPhase2,
    EndPhase
};

// CardState struct
struct CardState {
    uint16_t CardID;
    bool Tapped = false;
    bool SummoningSickness = true;
    uint8_t Counters = 0;
    uint8_t RemainingToughness = 0;
    uint8_t CurrentAttack = 0;
    std::vector<uint16_t> Attachments;

    explicit CardState(uint16_t id) : CardID(id) {}
};

// CardZone class
class CardZone {
public:
    std::vector<uint16_t> Cards;

    void AddCard(uint16_t cardID);
    void RemoveCard(std::optional<uint16_t> cardID = std::nullopt, std::optional<size_t> index = std::nullopt);
};

// Battlefield class
class Battlefield {
public:
    std::vector<CardState> Cards;

    void AddCard(const CardState& card);
    void RemoveCard(std::optional<uint16_t> cardID = std::nullopt, std::optional<size_t> index = std::nullopt);
};

// PlayerPerspective class
class PlayerPerspective {
public:
    struct PerspectiveData {
        std::vector<uint16_t> DefaultProbabilityVector;
        std::vector<std::vector<uint16_t>> AdditionalVectors;
    };

    std::unordered_map<uint8_t, PerspectiveData> Data;

    PlayerPerspective(uint8_t playerID, uint16_t totalCardCount);
};

// Player class
class Player {
public:
    uint8_t ID;
    uint8_t Life = 20;
    uint16_t ManaPool[6] = {0}; // White, Blue, Black, Red, Green, Colorless
    CardZone Hand;
    CardZone Library;
    CardZone Graveyard;
    CardZone ExileZone;
    Battlefield BattlefieldCards;
    PlayerPerspective Perspective;

    Player(uint8_t id, uint16_t totalCardCount);
};

// GameState class
class GameState {
public:
    uint16_t TurnCount = 0;
    GamePhase CurrentPhase = GamePhase::Setup;
    std::vector<Player> Players;
    GameSettings Settings;

    void InitializeGameSettings();
    void AdvancePhase();
    void SetupGameState();
};

#endif
