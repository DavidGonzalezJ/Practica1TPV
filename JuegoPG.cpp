#include "JuegoPG.h"
#include <iostream>
using namespace std;
//Implementación del programa

JuegoPG::JuegoPG()
{
}


JuegoPG::~JuegoPG()
{
}

void JuegoPG::run() {
	if (!error) {
		// Uint32 MSxUpdate = 500;  
		cout << "PLAY \n";
		Uint32 lastUpdate = SDL_GetTicks();
		render();
		handle_event();
		while (!exit && !salir) {
			if (SDL_GetTicks() - lastUpdate >= MSxUpdate) { // while(elapsed >= MSxUpdate)
				update();
				lastUpdate = SDL_GetTicks();
			}
			render();
			handle_event();
		}
		if (exit) cout << "EXIT \n";
		else cout << "Has obtenido " << puntuacion << "puntos\n";
		SDL_Delay(1000); //cin.get();
	}
}
void JuegoPG::handle_event(){
	SDL_Event e;
	if (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) onExit();
		else if (e.type == SDL_MOUSEBUTTONUP) {
			if (e.button.button == SDL_BUTTON_LEFT) {
				cout << "CLICK";
				onClick(e.button.x, e.button.y);
			}
			// else if(...)    
		}
		// else if(...)  
	}
}