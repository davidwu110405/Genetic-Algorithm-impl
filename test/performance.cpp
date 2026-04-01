#include "GA.hpp"
#include "tools.hpp"

int main(){
    int population_size = 10000;
    std::cout << "Basic population initialization (size = " << population_size << "):" << '\n';
    GA::Population<8> population(population_size);
    for(int i=0; i<10; i++){
        std::cout << "population[" << i << "]=" << population.chromos[i] << '\n';
    };

    float mutation_rate = 0.05;
    MEASURE_TIME(GA::mutation<8>, population, mutation_rate);
    // GA::mutation(population, mutation_rate);
    std::cout << "\nMutation test(mutation rate = " << mutation_rate << "):" << '\n';
    for(int i=0; i<10; i++){
        std::cout << "population[" << i << "]=" << population.chromos[i] << '\n';
    };

    std::cout << "\nParam initialization test:" << '\n';
    GA::GA_Params params_default;

    MEASURE_TIME(&GA::GA_Params::print_params, &params_default);

    std::cout << "\nPopulation value update test:" << '\n';
    
    std::cout << '\n' << "End of test." << '\n';
    return 0;
}