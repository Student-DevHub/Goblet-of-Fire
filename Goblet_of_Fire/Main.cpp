#include <iostream>
#include <memory>
#include <thread>

class MyClass {
public:
  void myFunction() {
    std::cout << "Hello from myFunction!" << std::endl;
  }
};

int main() {
  std::shared_ptr<MyClass> ptr = std::make_shared<MyClass>();

  // Create a jthread and pass the member function directly
  std::jthread t(&MyClass::myFunction, ptr.get());

  // Wait for the thread to finish
  t.join();

  return 0;
}
