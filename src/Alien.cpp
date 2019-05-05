#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "State.h"
#include "Game.h"
#include "Minion.h"
#include "Collider.h"

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
	hp = 50;
	speed.x = 0;
	speed.y = 0;
	this->nMinions = nMinions;
	Sprite *sp = new Sprite(associated, "assets/img/alien.png");
	Collider *cl = new Collider(associated);
	associated.AddComponent(sp);
	associated.AddComponent(cl);	
}

Alien::Action::Action(ActionType type, float x, float y) {
	this->type = type;
	pos.x = x;
	pos.y = y;
}

void Alien::Start() {
	std::weak_ptr<GameObject> weak_ptr;
	std::shared_ptr<GameObject> ptr;
	float offset;

	for (int i = 0; i < nMinions; i++){
		offset = (360/nMinions)*i;

		GameObject *go = new GameObject();
		weak_ptr = Game::GetInstance().GetState().AddObject(go);
		minionArray.emplace_back(weak_ptr);
		ptr = weak_ptr.lock();
		
		Minion *mini = new Minion(*ptr, Game::GetInstance().GetState().GetObjectPtr(&associated), offset);
		ptr->box.x = 0;
		ptr->box.y = 0;
		ptr->AddComponent(mini);
	}

}

Alien::~Alien() {
	minionArray.clear();
}

void Alien::Update(float dt) {
	InputManager& input = InputManager::GetInstance();
	float dst = 999999;

	associated.angleDeg += (ALIEN_VEL_ANG/0.0174533)*dt;

	if (input.MousePress(LEFT_MOUSE_BUTTON)) {
		Action act(Action::SHOOT, input.GetMouseX() + Camera::pos.x, input.GetMouseY() + Camera::pos.y);
		taskQueue.push(act);
	}
	if (input.MousePress(RIGHT_MOUSE_BUTTON)) {
		Action act(Action::MOVE, input.GetMouseX() + Camera::pos.x - associated.box.w/2, input.GetMouseY() + Camera::pos.y - associated.box.h/2);
		taskQueue.push(act);
	}

	if (taskQueue.size() != 0) {
		int j=0;
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
				for (unsigned int i = 0; i < minionArray.size(); i++) {
					std::shared_ptr<GameObject> ptr = minionArray[i].lock();
					if (ptr) {
						float tmp = sqrt((ptr->box.x - taskQueue.front().pos.x)*(ptr->box.x - taskQueue.front().pos.x) + (ptr->box.y - taskQueue.front().pos.y)*(ptr->box.y - taskQueue.front().pos.y));
						if (tmp < dst) {
							dst = tmp;
							j = i;
						}
					}
				}

				if (minionArray[j].lock()){
					Minion *mini = static_cast<Minion*>(minionArray[j].lock()->GetComponent("Minion"));
					mini->Shoot(taskQueue.front().pos);
				}
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