#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "GameObject.h"
#include "Component.h"
#include <string>
#include <iostream>
#include <stdbool.h>

#ifndef SOUND
	class Sound : public Component{
	private:
		Mix_Chunk* chunk;
		int channel;

	public:
		Sound(GameObject&);
		Sound(GameObject&, std::string);
		~Sound();

		void Play(int);
		void Stop();
		void Open(std::string);
		bool IsOpen();

		void Update(float);
		void Render();
		bool Is(std::string);
	};	
	#define SOUND	
#endif