#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include <stdexcept>
#include "utils.h"

uint16_t ObtainUInt16(const std::string& Message) {
    uint16_t PositiveInt;

    while (true) {
        std::cout << Message;
        std::string input;
        std::cin >> input; // Read the input as a string

        try {
            // Attempt to convert the string to an unsigned long
            size_t pos;
            unsigned long value = std::stoul(input, &pos);

            // Check if the entire input was used in the conversion and if the value is within range
            if (pos != input.length() || value > std::numeric_limits<uint16_t>::max()) {
                throw std::out_of_range("Out of range");
            }

            PositiveInt = static_cast<uint16_t>(value);
            break;
        } catch (const std::exception&) {
            std::cout << "Invalid input. Please enter a valid positive integer within the range [0, " 
                      << std::numeric_limits<uint16_t>::max() << "].\n";
        }
    }

    return PositiveInt;
}

uint8_t ObtainUInt8(const std::string& Message) {
    uint8_t PositiveInt;

    while (true) {
        std::cout << Message;
        std::string input;
        std::cin >> input; // Read the input as a string

        try {
            // Attempt to convert the string to an unsigned long
            size_t pos;
            unsigned long value = std::stoul(input, &pos);

            // Check if the entire input was used in the conversion and if the value is within range
            if (pos != input.length() || value > std::numeric_limits<uint8_t>::max()) {
                throw std::out_of_range("Out of range");
            }

            PositiveInt = static_cast<uint8_t>(value);
            break;
        } catch (const std::exception&) {
            std::cout << "Invalid input. Please enter a valid positive integer within the range [0, " 
                      << std::numeric_limits<uint8_t>::max() << "].\n";
        }
    }

    return PositiveInt;
}