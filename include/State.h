#define INCLUDE_SDL
#include "SDL_include.h"
#include "Sprite.h"
#include "Sound.h"
#include "Face.h"
#include "Music.h"
#include "Vec2.h"
#include "TileSet.h"
#include "TileMap.h"
#include <string>
#include <iostream>
#include <stdbool.h>
#include <memory>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

#ifndef STATE
	class State {
	private:
		//Sprite bg;
		Music music;
		bool quitRequested;
		std::vector<std::shared_ptr<GameObject>> objectArray;

		void Input();
		void AddObject(int, int);

	public:
		State();
		~State();

		bool QuitRequested();
		void LoadAssets();
		void Update(float);
		void Render();
	};

	#define STATE
#endif