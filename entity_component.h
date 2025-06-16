#ifndef ENTITY_COMPONENT_H
#define ENTITY_COMPONENT_H

#include "types.h"
#include <cstdint>

struct EntityComponent {
    EntityComponent(int16_t comp_id = -1){
	owner_id = comp_id; 
    }
    int16_t owner_id;
    virtual int16_t update() = 0;
};

struct cPos : EntityComponent{
    int16_t x;
    int16_t y;
    int16_t w;
    int16_t h;

    int16_t update() override {
    
	return OKAY;
    }

    cPos(int16_t own_id=-1, int16_t px=-1, int16_t py=-1, int16_t pw=-1, int16_t ph=-1){
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

    int16_t update() override {

	return OKAY;
    }

    cVel(int16_t own_id=-1, float px=-1.0f, float py=-1.0f){
	owner_id = own_id;
	x = px;
	y = py;
    }
};

#endif

