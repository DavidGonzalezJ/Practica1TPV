#include "JuegoPG.h"
#include <iostream>

JuegoPG::JuegoPG()
{
	srand(SDL_GetTicks());
	initSDL();
	initMusic();
	initGlobos();
	puntuacion=0;
	error = false;
	exit = false;
}


JuegoPG::~JuegoPG()
{
	freeGlobos();
	closeSDL();
}

void JuegoPG::muestraMensaje(std::string info, std::string boton) {
	//SDL_DisplayMode dm;
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, info.c_str(), boton.c_str(), nullptr);
}

void JuegoPG::initMusic() {
	sonido = new Sound_SDL("AllStar.wav", "Hitmarker.wav");
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
			if (pRender == nullptr){
				std::cout << "Renderer could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
				success = false;
			}
		}
	}

	return success;
}

//Este metodo borra el pWindow y el pRender y cierra el SDL
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
	pTexturaG.emplace_back(new TexturasSDL());
	//Creamos un SDL_Rect para pasarselo después al render
	fRect = new SDL_Rect();
	fRect->h = SCREEN_HEIGHT;
	fRect->w = SCREEN_WIDTH;
	fRect->x = 0;
	fRect->y = 0;
	//Ahora creamos los globos
	for (int n = 0; n < numGlobos; ++n){
		pGlobos.emplace_back(new GlobosPG(pTexturaG[0], rand() % 720, rand() % 480));
	}
	return success;
}

void JuegoPG::freeGlobos() {
	for (int n = 0; n < numGlobos; ++n){
		delete pGlobos[n];
		pGlobos[n] = nullptr;
	}
	delete fRect;
	delete pTexturaG[0];
	pTexturaG[0] = nullptr;
	delete pTexturaG[1];
	pTexturaG[1] = nullptr;
	delete pTexturaG[2];
	pTexturaG[2] = nullptr;
}



void JuegoPG::run() {
	if (!error) {
		Uint32 MSxUpdate = 500;
		std::cout << "PLAY \n";
		Uint32 lastUpdate = SDL_GetTicks();
		muestraMensaje("PLAY", "Ready?");
		sonido->playMusic();
		render();
		handle_event();
		while (!exit && !error && numGlobos>0) {
			if (SDL_GetTicks() - lastUpdate >= MSxUpdate){ // while(elapsed >= MSxUpdate)
				update();
				lastUpdate = SDL_GetTicks();
			}
			render();
			handle_event();
		}

		if (exit) std::cout << "EXIT \n";
		else std::cout << "Has obtenido " << puntuacion << " puntos\n";
		std::string puntos = std::to_string(puntuacion);
		muestraMensaje("ENHORABUENA", "Has obtenido " + puntos);
		sonido->close();
		SDL_Delay(1000); //cin.get();
	}
}

void JuegoPG::onExit() {
	exit = true;
}

void JuegoPG::handle_event(){
	SDL_Event e;
	if (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) onExit();
		else if (e.type == SDL_MOUSEBUTTONUP) {
			if (e.button.button == SDL_BUTTON_LEFT) {
				std::cout << "CLICK \n";
				onClick(e.button.x, e.button.y);
			}
			// else if(...)    
		}
	}
}

void JuegoPG::render()const{
	SDL_RenderClear(pRender);
	pTexturaG[1]->draw(pRender, *fRect);

	for each (GlobosPG* g in pGlobos)
	{
		g->draw(pRender);
	}
	std::string puntos = std::to_string(puntuacion);
	pTexturaG[2]->renderText(pRender, puntos);
	SDL_RenderPresent(pRender);
}

bool JuegoPG::gameOver(){
	return numGlobos <= 0;
}

void JuegoPG::update() {
	for each (GlobosPG* g in pGlobos)
	{
		if (g->update()) {
			--numGlobos;
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