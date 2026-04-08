#include <iostream>
#include <thread>
#include <random>
#include <vector>

// 6. Launch threads to compute factorials of different numbers.
int main() {
    std::random_device random_device;
    std::mt19937 random_engine(random_device());
    std::uniform_int_distribution<uint16_t> distribution(0, 20);

    std::vector<std::thread> threads;
    for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back([&] {
            uint64_t factorial = 1;
            uint16_t limit = distribution(random_engine);
            for (uint16_t n = 2; n <= limit; ++n) {
                factorial *= n;
            }
            std::cout << factorial << std::endl;
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }
    return 0;
}
