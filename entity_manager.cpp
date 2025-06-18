#include "entity_manager.h"
#include "entity_component.h"
#include "types.h"

rt EntityManager::add_entity(uint64_t comp_mask){
    i16 temp_id = entities.size();

    entities.push_back(comp_mask);

    if(comp_mask & CM_POS){
	if(pos.size() <= temp_id) { pos.resize(pos.size()*2+1); } // add 1 in case size is 0
	pos[temp_id] = cPos(temp_id);
    }

    if(comp_mask & CM_VEL){
	if(vel.size() <= temp_id) { vel.resize(vel.size()*2+1); } // add 1 in case size is 0
	vel[temp_id] = cVel(temp_id);
    }

    return OKAY;
}

rt EntityManager::set_pos(i16 own_id, float px, float py, float pw, float ph){
    if(own_id>=0 && own_id<entities.size()){
	if(entities[own_id] & CM_POS){
	   pos[own_id].x = px; 
	   pos[own_id].y = py; 
	   pos[own_id].w = pw; 
	   pos[own_id].h = ph; 
	}
	else { return ENTITY_LACKS_COMPONENT; }
    }
    else { return ENTITY_INVALID_ID; }

    return OKAY;
}

rt EntityManager::set_rendpos(i16 own_id, float px, float py, float pw, float ph){
    if(own_id>=0 && own_id<entities.size()){
	if(entities[own_id] & CM_RENDPOS){
	   rendpos[own_id].x = px; 
	   rendpos[own_id].y = py; 
	   rendpos[own_id].w = pw; 
	   rendpos[own_id].h = ph; 
	}
	else { return ENTITY_LACKS_COMPONENT; }
    }
    else { return ENTITY_INVALID_ID; }

    return OKAY;
}

rt EntityManager::set_vel(i16 own_id, float px, float py){
    if(own_id>=0 && own_id<entities.size()){
	if(entities[own_id] & CM_VEL){
	    vel[own_id].x = px;
	    vel[own_id].y = py;
	}
	else { return ENTITY_LACKS_COMPONENT; }
    }
    else { return ENTITY_INVALID_ID; }

    return OKAY;
}

