#ifndef LIB_GA
#define LIB_GA
#include <vector>
#include <fstream>
#include "GA_BIN.hpp"


struct GAResult {
    std::vector<bool> best_chromosome;
    std::vector<double> best_values;
    double best_fitness;
};

void generation_CSV_writter(std::ofstream& file, int generation, const GA_BIN::Population& pop);


template<typename Func>
GAResult run_ga(const GA_BIN::Params& params, Func fitness_func, bool verbose = false, const std::string& csv_filename = "") {
    //Population initialization
    GA_BIN::Population pop(params);
    std::ofstream csv_file;

    //CSV init
    if (!csv_filename.empty()) {
        csv_file.open(csv_filename);
        if (csv_file.is_open()) {
            //CSV column header
            csv_file << "Generation,BestFitnessValue, BestFunctionValue";
            for(int i = 0; i < params.answer_count; i++) {
                csv_file << "x_" << i << ",";
            }
            csv_file << "Chromosome\n";
        } else {
            std::cerr << "警告：無法開啟檔案 " << csv_filename << " 進行寫入。\n";
        }
    }

    //Iteration start
    for (int gen = 0; gen < params.generation_num; ++gen) {
        //update chromosome value(uint64_t)
        pop._update_chromo_value(params);
        pop._evaluation(fitness_func);

        //Store status in CSV
        if (csv_file.is_open()) {
            generation_CSV_writter(csv_file, gen, pop);
        }

        //Print progress
        if (verbose && (gen % (params.generation_num / 10) == 0 || gen == params.generation_num - 1)) {
            double max_fit = *std::max_element(pop.fitness_values.begin(), pop.fitness_values.begin() + pop.current_chromo_count);
            std::cout << "Generation " << gen << " | Best Fitness: " << max_fit << "\n";
        }

        //Crossover
        pop._init_selection(params);
        pop._crossover(params);

        //Mutation
        pop._mutation(params);
        
        //Prepare next generation
        pop._update_chromo_value(params);
        pop._evaluation(fitness_func);
        pop._prepare_next_generation(params);

        
    }

    if (csv_file.is_open()) {
        generation_CSV_writter(csv_file, params.generation_num, pop);
        csv_file.close();
    }

    //Update final value 
    pop._update_chromo_value(params);
    pop._evaluation(fitness_func);

    //Pick best answer
    auto best_it = std::max_element(pop.fitness_values.begin(), pop.fitness_values.begin() + pop.current_chromo_count);
    int best_idx = std::distance(pop.fitness_values.begin(), best_it);

    return {
        pop.chromos[best_idx],
        pop.chromo_values[best_idx],
        pop.fitness_values[best_idx]
    };
}

#endif