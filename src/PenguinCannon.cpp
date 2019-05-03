#include "PenguinCannon.h"
#include "Sprite.h"

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component(associated) {
	Sprite* sp = new Sprite(associated, "asstes/img/cubngun.png");
	associated.AddComponent(sp);

	angle = 0;
	pbody = penguinBody;
}