#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

typedef int16_t i16;
typedef uint16_t ui16;
typedef i16 rt;

typedef enum {
    OKAY = 0,
    QUIT = -1
} CORE_CODES;

typedef enum {
    KB_MEMSET_FAIL = -100
} KB_CODES;

typedef enum {
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
    COMPONENT_INVALID = -300,
    ENTITY_LACKS_COMPONENT = -301,
    ENTITY_INVALID_ID = -302
} EM_CODES;

typedef enum {
    CM_POS =	0b0001,
    CM_VEL =	0b0010,
    CM_RENDPOS= 0b0100
} COMPONENT_MASKS;

#endif

