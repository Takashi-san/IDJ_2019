#include "Vec2.h"

Vec2::Vec2(int x, int y) {
	this->x = x;
	this->y = y;
}

void Vec2::Rotate(float rad){
	// A referência é angulo positivo = rotação antihorária.
	int xn = x*cos(rad) + y*sin(rad);
	int yn = y*cos(rad) + x*sin(rad);

	x = xn;
	y = yn;
}

Vec2 Vec2::GetRotated(float rad){
	this->Rotate(rad);
	return *this;
}

Vec2 Vec2::operator+(const Vec2& arg) {
	Vec2 ans;
	ans.x = this->x + arg.x;
	ans.y = this->y + arg.y;
	return ans;
}

Vec2 Vec2::operator-(const Vec2& arg) {
	Vec2 ans;
	ans.x = this->x - arg.x;
	ans.y = this->y - arg.y;
	return ans;
}