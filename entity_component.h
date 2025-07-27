#ifndef ENTITY_COMPONENT_H
#define ENTITY_COMPONENT_H

// #include <iostream>
#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include <SDL2/SDL.h>
#include <vector>

#include "types.h"

typedef struct EC {
    i16 own_i;
    CM_MASK cm;

    EC(i16 pid=-1, CM_MASK pcm=CM_NULL){
	own_i = pid;
	cm = pcm;
    }
} EC;

typedef struct cPos : EC{
    float x;
    float y;
    float w;
    float h;

    cPos(i16 pid=-1, float px=-1.f, float py=-1.f, float pw=-1.f, float ph=-1.f){
	own_i = pid;
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
	own_i = pid;
	cm = CM_RENDPOS;

	x = px;
	y = py;
	w = pw;
	h = ph;
    }
} cRendPos;

typedef struct cVel : EC{
    float mov_x;
    float mov_y;
    float const_x;
    float const_y;
    float cur_x;
    float cur_y;

    cVel(i16 pid=-1,float pmov_x=0.f, float pmov_y=0.f,float pconst_x=0.f, float pconst_y=0.f,float pcur_x=0.f, float pcur_y=0.f){
	own_i = pid;
	cm = CM_VEL;

	cur_x = pcur_x;
	cur_y = pcur_y;
	mov_x = pmov_x;
	mov_y = pmov_y;
	const_x = pconst_x;
	const_y = pconst_y;
    }
} cVel;

typedef struct cTexture : EC {
    SDL_Renderer* rend;
    SDL_Texture* texture;
    SDL_Rect src;

    cTexture(i16 pid=-1, SDL_Renderer* prend=nullptr, SDL_Texture* ptexture=nullptr, SDL_Rect psrc=SDL_Rect()){
	own_i = pid;
	cm = CM_TEXTURE;

	rend = prend;
	texture = ptexture;
	src = psrc;
    }
} cTexture;

typedef struct cKB : EC {
    std::vector<KB_ACTION> acts;

    cKB(i16 pid=-1){
	own_i = pid;
	cm = CM_KB;

	acts.clear();
    }
} cKB;

typedef struct FPSdata {
    ui64 timespan;
    ui64 start_time;
    ui64 stop_time;
    ui64 start_frame;
    ui64 stop_frame;
    float last_fps;
    FRAME_TYPE frame_type;

    FPSdata(ui64 pts=0,FRAME_TYPE pft=FT_NONE){
	timespan=pts;
	start_time=0;
	stop_time=1;
	start_frame=0;
	stop_frame=0;
	last_fps=0.f;
	frame_type=pft;
    }
} FPSdata;

typedef struct cFPS : EC {
    // milliseconds
    std::vector<FPSdata> counts;

    cFPS(i16 pid=-1){
	own_i = pid;
	cm = CM_FPS;

	counts.clear();
    }
} cFPS;

typedef struct cColx : EC {
    bool clip;
    //bool is_static;
    float radius;
    COLLISION_SHAPE shape;

    // possibly use cPos data instead of vars like 'radius' here... TBD
    cColx(i16 pid=-1,COLLISION_SHAPE ps=COLLISION_UNKNOWN,bool pclip=false,float pr=0.f){
	own_i = pid;
	cm = CM_COLX;

	clip = pclip;
	radius = pr;
	shape = ps;
    }

} cColx;

typedef struct cShape : EC {
    SHAPE_TYPE shape;
    float radius;
    float width;
    float height;
    std::vector<SDL_Point> verts;
    ui32 color; //SDL_gfx color format
    bool filled;
    i16 thickness;

    cShape(i16 pid=-1){
	own_i = pid;
	cm = CM_SHAPE;


    }

} cShape;

#endif

