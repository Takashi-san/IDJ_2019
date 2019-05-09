#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> 	Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> 	Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> 	Resources::soundTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
	Game& instance = Game::GetInstance();
	SDL_Texture* texture;
	std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>::iterator it = imageTable.find(file.c_str());

	if (it != imageTable.end()){
		return it->second;
	}

	texture = IMG_LoadTexture(instance.GetRenderer(), file.c_str());
	if (texture != nullptr) {
		std::shared_ptr<SDL_Texture> s_txtr(texture, [](SDL_Texture* texture){ SDL_DestroyTexture(texture); });
		imageTable[file.c_str()] = s_txtr;
		return imageTable[file.c_str()];
	} else {
		return nullptr;
	}
}

void Resources::ClearImages() {
	std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>::iterator it;

	it = imageTable.begin();
	while (it != imageTable.end()) {
		if (it->second.unique()) {
			it = imageTable.erase(it);
		} else {
			it++;
		}
	}
}

Mix_Music* Resources::GetMusic(std::string file) {
	Mix_Music* music;
	std::unordered_map<std::string, Mix_Music*>::iterator it = musicTable.find(file.c_str());

	if (it != musicTable.end()){
		return it->second;
	}

	music = Mix_LoadMUS(file.c_str());
	musicTable[file.c_str()] = music;

	return music;
}

void Resources::ClearMusics() {
	std::unordered_map<std::string, Mix_Music*>::iterator it;

	for(it = musicTable.begin(); it != musicTable.end(); it++) {
		if (it->second != nullptr) {
			Mix_FreeMusic(it->second);
		}
	}

	musicTable.clear();
}

Mix_Chunk* Resources::GetSound(std::string file) {
	Mix_Chunk* sound;
	std::unordered_map<std::string, Mix_Chunk*>::iterator it = soundTable.find(file.c_str());

	if (it != soundTable.end()){
		return it->second;
	}

	sound = Mix_LoadWAV(file.c_str());
	soundTable[file.c_str()] = sound;

	return sound;
}

void Resources::ClearSounds() {
	std::unordered_map<std::string, Mix_Chunk*>::iterator it;

	for(it = soundTable.begin(); it != soundTable.end(); it++) {
		if (it->second != nullptr) {
			Mix_FreeChunk(it->second);
		}
	}

	soundTable.clear();
}