#ifndef SETTINGS_H
#define SETTINGS_H

#include <cstdint>

// sdl_wrap settings
constexpr uint8_t WINDOW_MAIN = 0;
constexpr uint8_t RENDERER_MAIN = 0;

// #ifndef WINDOW_MAIN
// #define WINDOW_MAIN core.sdlw.windows[0]
// #endif

// loop settings
constexpr float FIXED_LOGIC_TS = 1.0f / 60.0f; // ~16.67ms
constexpr float DFT_CAP = 0.1f; // 100ms. maybe change this in terms of FIXED_TS
				// i.e. max number of steps to fall behind
constexpr float FIXED_RENDER_TS = 1.0f / 60.0f;


#endif

