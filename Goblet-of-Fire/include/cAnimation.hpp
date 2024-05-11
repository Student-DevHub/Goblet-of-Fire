#pragma once
#ifndef C_ANIMATION_HPP
#define C_ANIMATION_HPP

#include <algorithm>
#include <cstdint>
#include <utility>
#include <vector>
#include <map>

#include <Utilities.hpp>
#include <ObjectComponents.hpp>

namespace GobletOfFire::ObjectComponent {
  class cAnimation : public iComponent {
  public:
    struct FrameData {
			FrameData(Physics::point2<int32_t>, Physics::point2<int32_t>, Utilities::Time::duration);

      Physics::point2<int32_t> origin_;
      Physics::point2<int32_t> size_; 
      Utilities::Time::duration display_time_;
    };

		enum class FacingDirection {
			kNone, kRight, kLeft
		};

		class Animation {
		public:
			Animation(FacingDirection direction);
			void addFrame(FrameData);
			FrameData getCurrentFrame() const;

			bool updateFrame(const Utilities::Time::duration);
			void reset();

			void changeDirection(FacingDirection);
			FacingDirection getDirection() const;

		private:
			void incrementFrame();

			std::vector<FrameData> frames_;
			uint32_t current_frame_index_;
			Utilities::Time::duration current_frame_time_;
			FacingDirection direction_;
		};

		enum class AnimationState {
			kNone, kTakeHit, kRun, kJump, kIdle, kFall, kAttack
		};

		cAnimation(std::shared_ptr<iObject>);
		
		virtual void create() override;
		virtual void destroy() override;

		virtual void activate() override;
		virtual void deActivate() override;

		virtual void update(const Utilities::Time::duration) override;
		virtual void render(Graphics::buffer&) override;

		void addAnimation(AnimationState, std::unique_ptr<Animation>);
		void setAnimationState(AnimationState);
		const AnimationState getAnimationState() const;
		void changeDirection(FacingDirection);

	private:
		std::weak_ptr<iObject> owner_;
		std::weak_ptr<cSprite> sprite_;

		std::map<AnimationState, std::unique_ptr<Animation>> animations_;
		
		AnimationState current_state_;
  };
}

#endif // !C_ANIMATION_HPP
