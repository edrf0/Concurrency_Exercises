#include <future>
#include <iostream>
#include <thread>

// 19. Run multiple asynchronous tasks and wait for results.
void threadFunction(std::promise<bool> promise) {
    try {
        promise.set_value(true);
    } catch (std::exception &e) {
        promise.set_exception(std::current_exception());
    }
}

int main() {
    unsigned int numberOfThreads = std::thread::hardware_concurrency();
    if (numberOfThreads == 0) numberOfThreads = 2;

    std::vector<std::future<bool>> futures;
    std::vector<std::thread> threads;

    futures.reserve(numberOfThreads);
    threads.reserve(numberOfThreads);

    for (unsigned int i = 0; i < numberOfThreads; ++i) {
        std::promise<bool> promise;
        futures.push_back(promise.get_future());

        threads.emplace_back(threadFunction, std::move(promise));
    }

    for (auto &future : futures) {
        std::cout << std::boolalpha << future.get() << "\n";
    }

    for (auto &thread : threads) {
        thread.join();
    }
    return 0;
}
