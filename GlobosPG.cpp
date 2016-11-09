#include "GlobosPG.h"


GlobosPG::GlobosPG(TexturasSDL* pText, int px, int py):
	pTexturaG(pText)
{
	tamPos = new SDL_Rect();
	puntos = 10;
	if (rand() % 100 < PVIS) vis = true; else vis = false;
	expl = false;
	tamPos->x = px;
	tamPos->y = py;
	pText->daTamaño(tamPos->h,tamPos->w);
}


GlobosPG::~GlobosPG()
{
	delete tamPos;
	pTexturaG=nullptr;
}

void GlobosPG::draw(SDL_Renderer* pRender) const {
	if(vis && !expl)
		pTexturaG->draw(pRender, *tamPos);
}

//Devuelve true si el globo desaparece
bool GlobosPG::onClick (int pmx, int pmy){
	bool desaparece = false;
	if (!expl && vis && pmy >= tamPos->y && pmy <= tamPos->y + tamPos->h &&  pmx >= tamPos->x && pmx <= tamPos->x + tamPos->w) {
		expl = true;
		desaparece = true;
		vis = false;
	}
	return desaparece;
}

//Devuelve true si el globo desaparece
bool GlobosPG::update(){
	bool desaparece = false;
	if (vis && !expl){
		//Aquí se genera un aleatorio para ver si el globo se deshincha o no
		if (rand() % 100 < PDES) {
			tamPos->h -= DT;
			tamPos->w -= DT;
			puntos += AP;
			if (tamPos->h <= 0 || tamPos->w <= 0) {
				vis = false;
				desaparece = true;
				expl = true;
			}
		}
	}
	if (!vis && !expl)
		//Generamos un aleatorio nueva para ver si un globo invisible se vuelve visible
		if (rand() % 100 < PVIS) vis = true; else vis = false;
	return desaparece;
}