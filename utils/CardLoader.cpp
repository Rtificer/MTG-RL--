#include <unordered_map>
#include <string>
#include <cstdint>
#include <regex>
#include <nlohmann/json.hpp>
#include <vector>
#include <fstream>
#include <iostream>

static const std::unordered_map<std::string, uint8_t> TypeToValue = {

    {"Land", 0}, {"Creature", 1}, {"Artifact", 2}, {"Enchant", 3}, {"Planeswalker", 4}, {"Battle", 5}, {"Instant", 6}, {"Sorcery", 7}, {"Kindred", 8}

};

static const std::unordered_map<std::string, uint16_t> SubtypeToValue = {
    // Artifact Subtypes
    {"Attraction", 0}, {"Blood", 1}, {"Bobblehead", 2}, {"Clue", 3}, {"Contraption", 4}, {"Equipment", 5}, 
    {"Food", 6}, {"Fortification", 7}, {"Gold", 8}, {"Incubator", 9}, {"Junk", 10}, {"Map", 11}, 
    {"Powerstone", 12}, {"Treasure", 13}, {"Vehicle", 14},

    // Battle Subtype
    {"Siege", 15},

    // Enchantment Subtypes
    {"Aura", 16}, {"Background", 17}, {"Cartouche", 18}, {"Case", 19}, {"Class", 20}, {"Curse", 21}, 
    {"Role", 22}, {"Room", 23}, {"Rune", 24}, {"Saga", 25}, {"Shard", 26}, {"Shrine", 27},

    // Land Subtypes
    {"Cave", 28}, {"Desert", 29}, {"Forest", 30}, {"Gate", 31}, {"Island", 32}, {"Lair", 33}, 
    {"Locus", 34}, {"Mine", 35}, {"Mountain", 36}, {"Plains", 37}, {"Power-Plant", 38}, {"Sphere", 39}, 
    {"Swamp", 40}, {"Tower", 41}, {"Urza’s", 42},

    // Planeswalker Subtypes
    {"Ajani", 43}, {"Aminatou", 44}, {"Angrath", 45}, {"Arlinn", 46}, {"Ashiok", 47}, {"Bahamut", 48}, 
    {"Basri", 49}, {"Bolas", 50}, {"Calix", 51}, {"Chandra", 52}, {"Comet", 53}, {"Dack", 54}, 
    {"Dakkon", 55}, {"Daretti", 56}, {"Davriel", 57}, {"Dihada", 58}, {"Domri", 59}, {"Dovin", 60}, 
    {"Ellywick", 61}, {"Elminster", 62}, {"Elspeth", 63}, {"Estrid", 64}, {"Freyalise", 65}, {"Garruk", 66}, 
    {"Gideon", 67}, {"Grist", 68}, {"Guff", 69}, {"Huatli", 70}, {"Jace", 71}, {"Jared", 72}, {"Jaya", 73}, 
    {"Jeska", 74}, {"Kaito", 75}, {"Karn", 76}, {"Kasmina", 77}, {"Kaya", 78}, {"Kiora", 79}, {"Koth", 80}, 
    {"Liliana", 81}, {"Lolth", 82}, {"Lukka", 83}, {"Minsc", 84}, {"Mordenkainen", 85}, {"Nahiri", 86}, 
    {"Narset", 87}, {"Niko", 88}, {"Nissa", 89}, {"Nixilis", 90}, {"Oko", 91}, {"Ral", 92}, {"Rowan", 93}, 
    {"Saheeli", 94}, {"Samut", 95}, {"Sarkhan", 96}, {"Serra", 97}, {"Sivitri", 98}, {"Sorin", 99}, {"Szat", 100}, 
    {"Tamiyo", 101}, {"Tasha", 102}, {"Teferi", 103}, {"Teyo", 104}, {"Tezzeret", 105}, {"Tibalt", 106}, 
    {"Tyvar", 107}, {"Ugin", 108}, {"Urza", 109}, {"Venser", 110}, {"Vivien", 111}, {"Vraska", 112}, 
    {"Vronos", 113}, {"Will", 114}, {"Windgrace", 115}, {"Wrenn", 116}, {"Xenagos", 117}, {"Yanggu", 118}, 
    {"Yanling", 119}, {"Zariel", 120},

    // Spell Subtypes (Instants/Sorceries)
    {"Adventure", 121}, {"Arcane", 122}, {"Lesson", 123}, {"Trap", 124},

    // Creature Subtypes
    {"Advisor", 125}, {"Aetherborn", 126}, {"Alien", 127}, {"Ally", 128}, {"Angel", 129}, {"Antelope", 130}, 
    {"Ape", 131}, {"Archer", 132}, {"Archon", 133}, {"Armadillo", 134}, {"Army", 135}, {"Artificer", 136}, 
    {"Assassin", 137}, {"Assembly-Worker", 138}, {"Astartes", 139}, {"Atog", 140}, {"Aurochs", 141}, {"Avatar", 142}, 
    {"Azra", 143}, {"Badger", 144}, {"Balloon", 145}, {"Barbarian", 146}, {"Bard", 147}, {"Basilisk", 148}, 
    {"Bat", 149}, {"Bear", 150}, {"Beast", 151}, {"Beaver", 152}, {"Beeble", 153}, {"Beholder", 154}, {"Berserker", 155}, 
    {"Bird", 156}, {"Blinkmoth", 157}, {"Boar", 158}, {"Bringer", 159}, {"Brushwagg", 160}, {"Camarid", 161}, 
    {"Camel", 162}, {"Capybara", 163}, {"Caribou", 164}, {"Carrier", 165}, {"Cat", 166}, {"Centaur", 167}, {"Child", 168}, 
    {"Chimera", 169}, {"Citizen", 170}, {"Cleric", 171}, {"Clown", 172}, {"Cockatrice", 173}, {"Construct", 174}, 
    {"Coward", 175}, {"Coyote", 176}, {"Crab", 177}, {"Crocodile", 178}, {"C’tan", 179}, {"Custodes", 180}, 
    {"Cyberman", 181}, {"Cyclops", 182}, {"Dalek", 183}, {"Dauthi", 184}, {"Demigod", 185}, {"Demon", 186}, 
    {"Deserter", 187}, {"Detective", 188}, {"Devil", 189}, {"Dinosaur", 190}, {"Djinn", 191}, {"Doctor", 192}, 
    {"Dog", 193}, {"Dragon", 194}, {"Drake", 195}, {"Dreadnought", 196}, {"Drone", 197}, {"Druid", 198}, 
    {"Dryad", 199}, {"Dwarf", 200}, {"Efreet", 201}, {"Egg", 202}, {"Elder", 203}, {"Eldrazi", 204}, 
    {"Elemental", 205}, {"Elephant", 206}, {"Elf", 207}, {"Elk", 208}, {"Employee", 209}, {"Eye", 210}, 
    {"Faerie", 211}, {"Ferret", 212}, {"Fish", 213}, {"Flagbearer", 214}, {"Fox", 215}, {"Fractal", 216}, 
    {"Frog", 217}, {"Fungus", 218}, {"Gamer", 219}, {"Gargoyle", 220}, {"Germ", 221}, {"Giant", 222}, 
    {"Gith", 223}, {"Glimmer", 224}, {"Gnoll", 225}, {"Gnome", 226}, {"Goat", 227}, {"Goblin", 228}, {"God", 229}, 
    {"Golem", 230}, {"Gorgon", 231}, {"Graveborn", 232}, {"Gremlin", 233}, {"Griffin", 234}, {"Guest", 235}, 
    {"Hag", 236}, {"Halfling", 237}, {"Hamster", 238}, {"Harpy", 239}, {"Hellion", 240}, {"Hippo", 241}, 
    {"Hippogriff", 242}, {"Homarid", 243}, {"Homunculus", 244}, {"Horror", 245}, {"Horse", 246}, {"Human", 247}, 
    {"Hydra", 248}, {"Hyena", 249}, {"Illusion", 250}, {"Imp", 251}, {"Incarnation", 252}, {"Inkling", 253}, 
    {"Inquisitor", 254}, {"Insect", 255}, {"Jackal", 256}, {"Jellyfish", 257}, {"Juggernaut", 258}, {"Kavu", 259}, 
    {"Kirin", 260}, {"Kithkin", 261}, {"Knight", 262}, {"Kobold", 263}, {"Kor", 264}, {"Kraken", 265}, {"Llama", 266},
    {"Lammasu", 267}, {"Lancer", 268}, {"Leech", 269}, {"Leviathan", 270}, {"Lhurgoyf", 271}, 
    {"Licid", 272}, {"Lizard", 273}, {"Manticore", 274}, {"Masticore", 275}, {"Mercenary", 276}, 
    {"Merfolk", 277}, {"Metathran", 278}, {"Minion", 279}, {"Minotaur", 280}, {"Mole", 281}, 
    {"Monger", 282}, {"Mongoose", 283}, {"Monk", 284}, {"Monkey", 285}, {"Moonfolk", 286}, 
    {"Mouse", 287}, {"Mutant", 288}, {"Myr", 289}, {"Mystic", 290}, {"Naga", 291}, {"Nautilus", 292}, 
    {"Necron", 293}, {"Nightmare", 294}, {"Nightstalker", 295}, {"Ninja", 296}, {"Noble", 297}, 
    {"Noggle", 298}, {"Nomad", 299}, {"Nymph", 300}, {"Octopus", 301}, {"Ogre", 302}, {"Ooze", 303}, 
    {"Orb", 304}, {"Orc", 305}, {"Orgg", 306}, {"Otter", 307}, {"Ouphe", 308}, {"Ox", 309}, {"Oyster", 310}, 
    {"Pandaren", 311}, {"Paratrooper", 312}, {"Pegasus", 313}, {"Penguin", 314}, {"Pentavite", 315}, 
    {"Pest", 316}, {"Phelddagrif", 317}, {"Phoenix", 318}, {"Phyrexian", 319}, {"Pilot", 320}, 
    {"Pincher", 321}, {"Pirate", 322}, {"Plant", 323}, {"Praetor", 324}, {"Processor", 325}, 
    {"Rabbit", 326}, {"Raccoon", 327}, {"Ranger", 328}, {"Rat", 329}, {"Rebel", 330}, {"Reflection", 331}, 
    {"Rhino", 332}, {"Rigger", 333}, {"Rogue", 334}, {"Salamander", 335}, {"Samurai", 336}, {"Saproling", 337}, 
    {"Satyr", 338}, {"Scarecrow", 339}, {"Scientist", 340}, {"Scion", 341}, {"Scorpion", 342}, 
    {"Scout", 343}, {"Sculpture", 344}, {"Serf", 345}, {"Serpent", 346}, {"Servo", 347}, {"Shade", 348}, 
    {"Shaman", 349}, {"Shapeshifter", 350}, {"Shark", 351}, {"Sheep", 352}, {"Siren", 353}, {"Skeleton", 354}, 
    {"Slith", 355}, {"Sliver", 356}, {"Slug", 357}, {"Snake", 358}, {"Soldier", 359}, {"Soltari", 360}, 
    {"Spawn", 361}, {"Specter", 362}, {"Spellshaper", 363}, {"Sphinx", 364}, {"Spider", 365}, {"Spike", 366}, 
    {"Spirit", 367}, {"Splinter", 368}, {"Sponge", 369}, {"Squid", 370}, {"Squirrel", 371}, {"Starfish", 372}, 
    {"Surrakar", 373}, {"Survivor", 374}, {"Tentacle", 375}, {"Tetravite", 376}, {"Thalakos", 377}, 
    {"Thopter", 378}, {"Thrull", 379}, {"Tief", 380}, {"Tiger", 381}, {"Titan", 382}, {"Tortoise", 383}, 
    {"Totem", 384}, {"Trader", 385}, {"Treefolk", 386}, {"Trilobite", 387}, {"Troll", 388}, {"Turtle", 389}, 
    {"Tyranid", 390}, {"Unicorn", 391}, {"Vampire", 392}, {"Vedalken", 393}, {"Viashino", 394}, {"Villain", 395}, 
    {"Volver", 396}, {"Wall", 397}, {"Warlock", 398}, {"Warrior", 399}, {"Weird", 400}, {"Werewolf", 401}, 
    {"Whale", 402}, {"Wizard", 403}, {"Wolf", 404}, {"Wolverine", 405}, {"Wombat", 406}, {"Wraith", 407}, 
    {"Wurm", 408}, {"Yeti", 409}, {"Zombie", 410}, {"Zubera", 411}
};

