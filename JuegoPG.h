#pragma once
#include <SDL.h>
#include <vector>
#include "GlobosPG.h"
#include "TexturasSDL.h"
#include "Sound_SDL.h"
//Cabeceras, declaraciones de todo lo necesario para el juego
class JuegoPG
{
public:
	JuegoPG();
	~JuegoPG();
	void run();
	//void onExit();
private:

	int numGlobos = 20;
	const int SCREEN_WIDTH = 640;   //Screen dimension
	const int SCREEN_HEIGHT = 480;  //Screen dimension
	SDL_Renderer* pRender; 
	SDL_Window* pWindow; 
	SDL_Color color;
	SDL_Rect* fRect; //Este será el rectangulo de fondo de la textura
	std::vector<GlobosPG*> pGlobos;
	std::vector<TexturasSDL*> pTexturaG;
	Sound_SDL* sonido;

	int tiempo, puntuacion;
	bool error, exit;
	//int lastUpdate, MSxUpdate;
	bool gameOver();
	bool initSDL(); // Inicia el renderizador.En caso de error, muestra un mensaje y deja todos los atributos con valores nulos.
	void closeSDL(); //Libera los atributos iniciados en initSDL.
	bool initGlobos();//Crea las texturas para los globos y todos los globos.
	void freeGlobos(); //Libera los elementos creados en initGlobos.
	void render() const;//Limpia el buffer, pide a todos los globos que se dibujen y lo muestra.
	void onClick(int pmx, int pmy); //Pide a los globos que comprueben si lo han pinchado(máximo uno) y actualiza el número de globos que quedan activos y los puntos obtenidos al pinchar globos.
	void update(); //Pide a todos los globos que actualicen su estado, y actualiza el número de globos que quedan activos.
	void handle_event(); /*Comprueba si se ha producido el evento SDL_Quit o el evento soltar el botón
	izquierdo del ratón. Para el caso SDL_Quit, ejecuta onExit(). En el otro caso, ejecuta onClick(),
	pasando como argumentos la posición del ratón.*/
	void onExit();
	void initMusic();
	void muestraMensaje();
};

