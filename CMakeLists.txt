# Specify the minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(sdl_core LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2, SDL2_image, and SDL2_mixer
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Define source files
set(SOURCES
    main.cpp
    sdl_w.cpp
    core.cpp
    entity_manager.cpp
)

# Define header files (optional, for IDE visibility)
set(HEADERS
    keyboard.h
    sdl_w.h
    core.h
    types.h
    settings.h
    component.h
    entity_manager.h
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories (if headers are in a separate include folder, adjust accordingly)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link SDL2 libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
)

# Set debug build flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

# Set release build flags
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
