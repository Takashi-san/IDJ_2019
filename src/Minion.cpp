#include "Minion.h"
#include "Sprite.h"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated) {
	Sprite* sp = new Sprite(associated, "assets/img/minion.png");
	associated.AddComponent(sp);
	arc = arcOffsetDeg * 0.0174533; // pi/180.
	this->alienCenter = alienCenter;
}

void Minion::Update(float dt) {
	Vec2 raio(150, 0);

	arc += VEL_ANG*dt;
	raio.Rotate(arc);
	if (alienCenter.expired()) {
		associated.RequestDelete();
		std::cout << "minion kill.\n";
		return;
	}

	associated.box.x = raio.x + alienCenter.lock()->box.x + alienCenter.lock()->box.w/2 - associated.box.w/2;
	associated.box.y = raio.y + alienCenter.lock()->box.y + alienCenter.lock()->box.h/2 - associated.box.h/2;
}

void Minion::Render() {

}

bool Minion::Is(std::string type) {
	return !strcmp(type.c_str(), "Minion");
}

void Minion::Shoot(Vec2 pos) {

}