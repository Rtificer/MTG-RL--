#include <cstdint>
#include <vector>
#include <iostream>
#include <algorithm>


class AbilityManager {
public:
    std::vector<uint16_t> ActiveStaticAbilities;

    void AddAbility(uint16_t AbilityID) {
        ActiveStaticAbilities.push_back(AbilityID);
    }

    void RemoveAbility(std::optional<uint16_t> AbilityID, std::optional<size_t> index) {
        //With std::optional the variable is a boolean (stating wether or not it contains data) and *variable is the actual data of the variable.
        if (AbilityID) {

            if (*index < ActiveStaticAbilities.size()) {

                ActiveStaticAbilities.erase(ActiveStaticAbilities.begin() + *index);

            } else {

                std::cout << "Index out of range.\n";

            }

        } else if (AbilityID) {
            //If it doesn't find any instances of AbilityID it returns ActiveStaticAbilities.end() which is the position after the current end of the vector.
            auto it = std::find(ActiveStaticAbilities.begin(), ActiveStaticAbilities.end(), *AbilityID);

            if (it != ActiveStaticAbilities.end()) {

                ActiveStaticAbilities.erase(it);

            } else {

                std::cout << "AbilityID not found.\n";
            }

        } else {

            std::cout << "No Index or AbilityID given for removal from ActiveStaticAbilities.\n";

        }
    }
};
