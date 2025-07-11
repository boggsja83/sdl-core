#include "core.h"
#include "entity_component.h"
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
    ui16 tw1 = 0, tw2 = 0;
    ui16 th1 = 0, th2 = 0;

    if(!r) r = core.sdlw.create_window("sdl_core", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEF_WIN_W, DEF_WIN_H, SDL_WINDOW_VULKAN);
    if(!r) r = core.sdlw.create_renderer(core.sdlw.windows[WINDOW_MAIN], -1, SDL_RENDERER_ACCELERATED);
    if(!r) r = SDL_SetRenderDrawColor(core.sdlw.renderers[REND_MAIN], DEF_R, DEF_G, DEF_B, DEF_A);

    if(!r) r = core.sdlw.create_texture_from_path("bg.jpg", core.sdlw.renderers[REND_MAIN]);
    if(!r) r = core.sdlw.create_chunk_wav_from_path("sound2.wav");
    if(!r) r = core.sdlw.create_music_from_path("background.mp3");
    
    std::cerr << "Previous Volume: " << 100.f*Mix_VolumeMusic(64)/128.f << "% | Current Volume: " << 100.f*Mix_VolumeMusic(-1)/128.f << '%' << std::endl;    // accepts 0-128
    if(!r) r = core.sdlw.play_music(0,-1); 

    if(!r) r = core.sdlw.open_font("BigBlue437-Regular.ttf", 24);
    // if(!r) r = core.sdlw.open_font("BigBlueTerm437NerdFont-Regular.ttf", 24);
    if(!r) r = core.sdlw.create_surface_from_ttf(core.sdlw.font,"abcdefghijklmnopqrstuvwxyz",SDL_Color({0,100,150,255}));
    if(r>=0) { tw1=core.sdlw.surfaces[r]->w; th1=core.sdlw.surfaces[r]->h; }
    if(r>=0) r = core.sdlw.create_texture_from_surface(core.sdlw.renderers[REND_MAIN], core.sdlw.surfaces[r]);
    if(r>=0) r = core.sdlw.create_texture_from_text(core.sdlw.font,"ABCDEFGHIJKLMNOPQRSTUVWXYZ",SDL_Color({0,255,0,255}),core.sdlw.renderers[REND_MAIN]);
    if(r>=0) tw2 = core.sdlw.surfaces[r]->w; th2 = core.sdlw.surfaces[r]->h;
    r=r>0?0:r;

    SDL_Rect src;
    cTexture tt;
    cVel tv;
    cPos tp;
    cKB tk;

    ui64 allz = (CM_POS|CM_RENDPOS|CM_VEL|CM_TEXTURE);

    if(!r) r = core.em.add_entity(allz);
    src = {0,0,756,568};
    tt = cTexture(0,0,0,src);
    tv = cVel(0, 50.f, -50.f);
    tp = cPos(0, 0.f, 0.f, DEF_WIN_W, DEF_WIN_H);
    if(!r) r = core.em.set(tt);
    if(!r) r = core.em.set(tv);
    if(!r) r = core.em.set(tp);

    if(!r) r = core.em.add_entity(allz | CM_KB);
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
    if(!r) r = core.em.set(tt);
    if(!r) r = core.em.set(tv);
    if(!r) r = core.em.set(tp);
    if(!r) r = core.em.set(tk);

    if(!r) r = core.em.add_entity(allz | CM_KB);
    src = {0,0, 200, 400};
    tt = cTexture(2,0,0,src);
    tv = cVel(2, -15.f, -15.f);
    tp = cPos(2, 800-150.f, 600-150.f, 151, 151);
    tk = cKB(2);
    tk.acts.push_back(MOVE_S);
    tk.acts.push_back(MOVE_E);
    tk.acts.push_back(MOVE_W);
    tk.acts.push_back(MOVE_N);
    if(!r) r = core.em.set(tt);
    if(!r) r = core.em.set(tv);
    if(!r) r = core.em.set(tp);
    if(!r) r = core.em.set(tk);

    if(!r) r = core.em.add_entity(allz);
    src = {0,0, 300, 500};
    tt = cTexture(3,0,0,src);
    tv = cVel(3, -25.f, 25.f);
    tp = cPos(3, 800.f, 000.f, 25, 35);
    if(!r) r = core.em.set(tt);
    if(!r) r = core.em.set(tv);
    if(!r) r = core.em.set(tp);

    if(!r) r = core.em.add_entity(allz-CM_VEL);
    src = {0,0, tw1, th1};
    tt = cTexture(4,0,1,src);
    tp = cPos(4,(1.f*800-tw1)/2,(1.f*600-th1)/2,tw1,th1);
    if(!r) r = core.em.set(tt);
    if(!r) r = core.em.set(tp);

    if(!r) r = core.em.add_entity(allz-CM_VEL);
    src = {0,0, tw2, th2};
    tt = cTexture(5,0,2,src);
    tp = cPos(5,(1.f*800-tw2)/2,(1.f*600-th2)/2-th2,tw2,th2);
    if(!r) r = core.em.set(tt);
    if(!r) r = core.em.set(tp);



    if(!r) r = core.loop();
    // r = (r==-1)?0:r;

    std::cerr << "*** Exit Code: " << r << " ***" << std::endl;

    return r;
}

