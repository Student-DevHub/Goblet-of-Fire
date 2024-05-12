#include "C_Sprite.h"
#include "Object.h"

C_Sprite::C_Sprite(Object* owner)
	: Component(owner), currentTextureID(-1)
{
}

void C_Sprite::load(const std::string& path) {
	if (allocator) {
		int textureId = allocator->Add(path);

		if (textureId >= 0 && textureId != currentTextureID) {
			std::shared_ptr<sf::Texture> texture = allocator->Get(textureId);
			sprite.setTexture(*texture);
		}
	}


}

void C_Sprite::load(int id) {
	if (id >= 0 && id != currentTextureID) {
		std::shared_ptr<sf::Texture> texture = allocator->Get(id);
		sprite.setTexture(*texture);
	}
}

void C_Sprite::setTextureAllocator(ResourceAllocator<sf::Texture>* allocator) {
	this->allocator = allocator;
}

void C_Sprite::lateUpdate(float dt)
{
	sprite.setPosition(owner->transform->getPosition());
}

void C_Sprite::draw(Window& window) {
	window.draw(sprite);
}

void C_Sprite::SetTextureRect(int x, int y, int width, int height)
{
	sprite.setTextureRect(sf::IntRect(x, y, width, height));
}

void C_Sprite::SetTextureRect(const sf::IntRect& rect)
{
	sprite.setTextureRect(rect);
}
