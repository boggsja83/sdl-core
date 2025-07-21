#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H

#include <SDL_render.h>
#include "entity_manager.h"
#include "types.h"
//#include "settings.h"

typedef struct ECS{ virtual rt update(EntityManager& em, float dtf) = 0; } ECS;

typedef struct ECSpos : ECS {
    rt update(EntityManager& em, float dft) override {
	for(i16 i=0; i<em.ents.size(); ++i){
	    if((em.ents[i] & (CM_POS|CM_VEL))==(CM_POS|CM_VEL)){
		em.pos[i].x = em.pos[i].x + em.vel[i].mov_x * dft;
		em.pos[i].y = em.pos[i].y + em.vel[i].mov_y * dft;
	    }
	}
	return OKAY;
    }
} ECSpos;

typedef struct ECSrendpos : ECS {
    rt update(EntityManager& em, float alpha) override {
	for(i16 i=0; i<em.ents.size(); ++i){
	    if((em.ents[i] & (CM_RENDPOS|CM_POS))==(CM_RENDPOS|CM_POS)){
		if(em.ents[i] & CM_VEL){
		    em.rendpos[i].x = em.pos[i].x + em.vel[i].mov_x * alpha * em.conf_ptr->logic_ts;
		    em.rendpos[i].y = em.pos[i].y + em.vel[i].mov_y * alpha * em.conf_ptr->logic_ts;
		}
		else{
		    em.rendpos[i].x = em.pos[i].x;
		    em.rendpos[i].y = em.pos[i].y;
		}
		em.rendpos[i].w = em.pos[i].w;
		em.rendpos[i].h = em.pos[i].h;
	    }
	}
	return OKAY;
    }
} ECSrendpos;

typedef struct ECStexture : ECS {
    rt update(EntityManager& em, float alpha=0.f) override {
	for(i16 i=0; i<em.ents.size(); ++i){
	    if((em.ents[i]&(CM_TEXTURE|CM_RENDPOS))==(CM_TEXTURE|CM_RENDPOS)){
		SDL_Renderer* tr = em.texture[i].rend;
		SDL_Texture* tt = em.texture[i].texture;
		// i16 tri = em.texture[i].rend;
		// i16 tti = em.texture[i].texture;

		// if(tri>=0 && tri<em.psdlw->renderers.size()) tr = em.psdlw->renderers[tri];	
		// else return INVALID_RENDERER;

		// if(tti>=0 && tti<em.psdlw->textures.size()) tt = em.psdlw->textures[tti];
		// else return INVALID_TEXTURE;

		SDL_Rect src = em.texture[i].src;
		SDL_Rect dst = { 
		    static_cast<i32>(em.rendpos[i].x),
		    static_cast<i32>(em.rendpos[i].y),
		    static_cast<i32>(em.rendpos[i].w), 
		    static_cast<i32>(em.rendpos[i].h) 
		};

		SDL_RenderCopy(tr, tt, &src, &dst);
	    }
	}
	return OKAY;
    }
} ECStexture;

// i should rewrite this function so that it doesnt loop through
// all of the entities. just work on the component vector irself
// same for all functions in this file
// AckTUaLLY, there will always be less entites (or =) than components,
// so loop through entities is better
typedef struct ECSkb : ECS {
    rt update(EntityManager& em, float alpha=0.f) override {
	KB_ACTION tka = KB_INVALID_ACTION;
	SDL_Scancode tsc = SDL_SCANCODE_UNKNOWN;

	rt r = OKAY;
	float tf = 0.f;

	float PLAYER_VEL = 250.f;	

	for(i16 o=0; o<em.ents.size(); ++o){
	    if(em.ents[o] & CM_KB){
		for(i16 i=0; i<em.kb[o].acts.size(); ++i){
		    tka = em.kb[o].acts[i];
		    tsc = em.kb_ptr->map[tka];
		    if(em.kb_ptr->keystate[tsc]){
			// key down actions
			// assumes entity has CM_VEL, may error check this in future
			switch(tka){
			    case MOVE_N:
				if(em.kb_ptr->keystate[em.kb_ptr->map[MOVE_S]]) em.vel[o].mov_y=0;
				else em.vel[o].mov_y = -1.f*PLAYER_VEL;
				break;
			    case MOVE_S:
				if(em.kb_ptr->keystate[em.kb_ptr->map[MOVE_N]]) em.vel[o].mov_y=0;
				else em.vel[o].mov_y = PLAYER_VEL;
				break;
			    case MOVE_E:
				if(em.kb_ptr->keystate[em.kb_ptr->map[MOVE_W]]) em.vel[o].mov_x=0;
				else em.vel[o].mov_x = PLAYER_VEL;
				break;
			    case MOVE_W:
				if(em.kb_ptr->keystate[em.kb_ptr->map[MOVE_E]]) em.vel[o].mov_x=0;
				else em.vel[o].mov_x = -1.f*PLAYER_VEL;
				break;
			    case TEST_ACTION:
				//need to experiment more with method a and method b and perhaps others 7-4-25
				//method a
				//if(em.pkb->is_held(TEST_ACTION)<KB_THRESHOLD_PRESS) if(!Mix_Playing(0)) em.psdlw->play_channel(0, 0, 0);
				//if(em.pkb->is_held(TEST_ACTION)<KB_THRESHOLD_PRESS) em.psdlw->play_channel(0,0,0);

				// method b
				// tf = em.pkb->repeats(TEST_ACTION);
				// if(tf<1.f){ em.psdlw->play_channel(-1, 0, 0); }
				// std::cerr<<"repeats: " << tf << std::endl;
				
				// method c
				if(em.kb_ptr->first_press[tsc]){
				    //em.psdlw->play_channel(0,0,0);
				    em.sdlw_ptr->play_channel(-1,0,0);
				    em.kb_ptr->first_press[tsc]=false;
				}
				break;
			    case VOL_UP:
				r = Mix_VolumeMusic(-1);				
				Mix_VolumeMusic(r+1);
				break;
			    case VOL_DN:
				r = Mix_VolumeMusic(-1);				
				Mix_VolumeMusic(r-1);
				break;
			    default:
				break;
			}
		    }
		    else{
			switch(tka){
			    // key not-down actions - not a "on key up action" function.
			    // can only assume key is not pressed at this point
			    case MOVE_N:
				em.vel[o].mov_y = (em.vel[o].mov_y<0)?0:em.vel[o].mov_y;
				break;
			    case MOVE_S:
				em.vel[o].mov_y = (em.vel[o].mov_y>0)?0:em.vel[o].mov_y;
				break;
			    case MOVE_E:
				em.vel[o].mov_x = (em.vel[o].mov_x>0)?0:em.vel[o].mov_x;
				break;
			    case MOVE_W:
				em.vel[o].mov_x = (em.vel[o].mov_x<0)?0:em.vel[o].mov_x;
				break;
			    case TEST_ACTION:
				break;
			    default:
				break;
			}
		    }
		    // tka = KB_INVALID_ACTION;
		    // tsc = SDL_SCANCODE_UNKNOWN;
		}
	    }
	}
	return OKAY;
    }
} ECSkb;

#endif
