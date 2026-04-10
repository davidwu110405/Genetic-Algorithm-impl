#ifndef LIB_TOOLS
#define LIB_TOOLS

#include <iostream>
#include <string>
#include <chrono>

// 定義一個計時器類別
class ScopedTimer {
public:
    // 建構子：記錄開始時間
    explicit ScopedTimer(const std::string& name) 
        : func_name(name), start_time(std::chrono::high_resolution_clock::now()) {}

    // 解構子：記錄結束時間並印出
    ~ScopedTimer() {
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end_time - start_time;
        
        std::cout << "測試對象: " << func_name << "\n"
                  << "執行耗時: " << elapsed.count() << " ms\n"
                  << "------------------------------" << std::endl;
    }

private:
    std::string func_name;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};

// 產生唯一的變數名稱，避免在同一個作用域內宣告多個計時器時發生命名衝突
#define CONCAT_IMPL(x, y) x##y
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)

// 最終使用的巨集
#define MEASURE_SCOPE(name) ScopedTimer MACRO_CONCAT(_timer_, __LINE__)(name)
#endif //LIB_TOOLS