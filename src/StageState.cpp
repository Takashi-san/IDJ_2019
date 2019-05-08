#include "State.h"

#include "Sound.h"
#include "TileSet.h"
#include "TileMap.h"
#include "Vec2.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "Minion.h"
#include "PenguinBody.h"
#include "Collision.h"
#include "Collider.h"

State::State() {
	started = false;
	quitRequested = false;
	objectArray.clear();

	std::weak_ptr<GameObject> weak_ptr;
	std::shared_ptr<GameObject> ptr;

	// Background
	GameObject *gobg = new GameObject();
	weak_ptr = AddObject(gobg);
	ptr = weak_ptr.lock();
	ptr->box.x = 0;
	ptr->box.y = 0;
	Sprite *sp = new Sprite(*ptr, "assets/img/ocean.jpg");
	CameraFollower *cmfl = new CameraFollower(*ptr);
	ptr->AddComponent(sp);
	ptr->AddComponent(cmfl);
	
	// TileMap
	GameObject *gomp = new GameObject();
	weak_ptr = AddObject(gomp);
	ptr = weak_ptr.lock();
	TileSet *tlst = new TileSet(*ptr, 64, 64, "assets/img/tileset.png");
	TileMap *tlmp = new TileMap(*ptr, "assets/map/tileMap.txt", tlst);
	tlmp->SetParallax(1);
	ptr->box.x = 0;
	ptr->box.y = 0;
	ptr->AddComponent(tlmp);

	// Alien
	GameObject *goali = new GameObject();
	weak_ptr = AddObject(goali);
	ptr = weak_ptr.lock();
	Alien *alien = new Alien(*ptr, 5);
	ptr->box.x = 512 - goali->box.w/2;
	ptr->box.y = 300 - goali->box.h/2;
	ptr->AddComponent(alien);

	/*
	// Minion
	GameObject *gomini = new GameObject();
	weak_ptr = AddObject(gomini);
	ptr = weak_ptr.lock();
	Minion *mini = new Minion(*ptr, GetObjectPtr(goali), 15);
	ptr->box.x = 0;
	ptr->box.y = 0;
	ptr->AddComponent(mini);
	*/

	// PenguinBody
	GameObject *gopen = new GameObject();
	weak_ptr = AddObject(gopen);
	ptr = weak_ptr.lock();
	PenguinBody *penb = new PenguinBody(*ptr);
	ptr->box.x = 704;
	ptr->box.y = 640;
	ptr->AddComponent(penb);
	Camera::Follow(ptr.get());

	// BGM
	music.Open("assets/audio/stageState.ogg");
	music.Play(-1);
}

State::~State() {
	objectArray.clear();
}

void State::LoadAssets() {

}

void State::Update(float dt) {
	InputManager& input = InputManager::GetInstance();

	// verifica fechamento do jogo.
	if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}
	
	// update dos game object.
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
	}
	
	// deleta objetos que devem sumir.
	for (std::vector<std::shared_ptr<GameObject>>::iterator i = objectArray.begin(); i < objectArray.end(); i++) {
		if (i->get()->IsDead()) {
			i = objectArray.erase(i);
			i--;
		}
	}

	// update dos colliders.
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		Collider *coli = static_cast<Collider*>(objectArray[i]->GetComponent("Collider"));
		if (coli != nullptr) {
			coli->Update(dt);
		}
	}

	// verifica colisão dos objetos.
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		Collider *coli = static_cast<Collider*>(objectArray[i]->GetComponent("Collider"));
		if (coli != nullptr) {
			for (unsigned int j = i+1; j < objectArray.size(); j++) {
				Collider *colj = static_cast<Collider*>(objectArray[j]->GetComponent("Collider"));
				if (colj != nullptr) {
					if (Collision::IsColliding(coli->box, colj->box, objectArray[i]->angleDeg/0.0174533, objectArray[j]->angleDeg/0.0174533)) {
						objectArray[i]->NotifyCollision(*(objectArray[j]));
						objectArray[j]->NotifyCollision(*(objectArray[i]));
					}
				}
			}
		}
	}

	Camera::Update(dt);
}

void State::Render() {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Render();
	}
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::Start(){
	LoadAssets();
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Start();
	}

	started = true;
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
	std::shared_ptr<GameObject> s_ptr(go);
	std::weak_ptr<GameObject> weak;

	objectArray.emplace_back(s_ptr);
	if (started) {
		objectArray.back()->Start();
	}

	weak = objectArray.back();
	return weak;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
	std::weak_ptr<GameObject> weak;

	for (unsigned int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i].get() == go) {
			weak = objectArray[i];
			return weak;
		}
	}

	return weak;
}