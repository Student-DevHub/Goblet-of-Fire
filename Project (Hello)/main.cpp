#include "Game.h"

int main() {
	Game game;
	while (game.isRunning()) {
		game.captureInput();
		game.update();
		game.lateUpdate();
		game.render();
		game.calculateDeltaTime();
	}
}