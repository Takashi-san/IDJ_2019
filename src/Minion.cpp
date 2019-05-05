#include "Minion.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Game.h"
#include "State.h"
#include "Collider.h"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated) {
	Sprite* sp = new Sprite(associated, "assets/img/minion.png");
	float escala = 1.0 + float(std::rand()/float(RAND_MAX/0.5));
	sp->SetScale(escala, escala);
	Collider *cl = new Collider(associated);
	associated.AddComponent(sp);
	associated.AddComponent(cl);
	
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
		arc += MINION_VEL_ANG*dt;
		associated.angleDeg = arc/0.0174533;
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
	std::weak_ptr<GameObject> weak_ptr;
	std::shared_ptr<GameObject> ptr;

	GameObject *go = new GameObject();
	weak_ptr = Game::GetInstance().GetState().AddObject(go);
	ptr = weak_ptr.lock();

	float angle = atan2(pos.y - (associated.box.y + associated.box.h/2), pos.x - (associated.box.x + associated.box.w/2));
	Bullet *bam = new Bullet(*ptr, angle, MINION_BULLET_SPEED, MINION_BULLET_DAMAGE, MINION_BULLET_RANGE, "assets/img/minionbullet2.png", 3, 0.04);
	ptr->box.Centered(associated.box.Center());
	ptr->AddComponent(bam);
}