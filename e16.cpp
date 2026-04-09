#include <condition_variable>
#include <iostream>
#include <thread>

// 16. Use std::condition_variable for thread signaling.

std::condition_variable cv;
std::mutex mtx;
bool flag = false;

int main() {
    std::thread t([&]() {
        std::unique_lock lock(mtx);
        cv.wait(lock,[] {return flag;});
        std::cout << "Thread has awakened.\n";
    });
    {
        std::lock_guard lock(mtx);
        flag = true;
    }
    cv.notify_one();
    t.join();
    std::cout << "Exiting...";
    return 0;
}
