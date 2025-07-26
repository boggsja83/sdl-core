#include "sdl_w.h"
#include <SDL_blendmode.h>
#include <SDL_error.h>
#include <SDL_render.h>

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
    return windows.size()-1;
}

rt SDL_Wrap::create_renderer(SDL_Window* win, i16 index, ui32 flags, SDL_BlendMode blend){
    SDL_Renderer* temp = SDL_CreateRenderer(win, index, flags);
    if(!temp){
	std::cerr << "CreateRenderer failed. SDL_Error: " << SDL_GetError() << std::endl;
	return CREATE_RENDERER_FAIL;
    }
    SDL_SetRenderDrawBlendMode(temp, blend);
    renderers.push_back(temp);
    return renderers.size()-1;
}

rt SDL_Wrap::create_surface(i32 pw, i32 ph, i32 pdepth, ui32 prmask, ui32 pgmask, ui32 pbmask, ui32 pamask){
    SDL_Surface* temp = SDL_CreateRGBSurface(0, pw, ph, pdepth, prmask, pgmask, pbmask, pamask);
    if(!temp){
	std::cerr << "CreateSurface failed. SDL_Error: " << SDL_GetError() << std::endl;
	return CREATE_SURFACE_FAIL;
    }
    SDL_SetSurfaceBlendMode(temp, SDL_BLENDMODE_BLEND);
    // delete - doing just for funz
    // SDL_FillRect(temp, NULL, SDL_MapRGBA(temp->format, 255, 255, 0, 64));
    //
    surfaces.push_back(temp);
    return surfaces.size()-1;
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

rt SDL_Wrap::create_texture(SDL_Renderer* prend, ui32 pformat, i32 paccess, i32 pw, i32 ph){
    SDL_Texture* temp = SDL_CreateTexture(prend, pformat, paccess, pw, ph);
    if(!temp){
	std::cerr << "CreateTextur failed. SDL_Error: " << SDL_GetError() << std::endl;
	return CREATE_TEXTURE_FAIL;
    }
    SDL_SetTextureBlendMode(temp, SDL_BLENDMODE_BLEND);
    textures.push_back(temp);
    return textures.size()-1;
}

rt SDL_Wrap::create_texture_from_surface(SDL_Renderer* renderer, SDL_Surface* surface){
    SDL_Texture* temp = SDL_CreateTextureFromSurface(renderer, surface);
    if(!temp){
	std::cerr << "CreateTextureFromSurface failed. SDL_Error: " << SDL_GetError() << std::endl;
	return CREATE_TEXTURE_FAIL;
    }
    textures.push_back(temp);
    return textures.size()-1;
}

rt SDL_Wrap::create_texture_from_path(str path, SDL_Renderer* renderer){
    rt r = create_surface_from_img_load(path);
    if(r<0) return r;

    if(renderer) return create_texture_from_surface(renderer, surfaces[r]);
    // else return create_texture_from_surface(renderers[REND_MAIN], surfaces[r]); 
    else return INVALID_RENDERER;
}

rt SDL_Wrap::create_texture_from_text(TTF_Font* pfont, str ptxt, SDL_Color pcol, SDL_Renderer* prend){
    rt r = create_surface_from_ttf(pfont, ptxt, pcol);
    if(r<0) return r;
    return create_texture_from_surface(prend, surfaces[r]);
}

rt SDL_Wrap::create_chunk_wav_from_path(str path){
    Mix_Chunk* temp = Mix_LoadWAV(path);
    if(!temp){
	std::cerr << "LoadWAV failed. Mix_Errror: " << Mix_GetError() << std::endl;
	return MIX_LOAD_WAV_FAIL;
    }
    chunks.push_back(temp);
    return chunks.size()-1;
}

rt SDL_Wrap::create_music_from_path(str path){
    Mix_Music* temp = Mix_LoadMUS(path);
    if(!temp){
	std::cerr << "LoadMUS failed. Mix_Error: " << Mix_GetError() << std::endl;
	return MIX_LOAD_MUS_FAIL;
    }
    musics.push_back(temp);
    return musics.size()-1;
}

rt SDL_Wrap::play_channel(i16 pchan, i16 pcid, i16 ploop){
    if(pcid<0 || pcid>=chunks.size()){ return INVALID_CHUNK; }
    if(Mix_PlayChannel(pchan, chunks[pcid], ploop)<0){
	std::cerr << "PlayChannel failed. Mix_Error: " << Mix_GetError() << std::endl;
	return PLAY_CHANNEL_FAIL;
    }
    return OKAY;
}

rt SDL_Wrap::play_music(i16 pmid, i16 ploop){
    if(pmid<0 || pmid>=musics.size()){ return INVALID_MUSIC; }
    if(Mix_PlayMusic(musics[pmid], ploop) < 0){
	std::cerr << "PlayMusic failed. Mix_Error: " << Mix_GetError() << std::endl;
	return PLAY_MUSIC_FAIL;
    }
    return OKAY;
}

rt SDL_Wrap::open_font(str path, ui16 pfontsz){
    TTF_Font* font = TTF_OpenFont(path, pfontsz);
    if(!font){
	std::cerr << "OpenFont failed. TTF_Error: " << TTF_GetError() << std::endl;
	return TTF_OPEN_FAIL;
    }
    fonts.push_back(font);
    return fonts.size()-1;
}

rt SDL_Wrap::render_text(str pstr, SDL_Texture* palphabet, SDL_Rect& psrc, SDL_Renderer* prend, SDL_Rect& pdst){
    // ALPHABET = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"
    // 95 chars long

    ui16 sz = strlen(pstr);

    ui16 tdw = pdst.w/sz;
    ui16 tdh = pdst.h;

    ui16 tsw = psrc.w/95;
    ui16 tsh = psrc.h;

    ui16 offset = 0;

    SDL_Rect src;
    SDL_Rect dst;

    for(ui16 i=0; i<sz; ++i){
	offset = pstr[i]-32;
	src = { psrc.x+tsw*offset, psrc.y, tsw, tsh };
	dst = { pdst.x+tdw*i, pdst.y, tdw, tdh };
	SDL_RenderCopy(prend,palphabet,&src,&dst);	
    }

    return OKAY;
}

rt SDL_Wrap::render_fill_rect(SDL_Renderer* prend, const SDL_Rect* prect, ui8 pr, ui8 pg, ui8 pb, ui8 pa){
    SDL_Color tc;
    rt r = OKAY;

    r = SDL_GetRenderDrawColor(prend,&tc.r,&tc.g,&tc.b,&tc.a);

    if(r>=0) r = SDL_SetRenderDrawColor(prend, pr, pg, pb, pa);
    else { std::cerr << "GetRenderDrawColor failed. SDL_Error: " << SDL_GetError() << std::endl; return r; }

    if(r>=0) r = SDL_RenderFillRect(prend,prect);
    else { std::cerr << "SetRenderDrawColor failed. SDL_Error: " << SDL_GetError() << std::endl; return r; }

    if(r>=0) r = SDL_SetRenderDrawColor(prend, tc.r, tc.g, tc.b, tc.a);
    else { std::cerr << "RenderFillRect failed. SDL_Error: " << SDL_GetError() << std::endl; return r; }

    if(r<0) std::cerr << "SetRenderDrawColor failed. SDL_Error: " << SDL_GetError() << std::endl;

    return r; 
}

rt SDL_Wrap::render_rect(SDL_Renderer* prend, const SDL_Rect* prect, ui8 pr, ui8 pg, ui8 pb, ui8 pa){
    rt r = OKAY;
    
    r = SDL_SetRenderDrawBlendMode(prend, SDL_BLENDMODE_BLEND);
    if(r<0) { std::cerr<<"SetRenderDrawBlendMode failed. SDL_Error: " << SDL_GetError() << std::endl; return r; }

    r = SDL_SetRenderDrawColor(prend,pr,pg,pb,pa);
    if(r<0) { std::cerr<<"SDL_SetRenderDrawColor failed. SDL_Error: " << SDL_GetError() << std::endl; return r; }

    r = SDL_RenderDrawRect(prend,prect);
    if(r<0) { std::cerr<<"SDL_RenderDrawRect failed. SDL_Error: " << SDL_GetError() << std::endl; return r; }
    
    return r;
}



