#include "entity_manager.h"

rt EntityManager::add_entity(ui64 comp_mask){

    i16 temp_id = ents.size();

    ents.push_back(comp_mask);

    if(comp_mask &  CM_POS){
	if(pos.size() <= temp_id) { pos.resize(pos.size()*2+1); } // add 1 in case size is 0
	pos[temp_id] = cPos();
    }

    if(comp_mask &  CM_RENDPOS){
	if(rendpos.size() <= temp_id) { rendpos.resize(rendpos.size()*2+1); } // add 1 in case size is 0
	rendpos[temp_id] = cRendPos();
    }

    if(comp_mask &  CM_VEL){
	if(vel.size() <= temp_id) { vel.resize(vel.size()*2+1); } // add 1 in case size is 0
	vel[temp_id] = cVel();
    }

    if(comp_mask &  CM_TEXTURE){
	if(texture.size() <= temp_id) { texture.resize(texture.size()*2+1); } // add 1 in case size is 0
	texture[temp_id] = cTexture();
    }

    if(comp_mask &  CM_KB){
	if(kb.size() <= temp_id) { kb.resize(kb.size()*2+1); } // add 1 in case size is 0
	kb[temp_id] = cKB();
    }

    return ents.size()-1;
}

rt EntityManager::set(EC& pec){

    if(pec.oid>=0 && pec.oid<ents.size()){
	switch(pec.cm){
	    case  CM_POS:
		if(ents[pec.oid] & CM_POS){
		    pos[pec.oid].x = static_cast<cPos*>(&pec)->x;
		    pos[pec.oid].y = static_cast<cPos*>(&pec)->y;
		    pos[pec.oid].w = static_cast<cPos*>(&pec)->w;
		    pos[pec.oid].h = static_cast<cPos*>(&pec)->h;
		}
		else return ECS_LACKS_COMP;
		break;
	    case  CM_RENDPOS:
		if(ents[pec.oid] & CM_RENDPOS){
		    rendpos[pec.oid].x = static_cast<cRendPos*>(&pec)->x;
		    rendpos[pec.oid].y = static_cast<cRendPos*>(&pec)->y;
		    rendpos[pec.oid].w = static_cast<cRendPos*>(&pec)->w;
		    rendpos[pec.oid].h = static_cast<cRendPos*>(&pec)->h;
		}
		else return ECS_LACKS_COMP;
		break;
	    case  CM_VEL:
		if(ents[pec.oid] & CM_VEL){
		    vel[pec.oid].mov_x = static_cast<cVel*>(&pec)->mov_x;
		    vel[pec.oid].mov_y = static_cast<cVel*>(&pec)->mov_y;
		    vel[pec.oid].const_x = static_cast<cVel*>(&pec)->const_x;
		    vel[pec.oid].const_y = static_cast<cVel*>(&pec)->const_y;
		    vel[pec.oid].cur_x = static_cast<cVel*>(&pec)->cur_x;
		    vel[pec.oid].cur_y = static_cast<cVel*>(&pec)->cur_y;
		} else return ECS_LACKS_COMP;
		break;
	    case  CM_TEXTURE:
		if(ents[pec.oid] & CM_TEXTURE){
		    texture[pec.oid].rend = static_cast<cTexture*>(&pec)->rend;
		    texture[pec.oid].texture = static_cast<cTexture*>(&pec)->texture;
		    texture[pec.oid].src = static_cast<cTexture*>(&pec)->src;
		}
		else return ECS_LACKS_COMP;
		break;
	    case  CM_KB:
		if(ents[pec.oid] & CM_KB){
		    kb[pec.oid].acts.resize(static_cast<cKB*>(&pec)->acts.size());
		    for(i16 i=0; i<static_cast<cKB*>(&pec)->acts.size(); ++i){
			kb[pec.oid].acts[i] = static_cast<cKB*>(&pec)->acts[i];
		    }
		}
		else return ECS_LACKS_COMP;
		break;
	    default:
		return ECS_INVALID_COMP;
	}
    } else return ECS_INVALID_ID;
    return OKAY;
}

