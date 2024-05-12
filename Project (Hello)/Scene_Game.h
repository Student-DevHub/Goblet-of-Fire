#pragma once

#include "Scene.h"
#include "WorkingDirectory.h"
#include "Input.h"
#include "SceneStateMachine.h"
#include "Object.h"
#include "C_Sprite.h"
#include "ObjectCollection.h"
#include "ResourceAllocator.h"
#include "C_KeyboardMove_P1.h"
#include "C_KeyBoardMove_P2.h"
#include "C_Animation.h"


class Scene_Game : public Scene {
public:
	Scene_Game(SceneStateMachine&, ResourceAllocator<sf::Texture>&);

	void onCreate();
	void onDestroy();

	virtual void ProcessInput();
	virtual void Update(float);
	virtual void LateUpdate(float) override;
	virtual void Draw(Window&);

private:
	std::shared_ptr<Object> player;
	std::shared_ptr<Object> player2;
	Input input;
	SceneStateMachine& sceneManager;
	ObjectCollection objects;
	ResourceAllocator<sf::Texture>& textureAllocator;
};
