#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

typedef int16_t rt;

typedef enum {
    OKAY = 0,
    QUIT = -1
} CORE_CODES;

typedef enum {
    //KB_OKAY = 0,
    //KB_QUIT = -1
    KB_MEMSET_FAIL = -100
} KB_CODES;

typedef enum {
    //SDLW_OKAY = 0,
    SDL_INIT_FAIL = -200,
    IMG_INIT_FAIL = -201,
    MIX_INIT_FAIL = -202,
    CREATE_WINDOW_FAIL = -210,
    CREATE_RENDERER_FAIL = -211,
    CREATE_SURFACE_FAIL = -212,
    CREATE_TEXTURE_FAIL = -213,
    MIX_LOAD_WAV_FAIL = -220,
    IMG_LOAD_FAIL = -221
} SDL_WRAP_CODES;

typedef enum {
    INVALID_COMPONENT = -300
} EM_CODES;

typedef enum {
    CM_POS =	0b0001,
    CM_VEL =	0b0010
} COMPONENT_MASKS;




#endif

