#include "entity_manager.h"
#include "entity_component.h"
#include "types.h"

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

    return OKAY;
}

rt EntityManager::set(EC& pec){

    if(pec.oid>=0 && pec.oid<ents.size()){
	switch(pec.cm){
	    case  CM_POS:
		if(ents[pec.oid]& CM_POS){
		    pos[pec.oid].x = static_cast<cPos*>(&pec)->x;
		    pos[pec.oid].y = static_cast<cPos*>(&pec)->y;
		    pos[pec.oid].w = static_cast<cPos*>(&pec)->w;
		    pos[pec.oid].h = static_cast<cPos*>(&pec)->h;
		}
		else return ECS_LACKS_COMP;
		break;
	    case  CM_RENDPOS:
		if(ents[pec.oid]& CM_RENDPOS){
		    rendpos[pec.oid].x = static_cast<cRendPos*>(&pec)->x;
		    rendpos[pec.oid].y = static_cast<cRendPos*>(&pec)->y;
		    rendpos[pec.oid].w = static_cast<cRendPos*>(&pec)->w;
		    rendpos[pec.oid].h = static_cast<cRendPos*>(&pec)->h;
		}
		else return ECS_LACKS_COMP;
		break;
	    case  CM_VEL:
		if(ents[pec.oid]& CM_VEL){
		    vel[pec.oid].x = static_cast<cVel*>(&pec)->x;
		    vel[pec.oid].y = static_cast<cVel*>(&pec)->y;
		} else return ECS_LACKS_COMP;
		break;
	    case  CM_TEXTURE:
		if(ents[pec.oid]& CM_TEXTURE){
		    texture[pec.oid].rend_i = static_cast<cTexture*>(&pec)->rend_i;
		    texture[pec.oid].text_i = static_cast<cTexture*>(&pec)->text_i;
		    texture[pec.oid].src = static_cast<cTexture*>(&pec)->src;
		}
		else return ECS_LACKS_COMP;
		break;
	    case  CM_KB:

		break;
	    default:
		return ECS_INVALID_COMP;
	}
    } else return ECS_INVALID_ID;
    return OKAY;
}

