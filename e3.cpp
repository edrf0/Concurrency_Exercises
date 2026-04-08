#include <iostream>
#include <random>
#include <thread>
#include <vector>

// 3. Pass parameters to a thread function.

void threadFunction(const size_t number, const size_t index) {
    std::cout << number << "\n";
    std::cout << index << "\n";
}

int main() {
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<size_t> distribution(0, std::numeric_limits<size_t>::max());

    std::vector<std::thread> threads;
    for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i) {
        auto number = distribution(generator);
        threads.emplace_back(threadFunction,number,i);
    }
    for (auto &t: threads) {
        t.join();
    }
    return 0;
}
