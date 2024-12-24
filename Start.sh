#!/bin/bash

echo "Checking for at least one deck..."

if [ -z "$(find ./Assets/Decks -mindepth 1 -type d 2>/dev/null)" ]; then
    echo "Zero decks found, please provide at least one deck."
    exit
fi
echo ""

echo "Checking Deck Contents..."
echo ""
for dir in ./Assets/Decks/*/
do
    dir=${dir%*/}  # Remove the trailing slash
    deckName=$(basename "${dir}")

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
        echo "         Zero (potential) cards found in ${deckName}'s Card Directory'}"
        exit
    fi
    echo ""

    echo "   Checking for Abilities directory in ${deckName}..."
    if [ ! -d "${dir}/Abilities" ]; then
        echo "      Missing Abilities folder in ${deckName}"
        echo "      Continuing, assuming no abilities are needed."
    fi
done