#ifndef COMPONENT_H
#define COMPONENT_H

#include "types.h"

struct Component {
    Component(COMPONENT_TYPE t=COMPONENT_DEFAULT){
	type = t;
	OWNER_ID = -1; 
    }

    COMPONENT_TYPE type;
    int16_t OWNER_ID;
};

struct cPosition : Component{

};

#endif

