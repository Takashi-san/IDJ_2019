#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite(GameObject& associated) : Component(associated){
	texture = nullptr;
}

Sprite::Sprite(GameObject& associated, std::string file) : Component(associated){
	texture = nullptr;
	Open(file);
}

Sprite::~Sprite() {
	// desaloca imagem se tiver.
	/* Resources cuida disso agora.
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
	*/
}

void Sprite::Open(std::string file) {
	// checa texture esta vazio.
	/* Resources cuida disso agora.
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
	*/

	// carrega textura
	texture = Resources::GetImage(file.c_str());
	//texture = IMG_LoadTexture(instance.GetRenderer(), file.c_str());
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
	Render(associated.box.x - Camera::pos.x, associated.box.y - Camera::pos.y);
}

void Sprite::Render(int x, int y) {
	Game& instance = Game::GetInstance();

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
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