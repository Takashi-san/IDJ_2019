#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "State.h"
#include "Game.h"
#include "Minion.h"

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
	hp = 50;
	speed.x = 0;
	speed.y = 0;
	this->nMinions = nMinions;
	Sprite* sp = new Sprite(associated, "assets/img/alien.png");
	associated.AddComponent(sp);	
}

Alien::Action::Action(ActionType type, float x, float y) {
	this->type = type;
	pos.x = x;
	pos.y = y;
}

void Alien::Start() {
	/*
	std::shared_ptr<GameObject> go = std::shared_ptr<GameObject>(new GameObject());
	Minion *mini = new Minion(*go, Game::GetInstance().GetState().GetObjectPtr(&associated));
	go->AddComponent(mini);
	std::cout << go.get() << "\n";

	std::weak_ptr<GameObject> weak = Game::GetInstance().GetState().AddObject(go.get());
	minionArray.push_back(weak);
	*/
}

Alien::~Alien() {
	minionArray.clear();
}

void Alien::Update(float dt) {
	InputManager& input = InputManager::GetInstance();
	float dst;

	if (input.MousePress(LEFT_MOUSE_BUTTON)) {
		Action act(Action::SHOOT, input.GetMouseX() + Camera::pos.x, input.GetMouseY() + Camera::pos.y);
		taskQueue.push(act);
	}
	if (input.MousePress(RIGHT_MOUSE_BUTTON)) {
		Action act(Action::MOVE, input.GetMouseX() + Camera::pos.x - associated.box.w/2, input.GetMouseY() + Camera::pos.y - associated.box.h/2);
		taskQueue.push(act);
	}

	if (taskQueue.size() != 0) {
		switch (taskQueue.front().type){
			case Action::MOVE:
				speed.x = taskQueue.front().pos.x - associated.box.x;
				speed.y = taskQueue.front().pos.y - associated.box.y;
				dst = sqrt((speed.x * speed.x) + (speed.y * speed.y));
				speed.x = (speed.x/dst) * ALIEN_SPEED;
				speed.y = (speed.y/dst) * ALIEN_SPEED;

				if ((associated.box.x < taskQueue.front().pos.x + dt*abs(speed.x)) && (associated.box.x > taskQueue.front().pos.x - dt*abs(speed.x)) &&
					(associated.box.y < taskQueue.front().pos.y + dt*abs(speed.y)) && (associated.box.y > taskQueue.front().pos.y - dt*abs(speed.y))) {
					associated.box.x = taskQueue.front().pos.x;
					associated.box.y = taskQueue.front().pos.y;
					speed.x = 0;
					speed.y = 0;
					taskQueue.pop();
					break;
				}

				associated.box.x += speed.x*dt;
				associated.box.y += speed.y*dt;
				break;

			case Action::SHOOT:
				taskQueue.pop();
				break;

			default:
				break;
		}
	}

	if (hp <= 0) {
		associated.RequestDelete();
	}
}

void Alien::Render() {

}

bool Alien::Is(std::string type) {
	return !strcmp(type.c_str(), "Alien");
}