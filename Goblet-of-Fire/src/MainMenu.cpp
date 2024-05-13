#include "MainMenu.hpp"

namespace GobletOfFire {
  namespace Scene {
    MainMenu::MainMenu(const std::shared_ptr<Core::SceneManager>& scene_manager, const std::shared_ptr<Input::InputManager> &input_manager,
      const std::weak_ptr<Core::CoreEngine> &engine)
      : input_manager_(input_manager), 
      scene_manager_(scene_manager), 
      local_buffer_(std::make_shared<Graphics::buffer>()),
      engine_(engine), 
      background_(nullptr),
      base_(nullptr), option_(nullptr), 
      option_textures_(), option_callbacks_(), c_option_(0)
    {
      auto size = Physics::window_dimensions_;
      local_buffer_->create(size.x, size.y);

      t_resource_manager_ = Core::ResourceManager<Graphics::texture>::getInstance();
      background_ = std::make_unique<Graphics::sprite>();
      base_ = std::make_unique<Graphics::sprite>();
      option_ = std::make_unique<Graphics::sprite>();
    }

    void MainMenu::create() {
      loadTextures();
      createCallBacks();
    }
    
    void MainMenu::loadTextures() {
      auto bg = t_resource_manager_->load(100);
      background_->setTexture(*bg);
      background_->setTextureRect(sf::IntRect(0, bg->getSize().y, bg->getSize().x, -1 * bg->getSize().y));

      auto bs = t_resource_manager_->load(101);
      base_->setTexture(*bs);
      base_->setTextureRect(sf::IntRect(0, bs->getSize().y, bs->getSize().x, -1 * bs->getSize().y));

      for (int32_t i = 102; i <= 104; i++) {
        auto pair = std::make_pair(i % 102, t_resource_manager_->load(i));
        option_textures_.insert(pair);
      }
    }

    void MainMenu::createCallBacks() {
      auto stop = [&]() {
        if (!engine_.expired()) {
          engine_.lock()->stop();
        }
      };

      auto play = [&]() {
        if (!scene_manager_.expired()) {
          scene_manager_.lock()->switchTo(2);
        }
      };

      option_callbacks_.insert(std::make_pair(0, play));
      option_callbacks_.insert(std::make_pair(1, stop));
      option_callbacks_.insert(std::make_pair(2, stop));
    }

    void MainMenu::activate() {
      updateOption(0);
      scene_manager_.lock()->remove(4u);
    }

    void MainMenu::updateOption(uint32_t option) {
      c_option_ = option;
      auto& t = option_textures_[c_option_];
      option_->setTexture(*t);
      option_->setTextureRect(sf::IntRect(0, t->getSize().y, t->getSize().x, -1 * t->getSize().y));
    }


    void MainMenu::updateLogic() {
      updateOption(processInput());
    }

    void MainMenu::updateRender() {
      local_buffer_->clear(Graphics::color::Black);
      if ((!background_) || (!base_) || (!option_)) {
        return;
      }
      local_buffer_->draw(*background_);
      local_buffer_->draw(*base_);
      local_buffer_->draw(*option_);
    }
    
    uint32_t MainMenu::processInput() {
      using key = Input::InputManager::Key;
      uint32_t option = c_option_;
      if (input_manager_->isKeyPressed(key::kEnter)) {
        option_callbacks_[option]();
        return 0;
      }

      if (input_manager_->isKeyPressed(key::kDown)) {
        option += 1;
        option %= kTotalOptions_;
      }

      if (input_manager_->isKeyPressed(key::kUp)) {
        option += kTotalOptions_ - 1;
        option %= kTotalOptions_;
      }

      return option;
    }

    std::shared_ptr<Graphics::buffer> MainMenu::getBuffer() const { 
      return local_buffer_;
    }
  }
}