#include <string>
#include <iostream>
#include <stdbool.h>

#ifndef COMPONENT
	class GameObject;

	class Component {
	protected:
		GameObject& associated;

	public:	
		Component(GameObject& associated);
		virtual ~Component();

		virtual void Update(float dt) = 0;
		virtual void Render() = 0;
		virtual bool Is(std::string type) = 0;

	};
	#define COMPONENT
	#include "GameObject.h"
#endif