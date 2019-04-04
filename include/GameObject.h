#include "Rect.h"
#include <iostream>
#include <vector>
#include <stdbool.h>

#ifndef GAMEOBJ
	class Component;

	class GameObject {
	private:
		std::vector<Component*> components;
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
	#define GAMEOBJ
	#include "Component.h"
#endif