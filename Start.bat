@echo off
echo Checking for at least one deck...

for /d %%i in (.\Assets\Decks\*) do (
    set "deckFound=true"
    goto :found
)

echo Zero decks found, please provide at least one deck.
exit /b

:found
echo.

echo Checking Deck Contents...
echo.

for /d %%i in (.\Assets\Decks\*) do (
    set "dir=%%i"
    set "deckName=%%~ni"

    echo    Checking for DeckAttributes file in %deckName%
    if not exist "%dir%\DeckAttributes.json" (
        echo       Missing DeckAttributes.json in %deckName%
        exit /b
    )
    echo.

    echo    Checking for Cards directory in %deckName%
    if not exist "%dir%\Cards" (
        echo       Missing Cards folder in %deckName%
        exit /b
    )
    echo.

    echo       Checking for at least one card in Card directory.
    set "cardFound=false"
    for %%f in (%dir%\Cards\*.json) do (
        set "cardFound=true"
        goto :cardFound
    )
    echo          Zero (potential) cards found in %deckName%'s Card Directory
    exit /b

    :cardFound
    echo.

    echo    Checking for Abilities directory in %deckName%
    if not exist "%dir%\Abilities" (
        echo       Missing Abilities folder in %deckName%
        echo       Continuing, assuming no abilities are needed.
    )
)