#include <iostream>
#include <thread>
#include <vector>

// 4. Join and detach threads.

void threadFunction(const unsigned int index) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << index << std::endl;
}

int main() {
    std::vector<std::thread> threads;
    for (unsigned int i = 0; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back(threadFunction,i);
        if (i%2==0) {
            threads[i].detach();
        }
    }
    for (auto &t: threads) {
        if (t.joinable()) {
            t.join();
        }
    }
    return 0;
}
