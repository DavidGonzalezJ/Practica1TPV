#include "GlobosPG.h"


GlobosPG::GlobosPG(TexturasSDL* pText, int px, int py):
	pTextura(pText), pX(px), pY(py)
{
	//Aqu� asignamos la posici�n (genera una aleatoria cada vez que se llame)
	int seed = rand();
	srand(seed);
	//Aqu� asignamos los booleanos
	vis = true;
	expl = false;
	//Queda por asignar el tama�o, que supongo lo tomamos de la textura
	tam=pText->daTama�o;

}


GlobosPG::~GlobosPG()
{
}

void GlobosPG::draw(SDL_Renderer* pRender) const {
	SDL_Rect sitio;
	//Falta en el sitio el tama�o de la ventana entera
	sitio.x = pX;
	sitio.y = pY;
	if(vis && !expl)
		pTextura->draw(pRender,/*Aqui va el sitio de la ventana donde queremos dibujar*/sitio, pTextura->daTextura());
}