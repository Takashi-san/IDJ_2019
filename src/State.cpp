#include "State.h"

State::State() {
	quitRequested = false;
    
    GameObject go;
    Sprite *sp = new Sprite(go, "assets/img/ocean.jpg");
	go.box.w = 0;
	go.box.h = 0;
	go.AddComponent(sp);
	objectArray.emplace_back(&go);

	music.Open("assets/audio/stageState.ogg");
	music.Play(-1);
}

State::~State() {
	objectArray.clear();
}

void State::LoadAssets() {

}

void State::Update(float dt) {
	/* State::Input() está cuidando disso.
	if (SDL_QuitRequested()) {
		quitRequested = true;
	}
	*/

	Input();
	std::cout << "Flag34 --------------------.\n";
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		std::cout << "Flag36 --------------------.\n";
		objectArray[i]->Update(dt);
	}
	std::cout << "Flag35 --------------------.\n";
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
	GameObject go;

	Sprite *sp = new Sprite(go, "assets/img/penguinface.png");
	go.box.w = mouseX - sp->GetWidth()/2;
	go.box.h = mouseX - sp->GetHeight()/2;
	go.AddComponent(sp);

	Sound *sd = new Sound(go, "assets/audio/boom.wav");
	go.AddComponent(sd);

	Face *fc = new Face(go);
	go.AddComponent(fc);

	objectArray.emplace_back(&go);
}

// Método fornecido no moodle.
void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		
		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				//if(go->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
					Face* face = (Face*)go->GetComponent("Face");
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				//}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2(200, 0);
				objPos.Rotate(-M_PI + M_PI*(rand() % 1001)/500.0);
				objPos = objPos + Vec2(mouseX, mouseY);
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}

