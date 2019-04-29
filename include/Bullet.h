#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

#include <string>
#include <iostream>
#include <stdbool.h>
#include <memory>

#ifndef BULLET
	#define BULLET

	class Bullet : public Component{
	private:
		Vec2 speed;
		float distanceLeft;
		int damage;

	public:
		Bullet(GameObject&, float, float, int, float, std::string, int = 1, float = 1);

		void Update(float);
		void Render();
		bool Is(std::string);
		int GetDamage();
	};
#endif