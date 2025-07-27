#include "core.h"

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
	r = ecs_fps.update(em);

	// UPDATE
	accumulator += dft;
	r = update(accumulator);
	if(r==QUIT) running = false;
	else if(r<0) return r;
	r = ecs_fps.update(em);

	// RENDER
	crt = SDL_GetTicks64();
	if((crt-lrt)/1000.0f>=conf.rend_ts){
	    alpha = accumulator / conf.logic_ts; // the progress through current
						  // time step
	    r = render(conf.main_rend, alpha);
	    if(r<0) return r;
	    lrt = crt;
	}
	r = ecs_fps.update(em);
    }
    return r;
}

rt Core::input(){
    rt r = kb.poll_events();
    // if(r>=0) r = ecs_fps.update(em);
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
	r = ecs_kb.update(em, conf.logic_ts);
	if(r<0) return r;

	// UPDATE GAME LOGIC (WITH FIXED_TS)
	r = ecs_pos.update(em, conf.logic_ts);
	if(r<0) return r;

	// r = ecs_fps.update(em);

	SDL_ShowCursor(conf.show_cursor);

	/**********************************************************************/
	accumulator -= conf.logic_ts;
	// if(r>=0) r = ecs_fps.update(em);
	++conf.lframes;
    }

    return r;
}

