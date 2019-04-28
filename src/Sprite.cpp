#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite(GameObject& associated) : Component(associated){
	texture = nullptr;
	scale.x = 1;
	scale.y = 1;
	width = 0;
	height = 0;
}

Sprite::Sprite(GameObject& associated, std::string file) : Component(associated){
	texture = nullptr;
	scale.x = 1;
	scale.y = 1;
	width = 0;
	height = 0;
	Open(file);
}

Sprite::~Sprite() {
	
}

void Sprite::Open(std::string file) {
	// carrega textura
	texture = Resources::GetImage(file.c_str());
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
	dst.w = clipRect.w*scale.x;
	dst.h = clipRect.h*scale.y;
	
	SDL_RenderCopyEx(instance.GetRenderer(), texture, &clipRect, &dst, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}

int Sprite::GetWidth() {
	return width*scale.x;
}

int Sprite::GetHeight() {
	return height*scale.y;
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

void Sprite::SetScale(float scaleX, float scaleY) {
	if (scaleX != 0) {
		scale.x = scaleX;
		associated.box.w = GetWidth();
	}
	if (scaleY != 0) {
		scale.y = scaleY;
		associated.box.h = GetHeight();
	}
}

Vec2 Sprite::GetScale() {
	return scale;
}