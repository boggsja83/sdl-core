#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>

#include "config.h"
#include "entity_component.h"
#include "keyboard.h"
#include "types.h"
#include "sdl_w.h"

class EntityManager{

    public:
	EntityManager(){
	    ents.clear();
	    pos.clear();
	    vel.clear();
	    rendpos.clear();
	    texture.clear();
	    kb.clear();
	    fps.clear();

	    sdlw_ptr = nullptr;
	    kb_ptr = nullptr;
	    conf_ptr = nullptr;
	}

    public:
	~EntityManager(){
	}

    public:
	rt add_entity(ui64 comp_mask);

	//TODO:
	//rt del_entity(i16 id);
	// inline rt add_comp(i16 pid, CM_MASK pcmp);
	// rt del_comp(i16 pid, CM_MASK pcmp);

    public:
	std::vector<ui64>	ents;
	std::vector<cPos>	pos;
	std::vector<cVel>	vel;
	std::vector<cRendPos>	rendpos;
	std::vector<cTexture>	texture;
	std::vector<cKB>	kb;
	std::vector<cFPS>	fps;

    public:
	SDL_Wrap*   sdlw_ptr;
	Keyboard*   kb_ptr;
	Config*	    conf_ptr;

    public:
	rt set(EC& pec);

};

#endif

