#include "GameObject.h"
#include "Vec2.h"

#include <string>
#include <iostream>
#include <stdbool.h>
#include <memory>
#define _USE_MATH_DEFINES
#include <math.h>

#ifndef MINION
	#define MINION
	
	#define VEL_ANG 0.5
	#define BULLET_SPEED 500
	#define BULLET_DAMAGE 10
	#define BULLET_RANGE 1000

	class Minion : public Component{
	protected:
		std::weak_ptr<GameObject> alienCenter;
		float arc;

	public:
		Minion(GameObject&, std::weak_ptr<GameObject>, float = 0);

		void Update(float);
		void Render();
		bool Is(std::string);
		void Shoot(Vec2);
	};
#endif