#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "State.h"
#include <string>
#include <iostream>
#include <stdbool.h>

#ifndef GAME
	class Game {
	private:
		Game(std::string, int, int);

		static Game* instance;
		SDL_Window* window;
		SDL_Renderer* renderer;
		State* state;

		Uint32 frameStart;
		float dt;
		void CalculateDeltaTime();

	public:
		~Game();

		void Run();
		SDL_Renderer* GetRenderer();
		State& GetState();
		static Game& GetInstance();
		float GetDeltaTime();
	};
	
	#define GAME	
#endif