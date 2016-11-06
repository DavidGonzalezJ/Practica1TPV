#include "TexturasSDL.h"


TexturasSDL::TexturasSDL()
{
}


TexturasSDL::~TexturasSDL()
{
}

bool TexturasSDL::load(SDL_Renderer* pRender, std::string const& nombArch) {
	//The image we will load es nombArch
	//std::string imgName{ nombArch };

	SDL_Surface* pTempSurface = nullptr;
	bool success = true;  //Loading success flag

						  //Load image
	pTempSurface = /*nombArch.c_str();*/ /*SDL_LoadBMP*/IMG_Load(nombArch.c_str());  // si usamos string: bmpName.c_str() 
	if (pTempSurface == nullptr) {
		std::cout << "Unable to load image " << nombArch << "! \nSDL Error: " << SDL_GetError() << '\n';
		success = false;
	}
	else {
		pTextura = SDL_CreateTextureFromSurface(pRender, pTempSurface);
		//La siguiente función me devuelve el ancho y el alto de la textura
		SDL_QueryTexture(pTextura, NULL, NULL, &Ancho, &Alto);
		SDL_FreeSurface(pTempSurface);
		success = pTextura != nullptr;
	}
	return success;
}/*Carga la imagen del archivo. En caso de error lo muestra y devuelve false, y en otro caso genera la textura. Cuidado con la anterior textura. */

void TexturasSDL::draw(SDL_Renderer* pRender, SDL_Rect /*const*/& rect) {
	//ESTO SEGURAMENTE NO LO TENGA QUE HACER ESTE METODO
	//Clear the window to background color 
	//SDL_RenderClear(pRender);

	// Draw objets 
	SDL_RenderCopy(pRender, pTextura, nullptr /*Toda la textura*/, & rect /*En el rectángulo rect*/);  // nullptr, nullptr -> toda la textura en toda la ventana

	//ES POSIBLE QUE ESTO TAMPOCO LO TENGA QUE HACER
	//Show the window
	//SDL_RenderPresent(pRender);
}//Dibuja toda la textura en el rectángulo rect.

void TexturasSDL::daTamaño(int & alto, int & ancho) {
	alto = Alto;
	ancho = Ancho;
}
SDL_Texture* TexturasSDL::daTextura() {
	return pTextura;
}

///////////////////////////////////////////////////////////////////////
//METODOS SOBRE LA FUENTE

//Llamo a la constructora de font
//Fuente TexturasSDL::font;
/*
bool TexturasSDL::loadFuente(std::string nombreArchivo,int tamaño) {
	font.load(nombreArchivo, tamaño);
	return true;
}

//A esto le falta algo
bool TexturasSDL::loadFromText(SDL_Renderer * pRender, std::string texto, SDL_Color color) {
	SDL_Surface* pTempSur = font.textSolid(texto, color);
	return true;
}

void TexturasSDL::closeFuente() {
	font.close();
}

void TexturasSDL::renderText(SDL_Renderer * pRender,int px,int py,std::string texto) {
	//Primero carga la textura con loadFromText() y luego la muestra.
}
*/