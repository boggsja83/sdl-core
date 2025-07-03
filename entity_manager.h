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
	    i16 s = 5;

	    ents.clear();
	    pos.resize(s);
	    vel.resize(s);
	    rendpos.resize(s);
	    texture.resize(s);
	    kb.resize(s);

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
	inline rt add_comp(i16 pid, CM_MASK pcmp){
	    if(pid>=0 && pid<ents.size()){
		
	    }
	    else { return ECS_INVALID_ID; }
	    return OKAY;
	}

	rt del_comp(i16 pid, CM_MASK pcmp);

    public:
	std::vector<ui64>	ents;
	std::vector<cPos>	pos;
	std::vector<cVel>	vel;
	std::vector<cRendPos>	rendpos;
	std::vector<cTexture>	texture;
	std::vector<cKB>	kb;

    public:
	SDL_Wrap*   psdlw;
	Keyboard*   pkb;

    public:
	rt set(EC& pec);

};

#endif

