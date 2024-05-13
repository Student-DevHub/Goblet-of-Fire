#include "CharacterSelectionB.hpp"

namespace GobletOfFire {
  namespace Scene {
    CharacterS_B::CharacterS_B(const std::shared_ptr<Core::SceneManager>& scene_manager,
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

    void CharacterS_B::create() {
      loadTextures();
      createCallBacks();
    }

    void CharacterS_B::loadTextures() {
      auto bg = t_resource_manager_->load(99);
      background_->setTexture(*bg);
      background_->setTextureRect(sf::IntRect(0, bg->getSize().y, bg->getSize().x, -1 * bg->getSize().y));

      auto bs = t_resource_manager_->load(120);
      base_->setTexture(*bs);
      base_->setTextureRect(sf::IntRect(0, bs->getSize().y, bs->getSize().x, -1 * bs->getSize().y));

      for (int32_t i = 121; i <= 126; i++) {
        auto pair = std::make_pair(i % 121, t_resource_manager_->load(i));
        option_textures_.insert(pair);
      }
    }

    void CharacterS_B::createCallBacks() {
      auto continue_ = [&]() {
        if (scene_manager_.expired()) return;
        auto ptr = std::make_shared<MainGame>(scene_manager_.lock(), input_manager_);
        scene_manager_.lock()->addNewScene(std::make_pair(4, ptr));
        scene_manager_.lock()->switchTo(4);
        };

      auto empty = [&]() {};

      callbacks_.insert(std::make_pair(0, continue_));

      for (int i = 1; i <= 6; i++)
        callbacks_.insert(std::make_pair(i, empty));
    }

    void CharacterS_B::activate() {
      updateOption(0);
    }

    void CharacterS_B::updateOption(uint32_t option) {
      c_option_ = option;
      auto& t = option_textures_[c_option_];
      option_->setTexture(*t);
      option_->setTextureRect(sf::IntRect(0, t->getSize().y, t->getSize().x, -1 * t->getSize().y));
    }

    void CharacterS_B::updateLogic() {
      updateOption(processInput());
    }

    void CharacterS_B::updateRender() {
      local_buffer_->clear(Graphics::color::Black);
      if (!(background_ && base_ && option_)) {
        return;
      }
      local_buffer_->draw(*background_);
      local_buffer_->draw(*base_);
      local_buffer_->draw(*option_);
    }

    uint32_t CharacterS_B::processInput() {
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

    std::shared_ptr<Graphics::buffer> CharacterS_B::getBuffer() const {
      return local_buffer_;
    }
  }
}