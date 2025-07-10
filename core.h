#ifndef CORE_H
#define CORE_H

#include "types.h"
#include "sdl_w.h"
#include "keyboard.h"
#include "entity_manager.h"
#include "entity_system.h"

class Core{
    public:
	Core():LFRAMES(0),RFRAMES(0),START(0){}
	~Core(){}
    public:
	SDL_Wrap	    sdlw;
	Keyboard	    kb; 
	EntityManager	    em;
	ECSpos		    ecs_pos;
	ECSrendpos	    ecs_rendpos;
	ECStexture	    ecs_texture;
	ECSkb		    ecs_kb;
    public:
	// i64	    STATUS_INT64;
	// str	    STATUS_STRING;
	ui64	    LFRAMES;
	ui64	    RFRAMES;
	ui64	    START;
    public:
	rt loop();
	rt input();
	rt update(float& accumulator);
	rt render(SDL_Renderer* renderer, float& alpha);
};

#endif
