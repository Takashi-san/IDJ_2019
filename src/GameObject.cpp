#include "GameObject.h"

GameObject::GameObject() {
	isDead = false;
	components.clear();
	std::cout << "Tamanho de components constructor: " << components.size() << "\n";
}

GameObject::~GameObject() {
	components.clear();
}

void GameObject::Update(float dt) {
	std::cout << "Tamanho de components Update inicio: " << components.size() << "\n";
	for (unsigned int i = 0; i < components.size(); i++){
		std::cout << "Tamanho de components Update for: " << components.size() << "\n";
		if (components[i] == nullptr) {
			std::cout << "components[i] é igual nullptr.\n";
		} else {
			std::cout << "components[i] é diferente nullptr.\n";
		}
		components[i]->Update(dt);
	}
}

void GameObject::Render() {
	for (unsigned int i = 0; i < components.size(); i++){
		components[i]->Render();
	}
}

bool GameObject::IsDead() {
	return isDead;
}

void GameObject::RequestDelete() {
	isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
	if (cpt == nullptr) {
			std::cout << "cpt invalid.\n";
		} else {
			std::cout << "cpt valid.\n";
		}
	components.emplace_back(cpt);
	std::cout << "Tamanho de components AddComponent: " << components.size() << "\n";
}

void GameObject::RemoveComponent(Component* cpt) {
	for (unsigned int i = 0; i < components.size(); i++){
		if (components[i].get() == cpt) {
			components.erase(components.begin() + i);
			break;
		}
	}
}

Component* GameObject::GetComponent(std::string type) {
	for (unsigned int i = 0; i < components.size(); i++){
		if (components[i]->Is(type)) {
			return components[i].get();
		}
	}
	return nullptr;
}