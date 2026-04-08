#include <chrono>
#include <iostream>
#include <thread>

// 14. Compare performance: single thread vs multithreaded sum.
constexpr size_t COUNT_SIZE = 10'000'000;

int main() {
    const unsigned int apparent_thread_count = std::thread::hardware_concurrency();
    const unsigned int thread_count = apparent_thread_count != 0 ? apparent_thread_count : 2;

    // Single threaded sum
    size_t single_sum = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < thread_count * COUNT_SIZE; ++i) {
        single_sum += i;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout <<"Single-threaded: " << duration.count() << " ns. Sum = " << single_sum << "\n";

    // Multithreaded sum
    std::vector<std::thread> threads;
    std::atomic<size_t> multithreaded_sum = 0;
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < thread_count; ++i) {
        threads.emplace_back([&,i]() {
            size_t local_sum = 0;

            const size_t start_count = i * COUNT_SIZE;
            const size_t end_count = (i + 1) * COUNT_SIZE;

            for (size_t j = start_count; j < end_count; ++j) {
                local_sum += j;
            }

            multithreaded_sum += local_sum;
        });
    }
    for (auto &t : threads) {
        t.join();
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Multi-threaded: " << duration.count() << " ns. Sum = " << multithreaded_sum << "\n";
    return 0;
}
