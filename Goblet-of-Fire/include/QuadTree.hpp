#pragma once
#ifndef QUAD_TREE_HPP
#define QUAD_TREE_HPP

#include <memory>
#include <vector>
#include <cstdint>

#include <Physics.hpp>

namespace GobletOfFire::ObjectComponent {
  class cCollision;
}

namespace GobletOfFire::Physics {

  class QuadTreeNode {
  public:
    using collisions = std::vector<std::shared_ptr<ObjectComponent::cCollision>>;

    QuadTreeNode(uint32_t, Physics::worldBox<float>, QuadTreeNode*);

    bool insert(std::shared_ptr<ObjectComponent::cCollision>);
    collisions getPotentialColliders(Physics::worldBox<float>);

    void update();

  private:
    enum class InsertStatus {
      kFullyInside, kPartiallyInside, kNotInside
    };

    InsertStatus isInside(Physics::worldBox<float>) const;
    bool checkCollision(Physics::worldBox<float>, Physics::worldBox<float>) const;

    void subDivide();
    void removeExpired();


    const uint32_t kChilds = 4u;
    const uint32_t kMaxObjects_;
    const Physics::worldBox<float> kBounds_;

    bool is_divided_;

    std::vector<std::weak_ptr<ObjectComponent::cCollision>> objects_;
    std::vector<std::shared_ptr<QuadTreeNode>> children_;
    QuadTreeNode* parent_;
  };

  class QuadTree {
  public:
    QuadTree(uint32_t = 30);

    bool insert(std::shared_ptr<ObjectComponent::cCollision> object);
    void update() { root_->update(); }

    QuadTreeNode::collisions getPotentialColliders(const Physics::worldBox<float>& queryBox) const;

  private:
    std::shared_ptr<QuadTreeNode> root_;
  };
}

#endif // !QUAD_TREE_HPP
