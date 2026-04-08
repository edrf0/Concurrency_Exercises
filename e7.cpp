#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// 7. Synchronize access to a shared variable using std::mutex.

size_t counter = 0;
std::mutex mtx;

void thread_func() {
    mtx.lock();
    for (size_t i = 0; i < 1000; ++i) {
        ++counter;
    }
    std::cout << counter << "\n";
    mtx.unlock();
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
