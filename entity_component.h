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

    cPos(i16 own_id=-1, float px=-1.0f, float py=-1.0f, float pw=-1.0f, float ph=-1.0f){
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

    cRendPos(i16 own_id=-1, float px=-1.0f, float py=-1.0f, float pw=-1.0f, float ph=-1.0f){
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

    cVel(i16 own_id=-1, float px=-1.0f, float py=-1.0f){
	owner_id = own_id;
	x = px;
	y = py;
    }
};

#endif

