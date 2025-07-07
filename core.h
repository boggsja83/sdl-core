#ifndef CORE_H
#define CORE_H

#include <cstdint>

#include "types.h"
#include "sdl_w.h"
#include "keyboard.h"
#include "entity_manager.h"
#include "entity_system.h"

class Core{
    public:
	Core(){}
	~Core(){}
    public:
	SDL_Wrap	    sdlw;
	Keyboard	    kb; 
	EntityManager	    em;
	ECSvel		    ecs_vel;
	ECSRendTransform    ecs_rtf;
	ECSRendTexture	    ecs_rtx;
	ECSKB		    ecs_kb;
    public:
	int64_t	    STATUS_INT64;
	str	    STATUS_STRING;
    public:
	rt loop();
	rt input();
	rt update(float& accumulator);
	rt render(SDL_Renderer* renderer, float& alpha);
};

#endif
