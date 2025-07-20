#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_timer.h>

#include "core.h"
#include "settings.h"

rt Core::loop(){
    rt r = OKAY;
    bool running = true; 

    float accumulator = 0.0f;		// time accumulator
    float alpha = 0.0f;			// progrss through current frame
    float dft = 0.0f;			// delta frame time
    ui64 lft = SDL_GetTicks64();	// last frame time
    ui64 cft = lft;			// current frame time
    ui64 lrt = SDL_GetTicks64();	// last render time
    ui64 crt = lrt;			// current render time
    ui64 lit = SDL_GetTicks64();	// last input time
    ui64 cit = lit;			// current input time

    SDL_Window* temp_win = sdlw.windows[WINDOW_MAIN];
    SDL_Renderer* temp_rend = sdlw.renderers[REND_MAIN];

    while(running){
	cft = SDL_GetTicks64();
	dft = (cft - lft)/1000.f; // convert to seconds
	lft = cft;
	dft = dft<DFT_CAP?dft:DFT_CAP; // dont let dft grow unchecked if system
				       // bogged down
	// INPUT
	cit = SDL_GetTicks64();
	if((cit-lit)/1000.f>=FIXED_INPUT_TS){
	    r = input();
	    if(r==QUIT) running = false;
	    else if(r<0) return r;
	    lit = cit;
	}

	// UPDATE
	accumulator += dft;
	r = update(accumulator);
	if(r==QUIT) running = false;
	else if(r<0) return r;

	// RENDER
	crt = SDL_GetTicks64();
	if((crt-lrt)/1000.0f>=FIXED_RENDER_TS){
	    alpha = accumulator / FIXED_LOGIC_TS; // the progress through current
						  // time step
	    r = render(temp_rend, alpha);
	    if(r<0) return r;
	    lrt = crt;
	}
    }
    return r;
}

rt Core::input(){
    rt r = kb.poll_events();
    ++IFRAMES;
    return r;
}

rt Core::update(float& accumulator){
    rt r = OKAY;

    while(accumulator >= FIXED_LOGIC_TS){
	/**********************************************************************/
	// eventually handle exits through contexts
	if(kb.keystate[SDL_SCANCODE_ESCAPE]) return QUIT;
	if(kb.keystate[SDL_SCANCODE_CAPSLOCK]) return QUIT;
	if(kb.keystate[SDL_SCANCODE_Q]) return QUIT;
	/**********************************************************************/
	// UPDATE GAME LOGIC (FROM KEYSTATE)
	em.pkb = &kb;
	r = ecs_kb.update(em, FIXED_LOGIC_TS);
	if(r) return r;

	// UPDATE GAME LOGIC (WITH FIXED_TS)
	r = ecs_pos.update(em, FIXED_LOGIC_TS);
	if(r) return r;

	/**********************************************************************/
	accumulator -= FIXED_LOGIC_TS;
	++LFRAMES;
    }

    return OKAY;
}

rt Core::render(SDL_Renderer* renderer, float& alpha){
    rt r = OKAY;

    SDL_SetRenderDrawColor(sdlw.renderers[REND_MAIN], DEF_R, DEF_G, DEF_B, DEF_A);
    SDL_RenderClear(renderer);

    /**************************************************************************/
    //	RENDER GAME STATE (WITH ALPHA)
    if(r>=0) r = ecs_rendpos.update(em, alpha);

    em.psdlw = &sdlw;
    if(r>=0) r = ecs_texture.update(em);
    /**************************************************************************/

    ////////////
    SDL_Rect src, dst;
    ui16 tw1=0, tw2=0, th1=0, th2=0;
    str tstr = "core 0.1";
    ui16 sz = strlen(tstr);

    tw1 = sdlw.surfaces[1]->w;
    th1 = sdlw.surfaces[1]->h;
    tw2 = tw1/95;
    src = {0,0,tw1,th1};
    dst = {DEF_WIN_W-tw2*sz,DEF_WIN_H-th1,tw2*sz,th1};
    sdlw.render_text(
	    tstr,
	    sdlw.textures[1],
	    src,
	    renderer,
	    dst
	    );
    ////////////

    ////////////
    float fade_speed = 0.55f;

    if(FADE_DO){
	if(FADE_ALPHA<0.f) FADE_ALPHA=0.f;
	SDL_SetRenderTarget(sdlw.renderers[0],sdlw.textures[2]);
	SDL_SetRenderDrawColor(sdlw.renderers[0], 0,0,0,255);
	SDL_RenderClear(sdlw.renderers[0]);
	SDL_SetRenderTarget(sdlw.renderers[0],nullptr);
	SDL_SetTextureAlphaMod(sdlw.textures[2],FADE_ALPHA);
	SDL_RenderCopy(sdlw.renderers[0],sdlw.textures[2],nullptr,nullptr);
	if(FADE_ALPHA==0.f) FADE_DO = false;
	FADE_ALPHA-=fade_speed;
	//std::cerr << "FADE_ALPHA: " << FADE_ALPHA << std::endl;
    }
    ////////////

    SDL_RenderPresent(renderer);
    ++RFRAMES;

    return r;
}

