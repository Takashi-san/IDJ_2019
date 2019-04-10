#include "Music.h"
#include "Game.h"

Music::Music() {
	music = nullptr;
}

Music::Music(std::string file) {
	music = nullptr;
	Open(file);
}

void Music::Play(int times = -1) {
	if (music != nullptr){
		Mix_PlayMusic(music, times);
	} else {
		// Nenhuma musica carregada.
		std::cout << "Nenhuma musica carregada para tocar.\n";
	}
}

void Music::Stop(int msToStop = 1500) {
	Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file) {
	music = Mix_LoadMUS(file.c_str());
	if (music == nullptr) {
		// Falha em carregar a musica.
		std::cout << "Falha em carregar musica: " << file.c_str() << "\n";
		std::cout << "SDL_GetError: " << SDL_GetError() << "\n";
		//exit(EXIT_FAILURE);
	}
}

bool Music::IsOpen() {
	if (music == nullptr){
		return false;
	} else {
		return true;
	}
}

Music::~Music() {
	Stop(0);
	Mix_FreeMusic(music);
}