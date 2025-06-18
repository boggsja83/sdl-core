#ifndef ENTITY_COMPONENT_H
#define ENTITY_COMPONENT_H

#include "types.h"

struct EntityComponent {
    EntityComponent(i16 comp_id = -1){
	owner_id = comp_id; 
    }
    i16 owner_id;
};

struct cPos : EntityComponent{
    float x;
    float y;
    float w;
    float h;

    cPos(i16 own_id=-1, float px=-1.f, float py=-1.f, float pw=-1.f, float ph=-1.f){
	owner_id = own_id;
	x = px;
	y = py;
	w = pw;
	h = ph;
    }
};

struct cRendPos : EntityComponent{
    float x;
    float y;
    float w;
    float h;

    cRendPos(i16 own_id=-1, float px=-1.f, float py=-1.f, float pw=-1.f, float ph=-1.f){
	owner_id = own_id;
	x = px;
	y = py;
	w = pw;
	h = ph;
    }
};

struct cVel : EntityComponent{
    float x;
    float y;

    cVel(i16 own_id=-1, float px=0.f, float py=0.f){
	owner_id = own_id;
	x = px;
	y = py;
    }
};

#endif

