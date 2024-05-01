#pragma once
#ifndef TIME_MANAGER_HPP
#define TIME_MANAGER_HPP

#include <chrono>

namespace GobletOfFire {
  namespace Utilities {

    class Time {
    public:
      using clock = std::chrono::steady_clock;
      using timePoint = std::chrono::time_point<clock>;
      using duration = std::chrono::milliseconds;

      template <typename DurationType = duration, typename Clock = clock>
      static duration getTimeElapsed(const std::chrono::time_point<Clock>& time_point) {
        auto currentTime = Clock::now();
        return std::chrono::duration_cast<DurationType>(currentTime - time_point);
      }

    private:
    };

  }
}

#endif // !TIME_MANAGER_HPP