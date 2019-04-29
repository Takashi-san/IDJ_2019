#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

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

	class Alien : public Component{
	private:
		class Action {
		public:
			enum ActionType {
				MOVE,
				SHOOT
			};
			ActionType type;
			Vec2 pos;

			Action(ActionType, float, float);
		};

		Vec2 speed;
		int hp;
		int nMinions;
		std::queue<Action> taskQueue;
		std::vector<std::weak_ptr<GameObject>> minionArray;

	public:
		Alien(GameObject&, int);
		~Alien();

		void Start();
		void Update(float);
		void Render();
		bool Is(std::string);
	};
#endif