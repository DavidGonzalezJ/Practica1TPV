#include "GlobosPG.h"


GlobosPG::GlobosPG(TexturasSDL* pText, int px, int py):
	pTextura(pText), pX(px), pY(py)
{
	//Aquí asignamos la posición (genera una aleatoria cada vez que se llame)
	int seed = rand();
	srand(seed);
	//Aquí asignamos los booleanos
	vis = true;
	expl = false;
	//Queda por asignar el tamaño, que supongo lo tomamos de la textura
	tam=pText->daTamaño;

}


GlobosPG::~GlobosPG()
{
}

void GlobosPG::draw(SDL_Renderer* pRender) const {
	SDL_Rect sitio;
	//Falta en el sitio el tamaño de la ventana entera
	sitio.x = pX;
	sitio.y = pY;
	if(vis && !expl)
		pTextura->draw(pRender,/*Aqui va el sitio de la ventana donde queremos dibujar*/sitio, pTextura->daTextura());
}