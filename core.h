#ifndef CORE_H
#define CORE_H

#include <random>

#include "config.h"
#include "types.h"
#include "sdl_w.h"
#include "keyboard.h"
#include "entity_manager.h"
#include "entity_system.h"

class Core{
    public:
	Core():IFRAMES(0),LFRAMES(0),RFRAMES(0),START(0),
	FADE_ALPHA(SDL_ALPHA_OPAQUE),FADE_DO(true){}
	~Core(){}
    public:
	Config		    conf;
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
	ui64	    IFRAMES;
	ui64	    LFRAMES;
	ui64	    RFRAMES;
	ui64	    START;
	// used for doing test doesnt necessarily need to be here
	float	    FADE_ALPHA;
	bool	    FADE_DO;
    public:
	static i64  rand(i64 plow, i64 phi){
	    std::random_device rd;
	    std::mt19937 gen(rd());
	    std::uniform_int_distribution<> dis(plow, phi);
	    return dis(gen);
	}
    public:
	rt loop();
	rt input();
	rt update(float& accumulator);
	rt render(SDL_Renderer* renderer, float& alpha);
};

#endif
