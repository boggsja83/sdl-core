#include "sdl_w.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>

#include <cstdint>

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

    return OKAY;
}

rt SDL_Wrap::create_window(const char* title, int x, int y, int w, int h, uint32_t flags){
    SDL_Window* temp = SDL_CreateWindow(title, x, y, w, h, flags);
    if(!temp){
	std::cerr << "CreateWindow failed. SDL_Error: " << SDL_GetError() << std::endl;
	return CREATE_WINDOW_FAIL;
    }
    windows.push_back(temp);
    return OKAY;
}

rt SDL_Wrap::create_renderer(SDL_Window* win, int16_t index, uint32_t flags){
    SDL_Renderer* temp = SDL_CreateRenderer(win, index, flags);
    if(!temp){
	std::cerr << "CreateRenderer failed. SDL_Error: " << SDL_GetError() << std::endl;
	return CREATE_RENDERER_FAIL;
    }
    renderers.push_back(temp);
    return OKAY;
}

rt SDL_Wrap::create_surface_from_img_load(const char* path){
    SDL_Surface* temp = IMG_Load(path);
    if(!temp){
	std::cerr << "IMG_Load failed. IMG_Error: " << IMG_GetError() << std::endl;
    	return IMG_LOAD_FAIL;
    }
    surfaces.push_back(temp);
    return OKAY;
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

rt SDL_Wrap::create_chunk_from_load_wav(const char* path){
    Mix_Chunk* temp = Mix_LoadWAV(path);
    if(!temp){
	std::cerr << "Load_WAV failed. Mix_Errror: " << Mix_GetError() << std::endl;
	return MIX_LOAD_WAV_FAIL;
    }
    chunks.push_back(temp);
    return OKAY;
}
