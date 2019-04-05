#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(GameObject& associated) : Component(associated){
	texture = nullptr;
}

Sprite::Sprite(GameObject& associated, std::string file) : Component(associated){
	texture = nullptr;
	Open(file);
}

Sprite::~Sprite() {
	// desaloca imagem se tiver.
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
}

void Sprite::Open(std::string file) {
	Game& instance = Game::GetInstance();

	// checa texture esta vazio.
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}

	// carrega textura
	texture = IMG_LoadTexture(instance.GetRenderer(), file.c_str());
	if (texture == nullptr) {
		// falha em carregar imagem.
		std::cout << "Falha em carregar textura: " << file.c_str() << "\n";
		std::cout << "SDL_GetError: " << SDL_GetError() << "\n";
		//exit(EXIT_FAILURE);
	}

	// descobre dimensoes da imagem.
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

	// clip da imagem.
	SetClip(0, 0, width, height);

	// seta altura e largura no gameobject.
	associated.box.w = width;
	associated.box.h = height;
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render() {
	Game& instance = Game::GetInstance();

	SDL_Rect dst;
	dst.x = associated.box.x;
	dst.y = associated.box.y;
	dst.w = clipRect.w;
	dst.h = clipRect.h;

	SDL_RenderCopy(instance.GetRenderer(), texture, &clipRect, &dst);
}

int Sprite::GetWidth() {
	return width;
}

int Sprite::GetHeight() {
	return height;
}

bool Sprite::IsOpen() {
	if (texture != nullptr) {
		return true;
	} else {
		return false;
	}
}

void Sprite::Update(float dt){

}

bool Sprite::Is(std::string type) {
	return !strcmp(type.c_str(), "Sprite");
}