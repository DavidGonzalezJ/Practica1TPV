#include "TexturasSDL.h"


TexturasSDL::TexturasSDL()
{
}


TexturasSDL::~TexturasSDL()
{
}

bool load(SDL_Renderer* pRender, std::string const& nombArch,SDL_Texture* & pTextura) {
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
		SDL_FreeSurface(pTempSurface);
		success = pTextura != nullptr;
	}
	return success;
}/*Carga la imagen del archivo. En caso de error lo muestra y devuelve false, y en otro caso genera la textura. Cuidado con la anterior textura. */

void draw(SDL_Renderer* pRender, SDL_Rect const& rect,SDL_Texture* pTextura) {
	//Clear the window to background color 
	SDL_RenderClear(pRender);

	// Draw objets 
	SDL_RenderCopy(pRender, pTextura, nullptr /*Toda la textura*/, & rect /*En el rectángulo rect*/);  // nullptr, nullptr -> toda la textura en toda la ventana

	//Show the window
	SDL_RenderPresent(pRender);
}//Dibuja toda la textura en el rectángulo rect.