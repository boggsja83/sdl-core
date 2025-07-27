#include "entity_manager.h"
#include "entity_component.h"
#include "types.h"

rt EntityManager::add_entity(ui64 comp_mask){

    i16 temp_id = ents.size();
    ui8 sz = 5;



    if(!temp_id){
	// zero entities at this point
	pos.resize(sz);
	rendpos.resize(sz);
	vel.resize(sz);
	texture.resize(sz);
	kb.resize(sz);
	fps.resize(sz);
	colx.resize(sz);
    }
    else
	if(pos.size()<=temp_id || rendpos.size()<=temp_id || vel.size()<=temp_id || 
		texture.size()<=temp_id || kb.size()<=temp_id || fps.size()<=temp_id) {
	    pos.resize(temp_id*2);
	    rendpos.resize(temp_id*2);
	    vel.resize(temp_id*2);
	    texture.resize(temp_id*2);
	    kb.resize(temp_id*2);
	    fps.resize(temp_id*2);
	    colx.resize(temp_id*2);
	}




    ents.push_back(comp_mask);

    if(comp_mask & CM_POS) pos[temp_id] = cPos();
    if(comp_mask & CM_RENDPOS) rendpos[temp_id] = cRendPos();
    if(comp_mask & CM_VEL) vel[temp_id] = cVel();
    if(comp_mask & CM_TEXTURE) texture[temp_id] = cTexture();
    if(comp_mask & CM_KB) kb[temp_id] = cKB();
    if(comp_mask & CM_FPS) fps[temp_id] = cFPS();
    if(comp_mask & CM_COLX) colx[temp_id] = cColx();


    return ents.size()-1;
}

rt EntityManager::set(EC& pec){

    if(pec.own_i>=0 && pec.own_i<ents.size()){
	switch(pec.cm){
	    case  CM_POS:
		if(ents[pec.own_i] & CM_POS){
		    pos[pec.own_i].x = static_cast<cPos*>(&pec)->x;
		    pos[pec.own_i].y = static_cast<cPos*>(&pec)->y;
		    pos[pec.own_i].w = static_cast<cPos*>(&pec)->w;
		    pos[pec.own_i].h = static_cast<cPos*>(&pec)->h;
		}
		else return ECS_LACKS_COMP;
		break;
	    case  CM_RENDPOS:
		if(ents[pec.own_i] & CM_RENDPOS){
		    rendpos[pec.own_i].x = static_cast<cRendPos*>(&pec)->x;
		    rendpos[pec.own_i].y = static_cast<cRendPos*>(&pec)->y;
		    rendpos[pec.own_i].w = static_cast<cRendPos*>(&pec)->w;
		    rendpos[pec.own_i].h = static_cast<cRendPos*>(&pec)->h;
		}
		else return ECS_LACKS_COMP;
		break;
	    case  CM_VEL:
		if(ents[pec.own_i] & CM_VEL){
		    vel[pec.own_i].mov_x = static_cast<cVel*>(&pec)->mov_x;
		    vel[pec.own_i].mov_y = static_cast<cVel*>(&pec)->mov_y;
		    vel[pec.own_i].const_x = static_cast<cVel*>(&pec)->const_x;
		    vel[pec.own_i].const_y = static_cast<cVel*>(&pec)->const_y;
		    vel[pec.own_i].cur_x = static_cast<cVel*>(&pec)->cur_x;
		    vel[pec.own_i].cur_y = static_cast<cVel*>(&pec)->cur_y;
		} else return ECS_LACKS_COMP;
		break;
	    case  CM_TEXTURE:
		if(ents[pec.own_i] & CM_TEXTURE){
		    texture[pec.own_i].rend = static_cast<cTexture*>(&pec)->rend;
		    texture[pec.own_i].texture = static_cast<cTexture*>(&pec)->texture;
		    texture[pec.own_i].src = static_cast<cTexture*>(&pec)->src;
		}
		else return ECS_LACKS_COMP;
		break;
	    case  CM_KB:
		if(ents[pec.own_i] & CM_KB){
		    kb[pec.own_i].acts.resize(static_cast<cKB*>(&pec)->acts.size());
		    for(i16 i=0; i<static_cast<cKB*>(&pec)->acts.size(); ++i){
			kb[pec.own_i].acts[i] = static_cast<cKB*>(&pec)->acts[i];
		    }
		}
		else return ECS_LACKS_COMP;
		break;
	    case CM_FPS:
		if(ents[pec.own_i] & CM_FPS){
		    fps[pec.own_i].counts.resize(static_cast<cFPS*>(&pec)->counts.size());
		    for(i16 i=0;i<fps[pec.own_i].counts.size();++i){
			fps[pec.own_i].counts[i].timespan = static_cast<cFPS*>(&pec)->counts[i].timespan;
			fps[pec.own_i].counts[i].start_time = static_cast<cFPS*>(&pec)->counts[i].start_time;
			fps[pec.own_i].counts[i].stop_time = static_cast<cFPS*>(&pec)->counts[i].stop_time;
			fps[pec.own_i].counts[i].start_frame = static_cast<cFPS*>(&pec)->counts[i].start_frame;
			fps[pec.own_i].counts[i].stop_frame = static_cast<cFPS*>(&pec)->counts[i].stop_frame;
			fps[pec.own_i].counts[i].frame_type = static_cast<cFPS*>(&pec)->counts[i].frame_type;
			fps[pec.own_i].counts[i].last_fps = static_cast<cFPS*>(&pec)->counts[i].last_fps;

		    }
		}
		else return ECS_LACKS_COMP;
		break;
	    case CM_COLX:
		if(ents[pec.own_i] & CM_COLX){
		    colx[pec.own_i].clip = static_cast<cColx*>(&pec)->clip;
		    colx[pec.own_i].radius = static_cast<cColx*>(&pec)->radius;
		    colx[pec.own_i].shape = static_cast<cColx*>(&pec)->shape;
		}
		else return ECS_LACKS_COMP;
		break;



	    default:
		return ECS_INVALID_COMP;
	}
    } else return ECS_INVALID_ID;

    return OKAY;
}

