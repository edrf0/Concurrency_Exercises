#include <iostream>
#include <thread>
#include <array>

// 5. Create a thread that calculates the sum of an array.
int main() {
    constexpr std::array<uint16_t,12> arr{1,2,3,4,5,6,7,8,9,10,11,12};
    uint16_t sum = 0;
    std::thread t([&]() {
        for (const uint16_t &i : arr) {
            sum += i;
        }
    });
    t.join();
    std::cout << sum << "\n";
    return 0;
}
