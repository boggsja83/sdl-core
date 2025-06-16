#include "core.h"
#include "settings.h"

// dropped make build system
// now using CMake to build 6-15-25

// mkdir build && cd build
// cmake -S .. -B . -DCMAKE_BUILD_TYPE=Debug
// cmake --build .

// build compile_commands.json for LSP to index definitions and declarations
// that is, basically tell clang which header files match which cpp files. 
// run in proj root. run when adding/deleting files to project.
// add additions/deletions to CMakeLists.txt also
// cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON


int main(int argc, char** argv){
    Core core;
    if( core.STATUS_INT64 ) return core.STATUS_INT64;

    core.STATUS_INT64 = OKAY;
    core.STATUS_STRING = "main()";

    rt r = core.sdlw.create_window("sdl_core", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEF_WIN_W, DEF_WIN_H, SDL_WINDOW_OPENGL);
    if(r) return r;

    r = core.sdlw.create_renderer(core.sdlw.windows[WINDOW_MAIN], -1, SDL_RENDERER_ACCELERATED);
    if(r) return r;

    core.em.add_entity(CM_POS|CM_VEL);
    core.em.add_entity(CM_VEL);
    core.em.add_entity(CM_POS);

    r = core.loop();

    return r;
}

