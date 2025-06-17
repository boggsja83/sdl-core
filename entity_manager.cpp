#include "entity_manager.h"
#include "entity_component.h"
#include "types.h"

rt EntityManager::add_entity(uint64_t comp_mask){
    i16 temp_id = entities.size();

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

rt EntityManager::set_pos(i16 own_id, float px, float py, float pw, float ph){
    if(own_id>=0 && own_id<entities.size()){
	if(entities[own_id] & CM_POS){
	   comps_pos[own_id].x = px; 
	   comps_pos[own_id].y = py; 
	   comps_pos[own_id].w = pw; 
	   comps_pos[own_id].h = ph; 
	}
	else { return ENTITY_LACKS_COMPONENT; }
    }
    else { return ENTITY_INVALID_ID; }

    return OKAY;
}

rt EntityManager::set_rendpos(i16 own_id, float px, float py, float pw, float ph){
    if(own_id>=0 && own_id<entities.size()){
	if(entities[own_id] & CM_RENDPOS){
	   comps_rendpos[own_id].x = px; 
	   comps_rendpos[own_id].y = py; 
	   comps_rendpos[own_id].w = pw; 
	   comps_rendpos[own_id].h = ph; 
	}
	else { return ENTITY_LACKS_COMPONENT; }
    }
    else { return ENTITY_INVALID_ID; }

    return OKAY;
}

rt EntityManager::set_vel(i16 own_id, float px, float py){
    if(own_id>=0 && own_id<entities.size()){
	if(entities[own_id] & CM_VEL){
	    comps_vel[own_id].x = px;
	    comps_vel[own_id].y = py;
	}
	else { return ENTITY_LACKS_COMPONENT; }
    }
    else { return ENTITY_INVALID_ID; }

    return OKAY;
}

