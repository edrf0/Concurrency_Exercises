#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// 10. Use std::unique_lock and std::mutex.

size_t counter = 0;
std::mutex mtx;

void thread_func() {
    {
        std::unique_lock lock(mtx);
        for (size_t i = 0; i < 1000; ++i) {
            ++counter;
        }
        std::cout << counter << "\n";
    }
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
