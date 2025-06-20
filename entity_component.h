#ifndef ENTITY_COMPONENT_H
#define ENTITY_COMPONENT_H
/******************************************************************************/
#include "types.h"
/******************************************************************************/
struct EC {
    EC(i16 own_id=-1, COMP_MASK pcm=CM_NULL){
	owner_id = own_id;
	cm = pcm;
    }
    i16 owner_id;
    COMP_MASK cm;
};
/******************************************************************************/
typedef struct cPos : EC{
/******************************************************************************/
    float x;
    float y;
    float w;
    float h;

    cPos(i16 own_id=-1, float px=-1.f, float py=-1.f, float pw=-1.f, float ph=-1.f){
	owner_id = own_id;
	cm = CM_POS;
	x = px;
	y = py;
	w = pw;
	h = ph;
    }
} cPos;
/******************************************************************************/
typedef struct cRendPos : EC{
/******************************************************************************/
    float x;
    float y;
    float w;
    float h;

    cRendPos(i16 own_id=-1, float px=-1.f, float py=-1.f, float pw=-1.f, float ph=-1.f){
	owner_id = own_id;
	cm = CM_RENDPOS;
	x = px;
	y = py;
	w = pw;
	h = ph;
    }
} cRendPos;
/******************************************************************************/
typedef struct cVel : EC{
/******************************************************************************/
    float x;
    float y;

    cVel(i16 own_id=-1, float px=0.f, float py=0.f){
	owner_id = own_id;
	cm = CM_VEL;
	x = px;
	y = py;
    }
} cVel;
/******************************************************************************/
typedef struct cTexture : EC {
/******************************************************************************/
    i16 renderer_index;
    i16 texture_index;

    cTexture(i16 own_id=-1, i16 rend_i=-1, i16 text_i=-1){
	owner_id = own_id;
	cm = CM_TEXTURE;
	renderer_index = rend_i;
	texture_index = text_i;
    }
} cTexture;
/******************************************************************************/
#endif
/******************************************************************************/

