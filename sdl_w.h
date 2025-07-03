
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

#include "types.h"

class SDL_Wrap{
    public:
	std::vector<SDL_Window*>    windows;
	std::vector<SDL_Renderer*>  renderers;
	std::vector<SDL_Surface*>   surfaces;
	std::vector<SDL_Texture*>   textures;
	std::vector<Mix_Music*>	    musics;
	std::vector<Mix_Chunk*>	    chunks;

    public:
	SDL_Wrap(){
	    windows.clear();
	    renderers.clear();
	    surfaces.clear();
	    textures.clear();
	    musics.clear();
	    chunks.clear();
	}

	~SDL_Wrap(){
	    rt r = chunks.size();
	    std::cerr << "Deleting " << r << " chunks" << std::endl;
	    for(i16 i=0; i < r; ++i){ Mix_FreeChunk(chunks[i]); }

	    r = musics.size();
	    std::cerr << "Deleting " << r << " musics" << std::endl;
	    for(i16 i=0; i < r; ++i){ Mix_FreeMusic(musics[i]); }

	    r = surfaces.size();
	    std::cerr << "Deleting " << r << " surfaces" << std::endl;
	    for(i16 i=0; i < r; ++i){ SDL_FreeSurface(surfaces[i]); }

	    r = textures.size();
	    std::cerr << "Deleting " << r << " textures" << std::endl;
	    for(i16 i=0; i < textures.size(); ++i){ SDL_DestroyTexture(textures[i]); }

	    r = renderers.size();
	    std::cerr << "Deleting " << r << " renderers" << std::endl;
	    for(i16 i=0; i < renderers.size(); ++i){ SDL_DestroyRenderer(renderers[i]); }

	    r = windows.size();
	    std::cerr << "Deleting " << r << " windows" << std::endl;
	    for(i16 i=0; i < windows.size(); ++i){ SDL_DestroyWindow(windows[i]); }

	    Mix_CloseAudio();
	    IMG_Quit();
	    SDL_Quit();
	    std::cerr << "All systems killed and memory released." << std::endl;
	}

	rt init();
	rt create_window(str title, i32 x, i32 y, i32 w, i32 h, ui32 flags);
	rt create_renderer(SDL_Window* win, i16 index, ui32 flags);
	rt create_texture_from_path(str path, SDL_Renderer* renderer=nullptr);
	rt create_texture_from_surface(SDL_Renderer* renderer, SDL_Surface* surface);
	rt create_surface_from_img_load(str path);
	rt create_chunk_from_load_wav(str path);
	rt create_music_from_load_mus(str path);

	rt play_music(i16 pmid, i16 ploop);
	rt play_channel(i16 pchan, i16 pcid, i16 ploop);
};

#endif

