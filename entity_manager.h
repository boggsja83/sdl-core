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
	    pos.resize(5);
	    vel.resize(5);
	    rendpos.resize(5);
	}
	~EntityManager(){
	    std::cerr << "Entities count: " << entities.size() << std::endl;
	    for(int i=0; i<entities.size(); ++i){
		if((entities[i]&(CM_POS|CM_VEL))==(CM_POS|CM_VEL)){
		    std::cerr << "ent[" <<i<<"] x: " << pos[i].x << " y: " << pos[i].y << std::endl;
		    if(entities[i]&CM_RENDPOS){
			std::cerr<<"rendpos_x: "<<rendpos[i].x<<" rendpos_y: " <<rendpos[i].y<<std::endl;
		    }
		    else { std::cerr<<"-No CM_RENDPOS"<<std::endl; }
		}

	    }
	}
    public:
	rt add_entity(uint64_t);
    public:
	std::vector<uint64_t> entities;
	std::vector<cPos> pos;
	std::vector<cVel> vel;
	std::vector<cRendPos> rendpos;
    public:
	rt set_pos(i16, float, float, float, float);
	rt set_vel(i16, float, float);
	rt set_rendpos(i16, float, float, float, float);
};

#endif

