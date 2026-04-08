#include <iostream>
#include <thread>
#include <random>
#include <vector>

// 6. Launch threads to compute factorials of different numbers.
int main() {
    std::random_device random_device;
    std::mt19937 random_engine(random_device());
    std::uniform_int_distribution<size_t> distribution(0, 20);

    std::vector<std::thread> threads;
    for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back([&] {
            size_t factorial = 1;
            const size_t limit = distribution(random_engine);
            for (size_t n = 2; n <= limit; ++n) {
                factorial *= n;
            }
            std::cout << factorial << "\n";
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }
    return 0;
}
