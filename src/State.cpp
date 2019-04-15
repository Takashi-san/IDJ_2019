#include "State.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"

State::State() {
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
	gomp->AddComponent(tlmp);
	objectArray.emplace_back(std::move(gomp));

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
		AddObject((int)objPos.x, (int)objPos.y);
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

void State::AddObject(int mouseX, int mouseY) {
	std::shared_ptr<GameObject> go = std::shared_ptr<GameObject>(new GameObject());
    
	Sprite *sp = new Sprite(*go, "assets/img/penguinface.png");
	go->box.x = mouseX - sp->GetWidth()/2 + Camera::pos.x;
	go->box.y = mouseY - sp->GetHeight()/2 + Camera::pos.y;
	go->AddComponent(sp);

	Sound *sd = new Sound(*go, "assets/audio/boom.wav");
	go->AddComponent(sd);

	Face *fc = new Face(*go);
	go->AddComponent(fc);

	objectArray.emplace_back(std::move(go));
}
