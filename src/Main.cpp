#include "Game.h"
#include "StageState.h"

int main(int argc, char** argv) {
	Game& game = Game::GetInstance();
	StageState* init = new StageState();

	game.Push(init);
	game.Run();

	return 0;
}
