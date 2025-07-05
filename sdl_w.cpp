#include "sdl_w.h"
#include "settings.h"
#include "types.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL_ttf.h>

rt SDL_Wrap::init(){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
	std::cerr << "SDL could not initialize. SDL_Error: " << SDL_GetError() << std::endl;
	return SDL_INIT_FAIL;
    }

    if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG)){
	std::cerr << "IMG_Init could not initialize. IMG_Error: " << IMG_GetError() << std::endl;
	return IMG_INIT_FAIL;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
	std::cerr << "MIX_OpenAudio failed. MIX_Error: " << Mix_GetError() << std::endl;
	return MIX_INIT_FAIL;
    }

    if(TTF_Init() < 0){
	std::cerr << "TTF_Init could not initialize. TTF_Error: " << TTF_GetError() << std::endl;	
	return TTF_INIT_FAIL;
    }

    return OKAY;
}

rt SDL_Wrap::create_window(str title, i32 x, i32 y, i32 w, i32 h, ui32 flags){
    SDL_Window* temp = SDL_CreateWindow(title, x, y, w, h, flags);
    if(!temp){
	std::cerr << "CreateWindow failed. SDL_Error: " << SDL_GetError() << std::endl;
	return CREATE_WINDOW_FAIL;
    }
    windows.push_back(temp);
    return OKAY;
}

rt SDL_Wrap::create_renderer(SDL_Window* win, i16 index, ui32 flags){
    SDL_Renderer* temp = SDL_CreateRenderer(win, index, flags);
    if(!temp){
	std::cerr << "CreateRenderer failed. SDL_Error: " << SDL_GetError() << std::endl;
	return CREATE_RENDERER_FAIL;
    }
    renderers.push_back(temp);
    return OKAY;
}

rt SDL_Wrap::create_surface_from_img_load(str path){
    SDL_Surface* temp = IMG_Load(path);
    if(!temp){
	std::cerr << "IMG_Load failed. IMG_Error: " << IMG_GetError() << std::endl;
    	return IMG_LOAD_FAIL;
    }
    surfaces.push_back(temp);
    return surfaces.size()-1;
}

rt SDL_Wrap::create_surface_from_ttf(TTF_Font* pfont, str ptxt, SDL_Color pcol){
    SDL_Surface* temp = TTF_RenderText_Solid(pfont, ptxt, pcol);
    if(!temp){
	std::cerr << "RenderText failed. TTF_Error: " << TTF_GetError() << std::endl;
	return TTF_SURFACE_FAIL;
    }
    surfaces.push_back(temp);
    return surfaces.size()-1;
}

rt SDL_Wrap::create_texture_from_surface(SDL_Renderer* renderer, SDL_Surface* surface){
    SDL_Texture* temp = SDL_CreateTextureFromSurface(renderer, surface);
    if(!temp){
	std::cerr << "CreateTextureFromSurface failed. SDL_Error: " << SDL_GetError() << std::endl;
	return CREATE_TEXTURE_FAIL;
    }
    textures.push_back(temp);
    return OKAY;
}

rt SDL_Wrap::create_texture_from_path(str path, SDL_Renderer* renderer){
    rt r = create_surface_from_img_load(path);
    if(r<0) return r;

    if(renderer){
	r = create_texture_from_surface(renderer, surfaces.back());
    }
    else{
	r = create_texture_from_surface(renderers[RENDERER_MAIN], surfaces.back());
    }

    return r;
}

rt SDL_Wrap::create_chunk_from_load_wav(str path){
    Mix_Chunk* temp = Mix_LoadWAV(path);
    if(!temp){
	std::cerr << "LoadWAV failed. Mix_Errror: " << Mix_GetError() << std::endl;
	return MIX_LOAD_WAV_FAIL;
    }
    chunks.push_back(temp);
    return OKAY;
}

rt SDL_Wrap::create_music_from_load_mus(str path){
    Mix_Music* temp = Mix_LoadMUS(path);
    if(!temp){
	std::cerr << "LoadMUS failed. Mix_Error: " << Mix_GetError() << std::endl;
	return MIX_LOAD_MP3_FAIL;
    }
    musics.push_back(temp);
    return OKAY;
}

rt SDL_Wrap::play_channel(i16 pchan=-1, i16 pcid=-1, i16 ploop=0){
    if(pcid<0 || pcid>=chunks.size()){ return INVALID_CHUNK; }
    if(Mix_PlayChannel(pchan, chunks[pcid], ploop)<0){
	std::cerr << "PlayChannel failed. Mix_Error: " << Mix_GetError() << std::endl;
	return PLAY_CHANNEL_FAIL;
    }
    return OKAY;
}

rt SDL_Wrap::play_music(i16 pmid=-1, i16 ploop=-1){
    if(pmid<0 || pmid>=musics.size()){ return INVALID_MUSIC; }
    if(Mix_PlayMusic(musics[pmid], ploop) < 0){
	std::cerr << "PlayMusic failed. Mix_Error: " << Mix_GetError() << std::endl;
	return PLAY_MUSIC_FAIL;
    }

    return OKAY;
}

rt SDL_Wrap::open_font(str path, ui16 size){
    font = TTF_OpenFont(path, size);
    if(!font){
	std::cerr << "OpenFont failed. TTF_Error: " << TTF_GetError() << std::endl;
	return TTF_OPEN_FAIL;
    }
    return OKAY;
}


