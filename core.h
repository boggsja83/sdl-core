#ifndef CORE_H
#define CORE_H

#include <cstdint>

#include "types.h"
#include "sdl_w.h"
#include "keyboard.h"
#include "entity_manager.h"
#include "entity_system.h"

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
	ECSLogicTransform ecs_lt;
	ECSRendTransform ecs_rt;

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
