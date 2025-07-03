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
	}

	~Keyboard(){}

    public:
	bool keystate[SDL_NUM_SCANCODES];
	SDL_Scancode map[KB_NUM_ACTIONS];

    public:

	inline rt reset_ks(){
	    void* rp = memset(keystate, 0, sizeof(keystate));
	    if (static_cast<bool*>(rp) != keystate) return KB_MEMSET_FAIL;
	    return OKAY;
	}

	inline rt reset_km(){
	    void* rp = memset(map, 0, sizeof(map));
	    if (static_cast<SDL_Scancode*>(rp) != map) return KB_MEMSET_FAIL;
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
			keystate[event.key.keysym.scancode] = true;
			break;
		    case SDL_KEYUP:
			keystate[event.key.keysym.scancode] = false;
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
			map[i] = SDL_SCANCODE_N;
			// map[i] = SDL_SCANCODE_SPACE;
			break;
		    default:
			map[i] = SDL_SCANCODE_UNKNOWN;
			break;
		}
	    }

	    return OKAY;
	}
};

// class Keymap{
//     public:
// 	SDL_Scancode map[KB_NUM_ACTIONS];
//
// 	Keymap(){
// 	    rt r = default_map();
// 	    if(r) std::cerr << "KM_MEMSET_FAIL" << std::endl;
// 	}
//
// 	inline rt reset(){
// 	    void* rp = memset(map, KB_NO_ACTION, sizeof(map));
// 	    if (static_cast<SDL_Scancode*>(rp) != map) return KM_MEMSET_FAIL;
// 	    return OKAY;
// 	}

// };

#endif

