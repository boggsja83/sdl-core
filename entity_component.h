#ifndef ENTITY_COMPONENT_H
#define ENTITY_COMPONENT_H

#include "types.h"
#include <SDL_rect.h>

typedef struct EC {
    i16 oid;
    CM_MASK cm;

    EC(i16 own_id=-1, CM_MASK pcm=CM_NULL){
	oid = own_id;
	cm = pcm;
    }
} EC;

typedef struct cPos : EC{
    float x;
    float y;
    float w;
    float h;

    cPos(i16 own_id=-1, float px=-1.f, float py=-1.f, float pw=-1.f, float ph=-1.f){
	oid = own_id;
	cm = CM_POS;
	x = px;
	y = py;
	w = pw;
	h = ph;
    }
} cPos;

typedef struct cRendPos : EC{
    float x;
    float y;
    float w;
    float h;

    cRendPos(i16 own_id=-1, float px=-1.f, float py=-1.f, float pw=-1.f, float ph=-1.f){
	oid = own_id;
	cm = CM_RENDPOS;
	x = px;
	y = py;
	w = pw;
	h = ph;
    }
} cRendPos;

typedef struct cVel : EC{
    float x;
    float y;

    cVel(i16 own_id=-1, float px=0.f, float py=0.f){
	oid = own_id;
	cm = CM_VEL;
	x = px;
	y = py;
    }
} cVel;

typedef struct cTexture : EC {
    i16 rend_i;
    i16 text_i;
    SDL_Rect src;

    cTexture(i16 own_id=-1, i16 prend_i=-1, i16 ptext_i=-1, SDL_Rect psrc=SDL_Rect()){
	oid = own_id;
	cm = CM_TEXTURE;
	rend_i = prend_i;
	text_i = ptext_i;
	src = psrc;
    }
} cTexture;

typedef struct cKB: EC {

    cKB(i16 own_id=-1){
	oid = own_id;
	cm = CM_KB;
    }
} cKB;

#endif

