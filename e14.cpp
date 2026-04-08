#include <chrono>
#include <iostream>
#include <thread>

// 14. Compare performance: single thread vs multithreaded sum.

int main() {
    // Single threaded sum
    uint16_t sum = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (uint16_t i = 1; i < 12000; ++i) {
        sum += i;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << duration.count() << " ns : sum = " << sum << std::endl;

    // Multithreaded sum
    std::vector<std::thread> threads;
    sum = 0;
    start = std::chrono::high_resolution_clock::now();
    for (uint16_t i = 1; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back([&]() {
            for (uint16_t j = 1; j < 1000; ++j) {
                sum += j;
            }
        });
    }
    for (auto &t : threads) {
        t.join();
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << duration.count() << " ns: sum = " << sum << std::endl;
    return 0;
}
