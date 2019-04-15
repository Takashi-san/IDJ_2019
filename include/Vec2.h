#include <math.h>

#ifndef VEC2
	#define VEC2

	class Vec2 {
	public:
		float x, y;

		Vec2(){}
		Vec2(int, int);

		void Rotate(float);
		Vec2 GetRotated(float);
		Vec2 operator+(const Vec2&);
		Vec2 operator-(const Vec2&);
	};
#endif