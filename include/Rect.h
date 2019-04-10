#ifndef RECT
	class Rect {
	public:
		float x, y, w, h;

		bool Within(int, int);
	};
	#define RECT
#endif