#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H

#include "entity_manager.h"
#include "types.h"
#include "settings.h"

struct ECS{ virtual rt update(EntityManager&, float) = 0; };

struct ECSLogicTransform : ECS {
    rt update(EntityManager& em, float dt) override {
	for(i16 i=0; i<em.entities.size(); ++i){
	    if((em.entities[i] & (CM_POS|CM_VEL))==(CM_POS|CM_VEL)){
		em.comps_pos[i].x = em.comps_pos[i].x + em.comps_vel[i].x * dt;
		em.comps_pos[i].y = em.comps_pos[i].y + em.comps_vel[i].y * dt;
	    }
	}
	return OKAY;
    }
};

struct ECSRendTransform : ECS {
    rt update(EntityManager& em, float alpha) override {
	for(i16 i=0; i<em.entities.size(); ++i){
	    if((em.entities[i] & (CM_RENDPOS|CM_POS))==(CM_RENDPOS|CM_POS)){
	    std::cerr<<"ECSRendTransform["<<i<<"]: ";
		if(em.entities[i] & CM_VEL){
		    std::cerr<<"has CM_VEL" << std::endl;
		    em.comps_pos[i].x = em.comps_pos[i].x + em.comps_vel[i].x * alpha * FIXED_LOGIC_TS;
		    em.comps_pos[i].y = em.comps_pos[i].y + em.comps_vel[i].y * alpha * FIXED_LOGIC_TS;
		}
		else{
		    std::cerr<<"does not have CM_VEL" << std::endl;
		    em.comps_rendpos[i].x = em.comps_pos[i].x;
		    em.comps_rendpos[i].y = em.comps_pos[i].y;
		}
		em.comps_rendpos[i].w = em.comps_pos[i].w;
		em.comps_rendpos[i].h = em.comps_pos[i].h;
	    }
	}
	return OKAY;
    }
};

#endif

