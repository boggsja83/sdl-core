#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_scancode.h>
#include <iostream>
#include <ostream>

#include "types.h"

class Keyboard{
    public:
	Keyboard(){
	    rt r = reset_ks();
	    if(r) std::cerr << "KB_MEMSET_FAIL" << std::endl;

	    r = set_default_map();
	    if(r) std::cerr << "KM_MEMSET_FAIL" << std::endl;

	    r = reset_rp();
	    if(r) std::cerr << "RP_MEMSET_FAIL" << std::endl;
	}

	~Keyboard(){}

    public:
	bool keystate[SDL_NUM_SCANCODES];
	SDL_Scancode map[KB_NUM_ACTIONS];
	i16 rpts[SDL_NUM_SCANCODES];

    public:
	inline rt reset_ks(){
	    void* rp = memset(keystate, 0, sizeof(keystate));
	    if (static_cast<bool*>(rp) != keystate) return KB_MEMSET_FAIL;
	    return OKAY;
	}

	inline rt reset_km(){
	    void* rp = memset(map, 0, sizeof(map));
	    if (static_cast<SDL_Scancode*>(rp) != map) return KM_MEMSET_FAIL;
	    return OKAY;
	}

	inline rt reset_rp(){
	    void* rp = memset(rpts, 0, sizeof(rpts));
	    if(static_cast<i16*>(rp) != rpts) return RP_MEMSET_FAIL;
	    return OKAY;
	}

	inline rt poll_events(){
	    SDL_Event event;
	    rt r = OKAY;

	    while(SDL_PollEvent(&event)) {
		switch(event.type){
		    case SDL_QUIT:
			return QUIT;
		    case SDL_KEYDOWN:
			if(event.key.repeat){
			    std::cerr << "incrementing key repeat" << std::endl;
			    ++rpts[event.key.keysym.scancode];
			}
			else{
			    keystate[event.key.keysym.scancode] = true;
			    rpts[event.key.keysym.scancode] = 0;
			}
			break;
		    case SDL_KEYUP:
			keystate[event.key.keysym.scancode] = false;
			rpts[event.key.keysym.scancode] = 0;
			break;
		    default:
			break;
		}
	    }
	    return OKAY;
	}

	inline rt set_default_map(){
	    rt r = reset_km();
	    if(r) return r;

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
		    default:
			map[i] = SDL_SCANCODE_UNKNOWN;
			break;
		}
	    }

	    return OKAY;
	}

	inline rt get_action_repeats(KB_ACTION pact){
	    if(pact>=0 && pact<KB_NUM_ACTIONS) return rpts[map[pact]];
	    return KB_INVALID_ACTION;
	}

	inline rt get_key_repeats(SDL_Scancode psc){
	    return rpts[psc];
	}
};

#endif

