#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Game.h"
#include <string>
#include <iostream>
#include <stdbool.h>
#include <unordered_map>

#ifndef RESOURCES
	class Resources{
	private:
		static std::unordered_map<std::string, SDL_Texture*> 	imageTable;
		static std::unordered_map<std::string, Mix_Music*> 		musicTable;
		static std::unordered_map<std::string, Mix_Chunk*> 		soundTable;

	public:
		static SDL_Texture* GetImage(std::string);
		static void ClearImages();

		static Mix_Music* GetMusic(std::string);
		static void ClearMusics();

		static Mix_Chunk* GetSound(std::string);
		static void ClearSounds();

	};	
	#define RESOURCES	
#endif