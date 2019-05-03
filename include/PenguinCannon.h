#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

#include <string>
#include <iostream>
#include <stdbool.h>
#include <memory>

#ifndef PENGUIN_CANNON
	#define PENGUIN_CANNON

	class PenguinCannon : public Component{
	private:
		std::weak_ptr<GameObject> pbody;
		float angle;

	public:
		PenguinCannon(GameObject&, std::weak_ptr<GameObject>);

		void Update(float);
		void Render();
		bool Is(std::string);

		void Shoot();
	};
#endif