#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

#include <string>
#include <iostream>
#include <stdbool.h>
#include <memory>

#ifndef PENGUIN_BODY
	#define PENGUIN_BODY

	class PenguinBody : public Component{
	private:
		std::weak_ptr<GameObject> pcannon;
		Vec2 speed;
		float linearSpeed;
		float angle;
		int hp;

	public:
		static PenguinBody* Player;
		
		PenguinBody(GameObject&);
		~PenguinBody();

		void Start();
		void Update(float);
		void Render();
		bool Is(std::string);
	};
#endif