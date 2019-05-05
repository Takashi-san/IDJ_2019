#include "Collider.h"
#include <string.h>

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated) {
	this->scale = scale;
	this->offset = offset;
}

void Collider::Update(float dt) {
	box.w = associated.box.w * scale.x;
	box.h = associated.box.h * scale.y;
	
	box.Centered(associated.box.Center());

	box.x += offset.GetRotated(associated.angleDeg/0.0174533).x;
	box.y += offset.GetRotated(associated.angleDeg/0.0174533).y;
}

void Collider::Render() {

}

bool Collider::Is(std::string type) {
	return !strcmp(type.c_str(), "Collider");
}

void Collider::SetOffset(Vec2 offset) {
	this->offset = offset;
}

void Collider::SetScale(Vec2 scale) {
	this->scale = scale;
}