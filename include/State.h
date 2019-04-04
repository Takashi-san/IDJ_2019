#define INCLUDE_SDL
#include "SDL_include.h"
#include "Sprite.h"
#include "Music.h"
#include <string>
#include <iostream>
#include <stdbool.h>

#ifndef STATE
	class State {
	private:
		Sprite bg;
		Music music;
		bool quitRequested;

	public:
		State();
		bool QuitRequested();
		void LoadAssets();
		void Update(float);
		void Render();
	};

	#define STATE
#endif