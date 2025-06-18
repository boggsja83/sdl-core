#include "core.h"
#include "settings.h"
#include "types.h"
#include <SDL_error.h>
#include <SDL_video.h>

// dropped make build system
// now using CMake to build 6-15-25

// mkdir build && cd build
// cmake -S .. -B . -DCMAKE_BUILD_TYPE=Debug
// cmake --build .

// build compile_commands.json for LSP to index definitions and declarations
// that is, basically tell clang which header files match which cpp files. 
// run in proj root. run when adding/deleting cpp files to project.
// add additions/deletions to CMakeLists.txt also
// cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON


int main(int argc, char** argv){
    Core core;
    if( core.STATUS_INT64 ) return core.STATUS_INT64;

    core.STATUS_INT64 = OKAY;
    core.STATUS_STRING = "main()";

    rt r = core.sdlw.create_window("sdl_core", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEF_WIN_W, DEF_WIN_H, SDL_WINDOW_VULKAN);
    if(r) return r;

    r = core.sdlw.create_renderer(core.sdlw.windows[WINDOW_MAIN], -1, SDL_RENDERER_ACCELERATED);
    if(r) return r;

    r = SDL_SetRenderDrawColor(core.sdlw.renderers[RENDERER_MAIN], DEF_R, DEF_G, DEF_B, DEF_A);
    if(r) { std::cerr << "SDL_SetRenderDrawColor failed. SDL_GetError: " << SDL_GetError(); return r; }

    r = core.em.add_entity(CM_POS|CM_VEL);
    r = core.em.add_entity(CM_VEL);
    r = core.em.add_entity(CM_POS|CM_RENDPOS);
    r = core.em.add_entity(CM_POS|CM_RENDPOS|CM_VEL);

    r = core.em.set_vel(0, 2.3f, 1.f);
    r = core.em.set_pos(0, 0.f, 100.f, 10.f, 10.f);

    r = core.em.set_pos(3,1,3,4,2);
    if(!r) r = core.em.set_vel(3,3,4);

    if(!r) r = core.loop();

    std::cerr << "Exit Code: " << r << std::endl;
    return r;
}

