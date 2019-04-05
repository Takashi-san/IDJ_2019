#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "GameObject.h"
#include "Component.h"
#include <string>
#include <iostream>
#include <stdbool.h>

#ifndef FACE
	class Face : public Component{
	private:
		int hitpoints;

	public:
		Face(GameObject&);

		void Damage(int);

		void Update(float);
		void Render();
		bool Is(std::string);
	};	
	#define FACE	
#endif