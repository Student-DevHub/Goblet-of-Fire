#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

struct Box
{
  explicit Box(int num) : num_things{ num } {}

  int num_things;
  std::mutex m;
};

void transfer(Box& from, Box& to, int num)
{
  // don't actually take the locks yet
  std::cout << "Worker thread: Waiting to acquire lock...\n";
  std::unique_lock lock1{ from.m, std::defer_lock };
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::unique_lock lock2{ to.m, std::defer_lock };
  std::this_thread::sleep_for(std::chrono::seconds(2));

  // lock both unique_locks without deadlock
  std::lock(lock1, lock2);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout << "Worker thread: Lock acquired, doing some work...\n";
  from.num_things -= num;
  to.num_things += num;
  std::cout << "Worker thread: Work completed, lock released.\n";
  // “from.m” and “to.m” mutexes unlocked in unique_lock dtors
}

int main()
{
  Box acc1{ 100 };
  Box acc2{ 50 };

  std::thread t1{ transfer, std::ref(acc1), std::ref(acc2), 10 };
  std::thread t2{ transfer, std::ref(acc1), std::ref(acc2), 5 };

  t1.join();
  t2.join();

  std::cout << "acc1: " << acc1.num_things << "\n"
    "acc2: " << acc2.num_things << '\n';
}