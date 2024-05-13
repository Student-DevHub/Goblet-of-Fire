#include <QuadTree.hpp>
#include <cCollision.hpp>

namespace GobletOfFire::Physics {
  QuadTreeNode::QuadTreeNode(uint32_t MaxObjects, Physics::worldBox<float> Bounds, QuadTreeNode* parent)
    : kMaxObjects_(MaxObjects),
    kBounds_(Bounds),
    is_divided_(false),
    parent_(parent) {}

  bool QuadTreeNode::insert(std::shared_ptr<ObjectComponent::cCollision> object) {
    auto box = object->getBoundingBox();
    auto status = isInside(box);

    if (status == InsertStatus::kNotInside) {
      return false;
    }

    if (!is_divided_) {
      objects_.push_back(object);
      if (objects_.size() > kMaxObjects_) {
        objects_.pop_back();
        subDivide();
        return insert(object);
      }

      return status == InsertStatus::kFullyInside;
    }

    for (auto& child : children_) {
      if (child->insert(object)) {
        break;
      }
    }
    return status == InsertStatus::kFullyInside;
  }

  QuadTreeNode::collisions QuadTreeNode::getPotentialColliders(Physics::worldBox<float> box) {
    collisions potential_colliders;
    auto status = isInside(box);

    if (status == InsertStatus::kNotInside) {
      return potential_colliders;
    }

    for (auto& object : objects_) {
      if (object.expired()) continue;

      if (checkCollision(box, object.lock()->getBoundingBox())) {
        potential_colliders.push_back(object.lock());
      }
    }

    if (is_divided_) {
      for (auto& child : children_) {
        auto child_colliders = child->getPotentialColliders(box);
        potential_colliders.insert(potential_colliders.end(),
          child_colliders.begin(), child_colliders.end()
        );
      }
    }

    return potential_colliders;
  }

  void QuadTreeNode::update() {
    removeExpired();

    for (auto it = objects_.begin(); it != objects_.end(); it++) {
      auto status = isInside(it->lock()->getBoundingBox());
      if (status == InsertStatus::kNotInside || status == InsertStatus::kPartiallyInside) {
        auto ptr = it->lock();
        *it = std::weak_ptr<ObjectComponent::cCollision>();
        if (parent_) {
          parent_->insert(ptr);
        }
      }
    }

    if (is_divided_) {
      for (auto& child : children_)
        child->update();
    }
  }

  QuadTreeNode::InsertStatus QuadTreeNode::isInside(Physics::worldBox<float> box) const
  {
    if (!kBounds_.intersects(box)) {
      return InsertStatus::kNotInside;
    }

    if (kBounds_.contains(box.getPosition()) && kBounds_.contains((box.left + box.width), (box.top + box.height))) {
      return InsertStatus::kFullyInside;
    }

    return InsertStatus::kPartiallyInside;
  }

  bool QuadTreeNode::checkCollision(Physics::worldBox<float> box1, Physics::worldBox<float> box2) const {
    return box1.intersects(box2);
  }

  void QuadTreeNode::subDivide() {
    if (is_divided_) return;

    auto half_width = kBounds_.width / 2.f;
    auto half_height = kBounds_.height / 2.f;

    for (uint32_t i = 0; i < kChilds; i++) {
      auto x = kBounds_.left + (i & 1) * half_width;
      auto y = kBounds_.top + (i >> 1) * half_height;
      children_.emplace_back(std::make_shared<QuadTreeNode>(kMaxObjects_, Physics::worldBox<float>(x, y, half_width, half_height), this));
    }

    is_divided_ = true;
  }

  void QuadTreeNode::removeExpired() {
    objects_.erase(std::remove_if(objects_.begin(), objects_.end(), [](const auto& object) {
      return !object.lock();
      }), objects_.end());
  }

  QuadTree::QuadTree(uint32_t max_objects_per_node)
    : root_(std::make_shared<QuadTreeNode>(max_objects_per_node, Physics::worldBox<float>(0, 0, (float)Physics::window_dimensions_.x, (float)Physics::window_dimensions_.y), nullptr)) {}

  bool QuadTree::insert(std::shared_ptr<ObjectComponent::cCollision> object) {
    return root_->insert(object);
  }
  QuadTreeNode::collisions QuadTree::getPotentialColliders(const Physics::worldBox<float>& queryBox) const {
    return root_->getPotentialColliders(queryBox);
  }
}