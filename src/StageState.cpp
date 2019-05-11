#include "StageState.h"

#include "Sprite.h"
#include "Sound.h"
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
#include "Data.h"
#include "EndState.h"
#include "Game.h"

StageState::StageState() {
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
	tileset = new TileSet(*ptr, 64, 64, "assets/img/tileset.png");
	TileMap *tlmp = new TileMap(*ptr, "assets/map/tileMap.txt", tileset);
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
	bgMusic.Open("assets/audio/stageState.ogg");
	bgMusic.Play(-1);
}

StageState::~StageState() {
	objectArray.clear();
}

void StageState::Update(float dt) {
	InputManager& input = InputManager::GetInstance();

	// verifica fechamento do jogo.
	if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
		popRequested = true;
	}

	// verifica condições de vitoria.
	if (PenguinBody::player == nullptr) {
		popRequested = true;
		Data::playerVictory = false;
		EndState *stage = new EndState();
		Game::GetInstance().Push(stage);
	} else if (Alien::alienCount == 0) {
		popRequested = true;
		Data::playerVictory = true;
		EndState *stage = new EndState();
		Game::GetInstance().Push(stage);
	}
	
	UpdateArray(dt);

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

void StageState::Render() {
	RenderArray();
}

void StageState::LoadAssets() {

}

void StageState::Start(){
	LoadAssets();
	
	StartArray();

	started = true;
}

void StageState::Pause() {

}

void StageState::Resume() {

}