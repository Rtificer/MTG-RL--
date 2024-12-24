#!/bin/bash
echo "DEBIAN ONLY (if you're an Arch user, figure it out yourself)"

# Check if git is installed, if not, install it
if ! command -v git &> /dev/null
then
    echo "Git is not installed. Installing Git..."
    sudo apt-get update
    sudo apt-get install -y git
else
    echo "Git is already installed."
fi

# Check if g++-14 is installed, if not, install it
if ! dpkg -l | grep -q g++-14
then
    echo "g++-14 is not installed. Installing g++-14..."
    sudo apt-get install -y g++-14
else
    echo "g++-14 is already installed."
fi

git clone https://github.com/Rtificer/MTG-RL_CPP.git

# Move files To the current directory
mv MTG-RL/++* .

# Delete the MTG-RL directory
rm -rf MTG-RL++

# Set executable permission on Start.sh
chmod +x Start.sh