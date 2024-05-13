#include "HealthBar.hpp"

#include <iostream>
#include <ObjectComponents.hpp>

namespace GobletOfFire::ObjectComponent {
  HealthBar::HealthBar(uint32_t player)
    : player_represent_(player) {}

  void HealthBar::create() {
    std::vector<uint32_t> texture_ids;
    if (player_represent_ == 1) {
      texture_ids.push_back(150);
      texture_ids.push_back(151);
      texture_ids.push_back(152);
    }
    else {
      texture_ids.push_back(153);
      texture_ids.push_back(154);
      texture_ids.push_back(155);
    }

    t_manager_ = Core::ResourceManager<Graphics::texture>::getInstance();
    std::for_each(texture_ids.begin(), texture_ids.end(), [&](uint32_t id) {
      textures_.push_back(t_manager_->load(id));
      });

    sprite_ = std::make_unique<Graphics::sprite>();
    sprite_->setTexture(*textures_[0]);
  }

  void HealthBar::update(DesignPatterns::Subject<cHealth>* subject) {
    auto ptr = dynamic_cast<cHealth*>(subject);
    if (!ptr) return;

    std::cerr << "Updating health bar\n";

    auto health = ptr->getHealth();
    size_t i = (health > 70) ? 0 : (health > 40) ? 1 : 2;
    sprite_->setTexture(*textures_[i]);
  }

  void HealthBar::subscribe(DesignPatterns::Subject<cHealth>* subject) {
    subject->attach(shared_from_this());
  }

  void HealthBar::render(Graphics::buffer& destination) const {
    destination.draw(*sprite_);
  }
  HealthBarObjectAdapter::HealthBarObjectAdapter(std::shared_ptr<HealthBar> bar) 
    : bar_(bar) {
    kLayer_ = 5;
  }
  void HealthBarObjectAdapter::create() {
    bar_->create();
  }

  void HealthBarObjectAdapter::destroy() {}

  void HealthBarObjectAdapter::activate() {}
  void HealthBarObjectAdapter::deActivate() {}
  void HealthBarObjectAdapter::update(const iComponent::Type, const Utilities::Time::duration) {}
  void HealthBarObjectAdapter::render(Graphics::buffer& destination) const {
    bar_->render(destination);
  }
  void HealthBarObjectAdapter::addComponent(const iComponent::Type, const std::shared_ptr<iComponent>&) {}
  void HealthBarObjectAdapter::removeComponent(const iComponent::Type) {}
  std::shared_ptr<iComponent> HealthBarObjectAdapter::getComponent(const iComponent::Type) const {
    return nullptr;
  }
  bool HealthBarObjectAdapter::isDestroyed() const {
    return false;
  }
}