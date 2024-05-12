#include "Game.h"

Game::Game() 
	: window("My Game") {
	
	/* Loading Screen */
	std::shared_ptr<Scene_SplashScreen> splashScreen =
		std::make_shared<Scene_SplashScreen>(
			sceneManager,
			window,
			textureAllocator
		);

	/* Game Screen */
	std::shared_ptr<Scene_Game> gameScreen =
		std::make_shared<Scene_Game>(sceneManager, textureAllocator);

	unsigned int splashScreenID = sceneManager.add(splashScreen);
	unsigned int gameScreenID = sceneManager.add(gameScreen);

	splashScreen->SetSwitchToScene(gameScreenID);
	sceneManager.switchTo(splashScreenID);

	dt = clock.restart().asSeconds();
}

void Game::update() {
	window.update();
	sceneManager.Update(dt);

}

void Game::lateUpdate() {
	sceneManager.LateUpdate(dt);
}

void Game::captureInput() {
	sceneManager.ProcessInput();
}

void Game::render() {
	window.beginDraw();
	sceneManager.Draw(window);
	window.endDraw();
}

bool Game::isRunning() const {
	return window.isOpen();
}

void Game::calculateDeltaTime() {
	dt = clock.restart().asSeconds();
}