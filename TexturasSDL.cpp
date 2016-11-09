#include "TexturasSDL.h"


TexturasSDL::TexturasSDL()
{
	loadFuente("MONOFONT.TTF", 12);
	rectLetra = new SDL_Rect();
	rectLetra->h = 50;
	rectLetra->w = 50;
	rectLetra->x = 50;
	rectLetra->y = 50;
}


TexturasSDL::~TexturasSDL()
{
	delete rectLetra;
}

bool TexturasSDL::load(SDL_Renderer* pRender, std::string const& nombArch) {
	//The image we will load es nombArch
	//std::string imgName{ nombArch };

	SDL_Surface* pTempSurface = nullptr;
	bool success = true;  //Loading success flag

	//Load image
	pTempSurface = IMG_Load(nombArch.c_str()); 
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
}

void TexturasSDL::draw(SDL_Renderer* pRender, SDL_Rect& rect) {
	// Draw objets 
	SDL_RenderCopy(pRender, pTextura, nullptr, & rect);  // nullptr, nullptr -> toda la textura en toda la ventana
}

void TexturasSDL::daTamaño(int & alto, int & ancho) {
	alto = Alto;
	ancho = Ancho;
}
SDL_Texture* TexturasSDL::daTextura() {
	return pTextura;
}

///////////////////////////////////////////////////////////////////////
//METODOS SOBRE LA FUENTE
///////////////////////////////////////////////////////////////////////

//Llamo a la constructora de font
Fuente TexturasSDL::font;

bool TexturasSDL::loadFuente(std::string nombreArchivo,int tamaño) {
	font.load(nombreArchivo, tamaño);
	return true;
}

bool TexturasSDL::loadFromText(SDL_Renderer * pRender, std::string texto, SDL_Color color) {
	SDL_Surface* pTempSurface = nullptr;
	bool success = true;  //Loading success flag

	//Load font
	pTempSurface = font.textSolid(texto,color);
	if (pTempSurface == nullptr) {
		std::cout << "Unable to load texto";
		success = false;
	}
	else {
		pTextura = SDL_CreateTextureFromSurface(pRender, pTempSurface);
		SDL_FreeSurface(pTempSurface);
		success = pTextura != nullptr;
	}
	return success;
}

void TexturasSDL::closeFuente() {
	font.close();
}

void TexturasSDL::renderText(SDL_Renderer * pRender, std::string texto) {
	//Primero carga la textura con loadFromText() y luego la muestra.
	SDL_Color colorLetra;
	colorLetra.r = 255;
	colorLetra.g = 255;
	colorLetra.b = 255;
	loadFromText(pRender, texto, colorLetra);
	SDL_RenderCopy(pRender, pTextura, nullptr, rectLetra);
}