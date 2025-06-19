#include "entity_manager.h"
#include "entity_component.h"
#include "types.h"
/******************************************************************************/
rt EntityManager::add_entity(ui64 comp_mask){
/******************************************************************************/
    i16 temp_id = ents.size();

    ents.push_back(comp_mask);

    if(comp_mask & CM_POS){
	if(pos.size() <= temp_id) { pos.resize(pos.size()*2+1); } // add 1 in case size is 0
	pos[temp_id] = cPos();
    }

    if(comp_mask & CM_RENDPOS){
	if(rendpos.size() <= temp_id) { rendpos.resize(rendpos.size()*2+1); } // add 1 in case size is 0
	rendpos[temp_id] = cRendPos();
    }

    if(comp_mask & CM_VEL){
	if(vel.size() <= temp_id) { vel.resize(vel.size()*2+1); } // add 1 in case size is 0
	vel[temp_id] = cVel();
    }

    if(comp_mask & CM_TEXTURE){
	if(texture.size() <= temp_id) { texture.resize(texture.size()*2+1); } // add 1 in case size is 0
	texture[temp_id] = cTexture();
    }

    return OKAY;
}
/******************************************************************************/
rt EntityManager::set(EC& pec){
    /******************************************************************************/
    if(pec.owner_id>=0 && pec.owner_id<ents.size()){
	switch(pec.cm){
	    case CM_POS:
		if(ents[pec.owner_id]&CM_POS){
		    pos[pec.owner_id].x = static_cast<cPos*>(&pec)->x;
		    pos[pec.owner_id].y = static_cast<cPos*>(&pec)->y;
		    pos[pec.owner_id].w = static_cast<cPos*>(&pec)->w;
		    pos[pec.owner_id].h = static_cast<cPos*>(&pec)->h;
		}
		else { return ECS_LACKS_COMP; }
		break;
	    case CM_RENDPOS:
		if(ents[pec.owner_id]&CM_RENDPOS){
		    rendpos[pec.owner_id].x = static_cast<cRendPos*>(&pec)->x;
		    rendpos[pec.owner_id].y = static_cast<cRendPos*>(&pec)->y;
		    rendpos[pec.owner_id].w = static_cast<cRendPos*>(&pec)->w;
		    rendpos[pec.owner_id].h = static_cast<cRendPos*>(&pec)->h;
		}
		else{ return ECS_LACKS_COMP; }
		break;
	    case CM_VEL:
		if(ents[pec.owner_id]&CM_VEL){
		    vel[pec.owner_id].x = static_cast<cVel*>(&pec)->x;
		    vel[pec.owner_id].y = static_cast<cVel*>(&pec)->y;
		} else { return ECS_LACKS_COMP; }
		break;
	    case CM_TEXTURE:
		if(ents[pec.owner_id]&CM_TEXTURE){
		    texture[pec.owner_id].renderer_index = static_cast<cTexture*>(&pec)->renderer_index;
		    texture[pec.owner_id].texture_index = static_cast<cTexture*>(&pec)->texture_index;
		}
		else { return ECS_LACKS_COMP; }
		break;
	    default:
		return ECS_INVALID_COMP;
	}
    } else { return ECS_INVALID_ID; }
    return OKAY;
}
/******************************************************************************/
// rt EntityManager::set(PP pp){
// /******************************************************************************/
//     if(pp.owner_id>=0 && pp.owner_id<ents.size()){
// 	switch(pp.cm){
// 	    case CM_POS:
// 		if(ents[pp.owner_id]&CM_POS){
// 		    pos[pp.owner_id].x = static_cast<PP_pos*>(&pp)->x;
// 		    pos[pp.owner_id].y = static_cast<PP_pos*>(&pp)->y;
// 		    pos[pp.owner_id].w = static_cast<PP_pos*>(&pp)->w;
// 		    pos[pp.owner_id].h = static_cast<PP_pos*>(&pp)->h;
// 		}
// 		else{ return ECS_LACKS_COMP; }
// 		break;
// 	    case CM_RENDPOS:
// 		if(ents[pp.owner_id]&CM_RENDPOS){
// 		    pos[pp.owner_id].x = static_cast<PP_rendpos*>(&pp)->x;
// 		    pos[pp.owner_id].y = static_cast<PP_rendpos*>(&pp)->y;
// 		    pos[pp.owner_id].w = static_cast<PP_rendpos*>(&pp)->w;
// 		    pos[pp.owner_id].h = static_cast<PP_rendpos*>(&pp)->h;
// 		}
// 		else { return ECS_LACKS_COMP; }
// 		break;
// 	    default:
// 		return ECS_INVALID_COMP;
// 	}
//     } else return ECS_INVALID_ID;
//     return OKAY;
// }
// /******************************************************************************/
// rt EntityManager::set_pos(i16 own_id, float px, float py, float pw, float ph){
// /******************************************************************************/
//     if(own_id>=0 && own_id<ents.size()){
// 	if(ents[own_id] & CM_POS){
// 	    pos[own_id].x = px; 
// 	    pos[own_id].y = py; 
// 	    pos[own_id].w = pw; 
// 	    pos[own_id].h = ph; 
// 	}
// 	else { return ECS_LACKS_COMP; }
//     }
//     else { return ECS_INVALID_ID; }
//
//     return OKAY;
// }
// /******************************************************************************/
// rt EntityManager::set_rendpos(i16 own_id, float px, float py, float pw, float ph){
// /******************************************************************************/
//     if(own_id>=0 && own_id<ents.size()){
// 	if(ents[own_id] & CM_RENDPOS){
// 	    rendpos[own_id].x = px; 
// 	    rendpos[own_id].y = py; 
// 	    rendpos[own_id].w = pw; 
// 	    rendpos[own_id].h = ph; 
// 	}
// 	else { return ECS_LACKS_COMP; }
//     }
//     else { return ECS_INVALID_ID; }
//
//     return OKAY;
// }
// /******************************************************************************/
// rt EntityManager::set_vel(i16 own_id, float px, float py){
// /******************************************************************************/
//     if(own_id>=0 && own_id<ents.size()){
// 	if(ents[own_id] & CM_VEL){
// 	    vel[own_id].x = px;
// 	    vel[own_id].y = py;
// 	}
// 	else { return ECS_LACKS_COMP; }
//     }
//     else { return ECS_INVALID_ID; }
//
//     return OKAY;
// }
// /******************************************************************************/
// rt EntityManager::set_texture(i16 own_id, i16 renderer_index, i16 texture_index){
// /******************************************************************************/
//     if(own_id>=0 && own_id<ents.size()){
// 	if(ents[own_id] & CM_TEXTURE){
// 	}
// 	else { return ECS_LACKS_COMP; }
//     }
//     else { return ECS_INVALID_ID; }
//
//     return OKAY;
// }
// /******************************************************************************/
