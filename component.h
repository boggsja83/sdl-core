#ifndef COMPONENT_H
#define COMPONENT_H

#include "types.h"
#include <iostream>

struct Component {
    Component(int16_t comp_id = -1){
	owner_id = comp_id; 
    }

    int16_t owner_id;
};

struct cPos : Component{
    int16_t x;
    int16_t y;
    int16_t w;
    int16_t h;

    cPos(int16_t own_id = -1, int16_t cx=-1, int16_t cy=-1, int16_t cw=-1, int16_t ch=-1){
	owner_id = own_id;
	x = cx;
	y = cy;
	w = cw;
	h = ch;
    }
};

#endif

