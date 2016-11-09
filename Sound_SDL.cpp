#include "Sound_SDL.h"



Sound_SDL::Sound_SDL(std::string musica, std::string efecto)
{
	soundInit();
	load(musica, efecto);
}


Sound_SDL::~Sound_SDL()
{
}

void Sound_SDL::load(std::string musica, std::string efecto) {
	pMusic = Mix_LoadMUS(musica.c_str());
	pEffect = Mix_LoadWAV(efecto.c_str());
}

void Sound_SDL::soundInit() {
	Mix_Init(27);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void Sound_SDL::playMusic() {
	if (Mix_PlayMusic(pMusic, -1) == -1)
		printf("Mix_PlayMusic: %s\n", Mix_GetError());
}

void Sound_SDL::playEffect() {
	Mix_PlayChannel(-1, pEffect, 0);
}

void Sound_SDL::close() {
	Mix_Quit();
}