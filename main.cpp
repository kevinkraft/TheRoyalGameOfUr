//Main implementation and game loop
//
//Kevin Maguire
//03/06/17
//
//Version 0.1
//

//-------------------------------------------------------------------------------------

#include <iostream>
//#include <string>
#include <sstream>
//#include <random>
//#include <ctime>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


#include "global.h"
#include "texture.h"
#include "Timer.h"

//-------------------------------------------------------------------------------------

int main(int argc, char **argv)
{
  //-------------------------------------------------------------------------------------
  // Variable declarations
  //-------------------------------------------------------------------------------------
  bool quit = false;
  SDL_Event event;

  Timer fpsTimer;
  int countedFrames = 0;
  Timer capTimer;

  int mouse_x = 0;
  int mouse_y = 0;
  int screen_width = SCREEN_WIDTH;
  int screen_height = SCREEN_HEIGHT;

  //bool scroll_active = true;
  bool fullscreen = false;
  bool use_custom_cursor = USE_CUSTOM_CURSOR;
  bool debug_mode = false;

  //-------------------------------------------------------------------------------------
  //Initialization:
  //-------------------------------------------------------------------------------------
  //initialise
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
      std::cout << "ERRO: main: SDL_Init" << std::endl;
      return 1;
    }
  if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
      std::cout << "ERRO: main: IMG_Init" << std::endl;
      SDL_Quit();
      return 1;
    }
  if (TTF_Init() != 0)
    {
      std::cout << "ERRO: main: TTF_Init" << std::endl;
      SDL_Quit();
      return 1;
    }

  SDL_Window *window = nullptr;
  window = SDL_CreateWindow("Civ",
			    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			    SCREEN_WIDTH, SCREEN_HEIGHT,
			    SDL_WINDOW_SHOWN);
  if (window == nullptr)
    {
      std::cout << "ERRO: main: CreateWindow" << std::endl;
      return 1;
    }

  SDL_Renderer *renderer = nullptr;
  if (VSYNC_ACTIVE)
    {
      renderer = SDL_CreateRenderer(window, -1,
				    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    }
  else
    {
      renderer = SDL_CreateRenderer(window, -1,
				    SDL_RENDERER_ACCELERATED);
    }
  if (renderer == nullptr)
    {
      std::cout << "ERRO: main: CreateRenderer" << std::endl;
      return 1;
    }

  if (use_custom_cursor)
    {
      SDL_ShowCursor(false);
    }

  //-------------------------------------------------------------------------------------
  // Create objects:
  //-------------------------------------------------------------------------------------
  std::cout << "INFO: main: Starting To Make Objects." << std::endl;

  //misc objects
  SDL_Texture *texture_cursor  = loadTexture("res/images/cursor.png", renderer, false);

  //Start timers:
  fpsTimer.start();

  //-------------------------------------------------------------------------------------
  // Main loop:
  //-------------------------------------------------------------------------------------
  while (!quit)
    {
      if (!VSYNC_ACTIVE)
        {
          capTimer.start();
        }

      //-------------------------------------------------------------------------------------
      // Screen
      //-------------------------------------------------------------------------------------

      //Mouse position:
      SDL_GetMouseState(&mouse_x, &mouse_y);

      //Resolution:
      SDL_GetWindowSize(window, &screen_width, &screen_height);

      //-------------------------------------------------------------------------------------
      //Events:
      //-------------------------------------------------------------------------------------
      while (SDL_PollEvent(&event))
        {
          //quit
          if (event.type == SDL_QUIT)
            {
              quit = true;
            }
          //keypress
          else if (event.type == SDL_KEYDOWN)
            {
              if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                  quit = true;
                }
              else if (event.key.keysym.sym == SDLK_f)
                {
                  fullscreen = not(fullscreen);
                  if (fullscreen)
                    {
                      SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                    }
                  else
                    {
                      SDL_SetWindowFullscreen(window, 0);
                    }
                }
              else if (event.key.keysym.sym == SDLK_c)
                {
                  use_custom_cursor = not(use_custom_cursor);
                  SDL_ShowCursor(not(use_custom_cursor));
                }
              else if (event.key.keysym.sym == SDLK_d)
                {
                  debug_mode = not(debug_mode);
                }
            }
          //mouse press
          if (event.type == SDL_MOUSEBUTTONDOWN)
            {
              if (event.button.button == SDL_BUTTON_LEFT)
                {
                }
              else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                }
            }
          //mouse motion
          else if (event.type == SDL_MOUSEMOTION)
            {
            }
          //mouse wheel
          else if (event.type == SDL_MOUSEWHEEL)
            {
            }
        }

      //-------------------------------------------------------------------------------------
      // Rendering:
      //-------------------------------------------------------------------------------------

      SDL_RenderClear(renderer);

      if (use_custom_cursor)
        {
          renderTexture(texture_cursor, renderer, mouse_x, mouse_y);
        }

      SDL_RenderPresent(renderer);

      //FPS:
      float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
      ++countedFrames;

      if (!VSYNC_ACTIVE)
        {
          int frameTicks = capTimer.getTicks();
          if (frameTicks < SCREEN_TICKS_PER_FRAME)
            {
              SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
            }
        }

      //Window title:
      if (debug_mode)
        {
          std::stringstream ss;
          ss << "temp";
          const std::string tmp = ss.str();
          const char *title = tmp.c_str();
          SDL_SetWindowTitle(window, title);
        }
      else
        {
          SDL_SetWindowTitle(window, "TheRoyalGameOfUr");
        }

    }

  //-------------------------------------------------------------------------------------
  //Cleanup:
  //-------------------------------------------------------------------------------------

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  IMG_Quit();
  SDL_Quit();

  return 0;
}
