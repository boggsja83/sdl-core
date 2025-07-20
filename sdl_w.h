#ifndef SDL_W
#define SDL_W

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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
	std::vector<TTF_Font*>	    fonts;

    public:
	SDL_Wrap(){
	    windows.clear();
	    renderers.clear();
	    surfaces.clear();
	    textures.clear();
	    musics.clear();
	    chunks.clear();
	    fonts.clear();
	    // font = nullptr;
	}

	~SDL_Wrap(){
	    rt r = fonts.size();
	    std::cerr << "Deleting " << r << " fonts" << std::endl;
	    for(i16 i=0; i < r; ++i){ TTF_CloseFont(fonts[i]); }

	    r = chunks.size();
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
	    for(i16 i=0; i < r; ++i){ SDL_DestroyTexture(textures[i]); }

	    r = renderers.size();
	    std::cerr << "Deleting " << r << " renderers" << std::endl;
	    for(i16 i=0; i < r; ++i){ SDL_DestroyRenderer(renderers[i]); }

	    r = windows.size();
	    std::cerr << "Deleting " << r << " windows" << std::endl;
	    for(i16 i=0; i < r; ++i){ SDL_DestroyWindow(windows[i]); }

	    TTF_Quit();
	    Mix_CloseAudio();
	    IMG_Quit();
	    SDL_Quit();
	    std::cerr << "All systems killed and memory released." << std::endl;
	}

	rt init();
	rt create_window(str title, i32 x, i32 y, i32 w, i32 h, ui32 flags);
	rt create_texture(SDL_Renderer* prend, ui32 pformat, i32 paccess, i32 pw, i32 ph);
	rt create_renderer(SDL_Window* win, i16 index, ui32 flags);
	rt create_texture_from_path(str path, SDL_Renderer* prend);
	rt create_texture_from_text(TTF_Font* pfont, str ptxt, SDL_Color pcol, SDL_Renderer* prend);
	rt create_texture_from_surface(SDL_Renderer* renderer, SDL_Surface* surface);
	rt create_surface(i32 pw, i32 ph, i32 pdepth=32, ui32 prmask=0xFF000000, ui32 pgmask=0x00FF0000, ui32 pbmask=0x0000FF00, ui32 pamask=0x000000FF);
	rt create_surface_from_img_load(str path);
	rt create_surface_from_ttf(TTF_Font* pfont, str ptxt, SDL_Color pcol);
	rt create_chunk_wav_from_path(str path);
	rt create_music_from_path(str path);

	rt play_music(i16 pmid=-1, i16 ploop=-1);
	rt play_channel(i16 pchan=-1, i16 pcid=-1, i16 ploop=0);

	rt open_font(str path, ui16 pfontsz);
	rt display_text(str pstr, SDL_Texture* palphabet, SDL_Rect& psrc, SDL_Renderer* prend, SDL_Rect& pdst);
};

#endif