static const std::unordered_map<std::string, uint8_t> SuperTypeToValue = {

    {"Basic", 0}, {"Legendary", 1}, {"Snow", 2}, {"World", 3}
    
};

static const std::unordered_map<std::string, uint8_t> ColorToValue = {

    {"White", 0}, {"Blue", 1}, {"Black", 2}, {"Red", 3}, {"Green", 4}, {"Colorless", 5},
    {"white", 0}, {"blue", 1}, {"black", 2}, {"red", 3}, {"green", 4}, {"colorless", 5},
    {"W", 0}, {"B", 1}, {"B", 2}, {"R", 3}, {"G", 4}, {"C", 5},

};

static const std::unordered_map<std::string, uint8_t> ManaSymbolToValue = {

    {"W", 0}, {"U", 1}, {"B", 2}, {"R", 3}, {"G", 4},

    {"C", 5},

    {"W/U", 6}, {"W/B", 7}, {"W/R", 8}, {"W/G", 9}, {"W/C", 10}, {"W/2", 11},
    {"U/W", 6}, {"U/B", 12}, {"U/R", 13}, {"U/G", 14}, {"U/C", 15}, {"U/2", 16},
    {"B/W", 7}, {"B/U", 12}, {"B/R", 17}, {"B/G", 18}, {"B/C", 19}, {"B/2", 20},
    {"R/W", 8}, {"R/U", 13}, {"R/B", 17}, {"R/G", 21}, {"R/C", 22}, {"R/2", 23},
    {"G/W", 9}, {"G/U", 14}, {"G/B", 18}, {"G/R", 21}, {"G/C", 24}, {"G/2", 25},
    {"C/W", 10}, {"C/U", 15}, {"C/B", 19}, {"C/R", 22}, {"C/G", 24}, {"C/2", 26},
    {"2/W", 11}, {"2/U", 16}, {"2/B", 20}, {"2/R", 23}, {"2/G", 25}, {"2/C", 26},

    {"W/P", 27}, {"U/P", 28}, {"B/P", 29}, {"R/P", 30}, {"G/P", 31},
    {"C/P", 32},

    {"W/U/P", 33}, {"W/B/P", 34}, {"W/R/P", 35}, {"W/G/P", 36}, {"W/C/P", 37}, {"W/2/P", 38},
    {"U/W/P", 33}, {"U/B/P", 39}, {"U/R/P", 40}, {"U/G/P", 41}, {"U/C/P", 42}, {"U/2/P", 43},
    {"B/W/P", 34}, {"B/U/P", 39}, {"B/R/P", 44}, {"B/G/P", 45}, {"B/C/P", 46}, {"B/2/P", 47},
    {"R/W/P", 35}, {"R/U/P", 40}, {"R/B/P", 44}, {"R/G/P", 48}, {"R/C/P", 49}, {"R/2/P", 50},
    {"G/W/P", 36}, {"G/U/P", 41}, {"G/B/P", 45}, {"G/R/P", 48}, {"G/C/P", 51}, {"G/2/P", 52},
    {"C/W/P", 37}, {"C/U/P", 42}, {"C/B/P", 46}, {"C/R/P", 49}, {"C/G/P", 51}, {"C/2/P", 53},
    {"2/W/P", 38}, {"2/U/P", 43}, {"2/B/P", 47}, {"2/R/P", 50}, {"2/G/P", 52}, {"2/C/P", 53},

    {"S", 54},

    {"0", 55}, {"1", 56}, {"2", 57}, {"3", 58}, {"4", 59}, {"5", 60}, {"6", 61}, {"7", 62}, {"8", 63}, {"9", 64}, {"10", 65}, 
    {"11", 66}, {"12", 67}, {"13", 68}, {"14", 69}, {"15", 70}, {"16", 71}, {"17", 72}, {"18", 73}, {"19", 74}, {"20", 75}, 
    {"21", 76}, {"22", 77}, {"23", 78}, {"24", 79}, {"25", 80}, {"26", 81}, {"27", 82}, {"28", 83}, {"29", 84}, {"30", 85}, 
    {"31", 86}, {"32", 87}, {"33", 88}, {"34", 89}, {"35", 90}, {"36", 91}, {"37", 92}, {"38", 93}, {"39", 94}, {"40", 95}, 
    {"41", 96}, {"42", 97}, {"43", 98}, {"44", 99}, {"45", 100}, {"46", 101}, {"47", 102}, {"48", 103}, {"49", 104}, {"50", 105}, 
    {"51", 106}, {"52", 107}, {"53", 108}, {"54", 109}, {"55", 110}, {"56", 111}, {"57", 112}, {"58", 113}, {"59", 114}, {"60", 115}, 
    {"61", 116}, {"62", 117}, {"63", 118}, {"64", 119}, {"65", 120}, {"66", 121}, {"67", 122}, {"68", 123}, {"69", 124}, {"70", 125}, 
    {"71", 126}, {"72", 127}, {"73", 128}
};

