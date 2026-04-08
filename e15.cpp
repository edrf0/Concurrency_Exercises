#include <iostream>
#include <thread>
#include <vector>
#include <syncstream>

// 15. Create multiple threads to increment a shared value N times.

std::atomic<size_t> counter{0};

int main() {
    std::vector<std::thread> threads;
    for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back([&]() {
            for (size_t j = 1; j <= std::numeric_limits<uint8_t>::max(); ++j) {
                ++counter;
                std::osyncstream(std::cout) << counter << " : threadID "
                << std::this_thread::get_id() << "\n";
            }
        });
    }
    for (auto &t : threads) {
        t.join();
    }
    return 0;
}
