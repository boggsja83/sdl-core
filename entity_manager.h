#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "entity_component.h"
#include "keyboard.h"
#include "types.h"
#include "sdl_w.h"
#include <vector>

class EntityManager{

    public:
	EntityManager(){
	    ents.clear();
	    pos.resize(5);
	    vel.resize(5);
	    rendpos.resize(5);
	    texture.resize(5);
	    kb.resize(5);
	    psdlw = nullptr;
	    pkb = nullptr;
	}

    public:
	~EntityManager(){
	}

    public:
	rt add_entity(ui64 comp_mask);
	//TODO:
	//rt del_entity(i16 id);
	//rt add_comp(i16 ownid, ENTITY_COMPONENT comp)
	//rt del_comp(i16 ownid, ENTITY_COMPONENT comp)

    public:
	std::vector<ui64> ents;
	std::vector<cPos> pos;
	std::vector<cVel> vel;
	std::vector<cRendPos> rendpos;
	std::vector<cTexture> texture;
	std::vector<cKB> kb;

    public:
	SDL_Wrap*   psdlw;
	Keyboard*   pkb;

    public:
	rt set(EC& pec);

};

#endif

