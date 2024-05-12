#include "Scene_SplashScreen.h"

Scene_SplashScreen::Scene_SplashScreen(SceneStateMachine& sceneStateMachine, Window& window, ResourceAllocator<sf::Texture>& textureAllocator)
	: sceneStateMachine(sceneStateMachine), window(window), showForSeconds(0.0f), currentSeconds(0.0f), switchToState(0), textureAllocator(textureAllocator)
{
}

void Scene_SplashScreen::onCreate() {

	int textureID = textureAllocator.Add(WorkingDirectory::get() + "Textures/Splash.png");
	if (textureID >= 0) {
		std::shared_ptr<sf::Texture> texture = textureAllocator.Get(textureID);
		splashSprite.setTexture(*texture);

		splashSprite.setOrigin(splashSprite.getLocalBounds().width / 2, splashSprite.getLocalBounds().height / 2);
		splashSprite.setPosition(sf::Vector2f(window.getCentre()));
	}
	/*
	splashTexture.loadFromFile(WorkingDirectory::get() + "Textures/Splash.png");
	splashSprite.setTexture(splashTexture);
	*/
}

void Scene_SplashScreen::onDestroy() {
}

void Scene_SplashScreen::onActivate()
{
	currentSeconds = 0.0f;
}

void Scene_SplashScreen::SetSwitchToScene(unsigned int id) {
	switchToState = id ;
}

void Scene_SplashScreen::Update(float deltaTime) {
	currentSeconds += deltaTime;

	if (currentSeconds >= showForSeconds)
		sceneStateMachine.switchTo(switchToState);
}

void Scene_SplashScreen::Draw(Window& window) {
	window.draw(splashSprite);
}
