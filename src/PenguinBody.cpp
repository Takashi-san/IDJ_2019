#include "PenguinBody.h"
#include "Game.h"
#include "Sprite.h"
#include "InputManager.h"
#include "PenguinCannon.h"

PenguinBody* PenguinBody::Player;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated) {
	Player = this;

	Sprite* sp = new Sprite(associated, "assets/img/penguin.png");
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
	GameObject *go = new GameObject();
	std::weak_ptr<GameObject> weak_ptr = Game::GetInstance().GetState().AddObject(go);
	std::shared_ptr<GameObject> ptr = weak_ptr.lock();
	pcannon = weak_ptr;

	PenguinCannon* pcan = new PenguinCannon(*ptr, Game::GetInstance().GetState().GetObjectPtr(&associated));
	ptr->box.x = associated.box.x;
	ptr->box.y = associated.box.y;
	ptr->AddComponent(pcan);
}

void PenguinBody::Update(float dt) {
	InputManager& input = InputManager::GetInstance();

	if (input.IsKeyDown(W_KEY)) {
		linearSpeed += PBODY_ACCEL*dt;
		if (linearSpeed > PBODY_VEL_CAP) {
			linearSpeed = PBODY_VEL_CAP;
		}
	}
	if (input.IsKeyDown(S_KEY)) {
		linearSpeed -= PBODY_ACCEL*dt;
		if (linearSpeed < -PBODY_VEL_CAP) {
			linearSpeed = -PBODY_VEL_CAP;
		}
	}

	if (input.IsKeyDown(A_KEY)) {
		angle -= PBODY_VEL_ANG*dt;
	}
	if (input.IsKeyDown(D_KEY)) {
		angle += PBODY_VEL_ANG*dt;
	}

	speed.x = linearSpeed;
	speed.y = 0;
	speed.Rotate(angle);
	associated.box.x += speed.x*dt;
	associated.box.y += speed.y*dt;
	associated.angleDeg = angle/0.0174533;

	if (hp <= 0) {
		associated.RequestDelete();
		std::shared_ptr<GameObject> cannon = pcannon.lock();
		if (cannon) {
			cannon->RequestDelete();
		}
	}
}

void PenguinBody::Render() {

}

bool PenguinBody::Is(std::string type) {
	return !strcmp(type.c_str(), "PenguinBody");
}