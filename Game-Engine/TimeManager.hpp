#pragma once
#ifndef TIME_MANAGER_HPP
#define TIME_MANAGER_HPP

#include <chrono>

#include "Namespaces.ns.hpp"

namespace GobletOfFire {
  namespace Utilities {

    class TimeManager {
    public:
      template <typename DurationType = duration, typename Clock = clock>
      static duration getTimeElapsed(const std::chrono::time_point<Clock>& time_point) {
        auto currentTime = Clock::now();
        return std::chrono::duration_cast<DurationType>(currentTime - timePoint);
      }

    private:
    };

  }
}

#endif // !TIME_MANAGER_HPP



