#ifndef TYPES_H
#define TYPES_H

#include <SDL2/SDL_pixels.h>
#include <cstdint>

typedef int16_t rt;

typedef enum {
    OKAY = 0,
    QUIT = -1
} CORE_CODES;

typedef enum {
    //KB_OKAY = 0,
    //KB_QUIT = -1
    KB_MEMSET_FAIL = -1
} KB_CODES;

typedef enum {
    //SDLW_OKAY = 0,
    SDL_INIT_FAIL = -1,
    IMG_INIT_FAIL = -2,
    MIX_INIT_FAIL = -3,
    CREATE_WINDOW_FAIL = -100,
    CREATE_RENDERER_FAIL = -101,
    CREATE_SURFACE_FAIL = -102,
    CREATE_TEXTURE_FAIL = -103,
    MIX_LOAD_WAV_FAIL = -200,
    IMG_LOAD_FAIL = -300
} SDL_WRAP_CODES;

#endif

