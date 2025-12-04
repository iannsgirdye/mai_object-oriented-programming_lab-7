CXX = g++-11
CXXFLAGS = -std=c++20 -Wall -Wextra
TARGET = a.out
SRC_DIR = src
OBJ_DIR = build
SRC_SUBDIRS = $(SRC_DIR) $(SRC_DIR)/game $(SRC_DIR)/npc
SOURCES = $(foreach dir,$(SRC_SUBDIRS),$(wildcard $(dir)/*.cpp))
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(wildcard $(SRC_DIR)/*.cpp)) \
		   $(patsubst $(SRC_DIR)/game/%.cpp,$(OBJ_DIR)/game_%.o,$(wildcard $(SRC_DIR)/game/*.cpp)) \
		   $(patsubst $(SRC_DIR)/npc/%.cpp,$(OBJ_DIR)/npc_%.o,$(wildcard $(SRC_DIR)/npc/*.cpp))

all: $(OBJ_DIR) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/game_%.o: $(SRC_DIR)/game/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/npc_%.o: $(SRC_DIR)/npc/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
