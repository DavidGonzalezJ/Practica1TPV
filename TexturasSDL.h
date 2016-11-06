#pragma once
#include <SDL.h>
#include <string>
#include <iostream>
#include "SDL_image.h"//Para poder utilizar el IMG_Load en el bool load
//#include "Fuente.h"
class TexturasSDL
{
public:
	TexturasSDL();
	~TexturasSDL();
	bool load(SDL_Renderer* pRender, std::string const& nombArch);
	void draw(SDL_Renderer* pRender, SDL_Rect /*const*/& rect);
	//Método necesario para obtener el globRect que necesita la clase globo para el tamaño
	void daTamaño(int & alto, int & ancho);
	SDL_Texture* daTextura();
private:
	SDL_Texture* pTextura;
	//Seguramente no necesite el globRect para el tamaño y me valgan simplemente dos int
	/*SDL_Rect globRect;*/
	//Aqui lo hago con int
	int Alto, Ancho;
	//bool load(SDL_Renderer* pRender, std::string const& nombArch, SDL_Color const& colKey); 
	/*: Una vez
	cargado el archivo, y antes de generar la textura, pone el color colKey transparente.
	Puedes definir una función static SDL_Surface* load(string nombreArchivo) para cargar el
	archivo.*/

	//METODOS DE LA FUENTE

	//static Fuente font;
	/*static bool loadFuente(std::string nombreArchivo, int tamaño);
	static void closeFuente();
	bool TexturasSDL::loadFromText(SDL_Renderer * pRender, std::string texto, SDL_Color color);
	void renderText(SDL_Renderer *, int px, int py, std::string texto);*/
};