#include "GlobosPG.h"


GlobosPG::GlobosPG(TexturasSDL* img, int px, int py)
{
	int seed = rand();
	srand(seed);

}


GlobosPG::~GlobosPG()
{
}

void draw(SDL_Renderer*) 