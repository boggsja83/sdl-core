
//  My SDL2 wrapper class

#ifndef SDL_W
#define SDL_W

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

#include <vector>
#include <iostream>

#include <cstdint>

#include "types.h"

/*----------------------------------------------------------------------------*/

class SDL_Wrap{
    private:
    public:
	std::vector<SDL_Window*>    windows;
	std::vector<SDL_Renderer*>  renderers;
	std::vector<SDL_Surface*>    surfaces;
	std::vector<SDL_Texture*>    textures;
	std::vector<Mix_Chunk*>	chunks;

    public:
	SDL_Wrap(){}
	~SDL_Wrap(){
	    rt r = chunks.size();
	    std::cerr << "Deleting " << r << " chunks" << std::endl;
	    for(int i=0; i < r; ++i){ Mix_FreeChunk(chunks[i]); }

	    r = surfaces.size();
	    std::cerr << "Deleting " << r << " surfaces" << std::endl;
	    for(int i=0; i < r; ++i){ SDL_FreeSurface(surfaces[i]); }

	    r = textures.size();
	    std::cerr << "Deleting " << r << " textures" << std::endl;
	    for(int i=0; i < textures.size(); ++i){ SDL_DestroyTexture(textures[i]); }

	    r = renderers.size();
	    std::cerr << "Deleting " << r << " renderers" << std::endl;
	    for(int i=0; i < renderers.size(); ++i){ SDL_DestroyRenderer(renderers[i]); }

	    r = windows.size();
	    std::cerr << "Deleting " << r << " windows" << std::endl;
	    for(int i=0; i < windows.size(); ++i){ SDL_DestroyWindow(windows[i]); }

	    Mix_CloseAudio();
	    IMG_Quit();
	    SDL_Quit();
	    std::cerr << "All systems killed and memory released." << std::endl;
	}

	int16_t init();
	int16_t create_window(const char*, int, int, int, int, uint32_t);
	int16_t create_renderer(SDL_Window*, int16_t, uint32_t);
	int16_t create_texture_from_surface(SDL_Renderer*, SDL_Surface*);
	int16_t create_surface_from_img_load(const char*);
	int16_t create_chunk_from_load_wav(const char*);
};

#endif

