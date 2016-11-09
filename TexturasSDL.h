#pragma once
#include <SDL.h>
#include <string>
#include <iostream>
#include "SDL_image.h" //Para poder utilizar el IMG_Load en el bool load
#include "Fuente.h"
class TexturasSDL
{
public:
	TexturasSDL();
	~TexturasSDL();
	bool load(SDL_Renderer* pRender, std::string const& nombArch);
	void draw(SDL_Renderer* pRender, SDL_Rect& rect);
	//Método necesario para obtener el globRect que necesita la clase globo para el tamaño
	void daTamaño(int & alto, int & ancho);
	SDL_Texture* daTextura();

	//METODO DE LA FUENTE
	void renderText(SDL_Renderer *, std::string texto);

private:
	SDL_Texture* pTextura;
	int Alto, Ancho;

	//METODOS DE LA FUENTE
	static Fuente font;
	static bool loadFuente(std::string nombreArchivo, int tamaño);
	static void closeFuente();
	bool loadFromText(SDL_Renderer * pRender, std::string texto, SDL_Color color);
	SDL_Rect* rectLetra;
};