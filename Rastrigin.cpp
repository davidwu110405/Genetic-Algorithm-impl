#include <iostream>
#include <iomanip>
#include "GA_BIN.hpp"
#include "GA_BIN_wrapper.hpp"

double rastrigin_func(const std::vector<double>& input){
    double output = 0.0;
    int n_var = input.size();
    output += 10 * n_var;
    for(int i=0; i<n_var; i++){
        output += std::pow(input[i], 2) - 10 * std::cos(2 * input[i] * std::acos(-1));
    }
    return output;
}

int main(){
    std::cout << "=== 基因演算法 (GA) 開始執行 ===\n";
    GA_BIN::Params params(
        300, // chromosome_length
        50, // bits_per_answer
        50, // population_size (群體大小)
        1000, // generation_num (最大世代數)
        GA_BIN::SelMethods::TOURNAMENT, //parent 選擇方法
        0.8f, // crossover_prob (交配機率 80%)
        GA_BIN::CrossMethods::SINGLE_POINT, // crossover_method
        0.1f, // mutation_prob (突變機率 5%)
        GA_BIN::MutMethods::CONST, // mutation_method
        5.12, // 搜尋上界 (Sphere 常用邊界)
        -5.12 // 搜尋下界
    );
    
    std::cout << "開始執行 GA:\n";
    params.print_params();

    // 2. 一行呼叫 GA (開啟 verbose 印出進度)
    // run_ga(GA::BIN::Params, targetfunction, verbose(bool), csv filename)
    GAResult result = run_ga(params, rastrigin_func, true, "test1.csv");

    // 3. 顯示結果
    std::cout << "\n=== 最佳解尋找完成 ===\n";
    std::cout << "最佳 Fitness: " << std::fixed << std::setprecision(6) << result.best_fitness << "\n";
    
    std::cout << "變數數值: \n";
    for(size_t i = 0; i < result.best_values.size(); i++){
        std::cout << "  x_" << i << " = " << result.best_values[i] << "\n";
    }

    return 0;
}