#include <iostream>
#include <vector>
#include <cassert>
#include <iomanip>
#include "GA_BIN.hpp"

// 定義測試目標函數：Sphere function f(x) = x_0^2 + x_1^2
// 最小值發生在 (0, 0)，此時 f(x) = 0，對應的 Fitness 為 1 / (1 + 0) = 1.0
double sphere_function(const std::vector<double>& x) {
    double sum = 0.0;
    for (double val : x) {
        sum += val * val;
    }
    return sum;
}

// 1. 輔助函數單元測試
void test_utilities() {
    std::cout << "--- 1. 測試輔助函數 ---\n";
    std::cout << "Selection Method (TOURNAMENT): " << GA_BIN::enum2str(GA_BIN::SelMethods::TOURNAMENT) << "\n";

    // 測試二進位轉換功能 (測試位元 1010，預期為十進位的 10)
    std::vector<bool> bits = {true, false, true, false};
    uint64_t val = GA_BIN::vector_bool2ulong(bits, 0, 4);
    std::cout << "二進位 1010 轉換結果: " << val << " (預期: 10)\n";
    assert(val == 10 && "Assertion failed: vector_bool2ulong 運算錯誤!");
    
    std::cout << "輔助函數測試通過。\n\n";
}

// 2. GA 核心管線單步測試
void test_ga_pipeline() {
    std::cout << "--- 2. 測試 GA 核心管線 ---\n";

    // 初始化參數: 2 個變數，每個 20 bits，總長 40。族群 10 人。
    GA_BIN::Params params(40, 20, 10, 100, GA_BIN::SelMethods::TOURNAMENT, 0.8f, GA_BIN::CrossMethods::SINGLE_POINT, 0.05f, GA_BIN::MutMethods::CONST, 5.12, -5.12);
    
    GA_BIN::Population pop(params);
    std::cout << "[初始狀態] 族群大小: " << pop.current_chromo_count << "\n";

    pop._update_chromo_value(params);
    pop._evaluation(sphere_function);
    std::cout << "[評估完成] 準備進行交配。\n";

    pop._init_selection(params);
    pop._crossover(params);
    std::cout << "[交配完成] 族群大小 (含子代): " << pop.current_chromo_count << "\n";

    pop._mutation(params);
    std::cout << "[突變完成] 已對子代執行突變。\n";

    // 關鍵步驟：世代交替前，必須先為「新產生的子代」解碼並計算 Fitness
    pop._update_chromo_value(params);
    pop._evaluation(sphere_function);

    pop._prepare_next_generation(params);
    std::cout << "[世代交替] 族群大小恢復為: " << pop.current_chromo_count << "\n";
    std::cout << "核心管線單步執行無崩潰，測試通過。\n\n";
}

// 3. 完整 GA 迴圈收斂測試
void run_full_ga() {
    std::cout << "--- 3. 執行完整 GA 迴圈測試 ---\n";
    
    // 初始化參數：族群 50 人，跑 100 代
    GA_BIN::Params params(60, 30, 50, 100, GA_BIN::SelMethods::TOURNAMENT, 0.8f, GA_BIN::CrossMethods::SINGLE_POINT, 0.05f, GA_BIN::MutMethods::CONST, 5.12, -5.12);
    GA_BIN::Population pop(params);

    std::cout << "目標：尋找 f(x, y) = x^2 + y^2 的最小值。\n";
    std::cout << "預期最佳 Fitness 應穩定趨近於 1.0。\n\n";

    for (int gen = 0; gen < params.generation_num; ++gen) {
        // 解碼與評估
        pop._update_chromo_value(params);
        pop._evaluation(sphere_function);

        // 每 20 代印出一次當代最佳 Fitness
        if (gen % 20 == 0 || gen == params.generation_num - 1) {
            double max_fit = 0.0;
            for(int i = 0; i < params.population_size; i++) {
                if(pop.fitness_values[i] > max_fit) max_fit = pop.fitness_values[i];
            }
            std::cout << "Generation " << std::setw(3) << gen << " | Best Fitness: " 
                      << std::fixed << std::setprecision(6) << max_fit << "\n";
        }

        // GA 演化操作
        pop._init_selection(params);
        pop._crossover(params);
        pop._mutation(params);
        
        // 評估新產生的群體 (包含父代與子代)
        pop._update_chromo_value(params);
        pop._evaluation(sphere_function);
        
        // 淘汰較差個體，保留最優秀的 population_size 個
        pop._prepare_next_generation(params); 
    }

    std::cout << "\n[演化結束] 最終最佳個體 (Top 1):\n";
    // 演化結束後的陣列已經被 _prepare_next_generation 排序過，index 0 即為最佳解
    pop.print_population(params, 1);
}

int main() {
    test_utilities();
    test_ga_pipeline();
    run_full_ga();
    return 0;
}