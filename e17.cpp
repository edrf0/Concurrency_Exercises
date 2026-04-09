#include <condition_variable>
#include <iostream>
#include <queue>
#include <thread>

// 17. Implement producer-consumer using a queue and condition variable.

std::condition_variable cv;
std::mutex mtx;
std::queue<uint16_t> q;

int main() {
    std::thread consumer([] {
        // Consumer thread
        std::unique_lock lock(mtx);
        std::cout << "Waiting for queue to have at least one item...\n";
        cv.wait(lock,[] {return !q.empty();});
        std::cout << "First item is: " << q.front() << "\n";
        q.pop();
    });
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // Main thread is producer
    {
        std::lock_guard lock(mtx);
        /*
        This error is a known false-positive that occurs when using Clangd
        (typically in CLion or VS Code) to edit C++ code, specifically when the
        project is using the Microsoft C++ Standard Library (MSVC STL) in C++20 mode.
        The issue arises because Clangd cannot correctly interpret MSVC-specific "magic" intrinsics
        (specifically _Is_pointer_address_convertible and __is_pointer_interconvertible_with_class)
        used in C++20 traits, causing it to incorrectly report that a constexpr variable is not
        initialized by a constant expression.
        */
        q.push(20);
    }
    cv.notify_one();
    consumer.join();
    std::cout << "Exiting...";
    return 0;
}
