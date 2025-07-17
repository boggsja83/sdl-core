#ifndef ENTITY_COMPONENT_H
#define ENTITY_COMPONENT_H

#include "types.h"
#include <SDL_rect.h>
#include <SDL_scancode.h>
#include <vector>

typedef struct EC {
    i16 oid;
    CM_MASK cm;

    EC(i16 pid=-1, CM_MASK pcm=CM_NULL){
	oid = pid;
	cm = pcm;
    }
} EC;

typedef struct cPos : EC{
    float x;
    float y;
    float w;
    float h;

    cPos(i16 pid=-1, float px=-1.f, float py=-1.f, float pw=-1.f, float ph=-1.f){
	oid = pid;
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

    cRendPos(i16 pid=-1, float px=-1.f, float py=-1.f, float pw=-1.f, float ph=-1.f){
	oid = pid;
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
    float const_x;
    float const_y;

    cVel(i16 pid=-1, float px=0.f, float py=0.f, float pcx=0.f, float pcy=0.f){
	oid = pid;
	cm = CM_VEL;
	x = px;
	y = py;
	const_x = pcx;
	const_y = pcy;
    }
} cVel;

typedef struct cTexture : EC {
    i16 rend_i;
    i16 text_i;
    SDL_Rect src;

    cTexture(i16 pid=-1, i16 prend_i=-1, i16 ptext_i=-1, SDL_Rect psrc=SDL_Rect()){
	oid = pid;
	cm = CM_TEXTURE;
	rend_i = prend_i;
	text_i = ptext_i;
	src = psrc;
    }
} cTexture;

typedef struct cKB : EC {
    std::vector<KB_ACTION> acts;

    cKB(i16 pid=-1){
	oid = pid;
	cm = CM_KB;

	acts.clear();
    }
} cKB;

// typedef struct cTest: EC {
//
//     cTest(i16 pid=-1){
// 	oid = pid;
// 	cm = CM_TEST;
//     }
// } cTest;

#endif

