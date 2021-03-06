#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <iostream>
#include <string>

#include <SDL.h>

SDL_Texture * loadTexture(std::string file, SDL_Renderer *renderer, bool colorkey=true);

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect dst);
void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h);
void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y);


#endif
