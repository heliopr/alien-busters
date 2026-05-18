TARGET = bin/jogo

CXX = g++
CXXFLAGS = -std=c++03 -Wall -Wextra -Iinclude
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SOURCES = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJECTS = $(patsubst src/%.cpp, build/%.o, $(SOURCES))

OBJECTS_NO_MAIN = $(filter-out build/main.o, $(OBJECTS))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p bin
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(OBJECTS_NO_MAIN)
	@mkdir -p bin/tests
	@echo "Iniciando testes"
	@for arquivo in tests/*.cpp; do \
		if [ -f "$$arquivo" ]; then \
			nome_exec=bin/tests/$$(basename $$arquivo .cpp).out; \
			$(CXX) $(CXXFLAGS) $$arquivo $(OBJECTS_NO_MAIN) -o $$nome_exec $(LDFLAGS); \
			echo "TESTANDO $$(basename $$arquivo)"; \
			./$$nome_exec || exit 1; \
		fi \
	done
	@echo "PASSOU Todos os testes passaram"

clean:
	rm -rf build bin

run: all
	./$(TARGET)

cleanrun:
	$(MAKE) clean
	$(MAKE) run

.PHONY: all clean run cleanrun test