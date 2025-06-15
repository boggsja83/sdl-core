#include "core.h"
#include "settings.h"
#include "types.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

int main(int argc, char** argv){
    Core core;
    if( core.STATUS_INT64 ) return core.STATUS_INT64;
    core.STATUS_INT64 = OKAY;
    core.STATUS_STRING = "main()";

    rt r = core.sdlw.create_window("sdl_core", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
    if(r) return r;

    r = core.sdlw.create_renderer(core.sdlw.windows[WINDOW_MAIN], -1, SDL_RENDERER_ACCELERATED);
    if(r) return r;


    core.em.add_entity(CM_MOVE|CM_POS|CM_BS);

    if((core.em.entities[0] & CM_MOVE)==CM_MOVE){
	std::cerr << "The entity has CM_MOVE!" << std::endl;
    }else{
	std::cerr << "The entity does NOT have CM_MOVE!" << std::endl;
    }

    r = core.loop();
    if(r) return r;

    return OKAY;
}