struct Card {
    uint16_t ID;
    std::string Name;
    std::vector<uint8_t> base_types;
    std::vector<uint16_t> base_subtypes;
    std::vector<uint8_t> base_supertypes;
    std::vector<uint8_t> base_colors;
    std::vector<uint8_t> base_cost;
    uint16_t power;
    uint16_t toughness;
    std::vector<uint16_t> AbilityIDs;
};

bool GetTypesFromStringVector(std::vector<std::string> Types, Card & Card) {
    for (std::string Type : Types) {

        auto it = TypeToValue.find(Type);

        if (it == TypeToValue.end()) {
            throw std::invalid_argument("Invalid card type: " + Type);
            return false;
        }

        Card.base_types.push_back(it -> second);
        return true;
    }
};

 bool GetSubtypesFromStringVector(std::vector<std::string> Subtypes, Card & Card) {
    for (std::string Subtype : Subtypes) {

        auto it = SubtypeToValue.find(Subtype);

        if (it == SubtypeToValue.end()) {
            throw std::invalid_argument("Invalid card subtype: " + Subtype);
            return false;
        }

        Card.base_subtypes.push_back(it -> second);
        return true;
    }
 };

 bool GetSupertypesFromStringVector(std::vector<std::string> SuperTypes, Card & Card) {
    for (std::string SuperType : SuperTypes) {

        auto it = SuperTypeToValue.find(SuperType);

        if (it == SuperTypeToValue.end()) {
            throw std::invalid_argument("Invalid card supertype: " + SuperType);
            return false;
        }

        Card.base_supertypes.push_back(it -> second);
        return true;
    }
};


 bool GetColorsFromStringVector(std::vector<std::string> Colors, Card & Card) {
    for (std::string Color : Colors) {

        auto it = ColorToValue.find(Color);

        if (it == ColorToValue.end()) {
            throw std::invalid_argument("Invalid card color: " + Color);
            return false;
        }

        Card.base_colors.push_back(it -> second);
        return true;
    }
};

