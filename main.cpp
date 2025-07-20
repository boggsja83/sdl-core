#include "core.h"
#include "entity_component.h"
#include "settings.h"
#include "types.h"

#include <SDL_error.h>
#include <SDL_mixer.h>
#include <SDL_timer.h>
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
    core.START = SDL_GetTicks64();

    ui16 tw1 = 0, tw2 = 0;
    ui16 th1 = 0, th2 = 0;
    ui16 text_layer = 0;
    ui16 fade_layer = 0;

    if(r>=0) r = core.sdlw.create_window("sdl_core", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEF_WIN_W, DEF_WIN_H, SDL_WINDOW_VULKAN|SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(r>=0) r = core.sdlw.create_renderer(core.sdlw.windows[WINDOW_MAIN], -1, SDL_RENDERER_ACCELERATED);

    if(r>=0) r = core.sdlw.create_texture_from_path("bg.jpg", core.sdlw.renderers[REND_MAIN]);
    if(r>=0) r = core.sdlw.create_chunk_wav_from_path("sound2.wav");
    if(r>=0) r = core.sdlw.create_music_from_path("background.mp3");

    if(r>=0) r = Mix_VolumeMusic(0);
    if(r>=0) r = core.sdlw.play_music(0,-1); 

    if(r>=0) r = core.sdlw.open_font("BigBlue437-Regular.ttf", 24);

    if(r>=0) text_layer = core.sdlw.create_texture_from_text(core.sdlw.fonts[0],ALPHABET,SDL_Color({255,255,255,255}),core.sdlw.renderers[REND_MAIN]);
    if(r>=0) { tw1 = core.sdlw.surfaces[text_layer]->w; th1 = core.sdlw.surfaces[text_layer]->h; }

    if(r>=0) fade_layer = core.sdlw.create_texture(core.sdlw.renderers[REND_MAIN],SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,DEF_WIN_W,DEF_WIN_H);

    //text shadow

    //foreground text
    // if(r>=0) r = core.sdlw.create_texture_from_text(core.sdlw.fonts[0],"abcdefghijklmnopqrstuvwxyz",SDL_Color({255,255,255,255}),core.sdlw.renderers[REND_MAIN]);
    // if(r>=0) { tw2 = core.sdlw.surfaces[r]->w; th2 = core.sdlw.surfaces[r]->h; }

    //semi-trans surface test
    // if(r>=0) r = core.sdlw.create_surface(DEF_WIN_W,DEF_WIN_H);
    // if(r>=0) r = core.sdlw.create_texture_from_surface(core.sdlw.renderers[REND_MAIN],core.sdlw.surfaces[r]);

    //r=r>0?0:r;

    SDL_Rect src;
    SDL_Rect dst;
    cTexture tt;
    cVel tv;
    cPos tp;
    cKB tk;

    ui64 allz = (CM_POS|CM_RENDPOS|CM_VEL|CM_TEXTURE);

    if(r>=0) r = core.em.add_entity(allz);
    src = {0,0,756,568};
    tt = cTexture(r,0,0,src);
    tv = cVel(r, 50.f, -50.f);
    tp = cPos(r, 0.f, 0.f, DEF_WIN_W, DEF_WIN_H);
    if(r>=0) r = core.em.set(tt);
    if(r>=0) r = core.em.set(tv);
    if(r>=0) r = core.em.set(tp);

    if(r>=0) r = core.em.add_entity(allz | CM_KB);
    src = {0,0,756,568};
    tt = cTexture(r,0,0,src);
    tv = cVel(r, 0.f, 0.f);
    tp = cPos(r, 0.f, 0.f, 50.f, 75.f);
    tk = cKB(r);
    tk.acts.push_back(MOVE_N);
    tk.acts.push_back(MOVE_S);
    tk.acts.push_back(MOVE_E);
    tk.acts.push_back(MOVE_W);
    tk.acts.push_back(TEST_ACTION);
    tk.acts.push_back(VOL_UP);
    tk.acts.push_back(VOL_DN);
    if(r>=0) r = core.em.set(tt);
    if(r>=0) r = core.em.set(tv);
    if(r>=0) r = core.em.set(tp);
    if(r>=0) r = core.em.set(tk);

    if(r>=0) r = core.em.add_entity(allz | CM_KB);
    src = {0,0, 200, 400};
    tt = cTexture(r,0,0,src);
    tv = cVel(r, -15.f, -15.f);
    tp = cPos(r, 800.f-150.f, 600.f-150.f, 151.f, 151.f);
    tk = cKB(r);
    tk.acts.push_back(MOVE_S);
    tk.acts.push_back(MOVE_E);
    // tk.acts.push_back(MOVE_W);
    tk.acts.push_back(MOVE_N);
    if(r>=0) r = core.em.set(tt);
    if(r>=0) r = core.em.set(tv);
    if(r>=0) r = core.em.set(tp);
    if(r>=0) r = core.em.set(tk);

    if(r>=0) r = core.em.add_entity(allz);
    src = {0,0, 300, 500};
    tt = cTexture(3,0,0,src);
    tv = cVel(r, -25.f, 25.f);
    tp = cPos(r, 800.f, 000.f, 25.f, 35.f);
    if(r>=0) r = core.em.set(tt);
    if(r>=0) r = core.em.set(tv);
    if(r>=0) r = core.em.set(tp);

    if(r>=0) r = core.em.add_entity(CM_POS|CM_TEXTURE|CM_RENDPOS|CM_KB|CM_VEL);
    src = {0,0,tw1,th1};
    tt = cTexture(r,REND_MAIN,text_layer,src);
    tp = cPos(r, (DEF_WIN_W-tw1)/2.f,(DEF_WIN_H-th1)/2.f,tw1,th1);
    tk = cKB(r);
    tk.acts.push_back(MOVE_N);
    // tk.acts.push_back(MOVE_S);
    // tk.acts.push_back(MOVE_E);
    tk.acts.push_back(MOVE_W);
    tv = cVel(r, 200.f,00.f);
    if(r>=0) r = core.em.set(tv);
    if(r>=0) r = core.em.set(tt);
    if(r>=0) r = core.em.set(tp);
    if(r>=0) r = core.em.set(tk);

	//    for(ui32 i=0; i<500; ++i){
	// //if(r>=0) r = core.em.add_entity(CM_NULL);
	// if(r>=0) r = core.em.add_entity(allz);
	// src = {0,0, 300, 500};
	// tt = cTexture(r,0,0,src);
	// tv = cVel(r, -25.f+i, 25.f-i);
	// tp = cPos(r, 800.f, 000.f, 25, 35);
	// if(r>=0) r = core.em.set(tt);
	// if(r>=0) r = core.em.set(tv);
	// if(r>=0) r = core.em.set(tp);
	//    }

    if(r>=0) r = core.loop();

    ui64 elapsed = SDL_GetTicks64() - core.START;

    std::cerr << "Total Runtime: "<< elapsed/1000.f << " seconds" << std::endl;
    std::cerr << "Total Input Frames: " << core.IFRAMES << "\t" << "Total IFPS: " << core.IFRAMES/(elapsed/1000.f) << std::endl;
    std::cerr << "Total Logic Frames: " << core.LFRAMES << "\t" << "Total LFPS: " << core.LFRAMES/(elapsed/1000.f) << std::endl;
    std::cerr << "Total Render Frames: " << core.RFRAMES << "\t" << "Total RFPS: " << core.RFRAMES/(elapsed/1000.f) << std::endl;
    std::cerr << "*** Exit Code: " << r << " ***" << std::endl;

    // for (ui8 c=32; c<127; ++c) std::cerr << c;
    std::cerr << "alphabet count: " << strlen(ALPHABET) << std::endl;
    std::cerr << "KB_NUM_ACTIONS: " << KB_NUM_ACTIONS << std::endl;

    return r;
}

