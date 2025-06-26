#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H

#include <SDL_render.h>
#include "entity_manager.h"
#include "types.h"
#include "settings.h"

typedef struct ECS{ virtual rt update(EntityManager& em, float dtf) = 0; } ECS;

typedef struct ECSLogicTransform : ECS {
    rt update(EntityManager& em, float dft) override {
	for(i16 i=0; i<em.ents.size(); ++i){
	    if((em.ents[i] & (CM_POS|CM_VEL))==(CM_POS|CM_VEL)){
		em.pos[i].x = em.pos[i].x + em.vel[i].x * dft;
		em.pos[i].y = em.pos[i].y + em.vel[i].y * dft;
	    }
	}
	return OKAY;
    }
} ECSLogicTransform;

typedef struct ECSRendTransform : ECS {
    rt update(EntityManager& em, float alpha) override {
	for(i16 i=0; i<em.ents.size(); ++i){
	    if((em.ents[i] & (CM_RENDPOS|CM_POS))==(CM_RENDPOS|CM_POS)){
		if(em.ents[i] & CM_VEL){
		    em.rendpos[i].x = em.pos[i].x + em.vel[i].x * alpha * FIXED_LOGIC_TS;
		    em.rendpos[i].y = em.pos[i].y + em.vel[i].y * alpha * FIXED_LOGIC_TS;
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
} ECSRendTransform;

typedef struct ECSRendTexture : ECS {
    rt update(EntityManager& em, float alpha=0.f) override {
	for(i16 i=0; i<em.ents.size(); ++i){
	    if((em.ents[i]&(CM_TEXTURE|CM_RENDPOS))==(CM_TEXTURE|CM_RENDPOS)){
		SDL_Renderer* tr = nullptr;
		SDL_Texture* tt = nullptr;
		i16 tri = em.texture[i].rend_i;
		i16 tti = em.texture[i].text_i;

		if(tri>=0 && tri<em.psdlw->renderers.size()) tr = em.psdlw->renderers[tri];	
		else return INVALID_RENDERER;
		
		if(tti>=0 && tti<em.psdlw->textures.size()) tt = em.psdlw->textures[tti];
		else return INVALID_TEXTURE;

		SDL_Rect* src = &em.texture[i].src;
		SDL_Rect dst = { 
		    static_cast<i32>(em.rendpos[i].x),
		    static_cast<i32>(em.rendpos[i].y),
		    static_cast<i32>(em.rendpos[i].w), 
		    static_cast<i32>(em.rendpos[i].h) 
		};

		SDL_RenderCopy(tr, tt, src, &dst);
	    }
	}
	return OKAY;
    }
} ECSRendTexture;

typedef struct ECSKB : ECS {
    rt update(EntityManager& em, float alpha=0.f) override {
	KB_ACTION tka = KB_NO_ACTION;
	SDL_Scancode tsc = SDL_SCANCODE_UNKNOWN;

	for(i16 o=0; o<em.ents.size(); ++o){
	    if(em.ents[o] & CM_KB){
		for(i16 i=0; i<em.kb[o].acts.size(); ++i){
		    tka = em.kb[o].acts[i];
		    tsc = em.pkb->map[tka];
		    if(em.pkb->keystate[tsc]){
			switch(tka){
			    case KB_NO_ACTION:
				std::cerr << "kb_no_action, somehow?" << std::endl;
				break;
			    case MOVE_N:
				std::cerr << "move N" << std::endl;
				break;
			    case MOVE_S:
				std::cerr << "move S" << std::endl;
				break;
			    case MOVE_E:
				std::cerr << "move E" << std::endl;
				break;
			    case MOVE_W:
				std::cerr << "move W" << std::endl;
				break;
			    default:
				std::cerr << "No binding set for SDL_Scancode: " << tsc << std::endl; 
				break;
			}
		    }
		    tka = KB_NO_ACTION;
		    tsc = SDL_SCANCODE_UNKNOWN;
		}
	    }
	}
	return OKAY;
    }
} ECSKB;

#endif
