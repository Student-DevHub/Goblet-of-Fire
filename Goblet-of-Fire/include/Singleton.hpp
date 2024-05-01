#pragma once
#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <memory>

namespace GobletOfFire {
  namespace DesignPatterns {
    template <class T>
    class Singleton {
    public:
      static std::shared_ptr<T> getInstance() {
        static std::shared_ptr<T> instance(new T);
        return instance;
      }

      Singleton(const Singleton&) = delete;
      Singleton& operator=(const Singleton&) = delete;
      Singleton(Singleton&&) = delete;
      Singleton& operator=(Singleton&&) = delete;

      Singleton() {}
      virtual ~Singleton() {}

    private:
    };
  }
}


#endif // !SINGLETON_HPP
