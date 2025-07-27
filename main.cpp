#include <iomanip>

#include "core.h"
#include "entity_component.h"
#include "types.h"

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
    rt r = core.sdlw.init();

    core.em.kb_ptr = &core.kb;
    core.em.sdlw_ptr = &core.sdlw;
    core.em.conf_ptr = &core.conf;
    core.kb.conf_ptr = &core.conf;

    if(r>=0) r = core.sdlw.create_window("sdl_core", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, core.conf.win_w, core.conf.win_h, SDL_WINDOW_VULKAN|SDL_WINDOW_FULLSCREEN_DESKTOP);
    core.conf.main_win = core.sdlw.windows[r];

    if(r>=0) r = core.sdlw.create_renderer(core.conf.main_win, -1, SDL_RENDERER_ACCELERATED);
    core.conf.main_rend = core.sdlw.renderers[r];

    if(r>=0) r = core.sdlw.open_font("BigBlue437-Regular.ttf", 24);

    if(r>=0) core.conf.white_txt_i = core.sdlw.create_texture_from_text(core.sdlw.fonts[r],core.conf.alphabet,SDL_Color({255,255,255,SDL_ALPHA_OPAQUE}),core.conf.main_rend);
    if(core.conf.white_txt_i>=0) core.conf.black_txt_i = core.sdlw.create_texture_from_text(core.sdlw.fonts[0],core.conf.alphabet,SDL_Color({0,0,0,SDL_ALPHA_OPAQUE}),core.conf.main_rend);
    if(core.conf.black_txt_i>=0) {
	core.conf.white_txt=core.sdlw.textures[core.conf.white_txt_i];
	core.conf.black_txt=core.sdlw.textures[core.conf.black_txt_i];
    } 

    r = core.conf.black_txt_i;

    cKB tck;
    cFPS tcf;

    if(r>=0){
	r = core.em.add_entity(CM_KB|CM_FPS);
	tcf = cFPS(r);
	tcf.counts.push_back(FPSdata(333,FT_INPUT));
	tcf.counts.push_back(FPSdata(333,FT_LOGIC));
	tcf.counts.push_back(FPSdata(333,FT_RENDER));
	tck = cKB(r);
	tck.acts.push_back(TEST_ACTION);
	tck.acts.push_back(TOGGLE_CURSOR);
	tck.acts.push_back(TOGGLE_STATS);
	if(r>=0) r = core.em.set(tck);
	if(r>=0) r = core.em.set(tcf);
    }

    if(r>=0) r = core.loop();

    /**************************************************************************/

    ui64 elapsed = SDL_GetTicks64() - core.START;

    float ifps = core.conf.iframes/(elapsed/1000.f);
    float lfps = core.conf.lframes/(elapsed/1000.f);
    float rfps = core.conf.rframes/(elapsed/1000.f);
    ui16 col_w = 6;

    std::cerr << std::fixed << std::setprecision(2) << std::left;

    std::cerr << "Total Runtime:  " << elapsed/1000.f << " seconds" << std::endl;
    std::cerr << "Total Entities: " << std::setw(col_w) << core.em.ents.size() << std::endl;
    std::cerr << "Total Input Frames:  " << std::setw(col_w) << core.conf.iframes << " | Total IFPS: " << ifps << std::endl;
    std::cerr << "Total Logic Frames:  " << std::setw(col_w) << core.conf.lframes << " | Total LFPS: " << lfps << std::endl;
    std::cerr << "Total Render Frames: " << std::setw(col_w) << core.conf.rframes << " | Total RFPS: " << rfps << std::endl;

    std::cerr << "Input Performance Rating:  " << ifps*core.conf.input_ts*100.f << '%' << std::endl;
    std::cerr << "Logic Performance Rating:  " << lfps*core.conf.logic_ts*100.f << '%' << std::endl;
    std::cerr << "Render Performance Rating: " << rfps*core.conf.rend_ts*100.f << '%' << std::endl;

    std::cerr << "Exit Code: " << r << std::endl;

    //std::cerr << "alphabet count: " << strlen(core.conf.alphabet) << std::endl; // should be 95
    //std::cerr << "KB_NUM_ACTIONS: " << KB_NUM_ACTIONS << std::endl;

    // r = SDL_GetNumVideoDisplays();
    // std::cerr << "Number of displays: " << r << std::endl;

    /**************************************************************************/

    return r;
}

