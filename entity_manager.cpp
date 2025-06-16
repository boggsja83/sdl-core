#include "entity_manager.h"
#include "types.h"

rt EntityManager::add_entity(uint64_t comp_mask){
    int16_t temp_id = entities.size();

    entities.push_back(comp_mask);

    if(comp_mask & CM_POS){
	if(comps_pos.size() <= temp_id) { comps_pos.resize(comps_pos.size()*2+1); } // add 1 in case size is 0
	comps_pos[temp_id] = cPos(temp_id);
    }

    if(comp_mask & CM_VEL){
	if(comps_vel.size() <= temp_id) { comps_vel.resize(comps_vel.size()*2+1); } // add 1 in case size is 0
	comps_vel[temp_id] = cVel(temp_id);
    }

    return OKAY;
}

