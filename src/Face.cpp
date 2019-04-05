#include "Face.h"
#include "Sound.h"

Face::Face(GameObject& associated) : Component(associated) {
	hitpoints = 30;
}

void Face::Damage(int damage) {
	Component* tmp;

	hitpoints -= damage;
	if (hitpoints <= 0) {
		tmp = associated.GetComponent("Sound");
		if (tmp != nullptr){
			static_cast<Sound*>(tmp)->Play(1);
		}
		associated.RequestDelete();
	}
}

void Face::Update(float dt) {

}

void Face::Render() {

}

bool Face::Is(std::string type) {
	return !strcmp(type.c_str(), "Face");
}