#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "entity_component.h"
#include "types.h"
#include <cstdint>
#include <iostream>
#include <vector>

class EntityManager{
    public:
	EntityManager(){
	    entities.clear();

	    // probably best to resize these initially vs. clear() [makes size=0]
	    // comps_pos.clear();
	    // comps_vel.clear();
	    comps_pos.resize(5);
	    comps_vel.resize(5);
	}
	~EntityManager(){
	    std::cerr << "Entities count: " << entities.size() << std::endl;
	    for(int i=0; i<entities.size(); ++i){
		std::cerr << "Entity Component Mask: " << entities[i] << std::endl;
	    }
	    std::cerr << "comp_pos count: " << comps_pos.size() << std::endl;
	    for(int i=0; i<comps_pos.size(); ++i){
		if(comps_pos[i].owner_id>-1){
		    std::cerr << "Component["<<i<<"] Owner ID: " << comps_pos[i].owner_id << std::endl;
		}
	    }
	    std::cerr << "comp_vel count: " << comps_vel.size() << std::endl;
	    for(int i=0; i<comps_vel.size(); ++i){
		if(comps_vel[i].owner_id>-1){
		    std::cerr << "Component["<<i<<"] Owner ID: " << comps_vel[i].owner_id << std::endl;
		    //std::cerr << "x = " << comps_vel[i].x << " y = " << comps_vel[i].y << std::endl;
		}
	    }
	}

    public:
	std::vector<uint64_t> entities;
	std::vector<cPos> comps_pos;
	std::vector<cVel> comps_vel;

    public:
	rt add_entity(uint64_t);
};

#endif

