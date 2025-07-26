#ifndef ENTITY_COMPONENT_H
#define ENTITY_COMPONENT_H

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include <SDL2/SDL.h>
#include <vector>

#include "types.h"

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
    float mov_x;
    float mov_y;
    float const_x;
    float const_y;
    float cur_x;
    float cur_y;

    cVel(i16 pid=-1,float pmov_x=0.f, float pmov_y=0.f,float pconst_x=0.f, float pconst_y=0.f,float pcur_x=0.f, float pcur_y=0.f){
	oid = pid;
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
	oid = pid;
	cm = CM_TEXTURE;

	rend = prend;
	texture = ptexture;
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

typedef struct cFPS : EC {
    // milliseconds
    ui64 timespan;
    float last_fps;
    ui64 start_time;
    ui64 stop_time;
    ui64 start_frame;
    ui64 stop_frame;
    FRAME_TYPE frame_type;

    cFPS(i16 pid=-1,ui64 pts=0, FRAME_TYPE pft=FT_NONE,float plfps=0.f,ui64 pstrt=0,ui64 pstpt=1,ui64 pstrf=0,ui64 pstpf=0){
	oid = pid;
	cm = CM_FPS;

	timespan = pts;
	
	last_fps = plfps;	

	start_time = pstrt;
	stop_time = pstpt;

	start_frame = pstrf;
	stop_frame = pstpf;

	frame_type = pft;
    }
} cFPS;

#endif

