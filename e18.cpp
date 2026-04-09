#include <future>
#include <iostream>

// 18. Use std::async and std::future to get result from a thread.

int main() {
    std::future future = std::async(std::launch::async, []() {
        return true;
    });
    std::cout << std::boolalpha << future.get();
    return 0;
}
