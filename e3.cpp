#include <iostream>
#include <random>
#include <thread>
#include <vector>

// 3. Pass parameters to a thread function.

void threadFunction(const uint64_t number, const unsigned int index) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << number << std::endl;
    std::cout << index << std::endl;
}

int main() {
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<uint64_t> distribution(0, std::numeric_limits<uint64_t>::max());

    std::vector<std::thread> threads;
    for (unsigned int i = 0; i < std::thread::hardware_concurrency(); ++i) {
        auto number = distribution(generator);
        threads.emplace_back(threadFunction,number,i);
    }
    for (auto &t: threads) {
        t.join();
    }
    return 0;
}
