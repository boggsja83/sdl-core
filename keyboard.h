#ifndef KEYBOARD_H
#define KEYBOARD_H
/******************************************************************************/
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_scancode.h>
#include <iostream>
#include <ostream>

#include "types.h"
/******************************************************************************/
class Keyboard{
    public:
	Keyboard(){
	    rt r = reset_keystate();
	    if(r) std::cerr << "KB_MEMSET_FAIL" << std::endl;
	}
	~Keyboard(){}
/******************************************************************************/
    public:
	bool keystate[SDL_NUM_SCANCODES];
/******************************************************************************/
    public:
	/**********************************************************************/
	inline rt reset_keystate(){
	/**********************************************************************/
	    void* rp = memset(keystate, 0, sizeof(keystate));
	    //std::cout << "sizeof(keystate): " << sizeof(keystate) << " sizeof(bool): " << sizeof(bool) << std::endl;
	    if (static_cast<bool*>(rp) != keystate) return KB_MEMSET_FAIL;
	    return OKAY;
	}

	/**********************************************************************/
	inline rt poll_events(){
	/**********************************************************************/
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
};
/******************************************************************************/
#endif
/******************************************************************************/
