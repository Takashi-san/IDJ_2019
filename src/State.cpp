#include "State.h"

State::State() {
	quitRequested = false;
    //bg.Open("assets/img/ocean.jpg");
    music.Open("assets/audio/stageState.ogg");
	music.Play(-1);
}

void State::LoadAssets() {

}

void State::Update(float dt) {
	if (SDL_QuitRequested()) {
		quitRequested = true;
	}
}

void State::Render() {

}

bool State::QuitRequested() {
	return quitRequested;
}
