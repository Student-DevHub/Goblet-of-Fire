#ifndef Game_hpp
#define Game_hpp

#include <memory>

#include "Window.h"
#include "SceneStateMachine.h"
#include "Scene_SplashScreen.h"
#include "Scene_Game.h"


class Game {
public:
	Game(); // Create window, Initialize Scenes, and Clock

	void update(); 
	void lateUpdate(); 
	void captureInput();
	
	void render();
	
	bool isRunning() const;
	void calculateDeltaTime();

private:
	Window window;

	/* Frame-Independant Movement */
	sf::Clock clock;
	float dt;

	/* Managers */
	SceneStateMachine sceneManager;
	ResourceAllocator<sf::Texture> textureAllocator;
};

#endif /* Game_hpp */