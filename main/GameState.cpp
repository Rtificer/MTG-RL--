#include <cstdint>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <iostream>

// Include game settings structure and function
typedef struct GameSettings {
    uint8_t PlayerCount;
    uint16_t MaxHandSize;
    uint16_t MaxLibrarySize;
    uint16_t MaxGraveyardSize;
    uint16_t MaxExileZoneSize;
    uint16_t MaxBattlefieldSize;
    uint16_t MaxAttachments;
} GameSettings;

void SetGameSettings(GameSettings &gamesettings);

// Enum for game phases
enum class GamePhase : uint8_t {
    Setup = 0,
    MainPhase1,
    Combat,
    MainPhase2,
    EndPhase
};

// CardZone class manages collections of cards like the graveyard exilzone, hand, etc
class CardZone {
public:
    std::vector<uint16_t> Cards;

    void AddCard(uint16_t cardID) {
        Cards.push_back(cardID);
    }

    void RemoveCard(std::optional<uint16_t> cardID, std::optional<size_t> index) {
        //With std::optional the variable is a boolean (stating wether or not it contains data) and *variable is the actual data of the variable.
        if (index) {

            if (*index < Cards.size()) {

                Cards.erase(Cards.begin() + *index);

            } else {

                std::cout << "Index out of range.\n";

            }

        } else if (cardID) {
            //If it doesn't find any instances of cardID it returns Cards.end() which is the position after the current end of the vector.
            auto it = std::find(Cards.begin(), Cards.end(), *cardID);

            if (it != Cards.end()) {

                Cards.erase(it);

            } else {

                std::cout << "CardID not found.\n";
            }

        } else {

            std::cout << "No Index or cardID given for CardZone Removal.\n";

        }
    }
};

// CardState struct represents individual cards on the battlefield
struct CardState {
    uint16_t CardID;
    bool Tapped = false;
    bool SummoningSickness = true;
    uint8_t Counters = 0;
    uint8_t RemainingToughness = 0;
    uint8_t CurrentAttack = 0;
    std::vector<uint16_t> Attachments;

    CardState(uint16_t id) : CardID(id) {}
};

// Battlefield class manages cards on the battlefield
class Battlefield {
public:
    std::vector<CardState> Cards;

    void AddCard(const CardState& card) {
        Cards.push_back(card);
    }

    void RemoveCard(std::optional<uint16_t> cardID, std::optional<size_t> index) {
        //With std::optional the variable is a boolean (stating wether or not it contains data) and *variable is the actual data of the variable.
        if (index) {

            if (*index < Cards.size()) {
                Cards.erase(Cards.begin() + *index);

            } else {

                std::cout << "Index out of range.\n";

            }

        } else if (cardID) {
            auto it = std::remove_if(Cards.begin(), Cards.end(), [&](const CardState& card) { return card.CardID == *cardID; });

            if (it != Cards.end()) {
                Cards.erase(it, Cards.end());

            } else {
                std::cout << "CardID not found.\n";

            }

        } else {
            std::cout << "No Index or cardID given for Battlefield Removal.\n";

        }
    }
};

// PlayerPerspective manages the view of the game state for each player
class PlayerPerspective {
public:
    struct PerspectiveData {
        std::vector<uint16_t> DefaultProbabilityVector;
        std::vector<std::vector<uint16_t>> AdditionalVectors;
    };

    std::unordered_map<uint8_t, PerspectiveData> Data;

    PlayerPerspective(uint8_t playerID, uint16_t totalCardCount) {

        Data[playerID].DefaultProbabilityVector.resize(totalCardCount, 0);

    }
};

// Player class represents a player in the game
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

    Player(uint8_t id, uint16_t totalCardCount)
        : ID(id), Perspective(id, totalCardCount) {}
};

// GameState class tracks the overall state of the game
class GameState {
public:
    uint16_t TurnCount = 0;
    GamePhase CurrentPhase = GamePhase::Setup;
    std::vector<Player> Players;
    GameSettings Settings;

    void InitializeGameSettings() {
        SetGameSettings(Settings);
    }

    void AdvancePhase() {
        CurrentPhase = static_cast<GamePhase>((static_cast<uint8_t>(CurrentPhase) + 1) % 5);
    }

    void SetupGameState() {
        for (uint8_t i = 0; i < Settings.PlayerCount; ++i) {
            uint16_t totalCardCount = Settings.MaxLibrarySize;
            Players.emplace_back(i + 1, totalCardCount);
        }
    }
};

// Main function
int main() {
    GameState gameState;
    gameState.InitializeGameSettings();
    gameState.SetupGameState();

    for (const auto& player : gameState.Players) {
        std::cout << "Player ID: " << (int)player.ID << "\n";
    }

    return 0;
}