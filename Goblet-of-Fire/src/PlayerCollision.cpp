#include <PlayerCollision.hpp>
#include <iostream>

namespace GobletOfFire::ObjectComponent {

  PlayerCollision::PlayerCollision(std::shared_ptr<iObject> owner, std::shared_ptr<Physics::QuadTree> quadtree, const CollisionBox& box)
    : cCollision(owner, quadtree, box, Layer::kPlayerLayer) {}

  void PlayerCollision::resolveCollision(std::shared_ptr<cCollision> object) {
    auto ledge_box = object->getBoundingBox();
    auto player_box = getBoundingBox();

    auto d_top_a = (ledge_box.top) -
      (player_box.top + player_box.height);
    auto d_top_b = (ledge_box.top) -
      (player_box.top);

    auto d_bottom_a = (ledge_box.top + ledge_box.height) -
      (player_box.top + player_box.height);
    auto d_bottom_b = (ledge_box.top + ledge_box.height) -
      (player_box.top);

    if (d_top_a < 0.f && d_top_b > 0.f) {
      whenAboveLedge(player_box, ledge_box);
    }
    else if (d_bottom_a < 0.f && d_bottom_b > 0.f && d_top_b < 0.f) {
      whenBelowLedge(player_box, ledge_box);
    }
  }

  void PlayerCollision::checkWindowBounds() {
    auto pos = transform_.lock()->getPoint();
    auto box = getBoundingBox();
    auto ldx = 0 - box.left;
    auto rdx = Physics::window_dimensions_.x - (box.left + box.width);
    if (ldx > 0) {
      pos.x += ldx + 0.5f;
      transform_.lock()->setPosition(pos);
    }
    else if (rdx < 0) {
      pos.x += (rdx - 0.5f);
      transform_.lock()->setPosition(pos);
    }
    return;
  }

  void PlayerCollision::whenAboveLedge(Physics::worldBox<float> player_box, Physics::worldBox<float> ledge_box) {
    auto dx = calculateLedgeCoverage({ player_box.left, player_box.left + player_box.width }, { ledge_box.left, ledge_box.left + ledge_box.width });
    auto dy = calculateLedgeCoverage({ player_box.top, player_box.top + player_box.height }, { ledge_box.top, ledge_box.top + ledge_box.height });

    auto pos = transform_.lock()->getPoint();
    auto vel = physics_.lock()->getVelocity();
    auto acc = physics_.lock()->getAcceleration();
    if (fabs(dx) >= player_box.width / 2.f) {
      pos.y += dy;
      transform_.lock()->setPosition(pos);
      vel.y = 0;
      physics_.lock()->setAcceleration(acc);
      physics_.lock()->setVelocity(vel);
    }
    else if (fabs(dx) < fabs(dy) || fabs(dx) < (player_box.width / 2.f)) {
      pos.x += dx;
      transform_.lock()->setPosition(pos);
      vel.x *= (dx / fabs(dx));
      physics_.lock()->setVelocity(vel);
    }
  }

  void PlayerCollision::whenBelowLedge(Physics::worldBox<float> player_box, Physics::worldBox<float> ledge_box) {
    auto dy = calculateLedgeCoverage({ player_box.left, player_box.left + player_box.width }, { ledge_box.left, ledge_box.left + ledge_box.width });
    auto dx = calculateLedgeCoverage({ player_box.top, player_box.top + player_box.height }, { ledge_box.top, ledge_box.top + ledge_box.height });

    auto pos = transform_.lock()->getPoint();
    auto vel = physics_.lock()->getVelocity();
    auto acc = physics_.lock()->getAcceleration();

    if (fabs(dx) >= player_box.width / 2.f) {
      pos.y += dy;
      transform_.lock()->setPosition(pos);
      vel.y = 0;
      physics_.lock()->setVelocity(vel);
    }
    else {
      pos.x += dx;
      transform_.lock()->setPosition(pos);
      vel.x *= -1.f;
      physics_.lock()->setVelocity(vel);
    }
  }

  float PlayerCollision::calculateLedgeCoverage(Physics::point2<float> p1, Physics::point2<float> p2) {
    float d = 1.f;
    if (p1.x < p2.x) {
      d *= -1.f;
      d *= (p1.y - p2.x);
    }
    else if (p1.x < p2.y && p1.y <= p2.y) {
      d *= (p1.y - p1.x);
    }
    else {
      d *= (p1.y - p2.y);
    }
    return d;
  }


}