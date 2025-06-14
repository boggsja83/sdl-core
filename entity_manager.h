#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "entity.h"
#include "component.h"

class EntityManager{
    public:
	EntityManager(){}
	~EntityManager() {}

    public:
	std::vector<Entity> entities;
	std::vector<cPosition> comp_pos;
};

#endif

