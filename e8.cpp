#include <iostream>
#include <thread>
#include <vector>

// 8. Demonstrate a race condition without std::mutex.

uint32_t counter = 0;

void thread_func() {
    for (uint16_t i = 0; i < 1000; ++i) {
        ++counter;
    }
    std::cout << counter << std::endl;
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back(thread_func);
    }
    for (auto &th : threads) {
        th.join();
    }
    return 0;
}