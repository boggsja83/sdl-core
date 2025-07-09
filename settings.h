#ifndef SETTINGS_H
#define SETTINGS_H

#include <SDL2/SDL_pixels.h>
#include <cstdint>

// sdl_wrap settings
constexpr uint8_t WINDOW_MAIN = 0;
constexpr uint8_t REND_MAIN = 0;

// #ifndef WINDOW_MAIN
// #define WINDOW_MAIN core.sdlw.windows[0]
// #endif

// loop settings
// constexpr float FIXED_LOGIC_TS = 1.0f / 30.0f; // ~16.67ms
constexpr float FIXED_LOGIC_TS = 1.0f / 45.f; // ~16.67ms
constexpr float DFT_CAP = FIXED_LOGIC_TS * 2.f; //0.1f; // 100ms. maybe change this in terms of FIXED_TS
				// i.e. max number of steps to fall behind
constexpr float FIXED_RENDER_TS = 1.0f / 144.0f;
// constexpr float FIXED_RENDER_TS = 1.0f / 60.0f;

constexpr uint64_t KB_THRESHOLD_PRESS = 25;	//milliseconds
// constexpr uint64_t KB_THRESHOLD_PRESS = 45;	//milliseconds

// default window settings
constexpr int16_t DEF_WIN_W = 800;
constexpr int16_t DEF_WIN_H = 600;
constexpr uint8_t DEF_R = 80;
constexpr uint8_t DEF_G = 90;
constexpr uint8_t DEF_B = 231;
constexpr uint8_t DEF_A = SDL_ALPHA_OPAQUE;

constexpr float PLAYER_VEL = 500.f;

#endif

