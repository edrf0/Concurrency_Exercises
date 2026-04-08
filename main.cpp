#include <iostream>
#include <thread>
#include <vector>
#include <syncstream>

// 15. Create multiple threads to increment a shared value N times.

std::atomic<size_t> counter{0};

int main() {
    std::vector<std::thread> threads;
    for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back([&]() {
            for (size_t j = 1; j <= std::numeric_limits<uint8_t>::max(); ++j) {
                ++counter;
                std::osyncstream(std::cout) << counter << " : threadID "
                << std::this_thread::get_id() << "\n";
            }
        });
    }
    for (auto &t : threads) {
        t.join();
    }
    return 0;
}

/*
Intermediate Level
1. Use std::condition_variable for thread signaling.
2. Implement producer-consumer using a queue and condition variable.
3. Use std::async and std::future to get result from a thread.
4. Run multiple asynchronous tasks and wait for results.
5. Simulate a dining philosophers problem.
6. Readers-Writers problem using std::shared_mutex.
7. Thread pool implementation (basic).
8. Thread-safe logging class using mutex.
9. Use std::atomic for lock-free increment.
10. Compare atomic and mutex-based counters.
11. Launch threads using a class member function.
12. Use thread local storage (thread_local keyword).
13. Implement a countdown timer using threads.
14. Run a background task and cancel it using a flag.
15. Simulate a bank account with deposit and withdraw using locks.
16. Multithreaded merge sort.
17. Parallel matrix multiplication.
18. Use std::promise and std::future for communication.
19. Measure thread execution time using std::chrono.
20. Implement a bounded blocking queue

Advanced Level
1. Simulate a multithreaded file downloader.
2. Implement a thread-safe cache (map with read/write lock).
3. Create a parallel web crawler using threads.
4. Use a thread-safe singleton pattern.
5. Build a multithreaded chat server (basic simulation).
6. Parallel image filter application (e.g., blur effect).
7. Implement work stealing thread pool.
8. Build a task scheduler using threads and a priority queue.
9. Simulate ticket booking system with concurrent access.
10. Parallel prime number finder in a given range.
11. Lock-free queue using std::atomic (advanced).
12. Design a thread-safe observer pattern.
13. Build a pipeline pattern (e.g., fetch -> decode -> process).
14. Performance comparison: std::thread vs std::async.
15. Debug deadlocks using std::mutex with intentional mistakes.*/
