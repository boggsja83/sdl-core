#include "core.h"
#include "settings.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

int main(int argc, char** argv){
    Core core;
    if( core.STATUS_INT64 ) return core.STATUS_INT64;

    rt r = core.sdlw.create_window("sdl_core", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
    if(r) return r;

    r = core.sdlw.create_renderer(core.sdlw.windows[WINDOW_MAIN], -1, SDL_RENDERER_ACCELERATED);
    if(r) return r;

    return core.loop();
}

