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
    ui64 start = SDL_GetTicks64();

    Core core;
    rt r = core.sdlw.init();
    core.START = start;

    str alphabet = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    ui16 tw1 = 0, tw2 = 0;
    ui16 th1 = 0, th2 = 0;
    ui16 text_layer = 0;

    if(r>=0) r = core.sdlw.create_window("sdl_core", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEF_WIN_W, DEF_WIN_H, SDL_WINDOW_VULKAN);
    if(r>=0) r = core.sdlw.create_renderer(core.sdlw.windows[WINDOW_MAIN], -1, SDL_RENDERER_ACCELERATED);
    if(r>=0) r = SDL_SetRenderDrawColor(core.sdlw.renderers[REND_MAIN], DEF_R, DEF_G, DEF_B, DEF_A);

    if(r>=0) r = core.sdlw.create_texture_from_path("bg.jpg", core.sdlw.renderers[REND_MAIN]);
    if(r>=0) r = core.sdlw.create_chunk_wav_from_path("sound2.wav");
    if(r>=0) r = core.sdlw.create_music_from_path("background.mp3");
    
    if(r>=0) Mix_VolumeMusic(0);
    if(r>=0) r = core.sdlw.play_music(0,-1); 

    if(r>=0) r = core.sdlw.open_font("BigBlue437-Regular.ttf", 24);

    //text shadow
    if(r>=0) text_layer = core.sdlw.create_texture_from_text(core.sdlw.fonts[0],alphabet,SDL_Color({0,0,255,255}),core.sdlw.renderers[REND_MAIN]);
    if(r>=0) { tw1 = core.sdlw.surfaces[text_layer]->w; th1 = core.sdlw.surfaces[text_layer]->h; }

    //foreground text
    // if(r>=0) r = core.sdlw.create_texture_from_text(core.sdlw.fonts[0],"abcdefghijklmnopqrstuvwxyz",SDL_Color({255,255,255,255}),core.sdlw.renderers[REND_MAIN]);
    // if(r>=0) { tw2 = core.sdlw.surfaces[r]->w; th2 = core.sdlw.surfaces[r]->h; }

    //semi-trans surface test
    // if(r>=0) r = core.sdlw.create_surface(DEF_WIN_W,DEF_WIN_H);
    // if(r>=0) r = core.sdlw.create_texture_from_surface(core.sdlw.renderers[REND_MAIN],core.sdlw.surfaces[r]);

    r=r>0?0:r;

    SDL_Rect src;
    SDL_Rect dst;
    cTexture tt;
    cVel tv;
    cPos tp;
    cKB tk;

    ui64 allz = (CM_POS|CM_RENDPOS|CM_VEL|CM_TEXTURE);

    if(r>=0) r = core.em.add_entity(allz);
    src = {0,0,756,568};
    tt = cTexture(0,0,0,src);
    tv = cVel(0, 50.f, -50.f);
    tp = cPos(0, 0.f, 0.f, DEF_WIN_W, DEF_WIN_H);
    if(r>=0) r = core.em.set(tt);
    if(r>=0) r = core.em.set(tv);
    if(r>=0) r = core.em.set(tp);

    if(r>=0) r = core.em.add_entity(allz | CM_KB);
    src = {0,0,756,568};
    tt = cTexture(1,0,0,src);
    tv = cVel(1, 0.f, 0.f);
    tp = cPos(1, 0.f, 0.f, 50, 75);
    tk = cKB(1);
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
    tt = cTexture(2,0,0,src);
    tv = cVel(2, -15.f, -15.f);
    tp = cPos(2, 800-150.f, 600-150.f, 151, 151);
    tk = cKB(2);
    tk.acts.push_back(MOVE_S);
    tk.acts.push_back(MOVE_E);
    tk.acts.push_back(MOVE_W);
    tk.acts.push_back(MOVE_N);
    if(r>=0) r = core.em.set(tt);
    if(r>=0) r = core.em.set(tv);
    if(r>=0) r = core.em.set(tp);
    if(r>=0) r = core.em.set(tk);

    if(r>=0) r = core.em.add_entity(allz);
    src = {0,0, 300, 500};
    tt = cTexture(3,0,0,src);
    tv = cVel(3, -25.f, 25.f);
    tp = cPos(3, 800.f, 000.f, 25, 35);
    if(r>=0) r = core.em.set(tt);
    if(r>=0) r = core.em.set(tv);
    if(r>=0) r = core.em.set(tp);

    if(r>=0) r = core.em.add_entity(CM_POS|CM_TEXTURE|CM_RENDPOS);
    src = {0,0,tw1,th1};
    tt = cTexture(r,REND_MAIN,text_layer,src);
    tp = cPos(r, (DEF_WIN_W-tw1)/2.f,(DEF_WIN_H-th1)/2.f,tw1,th1);
    if(r>=0) r = core.em.set(tt);
    if(r>=0) r = core.em.set(tp);

    tw2 = tw1/strlen(alphabet);

    // if(r>=0) r = core.em.add_entity(CM_POS|CM_TEXTURE|CM_RENDPOS);
    // src = {tw2*58,0, tw2, th1};
    // tt = cTexture(r,REND_MAIN,text_layer,src);
    // tp = cPos(r,10,10,tw2,th1);
    // if(r>=0) core.em.set(tt);
    // if(r>=0) core.em.set(tp);

    str tstr = "Test";
    src = {0,0,tw1,th1};
    dst = {0,0,static_cast<int>(tw2*strlen(tstr)),th1};
    core.sdlw.display_text(
	    tstr,
	    core.sdlw.textures[text_layer],
	    src,
	    core.sdlw.renderers[REND_MAIN],
	    dst
    );
    // if(r>=0) r = core.em.add_entity(allz-CM_VEL);
    // src = {0,0, tw1, th1};
    // tt = cTexture(4,0,1,src);
    // tp = cPos(4,(1.f*800-tw1)/2+1,(1.f*600-th1)/2+1,tw1,th1);
    // if(r>=0) r = core.em.set(tt);
    // if(r>=0) r = core.em.set(tp);
    //
    // if(r>=0) r = core.em.add_entity(allz-CM_VEL);
    // // src = {0,0, tw2, th2};
    // src = {9*tw2/85,0, tw1/85, th1};
    // tt = cTexture(5,0,2,src);
    // // tp = cPos(5,(1.f*800-tw2)/2,(1.f*600-th2)/2,tw2/84.f,th2);
    // tp = cPos(5,10,10,tw1/85.f,th1);
    // if(r>=0) r = core.em.set(tt);
    // if(r>=0) r = core.em.set(tp);
    //
    // if(r>=0) r = core.em.add_entity(CM_POS|CM_RENDPOS|CM_TEXTURE);
    // src = {0,0,DEF_WIN_W,DEF_WIN_H};
    // tt = cTexture(6,0,3,src);
    // tp = cPos(6,0,0,DEF_WIN_W,DEF_WIN_H);
    // if(r>=0) r = core.em.set(tt);
    // if(r>=0) r = core.em.set(tp);

	//    for(ui32 i=0; i<1000; ++i){
	// if(r>=0) r = core.em.add_entity(CM_NULL);
	//    }

    if(r>=0) r = core.loop();

    ui64 elapsed = SDL_GetTicks64() - start;
    
    std::cerr << "Total Runtime: "<< elapsed/1000.f << " seconds" << std::endl;
    std::cerr << "Total Logic Frames: " << core.LFRAMES << "\t" << "Total LFPS: " << core.LFRAMES/(elapsed/1000.f) << std::endl;
    std::cerr << "Total Render Frames: " << core.RFRAMES << "\t" << "Total RFPS: " << core.RFRAMES/(elapsed/1000.f) << std::endl;
    std::cerr << "*** Exit Code: " << r << " ***" << std::endl;

    // for (ui8 c=32; c<127; ++c) std::cerr << c;
    std::cerr << "alphabet count: " << strlen(alphabet) << std::endl;

    return r;
}

