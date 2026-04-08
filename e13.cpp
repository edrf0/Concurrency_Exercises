#include <iostream>
#include <thread>

// 13. Use a lambda function as thread entry point.

int main() {
    std::thread t1([]() {
        std::cout << "Hello world!" << "\n";
    });
    t1.join();
    return 0;
}
