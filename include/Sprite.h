#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Component.h"
#include <string>
#include <iostream>
#include <stdbool.h>

#ifndef SPRITE
	class Sprite : public Component{
	private:
		SDL_Texture* texture;
		int width;
		int height;
		SDL_Rect clipRect;

	public:
		Sprite(GameObject&);
		Sprite(std::string, GameObject&);
		~Sprite();
		void Open(std::string);
		void SetClip(int, int, int, int);
		void Render();
		int GetWidth();
		int GetHeight();
		bool IsOpen();

		void Update(float dt);
		bool Is(std::string type);
	};
	
	#define SPRITE
#endif