#include "Rect.h"

bool Rect::Within(int x, int y) {
	if ((x >= this->x) && (x <= this->x+w) && (y >= this->y) && (y <= this->y+h)) {
		return true;
	} else {
		return false;
	}
}