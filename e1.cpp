#include <iostream>
#include <thread>

// 1. Create a thread that prints “Hello from thread”.
int main() {
     std::thread t([]() {
          std::cout << "Hello World!" << std::endl;
     });
     t.join();
     return 0;
}
