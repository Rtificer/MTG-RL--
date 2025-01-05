#!/bin/bash

echo "Checking for at least one deck..."

if [ -z "$(find ./Assets/Decks -mindepth 1 -type d 2>/dev/null)" ]; then
    echo "Zero decks found, please provide at least one deck."
    exit
fi
echo ""

echo "Checking Deck Folder Contents..."
echo ""
for dir in ./Assets/Decks/*/
do
    dir=${dir%*/}  # Remove the trailing slash
    deckName=$(basename "${dir}")

    echo "   Checking the name of ${deckName}..."
    if [[ "$deckName" =~ [[:space:][:cntrl:][:punct:]] && ! "$deckName" =~ _ ]]; then
        echo "      Error: Deck name '$deckName' contains spaces or other unsupported characters."
        echo "      Please ensure deck names do not contain spaces or characters like punctuation."
        exit 1
    fi
    echo ""

    echo "   Checking for DeckAttributes file in ${deckName}..."
    if [ ! -f "${dir}/DeckAttributes.json" ]; then
        echo "      Missing DeckAttributes.json in ${deckName}"
        exit
    fi
    echo ""

    echo "   Checking for Card directory in ${deckName}..."
    if [ ! -d "${dir}/Cards" ]; then
        echo "      Missing Cards folder in ${deckName}"
        exit
    fi
    echo ""

    echo "      Checking for at least one card in Card directory..."
    if [ -z "$(find "${dir}/Cards" -maxdepth 1 -type f -name "*.json" 2>/dev/null)" ]; then
        echo "         Zero (potential) cards found in ${deckName}'s Card Directory"
        exit
    fi
    echo ""

    echo "   Checking for Abilities directory in ${deckName}..."
    if [ ! -d "${dir}/Abilities" ]; then
        echo "      Missing Abilities folder in ${deckName}"
        echo "      Continuing, assuming no abilities are needed."
    fi
done

echo ""
echo "Generating project files..."

# Dynamically create a registry file for decks and abilities
registryFile="./Assets/Decks/DeckRegistry.cpp"
echo "// Auto-generated Deck Registry" > "$registryFile"
echo "#include <iostream>" >> "$registryFile"
echo "#include \"Deck.h\"" >> "$registryFile"

# Include ability headers for static linking
echo "// Ability includes" >> "$registryFile"
for dir in ./Assets/Decks/*/
do
    abilitiesDir="${dir}Abilities/"
    if [ -d "$abilitiesDir" ]; then
        for abilityFile in "${abilitiesDir}"*.cpp; do
            if [ -f "$abilityFile" ]; then
                abilityName=$(basename "$abilityFile")
                echo "#include \"$abilityFile\"" >> "$registryFile"
            fi
        done
    fi
done

# Declare extern decks
for dir in ./Assets/Decks/*/
do
    deckName=$(basename "${dir}")
    echo "extern Deck ${deckName}Deck();" >> "$registryFile"
done

# Create loadAllDecks function
echo "std::vector<Deck> loadAllDecks() {" >> "$registryFile"
echo "    std::vector<Deck> decks;" >> "$registryFile"
for dir in ./Assets/Decks/*/
do
    deckName=$(basename "${dir}")
    echo "    decks.push_back(${deckName}Deck());" >> "$registryFile"
done
echo "    return decks;" >> "$registryFile"
echo "}" >> "$registryFile"

echo "Registry file generated: $registryFile"
echo ""

# Rebuild the project
if grep -q '^clean:' Makefile 2>/dev/null; then
    echo "Cleaning up previous builds..."
    make clean
fi

echo "Building the project..."
make

if [ $? -eq 0 ]; then
    echo "Build succeeded!"
else
    echo "Build failed. Please check the error messages above."
    exit 1
fi

echo ""
echo "Setup complete. Run ./MainProgram to start the game."
