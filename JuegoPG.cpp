#include "JuegoPG.h"
#include <iostream>
using namespace std;
//Implementación del programa guay

JuegoPG::JuegoPG()
{
	srand(SDL_GetTicks());
	initSDL();
	initMusic();
	initGlobos();
	color; //no asignada
	tiempo; 
	puntuacion=0;
	error = false;
	exit = false;
}


JuegoPG::~JuegoPG()
{
	freeGlobos();
	closeSDL();
}

void JuegoPG::muestraMensaje() {
	SDL_DisplayMode dm;
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
		"PLAY GAME", "Ready?", nullptr);
}

void JuegoPG::initMusic() {
	sonido = new Sound_SDL("AllStar.wav", "Hitmarker.wav");
	//sonido->soundInit();
	//sonido->load("MusicaFondo.mp3","Hitmarker.wav");
}

//Este metodo da valor al pRender y al pWindow
bool JuegoPG::initSDL() {

	bool success = true; //Initialization flag

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL could not initialize! \nSDL_Error: " << SDL_GetError() << '\n';
		success = false;
	}
	else {
		//Create window: SDL_CreateWindow("SDL Hello World", posX, posY, width, height, SDL_WINDOW_SHOWN);
		pWindow = SDL_CreateWindow("GloboJuego", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (pWindow == nullptr){
			std::cout << "Window could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
			success = false;
		}
		else {
			//Get window surface:
			pRender = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
			//SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255); //Set background color to black 
			if (pRender == nullptr){
				std::cout << "Renderer could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
				success = false;
			}
		}
	}

	return success;
}

//Este metodo borra el pWindow y el pRender y desinicializa el SDL
void JuegoPG::closeSDL() {

	SDL_DestroyRenderer(pRender);
	pRender = nullptr;
	SDL_DestroyWindow(pWindow);
	pWindow = nullptr;
	SDL_Quit();
}

//Crea las texturas para los globos y los globos
bool JuegoPG::initGlobos(){
	bool success = true; //Initialization flag
	//En esta parte asignamos las texturas
	pTexturaG.emplace_back(new TexturasSDL());
	pTexturaG[0]->load(pRender, "Globo.png");
	pTexturaG.emplace_back(new TexturasSDL());
	pTexturaG[1]->load(pRender, "fondo.png");
	//Esta parte podríamos hacerla de otra forma para no tener que
	//Pasar un SDL_Rect al render, sino un nullptr
	fRect = new SDL_Rect();
	fRect->h = SCREEN_HEIGHT;
	fRect->w = SCREEN_WIDTH;
	fRect->x = 0;
	fRect->y = 0;
	//Ahora creamos los globos
	for (int n = 0; n < numGlobos; ++n){//numero de globos empezamos con uno para ver si funciona
		//Aquí asignamos los booleanos
		//pGlobos.emplace_back(new GlobosPG(pTexturaG, n*100, n*160));
		pGlobos.emplace_back(new GlobosPG(pTexturaG[0], rand() % 720, rand() % 480));
	}
	return success;
}

void JuegoPG::freeGlobos() {
	for (int n = 0; n < numGlobos; ++n){//numero de globos empezamos con uno para ver si funciona
		delete pGlobos[n];
		pGlobos[n] = nullptr;
	}
	delete fRect;
	delete pTexturaG[0];
	pTexturaG[0] = nullptr;
	delete pTexturaG[1];
	pTexturaG[1] = nullptr;
}



void JuegoPG::run() {
	if (!error) {
		Uint32 MSxUpdate = 500;
		cout << "PLAY \n";
		Uint32 lastUpdate = SDL_GetTicks();
		//Aquí saco el mensaje
		muestraMensaje();
		//Aquí pongo a sonar la musica
		sonido->playMusic();
		render();
		handle_event();
		//No sé en qué momento deberían cambiar de valor exit y error
		while (!exit && !error && numGlobos>0) {
			if (SDL_GetTicks() - lastUpdate >= MSxUpdate){ // while(elapsed >= MSxUpdate)
				update();
				lastUpdate = SDL_GetTicks();
			}
			render();
			handle_event();
		}

		if (exit) cout << "EXIT \n";
		else cout << "Has obtenido " << puntuacion << " puntos\n";
		//Aquí apago el sonido
		sonido->close();
		SDL_Delay(1000); //cin.get();
	}
}

void JuegoPG::onExit() {
	//Supongo que ejecuta la destructora del juego
	exit = true;

}

void JuegoPG::handle_event(){
	SDL_Event e;
	if (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) onExit();
		else if (e.type == SDL_MOUSEBUTTONUP) {
			if (e.button.button == SDL_BUTTON_LEFT) {
				cout << "CLICK \n";
				onClick(e.button.x, e.button.y);
			}
			// else if(...)    
		}
	}
}

void JuegoPG::render()const{
	SDL_RenderClear(pRender);
	//Creamos y dibujamos la textura para el fondo
	/*TexturasSDL* fondo = new TexturasSDL();
	fondo->load(pRender, "fondo.png");
	SDL_Rect* fRect = new SDL_Rect();
	fRect->h = SCREEN_HEIGHT;
	fRect->w = SCREEN_WIDTH;
	fRect->x = 0;
	fRect->y = 0;*/
	pTexturaG[1]->draw(pRender, *fRect);

	for each (GlobosPG* g in pGlobos)
	{
		g->draw(pRender);
	}
	SDL_RenderPresent(pRender);//Este no sé si va dentro o fuera del bucle
}
bool JuegoPG::gameOver(){
	return numGlobos <= 0;
}
void JuegoPG::update() {
	for each (GlobosPG* g in pGlobos)
	{
		if (g->update()) {
			--numGlobos;
			//Hay que actualizar el numero de globos que quedan activos (no sé si está bien)
			g = nullptr;
		}
	}

}
void JuegoPG::onClick(int mpx, int mpy){
	
	for each (GlobosPG* g in pGlobos)
	{
		if (g->onClick(mpx, mpy)) {
			puntuacion += g->puntos;
			sonido->playEffect();
			--numGlobos;
		}
	}
}