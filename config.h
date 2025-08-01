#ifndef CONFIG_H
#define CONFIG_H

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include <SDL2/SDL.h>

#include "types.h"

typedef struct Config {
    SDL_Window*	    main_win;
    SDL_Renderer*   main_rend;

    i16		    win_w;
    i16 	    win_h;

    i16		    rend_w;
    i16		    rend_h;

    str		    debug_txt;

    ui8 	    red;
    ui8 	    green;
    ui8 	    blue;
    ui8 	    alpha;

    float	    input_ts;
    float 	    logic_ts;
    float 	    rend_ts;

    ui64	    iframes;
    ui64	    lframes;
    ui64	    rframes;

    float 	    dft_cap;
    ui64	    kb_press_threshold;

    str		    alphabet;

    bool	    show_cursor;
    bool	    show_stats;

    i16		    red_txt_i;
    i16		    green_txt_i;
    i16		    blue_txt_i;
    i16		    white_txt_i;
    i16		    black_txt_i;

    SDL_Texture*    red_txt;
    SDL_Texture*    green_txt;
    SDL_Texture*    blue_txt;
    SDL_Texture*    white_txt;
    SDL_Texture*    black_txt;

    Config(){
	main_win    = nullptr;
	main_rend   = nullptr;

	win_w	    = 1920;
	win_h	    = 1080;

	rend_w	    = win_w;
	rend_h	    = win_h;

	debug_txt   = "";

	red	    = 0;
	green	    = 0;
	blue	    = 0;
	alpha	    = SDL_ALPHA_OPAQUE;

	input_ts    = 1.0f / 500.f; // 1000 would be considered high-precision (1ms)
	logic_ts    = 1.0f / 45.f;
	rend_ts	    = 1.0f / 144.f;

	iframes	    = 0;
	lframes	    = 0;
	rframes	    = 0;

	dft_cap     = logic_ts * 3.f;
	kb_press_threshold = 25;

	alphabet = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

	show_cursor = false;
	show_stats  = false;

	red_txt_i   = -1;
	green_txt_i = -1;
	blue_txt_i  = -1;
	white_txt_i = -1;
	black_txt_i = -1;

	red_txt	    = nullptr;
	green_txt   = nullptr;
	blue_txt    = nullptr;
	white_txt   = nullptr;
	black_txt   = nullptr;

    }
} Config;

#endif

