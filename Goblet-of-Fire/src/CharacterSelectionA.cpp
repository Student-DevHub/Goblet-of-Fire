#include "CharacterSelectionA.hpp"

namespace GobletOfFire {
  namespace Scene {
    CharacterS_A::CharacterS_A(const std::shared_ptr<Core::SceneManager>& scene_manager, 
      const std::shared_ptr<Input::InputManager>& input_manager)

      : input_manager_(input_manager), 
      scene_manager_(scene_manager),
      local_buffer_(std::make_shared<Graphics::buffer>()), 
      background_(nullptr),
      base_(nullptr), option_(nullptr),
      option_textures_(), c_option_(0)
    {
      auto size = Physics::window_dimensions_;
      local_buffer_->create(size.x, size.y);

      t_resource_manager_ = Core::ResourceManager<Graphics::texture>::getInstance();
      background_ = std::make_unique<Graphics::sprite>();
      base_ = std::make_unique<Graphics::sprite>();
      option_ = std::make_unique<Graphics::sprite>();
    }

    void CharacterS_A::create() {
      loadTextures();
      createCallBacks();
    }

    void CharacterS_A::loadTextures() {
      auto bg = t_resource_manager_->load(100);
      background_->setTexture(*bg);
      background_->setTextureRect(sf::IntRect(0, bg->getSize().y, bg->getSize().x, -1 * bg->getSize().y));

      auto bs = t_resource_manager_->load(110);
      base_->setTexture(*bs);
      base_->setTextureRect(sf::IntRect(0, bs->getSize().y, bs->getSize().x, -1 * bs->getSize().y));

      for (int32_t i = 111; i <= 116; i++) {
        auto pair = std::make_pair(i % 111, t_resource_manager_->load(i));
        option_textures_.insert(pair);
      }
    }

    void CharacterS_A::createCallBacks() {
      auto continue_ = [&]() {
        if (scene_manager_.expired()) return;

        scene_manager_.lock()->switchTo(3);
        };

      auto empty = [&]() {};

      callbacks_.insert(std::make_pair(0, continue_));

      for(int i = 1; i <= 6; i++) 
        callbacks_.insert(std::make_pair(i, empty));
    }

    void CharacterS_A::activate() {
      updateOption(0);
    }

    void CharacterS_A::updateOption(uint32_t option) {
      c_option_ = option;
      auto& t = option_textures_[c_option_];
      option_->setTexture(*t);
      option_->setTextureRect(sf::IntRect(0, t->getSize().y, t->getSize().x, -1 * t->getSize().y));
    }

    void CharacterS_A::updateLogic() {
      updateOption(processInput());
    }

    void CharacterS_A::updateRender() {
      local_buffer_->clear(Graphics::color::Black);
      if (!(background_ && base_ && option_)) {
        return;
      }
      local_buffer_->draw(*background_);
      local_buffer_->draw(*base_);
      local_buffer_->draw(*option_);
    }

    uint32_t CharacterS_A::processInput() {
      using key = Input::InputManager::Key;
      uint32_t option = c_option_;
      if (input_manager_->isKeyPressed(key::kEnter)) {
        callbacks_[c_option_]();
        return 0;
      }

      if (input_manager_->isKeyPressed(key::kRight)) {
        option += 1;
        option %= kTotalOptions_;
      }

      if (input_manager_->isKeyPressed(key::kLeft)) {
        option += kTotalOptions_ - 1;
        option %= kTotalOptions_;
      }

      return option;
    }

    std::shared_ptr<Graphics::buffer> CharacterS_A::getBuffer() const {
      return local_buffer_;
    }
  }
}