rt Core::render(SDL_Renderer* renderer, float& alpha){
    rt r = OKAY;

    SDL_SetRenderDrawColor(conf.main_rend, conf.red, conf.green, conf.blue, conf.alpha);
    SDL_RenderClear(renderer);

    /**************************************************************************/
    //	RENDER GAME STATE (WITH ALPHA)
    if(r>=0) r = ecs_rendpos.update(em, alpha);
    if(r>=0) r = ecs_texture.update(em);
    /**************************************************************************/

    ////////////

    if(FADE_ALPHA<=0.f){
	FADE_SPEED *= -1.f;
	FADE_ALPHA = 0.f;
    }
    else if(FADE_ALPHA>=255.f){
	FADE_SPEED *= -1.f;
	FADE_ALPHA = 255.f;
    }
    FADE_ALPHA -= FADE_SPEED;

    /////////////

    if(conf.show_stats){

	SDL_Rect alpha_rct, rend_rct;
	ui16 alpha_w=0, char_w=0, alpha_h=0, tstr_w=0, tstr_wl=0;
	str tstr = " core 0.2 ";
	ui16 str_sz = tstr.size();
	std::stringstream ss;
	float perf = 0.f;

	alpha_w = sdlw.surfaces[conf.white_txt_i]->w;
	alpha_h = sdlw.surfaces[conf.white_txt_i]->h;
	char_w = alpha_w/conf.alphabet.size();//95;
	alpha_rct = {0,0,alpha_w,alpha_h};

	rend_rct = {0,conf.win_h-alpha_h,conf.win_w,alpha_h};
	if(r>=0) r = sdlw.render_fill_rect(conf.main_rend, &rend_rct, 86, 86, 86, 255);

	// draw core 0.1 text
	tstr_w = char_w*str_sz;
	rend_rct = {conf.win_w-tstr_w,conf.win_h-alpha_h,tstr_w,alpha_h};
	tstr_wl += tstr_w;
	if(r>=0) r = sdlw.render_fill_rect(conf.main_rend,&rend_rct,0,0,0,FADE_ALPHA);
	if(r>=0) r = sdlw.render_rect(conf.main_rend,&rend_rct,255,0,0,255-FADE_ALPHA);
	rend_rct = {conf.win_w-tstr_w+2,conf.win_h-alpha_h+2,tstr_w,alpha_h};
	if(r>=0) r = sdlw.render_text(tstr,conf.black_txt,alpha_rct,renderer,rend_rct);
	rend_rct = {conf.win_w-tstr_w,conf.win_h-alpha_h,tstr_w,alpha_h};
	if(r>=0) r = sdlw.render_text(tstr,conf.white_txt,alpha_rct,renderer,rend_rct);

	// draw ifps
	ss.str("");
	ss.clear();
	perf = em.fps[0].counts[0].last_fps*1000.f;
	ss << " IFPS:" << std::fixed << std::setprecision(2) << std::setw(6) << perf << ":"<< std::setw(6) << perf*conf.input_ts*100.f <<"% ";
	tstr = ss.str();
	str_sz = tstr.size();
	tstr_w = char_w*str_sz;
	rend_rct = {conf.win_w-tstr_wl-tstr_w,conf.win_h-alpha_h,tstr_w,alpha_h};
	if(r>=0) r = sdlw.render_fill_rect(conf.main_rend,&rend_rct,0,0,255,255-FADE_ALPHA);
	if(r>=0) r = sdlw.render_rect(conf.main_rend,&rend_rct,255,255,255,FADE_ALPHA);
	rend_rct = {conf.win_w-tstr_wl-tstr_w+2,conf.win_h-alpha_h+1,tstr_w,alpha_h};
	if(r>=0) r = sdlw.render_text(tstr,conf.black_txt,alpha_rct,renderer,rend_rct);
	rend_rct = {conf.win_w-tstr_wl-tstr_w,conf.win_h-alpha_h,tstr_w,alpha_h};
	if(r>=0) r = sdlw.render_text(tstr,conf.white_txt,alpha_rct,renderer,rend_rct);
	tstr_wl += tstr_w;

	// draw lfps
	ss.str("");
	ss.clear();
	perf = em.fps[0].counts[1].last_fps*1000.f;
	ss << " LFPS:" << std::fixed << std::setprecision(2) << std::setw(6) << perf << ":"<< std::setw(6) << perf*conf.logic_ts*100.f <<"% ";
	tstr = ss.str();
	str_sz = tstr.size();
	tstr_w = char_w*str_sz;
	rend_rct = {conf.win_w-tstr_wl-tstr_w,conf.win_h-alpha_h,tstr_w,alpha_h};
	if(r>=0) r = sdlw.render_fill_rect(conf.main_rend,&rend_rct,0,255,0,FADE_ALPHA);
	if(r>=0) r = sdlw.render_rect(conf.main_rend,&rend_rct,255,255,0,255-FADE_ALPHA);
	rend_rct = {conf.win_w-tstr_wl-tstr_w+2,conf.win_h-alpha_h+1,tstr_w,alpha_h};
	if(r>=0) r = sdlw.render_text(tstr,conf.black_txt,alpha_rct,renderer,rend_rct);
	rend_rct = {conf.win_w-tstr_wl-tstr_w,conf.win_h-alpha_h,tstr_w,alpha_h};
	if(r>=0) r = sdlw.render_text(tstr,conf.white_txt,alpha_rct,renderer,rend_rct);
	tstr_wl += tstr_w;

	// draw rfps
	ss.clear();
	ss.str("");
	perf = em.fps[0].counts[2].last_fps*1000.f;
	ss << " RFPS:" << std::fixed << std::setprecision(2) << std::setw(6) << perf << ":"<< std::setw(6) << perf*conf.rend_ts*100.f <<"% ";
	tstr = ss.str();
	str_sz = tstr.size();
	tstr_w = char_w*str_sz;
	rend_rct = {conf.win_w-tstr_wl-tstr_w,conf.win_h-alpha_h,tstr_w,alpha_h};
	if(r>=0) r = sdlw.render_fill_rect(conf.main_rend,&rend_rct,255,0,0,255-FADE_ALPHA);
	if(r>=0) r = sdlw.render_rect(conf.main_rend,&rend_rct,0,0,255,FADE_ALPHA);
	rend_rct = {conf.win_w-tstr_wl-tstr_w+2,conf.win_h-alpha_h+1,tstr_w,alpha_h};
	if(r>=0) r = sdlw.render_text(tstr,conf.black_txt,alpha_rct,renderer,rend_rct);
	rend_rct = {conf.win_w-tstr_wl-tstr_w,conf.win_h-alpha_h,tstr_w,alpha_h};
	if(r>=0) r = sdlw.render_text(tstr,conf.white_txt,alpha_rct,renderer,rend_rct);
	tstr_wl += tstr_w;

	// rend_rct = {1,conf.win_h-alpha_h,conf.win_w-tstr_wl,alpha_h};
	// if(r>=0) r = sdlw.render_rect(conf.main_rend,&rend_rct,000,255,000,FADE_ALPHA);

	// north
	sdlw.render_line(conf.main_rend, 0, conf.win_h-alpha_h, conf.win_w-tstr_wl-2, conf.win_h-alpha_h,SDL_Color({000,255,000,static_cast<ui8>(255-FADE_ALPHA)}));
	// south
	sdlw.render_line(conf.main_rend, 1, conf.win_h-1, conf.win_w-tstr_wl-2, conf.win_h-1,SDL_Color({255,255,255,static_cast<ui8>(255-FADE_ALPHA)}));
	// east
	sdlw.render_line(conf.main_rend, conf.win_w-tstr_wl-2, conf.win_h-alpha_h+1, conf.win_w-tstr_wl-2, conf.win_h,SDL_Color({255,255,255,static_cast<ui8>(255-FADE_ALPHA)}));
	// west
	sdlw.render_line(conf.main_rend,0, conf.win_h-alpha_h+1, 0, conf.win_h,SDL_Color({000,255,000,static_cast<ui8>(255-FADE_ALPHA)}));
	
    }

    ////////////

    /**************************************************************************/

    SDL_RenderPresent(renderer);
    // if(r>=0) r = ecs_fps.update(em);
    ++conf.rframes;

    return r;
}

