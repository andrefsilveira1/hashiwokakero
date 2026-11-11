CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic
CPPFLAGS ?= -Iinclude

TARGET := hashi
SOURCES := src/main.cpp src/board.cpp src/cell.cpp src/island.cpp src/static_puzzle.cpp src/puzzle_io.cpp src/render.cpp
OBJECTS := $(SOURCES:.cpp=.o)
DEPENDS := $(OBJECTS:.o=.d)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

src/%.o: src/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(DEPENDS) $(TARGET)

-include $(DEPENDS)
