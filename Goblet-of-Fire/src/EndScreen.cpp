#include "EndScreen.hpp"

namespace GobletOfFire::Scene{
  EndScreenA::EndScreenA(const std::shared_ptr<Core::SceneManager>&scene_manager, const std::shared_ptr<Input::InputManager>&input_manager)
  : input_manager_(input_manager),
  scene_manager_(scene_manager),
  local_buffer_(std::make_shared<Graphics::buffer>()),
  background_(nullptr), foreground_(nullptr), time_to_show_(Utilities::Time::duration(5000)) {}

  void EndScreenA::create()
  {
    auto size = Physics::window_dimensions_;
    local_buffer_->create(size.x, size.y);

    t_resource_manager_ = Core::ResourceManager<Graphics::texture>::getInstance();
    background_ = std::make_unique<Graphics::sprite>();
    foreground_ = std::make_unique<Graphics::sprite>();

    foreground_->setTexture(*(t_resource_manager_->load(200)));
  }

  void EndScreenA::destroy() {}
  
  void EndScreenA::activate() {
    start_ = Utilities::Time::clock::now();
    background_->setTexture(scene_manager_.lock()->getActiveBuffer()->getTexture());
  }
  void EndScreenA::deactivate() {}

  void EndScreenA::updateLogic() {
    auto t = Utilities::Time::getTimeElapsed(start_);
    if (t >= time_to_show_) {
      scene_manager_.lock()->switchTo(1u);
    }
  }
  void EndScreenA::updateRender() {
    local_buffer_->clear();
    local_buffer_->draw(*background_);
    local_buffer_->draw(*foreground_);
    local_buffer_->display();
  }

  std::shared_ptr<Graphics::buffer> EndScreenA::getBuffer() const {
    return local_buffer_;
  }

  EndScreenB::EndScreenB(const std::shared_ptr<Core::SceneManager>& scene_manager, const std::shared_ptr<Input::InputManager>& input_manager)
    : input_manager_(input_manager),
    scene_manager_(scene_manager),
    local_buffer_(std::make_shared<Graphics::buffer>()),
    background_(nullptr), foreground_(nullptr), time_to_show_(Utilities::Time::duration(5000)) {}

  void EndScreenB::create()
  {
    auto size = Physics::window_dimensions_;
    local_buffer_->create(size.x, size.y);

    t_resource_manager_ = Core::ResourceManager<Graphics::texture>::getInstance();
    background_ = std::make_unique<Graphics::sprite>();
    foreground_ = std::make_unique<Graphics::sprite>();

    foreground_->setTexture(*(t_resource_manager_->load(201)));
  }

  void EndScreenB::destroy() {}

  void EndScreenB::activate() {
    start_ = Utilities::Time::clock::now();
    background_->setTexture(scene_manager_.lock()->getActiveBuffer()->getTexture());
  }
  void EndScreenB::deactivate() {}

  void EndScreenB::updateLogic() {
    auto t = Utilities::Time::getTimeElapsed(start_);
    if (t >= time_to_show_) {
      scene_manager_.lock()->switchTo(1u);
    }
  }
  void EndScreenB::updateRender() {
    local_buffer_->clear();
    local_buffer_->draw(*background_);
    local_buffer_->draw(*foreground_);
    local_buffer_->display();
  }

  std::shared_ptr<Graphics::buffer> EndScreenB::getBuffer() const {
    return local_buffer_;
  }
}