bool GetCostFromString(std::string ManaCost, Card & Card) {

    const std::regex ManaSymbolRegex("^(\{([WUBRGCS])|([WUBRGCP2])/(?!\1)([WUBRGCP2])(/(?!\1|\2)([WUBRGCP2]))?|(200|1\d{2}|[1-9]\d|\d)\})$");

    std::smatch match;    

    uint8_t ExpectedIndex = 0;

    std::string ManaCostSubstr = ManaCost.substr(ExpectedIndex);

    while (std::regex_search(ManaCostSubstr, match, ManaSymbolRegex)) {
        if (ExpectedIndex >= ManaCost.length())
            break;

        std::string ManaSymbol = match.str();

        auto it = ManaSymbolToValue.find(ManaSymbol.substr(1, (ManaSymbol.length() - 2)));

        if (it == ManaSymbolToValue.end()) {
            throw std::invalid_argument("Invalid mana symbol in cost: " + ManaSymbol);
            return false;
        }

        Card.base_cost.push_back(it->second);

        ExpectedIndex += ManaSymbol.length();
        return true;

    }
};


Card ImportCardFromFile(std::string Deck, std::string FileName) {

    std::string CardPath = "../Assets/Decks/" + Deck + "/Cards/" + FileName + ".json";

    if (std::filesystem::exists(CardPath)) {
        
        Card card;

        std::ifstream CardFileStream("../Assets/Decks/" + Deck + "/Cards/" + FileName + ".json");
        nlohmann::json cardData = nlohmann::json::parse(CardFileStream);

        auto itID = cardData.find("ID");

        if (itID == cardData.end()) {
            throw std::invalid_argument("No ID found for card " + FileName);
        }
        else {
            card.ID = itID.value();
        }


        auto itName = cardData.find("Name");

        if (itName == cardData.end()) {

            throw std::invalid_argument("No Name found for card " + FileName);
        }
        else {
            card.Name = itName.value();
        }


        auto itTypes = cardData.find("Types");

        if (itTypes == cardData.end()) {

            throw std::invalid_argument("No Types found for card " + FileName);
        }
        else {
            if (GetTypesFromStringVector(itTypes.value(), card) == false) {
                throw std::invalid_argument("Error importing types for card " + FileName);
            }
        }


        auto itSubtypes = cardData.find("Subtypes");

        if (itSubtypes == cardData.end()) {

            std::cout << "No Subtypes found for card " << FileName << ", continuing assuming the card has none.";

        }
        else {
            if (GetSubtypesFromStringVector(itSubtypes.value(), card) == false) {
                throw std::invalid_argument("Error importing Subtypes for card " + FileName);
            }
        }


        auto itSupertypes = cardData.find("Supertypes");

        if (itSupertypes == cardData.end()) {

            std::cout << "No Supertypes found for card " << FileName << ", continuing assuming the card has none.";

        }
        else {
            if (GetSupertypesFromStringVector(itSupertypes.value(), card) == false) {
                throw std::invalid_argument("Error importing Supertypes for card " + FileName);
            }
        }


        auto itColors = cardData.find("Colors");

        if (itColors == cardData.end()) {

            throw std::invalid_argument("No Colors found for card " + FileName + ". Remeber to include colorless.");

        }
        else {
            if (GetColorsFromStringVector(itColors.value(), card) == false) {
                throw std::invalid_argument("Error importing Colors for card " + FileName);
            }
        }



        auto itCost = cardData.find("Base_Cost");

        if (itCost == cardData.end()) {

            std::cout << "No Cost found for card " << FileName << ", continuing assuming the card has has a cost of {X}.";

        }
        else {
            if (GetCostFromString(itCost.value(), card) == false) {
                throw std::invalid_argument("Error importing Cost for card " + FileName);
            }
        }


        auto itPower = cardData.find("Power");

        if (itPower == cardData.end()) {

            std::cout << "No Power found for card " << FileName << ", continuing assuming the card has has a power of *, or is not a creature.";

        }
        else {
            card.power = itPower.value();
        }


        auto itToughnessorLoyalty = cardData.find("Toughness/Loyalty");

        if (itToughnessorLoyalty == cardData.end()) {

            std::cout << "No Power found for card " << FileName << ", continuing assuming the card has has a toughness of *, or is not a planeswalker or creature.";

        }
        else {
            card.toughness = itToughnessorLoyalty.value();
        }


        return card;

    }
};