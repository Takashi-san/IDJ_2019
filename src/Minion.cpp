#include "Minion.h"
#include "Sprite.h"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated) {
	Sprite* sp = new Sprite(associated, "assets/img/minion.png");
	associated.AddComponent(sp);
	arc = arcOffsetDeg * 0.0174533; // pi/180.
	this->alienCenter = alienCenter;

	// Coloca na posição inicial. Mesma coisa que em Update().
	std::shared_ptr<GameObject> center = alienCenter.lock();
	Vec2 raio(150, 0);
	if (center) {
		raio.Rotate(arc);
		associated.box.x = raio.x + center->box.x + center->box.w/2 - associated.box.w/2;
		associated.box.y = raio.y + center->box.y + center->box.h/2 - associated.box.h/2;
	} else {
		associated.RequestDelete();
		return;
	}
}

void Minion::Update(float dt) {
	std::shared_ptr<GameObject> center;
	Vec2 raio(150, 0);

	center = alienCenter.lock();
	if (center) {
		arc += VEL_ANG*dt;
		raio.Rotate(arc);
		associated.box.x = raio.x + center->box.x + center->box.w/2 - associated.box.w/2;
		associated.box.y = raio.y + center->box.y + center->box.h/2 - associated.box.h/2;
	} else {
		associated.RequestDelete();
		return;
	}
}

void Minion::Render() {

}

bool Minion::Is(std::string type) {
	return !strcmp(type.c_str(), "Minion");
}

void Minion::Shoot(Vec2 pos) {

}