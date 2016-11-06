#include "GlobosPG.h"


GlobosPG::GlobosPG(TexturasSDL* pText, int px, int py):
	pTexturaG(pText)
{
	tamPos = new SDL_Rect();
	puntos = 10;
	//NO ESTOY SEGURO DE QUE ESTO FUNCIONE COMO DEBE (los aleatorios)
	//Aquí asignamos la posición (genera una aleatoria cada vez que se llame)
	//Aquí asignamos los booleanos
	if (rand() % 100 < PVIS) vis = true; else vis = false;
	expl = false;
	//Queda por asignar el tamaño, que supongo lo tomamos de la textura
	tamPos->x = px;
	tamPos->y = py;
	pText->daTamaño(tamPos->h,tamPos->w);
}


GlobosPG::~GlobosPG()
{
	delete tamPos;
	pTexturaG=nullptr;
}

//No estoy muy seguro sobre el segundo parametro del draw
void GlobosPG::draw(SDL_Renderer* pRender) const {
	if(vis && !expl)
		pTexturaG->draw(pRender,/*Aqui va el sitio de la ventana donde queremos dibujar*/*tamPos);
}

//DEVUELVE TRUE SI EL GLOBO SE PINCHA Y DESAPARECE
bool GlobosPG::onClick (int pmx, int pmy){
	bool desaparece = false;
	if (!expl && vis && pmy >= tamPos->y && pmy <= tamPos->y + tamPos->h &&  pmx >= tamPos->x && pmx <= tamPos->x + tamPos->w) {
		expl = true;
		desaparece = true;
		vis = false;
	}
	return desaparece;
}

//Devuelve true si el globo desaparece para siempre (pero no sé si se considera explotado)
//Este no sé si funciona como debería por la parte de los random
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
		//Generamos una semilla nueva para ver si un globo invisible se vuelve visible
		if (rand() % 100 < PVIS) vis = true; else vis = false;
	return desaparece;
}