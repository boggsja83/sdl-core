#ifndef CORE_H
#define CORE_H

#include <cstdint>

#include "types.h"
#include "settings.h"
#include "sdl_w.h"
#include "keyboard.h"
#include "entity_manager.h"

// highest-level component of GAME 
class Core{
    public:
	Core(){
	    STATUS_INT64 = sdlw.init();
	    STATUS_STRING = "Core()";
	}

	~Core(){

	}

    public:
	SDL_Wrap sdlw;
	Keyboard kb; 
	EntityManager em;

    public:
	int64_t STATUS_INT64;
	const char* STATUS_STRING;

    public:
	rt loop();
	rt input();
	rt update(float&);
	rt render(SDL_Renderer*, float&);
};

#endif
