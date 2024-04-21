#pragma once
#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>

namespace GobletOfFire {
  namespace Core {

    class ThreadPool {
    public:
      ThreadPool(size_t numThreads) : running_(true) {

        for (size_t i = 0; i < numThreads; ++i) {
          threads_.emplace_back(thread_function_);
        }
      }

      template<class F, class... Args>
      void enqueue(F&& f, Args&&... args) {
        {
          std::unique_lock<std::mutex> lock(queueMutex_);
          if (!running_) {
            throw std::runtime_error("enqueue on stopped ThreadPool");
          }
          tasks_.emplace([f, args...] { f(args...); });
        }
        condition_.notify_one();
      }

      ~ThreadPool() {
        {
          std::unique_lock<std::mutex> lock(queueMutex_);
          running_ = false;
        }
        condition_.notify_all();
        for (std::thread& thread : threads_) {
          thread.join();
        }
      }

    private:
      std::function<void()> thread_function_ = [this] {
        while (true) {
          std::function<void()> task;
          {
            std::unique_lock<std::mutex> lock(queueMutex_);
            condition_.wait(lock, [this] { return !running_ || !tasks_.empty(); });
            if (!running_ && tasks_.empty()) {
              return;
            }
            task = std::move(tasks_.front());
            tasks_.pop();
          }
          task();
        }
      };

      std::vector<std::thread> threads_;
      std::queue<std::function<void()>> tasks_;
      std::mutex queueMutex_;
      std::condition_variable condition_;
      bool running_;
    };
  }
}

#endif // !THREAD_POOL_HPP
