#ifndef GLOBAL_HPP_
#define GLOBAL_HPP_

#include <SDL.h>

//Notes:
// * Everything defined in here must be const

//-------------------------------------------------------------------------------------
// Screen Constants
//-------------------------------------------------------------------------------------
const bool VSYNC_ACTIVE = true;
const bool USE_CUSTOM_CURSOR = false;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 600;

#endif
