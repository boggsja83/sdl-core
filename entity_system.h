#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H

#include "entity_manager.h"
#include "types.h"
#include "settings.h"

struct ECS{ virtual rt update(EntityManager&, float) = 0; };

struct ECSLogicTransform : ECS {
    rt update(EntityManager& em, float dft) override {
	for(i16 i=0; i<em.entities.size(); ++i){
	    if((em.entities[i] & (CM_POS|CM_VEL))==(CM_POS|CM_VEL)){
		em.pos[i].x = em.pos[i].x + em.vel[i].x * dft;
		em.pos[i].y = em.pos[i].y + em.vel[i].y * dft;
	    }
	}
	return OKAY;
    }
};

struct ECSRendTransform : ECS {
    rt update(EntityManager& em, float alpha) override {
	for(i16 i=0; i<em.entities.size(); ++i){
	    if((em.entities[i] & (CM_RENDPOS|CM_POS))==(CM_RENDPOS|CM_POS)){
		if(em.entities[i] & CM_VEL){
		    em.rendpos[i].x = em.pos[i].x + em.vel[i].x * alpha * FIXED_LOGIC_TS;
		    em.rendpos[i].y = em.pos[i].y + em.vel[i].y * alpha * FIXED_LOGIC_TS;
		}
		else{
		    em.rendpos[i].x = em.pos[i].x;
		    em.rendpos[i].y = em.pos[i].y;
		}
		em.rendpos[i].w = em.pos[i].w;
		em.rendpos[i].h = em.pos[i].h;
	    }
	}
	return OKAY;
    }
};

#endif

