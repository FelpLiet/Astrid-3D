# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Files
SOURCE_FILES = $(wildcard $(SRC_DIR)/*.cpp)
HEADER_FILES = $(wildcard $(INCLUDE_DIR)/*.hpp)
OBJECT_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCE_FILES))

# Libraries
LIBS = -lglfw -lSOIL -lGLEW -lGL -lGLU

# Executable
TARGET = astrid3d

# Targets
all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJECT_FILES)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $^ -o $@ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADER_FILES)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
