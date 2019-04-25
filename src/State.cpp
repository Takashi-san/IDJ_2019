#include "State.h"

#include "Sound.h"
#include "TileSet.h"
#include "TileMap.h"
#include "Vec2.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"

State::State() {
	started = false;
	quitRequested = false;

	// Background
	std::shared_ptr<GameObject> go = std::shared_ptr<GameObject>(new GameObject());
	go->box.x = 0;
	go->box.y = 0;
	Sprite *sp = new Sprite(*go, "assets/img/ocean.jpg");
	CameraFollower *cmfl = new CameraFollower(*go);
	go->AddComponent(sp);
	go->AddComponent(cmfl);
	objectArray.emplace_back(std::move(go));
	
	// TileMap
	std::shared_ptr<GameObject> gomp = std::shared_ptr<GameObject>(new GameObject());
	gomp->box.x = 0;
	gomp->box.y = 0;
	TileSet *tlst = new TileSet(*gomp, 64, 64, "assets/img/tileset.png");
	TileMap *tlmp = new TileMap(*gomp, "assets/map/tileMap.txt", tlst);
	tlmp->SetParallax(1);
	gomp->AddComponent(tlmp);
	objectArray.emplace_back(std::move(gomp));

	// Alien
	std::shared_ptr<GameObject> goali = std::shared_ptr<GameObject>(new GameObject());
	Alien *alien = new Alien(*goali, 3);
	goali->box.x = 512 - goali->box.w/2;
	goali->box.y = 300 - goali->box.h/2;
	goali->AddComponent(alien);
	objectArray.emplace_back(std::move(goali));

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

	Camera::Update(dt);

	if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}

	if (input.KeyPress(SPACE_KEY)) {
		Vec2 objPos = Vec2(200, 0);
		objPos.Rotate(-M_PI + M_PI*(rand() % 1001)/500.0);
		objPos = objPos + Vec2(input.GetMouseX(), input.GetMouseY());
	}
	
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
	}
	
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i]->IsDead()) {
			objectArray.erase(objectArray.begin() + i);
		}
	}
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

	objectArray.push_back(s_ptr);
	if (started) {
		objectArray.end()->get()->Start();
	}

	weak = objectArray[objectArray.size() - 1];
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