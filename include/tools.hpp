#ifndef LIB_TOOLS
#define LIB_TOOLS

#include <iostream>
#include <chrono>
#include <functional> // 包含 std::invoke
#include <string>

template <typename Func, typename... Args>
void _measure_time_impl(std::string func_name, Func&& func, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();

    // 執行函式
    std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    // 輸出格式化結果
    std::cout << "[測試對象: " << func_name << "]\n"
              << "執行耗時: " << elapsed.count() << " ms\n"
              << "------------------------------" << std::endl;
}

#define MEASURE_TIME(func, ...) _measure_time_impl(#func, func, ##__VA_ARGS__)

#endif //LIB_TOOLS