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
    rt r = core.sdlw.init();

    if(!r) r = core.sdlw.create_window("sdl_core", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEF_WIN_W, DEF_WIN_H, SDL_WINDOW_VULKAN);
    if(!r) r = core.sdlw.create_renderer(core.sdlw.windows[WINDOW_MAIN], -1, SDL_RENDERER_ACCELERATED);
    if(!r) r = SDL_SetRenderDrawColor(core.sdlw.renderers[RENDERER_MAIN], DEF_R, DEF_G, DEF_B, DEF_A);

    if(!r) r = core.em.add_entity(CM_POS|CM_VEL);
    if(!r) r = core.em.add_entity(CM_VEL|CM_TEXTURE);
    if(!r) r = core.em.add_entity(CM_POS|CM_RENDPOS);
    if(!r) r = core.em.add_entity(CM_POS|CM_RENDPOS|CM_VEL);

    cPos tp = cPos(3, 0.f, 100.f, 10.f, 10.f);
    cVel tv = cVel(3, 1.2f, 3.7f);

    if(!r) r = core.em.set(tp);
    if(!r) r = core.em.set(tv);

    /***************************************************************************/
    if(!r) r = core.loop();
    /***************************************************************************/
    for(i16 i=0; i<core.em.ents.size(); ++i){
	if(core.em.ents[i]&CM_POS){
	    std::cerr << "ent["<<i<<"].x: " << core.em.pos[i].x <<
		"\tent["<<i<<"].y: " << core.em.pos[i].y << std::endl <<
		"ent["<<i<<"].w: " << core.em.pos[i].w <<
		"\tent["<<i<<"].h: " <<core.em.pos[i].h << std::endl;

	    if(core.em.ents[i]&CM_RENDPOS){
	    std::cerr << "ent["<<i<<"].x: " << core.em.rendpos[i].x <<
		"\tent["<<i<<"].y: " << core.em.rendpos[i].y << std::endl <<
		"ent["<<i<<"].w: " << core.em.rendpos[i].w <<
		"\tent["<<i<<"].h: " <<core.em.rendpos[i].h << std::endl;
	    }
	}
    }
    /**************************************************************************/
    /**************************************************************************/
    /**************************************************************************/
    /**************************************************************************/
    /**************************************************************************/
    std::cerr << "*** Exit Code: " << r << " ***" << std::endl;
    /**************************************************************************/
    return r;
}

