#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_scancode.h>
#include <SDL_timer.h>

#include "settings.h"
#include "types.h"

class Keyboard{
    public:
	Keyboard(){
	    reset_array(keystate, false);
	    reset_array(time_down,ui64(0));
	    reset_array(time_up,ui64(1));
	    reset_array(first_press);
	    set_default_map();
	}

	~Keyboard(){}

    public:
	bool		keystate[SDL_NUM_SCANCODES];
	SDL_Scancode	map[KB_NUM_ACTIONS];
	bool		first_press[SDL_NUM_SCANCODES];
	ui64		time_down[SDL_NUM_SCANCODES];
	ui64		time_up[SDL_NUM_SCANCODES];

    public:

	template<typename T, size_t N>
	    inline void reset_array(T (&arr)[N], T val){ memset(arr, val, N*sizeof(T)); }

	template<typename T, size_t N>
	    inline void reset_array(T (&arr)[N]){ memset(arr, 0, N*sizeof(T)); }
	
	inline rt poll_events(){
	    SDL_Event event;
	    SDL_Scancode tcode = SDL_SCANCODE_UNKNOWN;

	    while(SDL_PollEvent(&event)) {
		tcode = event.key.keysym.scancode;
		switch(event.type){
		    case SDL_QUIT:
			return QUIT;
		    case SDL_KEYDOWN:
			keystate[tcode] = true;
			if(time_down[tcode]<time_up[tcode]){
			    time_down[tcode] = SDL_GetTicks64();
			    first_press[tcode] = true;
			}
			// else first_press[tcode] = false;
		    break;
		    case SDL_KEYUP:
			keystate[tcode] = false;
			time_up[tcode] = SDL_GetTicks64();
			first_press[tcode] = false;
		    break;
		    default:
		    break;
		}
	    }
	    return OKAY;
	}

	inline rt set_default_map(){
	    reset_array(map, SDL_SCANCODE_UNKNOWN);

	    for(i16 i=0; i<KB_NUM_ACTIONS; ++i){
	        switch(i){
		    case MOVE_N:
		        map[i] = SDL_SCANCODE_W;
		    break;
		    case MOVE_S:
		        map[i] = SDL_SCANCODE_S;
		    break;
		    case MOVE_E:
		        map[i] = SDL_SCANCODE_D;
		    break;
		    case MOVE_W:
		        map[i] = SDL_SCANCODE_A;
		    break;
		    case TEST_ACTION:
			map[i] = SDL_SCANCODE_SPACE;
		    break;
		    case VOL_UP:
			map[i] = SDL_SCANCODE_KP_PLUS;  
		    break;
		    case VOL_DN:
			map[i] = SDL_SCANCODE_KP_MINUS;
		    break;
		    default:
			map[i] = SDL_SCANCODE_UNKNOWN;
		    break;
		}
	    }
	    return OKAY;
	}


	// TODO
	// need to test out considering KB_THRESHOLD_PRESS here to determine
	// if is held... (by definition this should be done, right??) 7-4-25
	// answerish: acktualLy prob not. keep this function "raw"
	inline ui64 is_held(KB_ACTION pka){
	    if(pka>=0 && pka<KB_NUM_ACTIONS)
		if(time_down[map[pka]]>time_up[map[pka]]) return SDL_GetTicks64() - time_down[map[pka]];
		else return 0;
	    else return 0;
	}

	inline ui64 is_held(SDL_Scancode psc){
	    ui64 t = 0;
	    if(psc>=0 && psc<SDL_NUM_SCANCODES)
		if(time_down[psc]>time_up[psc]) return SDL_GetTicks64() - time_down[psc];
		else return 0;
	    else return 0;
	}

	inline float repeats(KB_ACTION pka){
	    if(pka>=0 && pka<KB_NUM_ACTIONS) 
	        if(time_down[map[pka]]>time_up[map[pka]]) return (1.f*SDL_GetTicks64() - time_down[map[pka]]) / KB_THRESHOLD_PRESS;
	        else return 0;
	    else return 0;
	}

	    // inline rt get_action_repeats(KB_ACTION pact){
	    //     if(pact>=0 && pact<KB_NUM_ACTIONS) return rpts[map[pact]];
	    //     return KB_INVALID_ACTION;
	    // }

	    // inline rt get_key_repeats(SDL_Scancode psc){
	    //     return rpts[psc];
	    // }
};

#endif

