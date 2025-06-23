#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "component.h"
#include "types.h"
#include <cstdint>
#include <iostream>
#include <vector>

class EntityManager{
    public:
	EntityManager(){
	    entities.clear();
	    comp_pos.clear();
	}
	~EntityManager(){
	    std::cerr << "Entities count: " << entities.size() << std::endl;
	    for(int i=0; i<entities.size(); ++i){
		std::cerr << "Entity Component Mask: " << entities[i] << std::endl;

	    }
	    std::cerr << "comp_pos count: " << comp_pos.size() << std::endl;
	    for(int i=0; i<comp_pos.size(); ++i){
		std::cerr << "Component Owner ID: " << comp_pos[i].owner_id << std::endl;
		std::cerr << "x: " << comp_pos[i].x 
		    << " y: " << comp_pos[i].y
		    << " w: " << comp_pos[i].w
		    << " h: " << comp_pos[i].h
		    << std::endl;
	    }
	}

    public:
	std::vector<uint64_t> entities;
	std::vector<cPos> comp_pos;

    public:
	rt add_entity(uint64_t);
};

#endif

