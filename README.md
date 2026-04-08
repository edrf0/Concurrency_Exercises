Original link: https://medium.com/@krishnacse20/c-multithreading-practice-programs-ea8f8a1be446

# C++ Concurrency & Synchronization Exercises

A collection of high-performance C++ implementations focused on multi-threading, memory safety, and synchronization primitives. These exercises explore the "truth" behind writing thread-safe code in modern C++ (C++20).

## 🚀 Featured Highlight: Thread-Safe Counters
One of the core challenges addressed is safely incrementing shared resources across multiple CPU cores.

### Evolution of the Solution:
1.  **The Naive Approach (Unsafe):** Identified critical **data races** when multiple threads accessed a standard integer.
2.  **The Mutex Approach:** Implemented `std::mutex` with `std::lock_guard` to ensure atomicity and ordered console output.
3.  **The Atomic Approach (Optimized):** Leveraged `std::atomic<size_t>` for a lock-free implementation, significantly reducing overhead while maintaining data integrity. A significant performance improvement was obtained as a result of avoiding a standard mutex object.

### Key Technical Takeaways:
*   **Memory Safety:** Used `size_t` for loop counters and shared variables to ensure architecture-agnostic stability and prevent overflow/infinite loops (avoiding common pitfalls with `uint8_t`).
*   **Synchronized I/O:** Utilized `std::osyncstream` (C++20) to prevent interleaved/garbled console output without the heavy performance cost of a global mutex.
*   **Hardware Concurrency:** Dynamically scaled thread pools using `std::thread::hardware_concurrency()` to match the host machine's physical cores.

## 📂 Project Structure
Each exercise is contained in a standalone `.cpp` file to demonstrate a specific concurrency concept. In each file there is a comment describing the exercise requirements.

## 🔨 How to Build
Since each exercise is a standalone program, they can be compiled individually.

## 🔍 Debugging Case Study: The Lambda Capture Race
While developing the performance benchmark (Exercise 14), I encountered a significant logic error where the multithreaded sum was much higher than the single-threaded sum.
*   **The Bug:** I was originally capturing the loop index i by reference ([&]). Because the main thread finished the creation loop faster than the threads could start, all threads were referencing the final value of i (e.g., 12) rather than their unique IDs (0, 1, 2...). This caused every thread to calculate the same high-range "slice" of the math simultaneously.
*   **The Fix:** I switched to capturing the index by value ([&, i]). This ensured each thread received a private, immutable copy of its specific workload range at the moment of creation.
*   **Key Insight:** This highlighted the critical difference between reference lifetimes and thread execution timing. In concurrent programming, capturing local loop variables by reference creates a "race condition" on the variable itself.
