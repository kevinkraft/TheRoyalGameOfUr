#include "texture.h"
#include <SDL_image.h>

SDL_Texture *loadTexture(std::string file, SDL_Renderer *renderer, bool colorkey)
{
  SDL_Texture *texture = nullptr;
  SDL_Surface *loadedImage = IMG_Load(file.c_str());

  if (loadedImage != nullptr)
    {
      if (colorkey)
        SDL_SetColorKey(loadedImage, SDL_TRUE, SDL_MapRGB(loadedImage->format, 0, 0xFF, 0xFF));	//Cyan.
      if ( renderer == nullptr )
        std::cout << "INFO: texture:loadTexture: renderer is NULL" << std::endl;
      texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
      SDL_FreeSurface(loadedImage);
      if (texture == nullptr)
        std::cout << "ERRO: main: CreateTextureFromSurface" << std::endl;
    }
  else
    std::cout << "ERRO: main: LoadBMP" << std::endl;

  return texture;
}

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect dst)
{
  SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h)
{
  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  dst.w = w;
  dst.h = h;
  SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y)
{
  int w, h;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  renderTexture(texture, renderer, x, y, w, h);
}
