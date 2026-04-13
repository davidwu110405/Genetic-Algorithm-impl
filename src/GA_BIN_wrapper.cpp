#include "GA_BIN_wrapper.hpp"

void generation_CSV_writter(std::ofstream& file, int generation, const GA_BIN::Population& pop) {
    if (!file.is_open() || pop.current_chromo_count == 0) return;

    auto best_it = std::max_element(pop.fitness_values.begin(), pop.fitness_values.begin() + pop.current_chromo_count);
    int best_idx = std::distance(pop.fitness_values.begin(), best_it);
    
    file << generation << ",";
    file << std::fixed << std::setprecision(10) << pop.fitness_values[best_idx] << ",";
    file << std::fixed << std::setprecision(10) << pop.function_values[best_idx] << ",";
    for (size_t j = 0; j < pop.chromo_values[best_idx].size(); j++) {
        file << pop.chromo_values[best_idx][j] << ",";
    }
    for (size_t j = 0; j < pop.chromos[best_idx].size(); j++) {
        file << (pop.chromos[best_idx][j] ? '1' : '0');
    }

    file << "\n";
}