#include "PenguinBody.h"
#include "Sprite.h"
#include "PenguinCannon.h"

PenguinBody* PenguinBody::Player;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated) {
	Player = this;

	Sprite* sp = new Sprite(associated, "asstes/img/penguin.png");
	associated.AddComponent(sp);

	linearSpeed = 0;
	angle = 0;
	hp = 100;
	speed.x = 0;
	speed.y = 0;
}

PenguinBody::~PenguinBody() {
	Player = nullptr;
}

void PenguinBody::Start() {
	PenguinCannon* pcan = new PenguinCannon(associated, );
}