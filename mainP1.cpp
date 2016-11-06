#include "SDL.h"
#include "JuegoPG.h"
#include <iostream>

int main(int argc, char* args[]) {  // SDL require esta cabecera 
	system("chcp 1252");
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	JuegoPG* partida = new JuegoPG();
	//Antes de hacer run hay que valorar si hay algún error
	partida->run();
	system("PAUSE");
	return 0;
}