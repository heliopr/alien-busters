TARGET_NAME = jogo

ifeq ($(OS),Windows_NT)
    TARGET = bin/$(TARGET_NAME).exe
    TEST_EXT = .exe
    CLEAN_CMD = if exist "build" rmdir /s /q "build" & if exist "bin" rmdir /s /q "bin"
    
    OS_INCLUDES = -I./SFML/include
    OS_LIB_PATHS = -L./SFML/lib
    
    define make_dir
		@if not exist "$(subst /,\,$1)" mkdir "$(subst /,\,$1)"
    endef
    
    define setup_env
		@if exist "SFML\bin\*.dll" copy /Y "SFML\bin\*.dll" "bin\" >nul
    endef
else
    TARGET = bin/$(TARGET_NAME)
    TEST_EXT = .out
    CLEAN_CMD = rm -rf build bin
    
    OS_INCLUDES = 
    OS_LIB_PATHS = 
    
    define make_dir
		@mkdir -p "$1"
    endef
    
    define setup_env
    endef
endif

CXX = g++
CXXFLAGS = -std=c++03 -Wall -Wextra -Iinclude $(OS_INCLUDES)
LDFLAGS = $(OS_LIB_PATHS) -lsfml-graphics -lsfml-window -lsfml-system

SOURCES = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJECTS = $(patsubst src/%.cpp, build/%.o, $(SOURCES))
OBJECTS_NO_MAIN = $(filter-out build/main.o, $(OBJECTS))

TEST_SOURCES = $(wildcard tests/*.cpp)
TEST_BINS = $(patsubst tests/%.cpp, bin/tests/%$(TEST_EXT), $(TEST_SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(call make_dir,bin)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	$(call setup_env)

build/%.o: src/%.cpp
	$(call make_dir,$(dir $@))
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_BINS)
	@echo PASSOU Todos os testes passaram

bin/tests/%$(TEST_EXT): tests/%.cpp $(OBJECTS_NO_MAIN)
	$(call make_dir,bin/tests)
	$(CXX) $(CXXFLAGS) $< $(OBJECTS_NO_MAIN) -o $@ $(LDFLAGS)
	$(call setup_env)
	@echo TESTANDO $<
	@$@

clean:
	@$(CLEAN_CMD)

run: all
	@$(TARGET)

cleanrun: clean run

.PHONY: all clean run cleanrun test