#include <iostream>
#include <iomanip>
#include "GA_BIN.hpp"

// 1. 定義目標函數 (Objective Function)
double rastrigin_func(std::vector<double>& input){
    double output = 0.0;
    int n_var = input.size();
    output += 10 * n_var;
    for(int i=0; i<n_var; i++){
        output += std::pow(input[i], 2) - 10 * std::cos(2 * input[i] * std::acos(-1));
    }
    return output;
}

int main() {
    using namespace GA_BIN;

    std::cout << "=== 基因演算法 (GA) 開始執行 ===\n";
    // 2. 初始化參數設定 (Parameters Setup)
    Params params(
        300, // chromosome_length
        50, // bits_per_answer
        50, // population_size (群體大小)
        1000, // generation_num (最大世代數)
        SelMethods::TOURNAMENT, //parent 選擇方法
        0.8f, // crossover_prob (交配機率 80%)
        CrossMethods::SINGLE_POINT, // crossover_method
        0.05f, // mutation_prob (突變機率 5%)
        MutMethods::CONST, // mutation_method
        5.12, // 搜尋上界 (Sphere 常用邊界)
        -5.12 // 搜尋下界
    );
    
    params.print_params();
    std::cout << "---------------------------------\n";
    // 3. 初始化群體與首次評估 (Initialization)
    Population pop(params);

    // 第一次解碼與計算適應度
    pop._update_chromo_value(params);
    pop._evaluation(rastrigin_func);

    // 4. GA 主控制迴圈 (Main Generation Loop)
    for (int gen = 0; gen < params.generation_num; ++gen) {
        
        // --- Step 4.1: 準備父代選擇 (Mating Selection Setup) ---
        // 呼叫我們討論過的重構函式，建立當代的機率分佈或輪盤
        // 假設你已經在 struct 中加入了 TOURNAMENT 或實作了 ROULETTE_DEFAULT
        pop._init_selection(params); 

        // --- Step 4.2: 交配 (Crossover) ---
        // 這裡面會呼叫 _draw_two_parents 來抽樣，並產生新的子代加入 chromos 陣列後方
        pop._crossover(params);

        // --- Step 4.3: 突變 (Mutation) ---
        // 對新產生的個體進行基因突變
        pop._mutation(params);

        // --- Step 4.4: 重新評估 (Re-evaluation) ---
        // 將包含子代在內的所有基因解碼成實數，並重新計算所有人的適應度
        pop._update_chromo_value(params);
        pop._evaluation(rastrigin_func);

        // --- Step 4.5: 生存選擇 (Survivor Selection / Truncation) ---
        // 呼叫我們討論過的截斷選擇：排序所有人，砍掉後段班，只留下最好的 population_size 個
        pop._prepare_next_generation(params);

        // --- Step 4.6: 記錄與輸出 (Logging) ---
        // 因為 _prepare_next_generation 已經將最好的個體排在 index 0 了
        double best_fitness = pop.fitness_values[0];
        
        // 每 10 代印出一次進度，避免畫面太亂
        if ((gen + 1) % 10 == 0 || gen == 0) {
            std::cout << "Generation " << std::setw(3) << gen + 1 
                      << " | Best Fitness: " << std::fixed << std::setprecision(6) << best_fitness 
                      << " | f(x) value: " << rastrigin_func(pop.chromo_values[0]) << '\n';
        }
    }

    // ==========================================
    // 5. 輸出最終結果
    // ==========================================
    std::cout << "\n=== 最佳化完成 ===\n";
    std::cout << "最終找到的最佳解 (Top 1):\n";
    pop.print_population(params, 1);

    return 0;
}