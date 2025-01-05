#include <string>
#include <cstdint>
#include <vector>

struct Card {
    const uint16_t ID;
    const std::string Name;
    const std::vector<uint8_t> base_types;
    const std::vector<uint8_t> base_colors;
    const std::vector<uint8_t> base_cost;
    const uint16_t power;
    const uint16_t toughness;
    const std::vector<uint16_t> AbilityIDs;
};