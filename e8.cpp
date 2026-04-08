#include <iostream>
#include <thread>
#include <vector>

// 8. Demonstrate a race condition without std::mutex.

size_t counter = 0;

void thread_func() {
    for (size_t i = 0; i < 1000; ++i) {
        ++counter;
    }
    std::cout << counter << "\n";
}

int main() {
    std::vector<std::thread> threads;
    for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back(thread_func);
    }
    for (auto &th : threads) {
        th.join();
    }
    return 0;
}