#pragma once

#include "Component.h"
#include "C_Transform.h"
#include "ResourceAllocator.h"


class C_Sprite : public Component {
public:
	C_Sprite(Object* owner);

	void load(const std::string& path);
	void load(int id);
	void setTextureAllocator(ResourceAllocator<sf::Texture>* allocator);

	void lateUpdate(float dt) override;
	void draw(Window& window) override;

	/* For Animation */
	void SetTextureRect(int x, int y, int width, int height);
	void SetTextureRect(const sf::IntRect& rect);

private:
	ResourceAllocator<sf::Texture>* allocator;
	sf::Sprite sprite;

	int currentTextureID;
};

