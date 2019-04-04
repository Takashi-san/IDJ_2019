#include "Sprite.h"
#include "Game.h"

Sprite::Sprite() {
	texture = nullptr;
}

Sprite::Sprite(std::string file) {
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
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
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