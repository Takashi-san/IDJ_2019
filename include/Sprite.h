#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include <string>
#include <iostream>
#include <stdbool.h>

#ifndef SPRITE
	class Sprite {
	private:
		SDL_Texture* texture;
		int width;
		int height;
		SDL_Rect clipRect;

	public:
		Sprite();
		Sprite(std::string);
		~Sprite();
		void Open(std::string);
		void SetClip(int, int, int, int);
		void Render(int, int);
		int GetWidth();
		int GetHeight();
		bool IsOpen();
	};
	
	#define SPRITE
#endif