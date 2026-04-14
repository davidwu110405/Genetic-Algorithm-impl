#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
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
        0.1f, // mutation_prob (突變機率 10%)
        GA_BIN::MutMethods::CONST, // mutation_method
        5.12, // 搜尋上界
        -5.12 // 搜尋下界
    );
    
    std::cout << "開始執行 GA:\n";
    params.print_params();

    // run_ga(GA::BIN::Params, targetfunction, verbose(bool), csv filename)
    // verbose: 是否列印進度
    int total_runs = 10; 

    for(int run_idx = 0; run_idx < total_runs; ++run_idx) {
        std::cout << "\n========================================\n";
        std::cout << "開始執行 GA: 第 " << run_idx << " 次\n";
        std::string filename = "Rastrigin_result/Rastrigin-" + std::to_string(run_idx) + ".csv";
        
        GAResult result = run_ga(params, rastrigin_func, true, filename);

        std::cout << "\n第 " << run_idx << " 次完成\n";
        std::cout << "最佳 Fitness: " << std::fixed << std::setprecision(6) << result.best_fitness << "\n";
        
        std::cout << "變數數值: \n";
        for(size_t i = 0; i < result.best_values.size(); i++){
            std::cout << "  x_" << i << " = " << result.best_values[i] << "\n";
        }
    }

    return 0;
}