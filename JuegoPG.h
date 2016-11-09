#pragma once
#include <SDL.h>
#include <vector>
#include "GlobosPG.h"
#include "TexturasSDL.h"
#include "Sound_SDL.h"

class JuegoPG
{
public:
	JuegoPG();
	~JuegoPG();
	void run();
	
private:

	int numGlobos = 20;
	const int SCREEN_WIDTH = 640;   //Screen dimension
	const int SCREEN_HEIGHT = 480;  //Screen dimension
	SDL_Renderer* pRender; 
	SDL_Window* pWindow; 
	SDL_Rect* fRect; //Este será el rectangulo de fondo de la textura
	std::vector<GlobosPG*> pGlobos;
	std::vector<TexturasSDL*> pTexturaG;
	Sound_SDL* sonido;

	int puntuacion;
	bool error, exit;
	bool gameOver();
	bool initSDL(); 
	void closeSDL(); 
	bool initGlobos();
	void freeGlobos();
	void render() const;
	void onClick(int pmx, int pmy); 
	void update(); 
	void handle_event();
	void onExit();
	void initMusic();
	void muestraMensaje(std::string info, std::string boton);
};

