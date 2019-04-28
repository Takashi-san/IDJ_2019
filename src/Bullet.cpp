#include "Bullet.h"
#include "Sprite.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite) : Component(associated) {
	Sprite* sp = new Sprite(associated, sprite);
	associated.AddComponent(sp);

	this->speed.x = speed;
	this->speed.y = 0;
	this->speed.Rotate(angle);
	this->damage = damage;
	this->distanceLeft = maxDistance;
}

void Bullet::Update(float dt) {
	associated.box.x += speed.x*dt;
	associated.box.y += speed.y*dt;
	distanceLeft -= speed.Modulo()*dt;
	if (distanceLeft <= 0) {
		associated.RequestDelete();
	}
}

void Bullet::Render() {

}

bool Bullet::Is(std::string type) {
	return !strcmp(type.c_str(), "Bullet");
}

int Bullet::GetDamage() {
	return damage;
}