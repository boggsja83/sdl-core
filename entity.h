#ifndef ENTITY_H
#define ENTITY_H

#include <cstdint>
#include <vector>

#include "types.h"
#include "component.h"

struct Entity {
    Entity(ENTITY_TYPE t=ENTITY_DEFAULT){
	type = t;
	ID = -1;
	components.clear();
    }

    ENTITY_TYPE type;
    int16_t ID;
    std::vector<COMPONENT_TYPE> components;


};

struct Scene : Entity {
    Scene(){
	type = ENTITY_SCENE;

	components.push_back(COMPONENT_POSITION);
    }
};


#endif

