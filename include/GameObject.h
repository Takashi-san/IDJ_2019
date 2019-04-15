#include "Rect.h"
#include "Component.h"

#include <iostream>
#include <vector>
#include <stdbool.h>
#include <memory>

#ifndef GAMEOBJ
	#define GAMEOBJ

	class GameObject {
	private:
		std::vector<std::shared_ptr<Component>> components;
		bool isDead;

	public:
		Rect box;

		GameObject();
		~GameObject();

		void Update(float);
		void Render();
		bool IsDead();
		void RequestDelete();
		void AddComponent(Component*);
		void RemoveComponent(Component*);
		Component* GetComponent(std::string);

	};
#endif