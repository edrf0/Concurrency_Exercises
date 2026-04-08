#include <iostream>
#include <thread>
#include <vector>

// 2. Launch multiple threads that print their thread IDs.
int main() {
    std::vector<std::thread> threads;
    for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back([]() {
             std::cout << std::this_thread::get_id() << "\n";
        });
    }
    for (auto& t : threads) {
        t.join();
    }
    return 0;
}
