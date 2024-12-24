# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Directories
UTILS_DIR = utils
MAIN_DIR = main
DECKS_DIR = Assets/Decks
OBJ_DIR = obj
BIN_DIR = bin

# Output
TARGET = $(BIN_DIR)/MainProgram

# Source files
SOURCES = $(wildcard $(MAIN_DIR)/*.cpp $(UTILS_DIR)/*.cpp $(DECKS_DIR)/*/Abilities/*.cpp)
OBJECTS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SOURCES)))

# Default rule: Build the executable
all: $(TARGET)

# Link all object files into the final program
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each source file into an object file
$(OBJ_DIR)/%.o: $(MAIN_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(DECKS_DIR)/*/Abilities/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories if they don't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean rule: Remove build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
