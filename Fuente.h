/*#pragma once
#include <SDL.h>
#include "SDL_ttf.h"
#include <string>
class Fuente
{
public:
	Fuente();
	~Fuente();
	void load(std::string nombreArch, int tamaño);
	void close();
	SDL_Surface* textSolid(std::string texto, SDL_Color color);
private:
	TTF_Font* pFont;
};*/