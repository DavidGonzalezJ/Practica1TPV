#pragma once
#include <SDL.h>
#include "TexturasSDL.h"
class GlobosPG
{
public:
	GlobosPG(TexturasSDL* pText, int px, int py);
	~GlobosPG();
	void draw(SDL_Renderer* pRender) const;
	bool onClick(int pmx, int pmy);
	bool update();
	int puntos;
	SDL_Rect* tamPos; //Tamaño total (Toma el Ancho y el Alto de la textura)
private:
	TexturasSDL* pTexturaG;
	//Las dos variables siguientes posiblemente entren dentro de la anterior
	/*int pX;
	int pY;*/
	bool expl;
	bool vis;
	static const int PVIS = 70; //La probabilidad de que un globo esté visible
	static const int PDES = 30; //La probabilidad de que se desinfle
	static const int DT = 5; //Disminución tamaño
	static const int AP = 5; //Puntos que suma cada vez que se desinfle

};
