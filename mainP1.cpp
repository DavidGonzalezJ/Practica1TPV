//Patricia Cabrero y David González
#include "SDL.h"
#include "JuegoPG.h"
#include <iostream>

int main(int argc, char* args[]) {  // SDL require esta cabecera 
	system("chcp 1252");
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	JuegoPG* partida = new JuegoPG();
	//Valora si hay errores dentro del run
	partida->run();
	//Comento la siguiente linea para que se cierre una vez pulsas el ultimo ok
	//system("PAUSE");
	return 0;
}