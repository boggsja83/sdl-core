#include "core.h"
#include <SDL_pixels.h>
#include <SDL_timer.h>
#include <string>

rt Core::loop(){
    rt r = OKAY;
    bool running = true; 

    float accumulator = 0.0f;		// ms time accumulator
    float alpha = 0.0f;			// progress through current frame
    float dft = 0.0f;			// delta frame time
    ui64 lft = SDL_GetTicks64();	// last frame time
    ui64 cft = lft;			// current frame time
    ui64 lrt = SDL_GetTicks64();	// last render time
    ui64 crt = lrt;			// current render time
    ui64 lit = SDL_GetTicks64();	// last input time
    ui64 cit = lit;			// current input time

    START = SDL_GetTicks64();

    while(running){
	cft = SDL_GetTicks64();
	dft = (cft - lft)/1000.f; // convert to seconds
	lft = cft;
	dft = dft<conf.dft_cap?dft:conf.dft_cap; // dont let dft grow unchecked 
						 // if system bogged down
	// INPUT
	cit = SDL_GetTicks64();
	if((cit-lit)/1000.f>=conf.input_ts){
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
	if((crt-lrt)/1000.0f>=conf.rend_ts){
	    alpha = accumulator / conf.logic_ts; // the progress through current
						  // time step
	    r = render(conf.rend, alpha);
	    if(r<0) return r;
	    lrt = crt;
	}
	// ++GFRAMES;
    }
    return r;
}

rt Core::input(){
    rt r = kb.poll_events();
    // ++IFRAMES;
    ++conf.iframes;
    return r;
}

rt Core::update(float& accumulator){
    rt r = OKAY;

    while(accumulator >= conf.logic_ts){
	/**********************************************************************/
	// eventually handle exits through contexts
	if(kb.keystate[SDL_SCANCODE_ESCAPE]) return QUIT;
	if(kb.keystate[SDL_SCANCODE_CAPSLOCK]) return QUIT;
	if(kb.keystate[SDL_SCANCODE_Q]) return QUIT;
	/**********************************************************************/
	// UPDATE GAME LOGIC (FROM KEYSTATE)
	// em.pkb = &kb;
	r = ecs_kb.update(em, conf.logic_ts);
	if(r<0) return r;

	// UPDATE GAME LOGIC (WITH FIXED_TS)
	r = ecs_pos.update(em, conf.logic_ts);
	if(r<0) return r;

	r = ecs_fps.update(em);
	// r = ecs_fps.update(em,conf.rframes);
	// r = ecs_fps.update(em,RFRAMES);

	SDL_ShowCursor(conf.show_cursor);

	/**********************************************************************/
	accumulator -= conf.logic_ts;
	// ++LFRAMES;
	++conf.lframes;
    }

    return OKAY;
}

rt Core::render(SDL_Renderer* renderer, float& alpha){
    rt r = OKAY;

    SDL_SetRenderDrawColor(conf.rend, conf.red, conf.green, conf.blue, conf.alpha);
    SDL_RenderClear(renderer);

    /**************************************************************************/
    //	RENDER GAME STATE (WITH ALPHA)
    if(r>=0) r = ecs_rendpos.update(em, alpha);

    // em.psdlw = &sdlw;
    if(r>=0) r = ecs_texture.update(em);
    /**************************************************************************/

    ////////////
    SDL_Rect src, dst;
    ui16 tw1=0, tw2=0, th1=0, th2=0;
    // str tstr = " core 0.1 ";
    str tstr = "RFPS: " +  std::to_string((em.fps[0].last_fps*1000.f));

    ui16 sz = tstr.size();
    // ui16 sz = strlen(tstr);
    ////////////
    tw1 = sdlw.surfaces[1]->w;
    th1 = sdlw.surfaces[1]->h;
    tw2 = tw1/conf.alphabet.size();//95;
    src = {0,0,tw1,th1};
    dst = {conf.win_w-tw2*sz,conf.win_h-th1,tw2*sz,th1};

    if(FADE_ALPHA<=0.f){
	FADE_SPEED *= -1.f;
	FADE_ALPHA = 0.f;
    }
    else if(FADE_ALPHA>=255.f){
	FADE_SPEED *= -1.f;
	FADE_ALPHA = 255.f;
    }
    FADE_ALPHA -= FADE_SPEED;

    r = sdlw.render_fill_rect(conf.rend,&dst,19,144,0,FADE_ALPHA);
    if(r>=0) r = sdlw.render_rect(conf.rend,&dst,255,136,0,255-FADE_ALPHA);
    
    sdlw.render_text(
	    tstr,
	    sdlw.textures[1],
	    src,
	    renderer,
	    dst
	    );
    ////////////

    SDL_RenderPresent(renderer);
    // ++RFRAMES;
    ++conf.rframes;
   
    return r;
}

