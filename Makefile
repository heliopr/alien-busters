TARGET = bin/jogo

CXX = g++
CXXFLAGS = -std=c++03 -Wall -Wextra -Iinclude
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SOURCES = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)

OBJECTS = $(patsubst src/%.cpp, build/%.o, $(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p bin
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build bin

run: all
	./$(TARGET)

cleanrun:
	$(MAKE) clean
	$(MAKE) run

.PHONY: all clean run cleanrun