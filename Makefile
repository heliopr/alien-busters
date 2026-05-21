ifeq ($(OS),Windows_NT)
    TARGET = bin/jogo.exe
    TEST_EXT = .exe
    
    INCLUDES = -Iinclude -IC:\SFML-2.5.1\include
    LIBS = -LC:\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system
    
    MKDIR_BUILD = if not exist "$(subst /,\,$(dir $@))" mkdir "$(subst /,\,$(dir $@))"
    MKDIR_BIN = if not exist "bin" mkdir "bin"
    MKDIR_TESTS = if not exist "bin\tests" mkdir "bin\tests"
    CLEAN_CMD = if exist build rmdir /S /Q build & if exist bin rmdir /S /Q bin
    
    RUN_TARGET = $(subst /,\,$(TARGET))
    RUN_TEST = $(subst /,\,$@)
else
    TARGET = bin/jogo
    TEST_EXT = .out
    
    INCLUDES = -Iinclude
    LIBS = -lsfml-graphics -lsfml-window -lsfml-system
    
    MKDIR_BUILD = mkdir -p $(dir $@)
    MKDIR_BIN = mkdir -p bin
    MKDIR_TESTS = mkdir -p bin/tests
    CLEAN_CMD = rm -rf build bin
    
    RUN_TARGET = ./$(TARGET)
    RUN_TEST = ./$@
endif

CXX = g++
CXXFLAGS = -std=c++03 -Wall -Wextra $(INCLUDES)
LDFLAGS = $(LIBS)

SOURCES = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJECTS = $(patsubst src/%.cpp, build/%.o, $(SOURCES))
OBJECTS_NO_MAIN = $(filter-out build/main.o, $(OBJECTS))

TEST_SOURCES = $(wildcard tests/*.cpp)
TEST_EXECS = $(patsubst tests/%.cpp, bin/tests/%$(TEST_EXT), $(TEST_SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@$(MKDIR_BIN)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

build/%.o: src/%.cpp
	@$(MKDIR_BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_EXECS)
	@echo PASSOU Todos os testes passaram

bin/tests/%$(TEST_EXT): tests/%.cpp $(OBJECTS_NO_MAIN)
	@$(MKDIR_TESTS)
	$(CXX) $(CXXFLAGS) $< $(OBJECTS_NO_MAIN) -o $@ $(LDFLAGS)
	@echo TESTANDO $(notdir $<)
	@$(RUN_TEST)

clean:
	@$(CLEAN_CMD)

run: all
	@$(RUN_TARGET)

cleanrun: clean run

.PHONY: all clean run cleanrun test