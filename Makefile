# Compiler to use
CXX = g++

# Common flags for SDL2, SDL2_image, and SDL2_mixer
BASE_CFLAGS = $(shell sdl2-config --cflags) $(shell pkg-config --cflags SDL2_mixer) $(shell pkg-config --cflags SDL2_image)
BASE_LDFLAGS = $(shell sdl2-config --libs) $(shell pkg-config --libs SDL2_mixer) $(shell pkg-config --libs SDL2_image)

# Source files and target executable
SOURCES = main.cpp sdl_w.cpp core.cpp entity_manager.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = sdl_core

# Default target
all: debug

# Debug build
debug: CFLAGS = $(BASE_CFLAGS) -g -O0
debug: LDFLAGS = $(BASE_LDFLAGS)
debug: $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

# Release build
release: CFLAGS = $(BASE_CFLAGS) -O2
release: LDFLAGS = $(BASE_LDFLAGS)
release: $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

# Compile source files to object files
%.o: %.cpp keyboard.h sdl_w.h core.h types.h settings.h component.h entity_manager.h
	$(CXX) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJECTS) $(TARGET) 

.PHONY: all debug release clean

