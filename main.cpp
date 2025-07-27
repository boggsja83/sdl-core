#include <SDL_video.h>
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

    ui16 tw1 = 0, tw2 = 0;
    ui16 th1 = 0, th2 = 0;
    ui16 main_layer = 0;
    ui16 white_txt = 0;
    ui16 black_txt = 0;
    // ui16 fade_layer = 0;

    // ui8 cr = 255;
    // ui8 cg = 136;
    // ui8 cb = 0;
    ui8 cr = 255;
    ui8 cg = 255;
    ui8 cb = 255;
    ui8 ca = SDL_ALPHA_OPAQUE;

    if(r>=0) r = core.sdlw.create_window("sdl_core", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, core.conf.win_w, core.conf.win_h, SDL_WINDOW_VULKAN|SDL_WINDOW_FULLSCREEN_DESKTOP);
    core.conf.win = core.sdlw.windows[r];

    if(r>=0) r = core.sdlw.create_renderer(core.conf.win, -1, SDL_RENDERER_ACCELERATED);
    core.conf.rend = core.sdlw.renderers[r];

    if(r>=0) main_layer = core.sdlw.create_texture_from_path("bg.jpg", core.conf.rend);
    if(main_layer>=0) r = core.sdlw.create_chunk_wav_from_path("sound2.wav");
    if(r>=0) r = core.sdlw.create_music_from_path("background.mp3");

    if(r>=0) r = Mix_VolumeMusic(0);
    if(r>=0) r = core.sdlw.play_music(0,-1); 

    if(r>=0) r = core.sdlw.open_font("BigBlue437-Regular.ttf", 24);


    if(r>=0) white_txt = core.sdlw.create_texture_from_text(core.sdlw.fonts[r],core.conf.alphabet,SDL_Color({cr,cg,cb,ca}),core.conf.rend);
    if(white_txt>=0) { tw1 = core.sdlw.surfaces[white_txt]->w; th1 = core.sdlw.surfaces[white_txt]->h; }

    if(white_txt>=0) black_txt = core.sdlw.create_texture_from_text(core.sdlw.fonts[0],core.conf.alphabet,SDL_Color({0,0,0,SDL_ALPHA_OPAQUE}),core.conf.rend);

    r = black_txt;

    SDL_Rect src;
    cTexture tct;
    cVel tcv;
    cPos tcp;
    cKB tck;
    cFPS tcf;
    SDL_Texture* temp_text = core.sdlw.textures[main_layer];

    ui64 allz = (CM_POS|CM_RENDPOS|CM_VEL|CM_TEXTURE);

    if(r>=0) r = core.em.add_entity(CM_KB|CM_FPS);
    tcf = cFPS(r);//,500,FT_LOGIC);
    tcf.counts.push_back(FPSdata(500,FT_INPUT));
    tcf.counts.push_back(FPSdata(500,FT_LOGIC));
    tcf.counts.push_back(FPSdata(500,FT_RENDER));
    tck = cKB(r);
    tck.acts.push_back(TEST_ACTION);
    tck.acts.push_back(VOL_UP);
    tck.acts.push_back(VOL_DN);
    tck.acts.push_back(TOGGLE_CURSOR);
    if(r>=0) r = core.em.set(tck);
    if(r>=0) r = core.em.set(tcf);

    if(r>=0) r = core.em.add_entity(allz);
    src = {0,0,core.sdlw.surfaces[main_layer]->w,core.sdlw.surfaces[main_layer]->h};
    tct = cTexture(r,core.conf.rend,temp_text,src);
    tcv = cVel(r, 0.f,0.f,50.f,-50.f);
    tcp = cPos(r, 0.f, 0.f, core.conf.win_w, core.conf.win_h);
    if(r>=0) r = core.em.set(tct);
    if(r>=0) r = core.em.set(tcv);
    if(r>=0) r = core.em.set(tcp);

    if(r>=0) r = core.em.add_entity(allz | CM_KB);
    src = {0,0,core.sdlw.surfaces[main_layer]->w,core.sdlw.surfaces[main_layer]->h};
    tct = cTexture(r,core.conf.rend,temp_text,src);
    tcv = cVel(r, 0.f, 0.f, 150.f,150.f);
    tcp = cPos(r, 0.f, 0.f, 50.f, 75.f);
    tck = cKB(r);
    tck.acts.push_back(MOVE_N);
    tck.acts.push_back(MOVE_S);
    tck.acts.push_back(MOVE_E);
    tck.acts.push_back(MOVE_W);
    if(r>=0) r = core.em.set(tct);
    if(r>=0) r = core.em.set(tcv);
    if(r>=0) r = core.em.set(tcp);
    if(r>=0) r = core.em.set(tck);

    if(r>=0) r = core.em.add_entity(allz | CM_KB);
    src = {0,0, 200, 400};
    tct = cTexture(r,core.conf.rend,temp_text,src);
    tcv = cVel(r, 50.f, 50.f);
    tcp = cPos(r, 800.f-150.f, 600.f-150.f, 151.f, 151.f);
    tck = cKB(r);
    tck.acts.push_back(MOVE_S);
    tck.acts.push_back(MOVE_E);
    tck.acts.push_back(MOVE_W);
    tck.acts.push_back(MOVE_N);
    if(r>=0) r = core.em.set(tct);
    if(r>=0) r = core.em.set(tcv);
    if(r>=0) r = core.em.set(tcp);
    if(r>=0) r = core.em.set(tck);

    if(r>=0) r = core.em.add_entity(allz);
    src = {0,0, 300, 500};
    tct = cTexture(r,core.conf.rend,temp_text,src);
    tcv = cVel(r, 25.f, 25.f, 25.f,25.f);
    tcp = cPos(r, 800.f, 000.f, 25.f, 35.f);
    if(r>=0) r = core.em.set(tct);
    if(r>=0) r = core.em.set(tcv);
    if(r>=0) r = core.em.set(tcp);

    if(r>=0) r = core.em.add_entity(CM_POS|CM_TEXTURE|CM_RENDPOS|CM_KB|CM_VEL);
    src = {0,0,tw1,th1};
    tct = cTexture(r,core.conf.rend,core.sdlw.textures[white_txt],src);
    tcp = cPos(r, (core.conf.win_w-tw1)/2.f,(core.conf.win_h-th1)/2.f,tw1,th1);
    tcv = cVel(r, 200.f,0.f,100.f,0.f);
    tck = cKB(r);
    tck.acts.push_back(MOVE_N);
    tck.acts.push_back(MOVE_S);
    tck.acts.push_back(MOVE_E);
    tck.acts.push_back(MOVE_W);
    if(r>=0) r = core.em.set(tcv);
    if(r>=0) r = core.em.set(tct);
    if(r>=0) r = core.em.set(tcp);
    if(r>=0) r = core.em.set(tck);

	   for(ui32 i=0; i<30000; ++i){
	if(r>=0) r = core.em.add_entity(allz|CM_KB);
	src = {0,0, 300, 500};
	tct = cTexture(r,core.conf.rend,temp_text,src);
	tcv = cVel(r, Core::rand(-250,250),Core::rand(-250,250),Core::rand(-250,250), Core::rand(-250,250));
	tcp = cPos(r, (core.conf.win_w-25)/2.f, (core.conf.win_h-35)/2.f, 25, 35);
	tck = cKB(r);
	tck.acts.push_back(MOVE_N);
	tck.acts.push_back(MOVE_S);
	tck.acts.push_back(MOVE_E);
	tck.acts.push_back(MOVE_W);
	if(r>=0) r = core.em.set(tct);
	if(r>=0) r = core.em.set(tcv);
	if(r>=0) r = core.em.set(tcp);
	if(r>=0) r = core.em.set(tck);
	   }

    // core.START = SDL_GetTicks64();

    if(r>=0) r = core.loop();

    ui64 elapsed = SDL_GetTicks64() - core.START;

    float ifps = core.conf.iframes/(elapsed/1000.f);
    float lfps = core.conf.lframes/(elapsed/1000.f);
    float rfps = core.conf.rframes/(elapsed/1000.f);
    // float gfps = core.GFRAMES/(elapsed/1000.f);
    ui16 col_w = 6;

    std::cerr << std::fixed << std::setprecision(2) << std::left;

    std::cerr << "Total Runtime:  " << elapsed/1000.f << " seconds" << std::endl;
    std::cerr << "Total Entities: " << std::setw(col_w) << core.em.ents.size() << std::endl;
    std::cerr << "Total Input Frames:  " << std::setw(col_w) << core.conf.iframes << " | Total IFPS: " << ifps << std::endl;
    std::cerr << "Total Logic Frames:  " << std::setw(col_w) << core.conf.lframes << " | Total LFPS: " << lfps << std::endl;
    std::cerr << "Total Render Frames: " << std::setw(col_w) << core.conf.rframes << " | Total RFPS: " << rfps << std::endl;
    // std::cerr << "Total Game Frames:   " << std::setw(col_w) << core.GFRAMES << " | Total GFPS: " << gfps << std::endl;

    std::cerr << "Input Performance Rating:  " << ifps*core.conf.input_ts*100.f << '%' << std::endl;
    std::cerr << "Logic Performance Rating:  " << lfps*core.conf.logic_ts*100.f << '%' << std::endl;
    std::cerr << "Render Performance Rating: " << rfps*core.conf.rend_ts*100.f << '%' << std::endl;

    std::cerr << "Exit Code: " << r << std::endl;

    //std::cerr << "alphabet count: " << strlen(core.conf.alphabet) << std::endl; // should be 95
    //std::cerr << "KB_NUM_ACTIONS: " << KB_NUM_ACTIONS << std::endl;

    // r = SDL_GetNumVideoDisplays();
    // std::cerr << "Number of displays: " << r << std::endl;

    return r;
}

