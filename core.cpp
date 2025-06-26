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

    float accumulator = 0.0f;
    float alpha = 0.0f;
    float dft = 0.0f;	// delta frame time
    uint64_t lft = SDL_GetTicks64();	// last frame time
    uint64_t cft = lft;	// current frame time
    uint64_t lrt = SDL_GetTicks64();	// last render time
    uint64_t crt = lrt;	// current render time

    SDL_Window* temp_win = sdlw.windows[WINDOW_MAIN];
    SDL_Renderer* temp_rend = sdlw.renderers[RENDERER_MAIN];

    while(running){
	cft = SDL_GetTicks64();
	dft = (cft - lft)/1000.0f; // convert to seconds
	lft = cft;
	dft = dft<DFT_CAP?dft:DFT_CAP; // dont let dft grow unchecked if system
				       // bogged down
	r = input();
	if(r==QUIT) running = false;

	accumulator += dft;
	r = update(accumulator);
	if(r==QUIT) running = false;

	crt = SDL_GetTicks64();
	if((crt-lrt)/1000.0f>=FIXED_RENDER_TS){
	    alpha = accumulator / FIXED_LOGIC_TS; // the progress through current
						  // time step
	    r = render(temp_rend, alpha);
	    if(r) return r;
	    lrt = crt;
	}
    }
    return r;
}

rt Core::input(){
    rt r = kb.poll_events();
    if(r) return r;
    /**************************************************************************/
    // HANDLE CONTEXTS

    /**************************************************************************/
    return OKAY;
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

	em.pkb = &kb;
	r = ecs_kb.update(em, FIXED_LOGIC_TS);
	if(r) return r;

	// UPDATE GAME LOGIC (WITH FIXED_TS)
	r = ecs_ltf.update(em, FIXED_LOGIC_TS);
	if(r) return r;

	/**********************************************************************/
	accumulator -= FIXED_LOGIC_TS;
    }

    // clamp accumulator - added 6/22/25 may delete needs testing
    //  decided this is just redundant to loop logic
    //if(accumulator < 0.0f) accumulator = 0.0f;
    //if(accumulator > FIXED_LOGIC_TS) accumulator = FIXED_LOGIC_TS;

    return OKAY;
}

rt Core::render(SDL_Renderer* renderer, float& alpha){
    rt r = OKAY;

    SDL_RenderClear(renderer);

    /**************************************************************************/
    //	RENDER GAME STATE (WITH ALPHA)
    r = ecs_rtf.update(em, alpha);
    if(r) return r;

    em.psdlw = &sdlw;
    r = ecs_rtx.update(em);
    if(r) return r;
    /**************************************************************************/

    SDL_RenderPresent(renderer);

    return OKAY;
}
