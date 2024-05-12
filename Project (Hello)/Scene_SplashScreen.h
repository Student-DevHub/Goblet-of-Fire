#pragma once

#include <SFML/Graphics.hpp>

#include "Scene.h"
#include "ResourceAllocator.h"
#include "SceneStateMachine.h"
#include "WorkingDirectory.h"

class Scene_SplashScreen :
    public Scene {
public:
    Scene_SplashScreen(SceneStateMachine&, Window&, ResourceAllocator<sf::Texture>&);

    void onCreate() override;
    void onDestroy() override;

    void onActivate() override;

    void SetSwitchToScene(unsigned int id);

    void Update(float deltaTime) override;
    void Draw(Window& window) override;
private:
    sf::Texture splashTexture;
    sf::Sprite splashSprite;

    SceneStateMachine& sceneStateMachine;
    ResourceAllocator<sf::Texture>& textureAllocator;
    Window& window;

    /* Screen will exist for certain seconds and then switch */
    float showForSeconds;
    float currentSeconds;
    unsigned int switchToState;
};

