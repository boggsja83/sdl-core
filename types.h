#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

typedef int8_t	i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t	 ui8;
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
    KS_MEMSET_FAIL =	    -100,
    KM_MEMSET_FAIL =	    -125,
    RP_MEMSET_FAIL =	    -150
	// INVALID_ACTION =	    -400
} KB_CODES;

typedef enum {
    KB_INVALID_ACTION =     0,
    MOVE_N =		    1,
    MOVE_S =		    2,
    MOVE_E =		    3,
    MOVE_W =		    4,
    TEST_ACTION =	    5,
    VOL_UP =		    6,
    VOL_DN =		    7,
    KB_NUM_ACTIONS =	    10
} KB_ACTION;

typedef enum {
    SDL_INIT_FAIL =	    -200,
    IMG_INIT_FAIL =	    -201,
    MIX_INIT_FAIL =	    -202,
    TTF_INIT_FAIL =	    -203,
    CREATE_WINDOW_FAIL =    -210,
    CREATE_RENDERER_FAIL =  -211,
    CREATE_SURFACE_FAIL =   -212,
    CREATE_TEXTURE_FAIL =   -213,
    MIX_LOAD_WAV_FAIL =	    -220,
    MIX_LOAD_MUS_FAIL =	    -221,
    IMG_LOAD_FAIL =	    -222,
    TTF_OPEN_FAIL =	    -223,
    TTF_SURFACE_FAIL =	    -224,
    INVALID_TEXTURE =	    -232,
    INVALID_RENDERER =	    -233,
    INVALID_CHUNK =	    -234,
    INVALID_MUSIC =	    -235,
    PLAY_CHANNEL_FAIL =	    -275,
    PLAY_MUSIC_FAIL =	    -276
} SDL_WRAP_CODES;

typedef enum {
    ECS_INVALID_COMP =	    -400,
    ECS_INVALID_ID =	    -401,
    ECS_LACKS_COMP =	    -402
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

