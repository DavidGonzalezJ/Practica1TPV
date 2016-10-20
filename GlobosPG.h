#pragma once
#include <SDL.h>
#include "TexturasSDL.h"
class GlobosPG
{
public:
	GlobosPG(TexturasSDL* img, int px, int py);
	~GlobosPG();
	void draw(SDL_Renderer*) const;
	bool onClick(int pmx, int pmy);
	bool update();
private:
	TexturasSDL* img;
	int px;
	int py;
	static const int PVIS = 70; //La probabilidad de que un globo esté visible
	static const int PDES = 30; //La probabilidad de que se desinfle
	static const int DT = 5; //Disminución tamaño
	static const int AP = 5; //Puntos que suma cada vez que se desinfle

};
