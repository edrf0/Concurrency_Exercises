#include <iostream>
#include <thread>

// 12. Print even and odd numbers using two threads.
void even() {
    for (int i = 1; i < 10; i+=2) {
        std::cout << i << std::endl;
    }
}
void odd() {
    for (int i = 0; i < 10; i+=2) {
        std::cout << i << std::endl;
    }
}

int main() {
    std::thread t1(odd);
    std::thread t2(even);
    t1.join();
    t2.join();
    return 0;
}
