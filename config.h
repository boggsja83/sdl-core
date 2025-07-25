#ifndef CONFIG_H
#define CONFIG_H

#include <SDL2/SDL.h>

#include "types.h"

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

    bool	    show_cursor;

    Config(){
	win	    = nullptr;
	rend	    = nullptr;

	win_w	    = 1920;
	win_h	    = 1080;

	red	    = 80;
	green	    = 90;
	blue	    = 231;
	alpha	    = SDL_ALPHA_OPAQUE;

	input_ts    = 1.0f / 500.f; // 1000 would be considered high-precision (1ms)
	logic_ts    = 1.0f / 45.f;
	rend_ts	    = 1.0f / 144.f;
	// rend_ts	    = 1.0f/60.f;

	dft_cap     = logic_ts * 3.f;
	kb_press_threshold = 25;

	alphabet = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

	show_cursor = false;
    }

} Config;

#endif

