#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "State.h"
#include "Timer.h"

#include <string>
#include <iostream>
#include <stdbool.h>
#include <memory>
#include <vector>
#include <queue>

#ifndef ALIEN
	#define ALIEN
	
	#define ALIEN_VEL_ANG -0.2
	#define ALIEN_SPEED 250
	#define ALIEN_REST_BASE 0.3
	#define ALIEN_REST_RAND 0.5

	class Alien : public Component{
	private:
		enum AlienState { MOVING, RESTING };
		AlienState state;
		Timer restTimer;
		Vec2 destination;

		Vec2 speed;
		int hp;
		int nMinions;
		std::vector<std::weak_ptr<GameObject>> minionArray;

	public:
		static int alienCount;

		Alien(GameObject&, int);
		~Alien();

		void Start();
		void Update(float);
		void Render();
		bool Is(std::string);
		void NotifyCollision(GameObject&);
	};
#endif