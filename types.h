#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint16_t ui16;
typedef uint32_t ui32;
typedef uint64_t ui64;

typedef const char* str;

typedef i16 rt;

typedef enum {
    OKAY =		    0,
    QUIT =		    -1
} CORE_CODES;

typedef enum {
    KB_MEMSET_FAIL =	    -100,
    KM_MEMSET_FAIL =	    -200
} KB_CODES;

typedef enum {
    KB_NO_ACTION =          0,
    MOVE_N =		    1,
    MOVE_S =		    2,
    MOVE_E =		    3,
    MOVE_W =		    4,
    TEST_ACTION =	    5,
    KB_NUM_ACTIONS =	    10
} KB_ACTION;

typedef enum {
    SDL_INIT_FAIL =	    -200,
    IMG_INIT_FAIL =	    -201,
    MIX_INIT_FAIL =	    -202,
    CREATE_WINDOW_FAIL =    -210,
    CREATE_RENDERER_FAIL =  -211,
    CREATE_SURFACE_FAIL =   -212,
    CREATE_TEXTURE_FAIL =   -213,
    MIX_LOAD_WAV_FAIL =	    -220,
    MIX_LOAD_MP3_FAIL =	    -221,
    IMG_LOAD_FAIL =	    -222,
    INVALID_TEXTURE =	    -232,
    INVALID_RENDERER =	    -233,
    INVALID_CHUNK =	    -234,
    INVALID_MUSIC =	    -235,
    PLAY_CHANNEL_FAIL =	    -300,
    PLAY_MUSIC_FAIL =	    -301
} SDL_WRAP_CODES;

typedef enum {
    ECS_INVALID_COMP =	    -300,
    ECS_INVALID_ID =	    -301,
    ECS_LACKS_COMP =	    -302
} ECS_CODES;

typedef enum {
    CM_NULL =		    0b0000'0000,
    CM_POS =		    0b0000'0001,
    CM_VEL =		    0b0000'0010,
    CM_RENDPOS =	    0b0000'0100,
    CM_TEXTURE =	    0b0000'1000,
    // CM_TEST =		    0b0001'0000,    // not using this aKtuALLy
    CM_KB =		    0b0010'0000
} CM_MASK;

#endif

