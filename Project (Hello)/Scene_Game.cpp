#include "Scene_Game.h"

Scene_Game::Scene_Game(SceneStateMachine& sceneManager, ResourceAllocator<sf::Texture>& textureAllocator)
	: sceneManager(sceneManager), textureAllocator(textureAllocator) {
}

void Scene_Game::onCreate() {
	player = std::make_shared<Object>();

	auto movement = player->AddComponent<C_KeyboardMove_P1>();
	movement->setInput(&input);

	auto animation = player->AddComponent<C_Animation>();

	auto sprite = player->AddComponent<C_Sprite>();
	sprite->setTextureAllocator(&textureAllocator);

	int sumaraiTextureID = textureAllocator.Add(WorkingDirectory::get() + "Textures/Sumarai.png");

	std::shared_ptr<Animation> idleAnimation = std::make_shared<Animation>();
	idleAnimation->addFrame(sumaraiTextureID, 0, 0, 150, 150, 0.2f);
	idleAnimation->addFrame(sumaraiTextureID, 150, 0, 150, 150, 0.2f);
	idleAnimation->addFrame(sumaraiTextureID, 300, 0, 150, 150, 0.2f);
	idleAnimation->addFrame(sumaraiTextureID, 450, 0, 150, 150, 0.2f);
	idleAnimation->addFrame(sumaraiTextureID, 600, 0, 150, 150, 0.2f);
	idleAnimation->addFrame(sumaraiTextureID, 750, 0, 150, 150, 0.2f);

	animation->addAnimation(AnimationState::Idle, idleAnimation);

	
	objects.Add(player);

	// Adding Player 2
	player2 = std::make_shared<Object>();

	auto movement2 = player2->AddComponent<C_KeyboardMove_P2>();
	movement2->setInput(&input);

	auto animation2 = player2->AddComponent<C_Animation>();

	
	auto sprite2 = player2->AddComponent<C_Sprite>();
	sprite2->setTextureAllocator(&textureAllocator);

	int sumaraiTextureID2 = textureAllocator.Add(WorkingDirectory::get() + "Textures/Sumarai.png");


	std::shared_ptr<Animation> idleAnimation2 = std::make_shared<Animation>();
	idleAnimation2->addFrame(sumaraiTextureID2, 0, 0, 150, 150, 0.2f);
	idleAnimation2->addFrame(sumaraiTextureID2, 150, 0, 150, 150, 0.2f);
	idleAnimation2->addFrame(sumaraiTextureID2, 300, 0, 150, 150, 0.2f);
	idleAnimation2->addFrame(sumaraiTextureID2, 450, 0, 150, 150, 0.2f);
	idleAnimation2->addFrame(sumaraiTextureID2, 600, 0, 150, 150, 0.2f);
	idleAnimation2->addFrame(sumaraiTextureID2, 750, 0, 150, 150, 0.2f);

	animation2->addAnimation(AnimationState::Idle, idleAnimation2);

	
	objects.Add(player2);
	
}

void Scene_Game::onDestroy()
{
}

void Scene_Game::ProcessInput() {
	input.update();
}

void Scene_Game::Update(float dt) {
	objects.processNewObjects();
	objects.update(dt);
	
	player->GetComponent<C_KeyboardMove_P1>()->attack(player2.get(), dt);
}

void Scene_Game::LateUpdate(float dt) {
	objects.lateUpdate(dt);
}

void Scene_Game::Draw(Window& window) {
	/*player2->GetComponent<C_Sprite>()->draw(window);*/
	objects.draw(window);
}
