#include <string>
#include <iostream>
#include <stdbool.h>
#include "Sprite.h"
#include "GameObject.h"

#ifndef TILESET
	class TileSet{
	private:
		Sprite tileSet;
		int rows, columns;
		int tileWidth, tileHeight;

	public:
		TileSet(GameObject&, int, int, std::string);
		void RenderTile(unsigned int, int, int);
		int GetTileWidth();
		int GetTileHeight();

	};

	#define TILESET
#endif
