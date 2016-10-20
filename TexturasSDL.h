#pragma once
#include <SDL.h>
#include <string>
class TexturasSDL
{
public:
	TexturasSDL();
	~TexturasSDL();
	bool load(SDL_Renderer*, std::string const& nombArch);
	void draw(SDL_Renderer*, SDL_Rect const& rect);
private:
	SDL_Texture* pTextura;
	SDL_Rect globRect;
	bool load(SDL_Renderer*, std::string const& nombArch);/*Carga la imagen del archivo. En caso de
	error lo muestra y devuelve false, y en otro caso genera la textura. Cuidado con la anterior textura. */
	void draw(SDL_Renderer*, SDL_Rect const& rect); //Dibuja toda la textura en el rectángulo rect.
	/*bool load(SDL_Renderer*, string const& nombArch, SDL_Color const& colKey) : Una vez
	cargado el archivo, y antes de generar la textura, pone el color colKey transparente.
	Puedes definir una función static SDL_Surface* load(string nombreArchivo) para cargar el
	archivo.*/
};

