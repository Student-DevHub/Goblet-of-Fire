#include "MainMenu.hpp"

namespace GobletOfFire {
  namespace Scene {
    MainMenu::MainMenu(std::shared_ptr<Input::InputManager> input_manager) 
      : input_manager_(input_manager), local_buffer_(std::make_shared<Graphics::buffer>()) {

      auto size = Physics::window_dimensions_;
      local_buffer_->create(size.x, size.y);

      t_resource_allocator_ = Core::ResourceManager<Graphics::texture>::getInstance();
    }

    void MainMenu::create() {
      t_resource_allocator_->load(100);
      t_resource_allocator_->load(101);
      t_resource_allocator_->load(102);
      t_resource_allocator_->load(103);
      t_resource_allocator_->load(104);
    }

  }
}