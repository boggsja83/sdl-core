#include "core.h"

int main(int argc, char** argv){
    Core core;
    if( core.STATUS_INT64 ) return core.STATUS_INT64;

    core.STATUS_INT64 = OKAY;
    core.STATUS_STRING = "main()";

    rt r = core.sdlw.create_window("sdl_core", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEF_WIN_W, DEF_WIN_H, SDL_WINDOW_OPENGL);
    if(r) return r;

    r = core.sdlw.create_renderer(core.sdlw.windows[WINDOW_MAIN], -1, SDL_RENDERER_ACCELERATED);
    if(r) return r;

    core.em.add_entity(CM_MOVE|CM_POS|CM_BS);
    core.em.add_entity(CM_MOVE|CM_BS);
    core.em.add_entity(CM_BS|CM_POS);

    r = core.loop();
    //if(r) return r;

    return r;
}

