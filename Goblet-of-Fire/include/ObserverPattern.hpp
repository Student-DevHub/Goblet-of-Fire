#pragma once
#ifndef OBSERVER_PATTERN_HPP
#define OBSERVER_PATTERN_HPP

#include <memory>
#include <vector>
#include <algorithm>

namespace GobletOfFire {
  namespace DesignPatterns {

    template <class SubjectType>
    class Observer : public std::enable_shared_from_this<Observer<SubjectType>> {
    public:
      virtual ~Observer() {}
      virtual void update(Subject<SubjectType>* subject) = 0;
      virtual void subscribe(Subject<SubjectType>* subject) = 0;
    };

    template <class SubjectType>
    class Subject {
    public:
      virtual ~Subject() {}
      void attach(const std::shared_ptr<Observer<SubjectType>>& observer) {
        observers_.push_back(observer);
      }
      void detach(const std::weak_ptr<Observer<SubjectType>>& observer) {
        removeExpired();
        auto check_for_equality = [&](std::weak_ptr<Observer<SubjectType>>& weakPtr) {
          return !weakPtr.expired() && weakPtr.lock() == observer.lock();
          };

        auto it = std::find_if(observers_.begin(), observers_.end(), check_for_equality);

        if (it != observers_.end())
          observers_.erase(it);
      }

      void notify() {
        removeExpired();
        auto notify_all = [&](std::weak_ptr<Observer<SubjectType>>& observer) {
          observer.lock()->update(this);
          };
        std::for_each(observers_.begin(), observers_.end(), notify_all);
      }

    private:
      void removeExpired() {
        auto expired = [&](const std::weak_ptr<Observer<SubjectType>>& weakPtr) {
          return weakPtr.expired();
          };

        auto new_end = std::remove_if(observers_.begin(), observers_.end(), expired);

        observers_.erase(new_end, observers_.end());
      }

      std::vector<std::weak_ptr<Observer<SubjectType>>> observers_;
    };

  }
}

#endif // !OBSERVER_PATTERN_HPP
