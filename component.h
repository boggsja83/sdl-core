#ifndef COMPONENT_H
#define COMPONENT_H

#include "types.h"

struct Component {
    Component(COMPONENT_TYPE t=COMPONENT_DEFAULT){
	type = t;
	owner_id = -1; 
    }

    COMPONENT_TYPE type;
    int16_t owner_id;
};

struct cPosition : Component{
    cPosition(){
	type = COMPONENT_POSITION;
	x = -1;
	y = -1;
	w = -1;
	h = -1;
    }

    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
};

#endif

