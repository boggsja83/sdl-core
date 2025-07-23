#ifndef CONFIG_H
#define CONFIG_H

#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <random>

#include "types.h"

// typedef int8_t	i8;
// typedef int16_t i16;
// typedef int32_t i32;
// typedef int64_t i64;
//
// typedef uint8_t	 ui8;
// typedef uint16_t ui16;
// typedef uint32_t ui32;
// typedef uint64_t ui64;
//
// typedef const char* str;
//
// typedef i16 rt;

typedef struct Config {
    SDL_Window*	    win;
    SDL_Renderer*   rend;

    i16		    win_w;
    i16 	    win_h;

    ui8 	    red;
    ui8 	    green;
    ui8 	    blue;
    ui8 	    alpha;

    float	    input_ts;
    float 	    logic_ts;
    float 	    rend_ts;

    float 	    dft_cap;
    ui64	    kb_press_threshold;

    str		    alphabet;

    Config(){
	win	    = nullptr;
	rend	    = nullptr;

	win_w	    = 1920;
	win_h	    = 1080;

	red	    = 80;
	green	    = 90;
	blue	    = 231;
	alpha	    = SDL_ALPHA_OPAQUE;

	input_ts    = 1.0f / 500.f;
	logic_ts    = 1.0f / 45.f;
	rend_ts	    = 1.0f / 144.f;

	dft_cap     = logic_ts * 3.f;
	kb_press_threshold = 25;

	alphabet = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    }

} Config;

#endif

