@echo off
echo "DEBIAN ONLY (if you're an Arch user, figure it out yourself)"

:: Check if git is installed, if not, terminate the program
git --version > nul 2>&1
if %errorlevel% neq 0 (
    echo Git is not installed. Please install Git from https://git-scm.com/.
    exit /b 1
) else (
    echo Git is already installed.
)

:: Check if g++ is installed, if not, terminate the program
where g++ > nul 2>&1
if %errorlevel% neq 0 (
    echo g++ is not installed. Please install it from your package manager or Visual Studio.
    exit /b 1
) else (
    echo g++ is already installed.
)

:: Clone the repository
git clone https://github.com/Rtificer/MTG-RL.git

:: Move files from the cloned repository to the current directory
move /Y MTG-RL\++* .

:: Delete the MTG-RL directory and all its contents
rd /S /Q MTG-RL++