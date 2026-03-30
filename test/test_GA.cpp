#include "GA.hpp"

int main(){
    int population_size = 10000;
    std::cout << "Basic population initialization (size = " << population_size << "):" << '\n';
    GA::Population<8> population(population_size);
    for(int i=0; i<10; i++){
        std::cout << "population[" << i << "]=" << population.chrosomes[i] << '\n';
    };

    float mutation_rate = 0.05;
    GA::mutation(population, mutation_rate);
    std::cout << "Mutation test(mutation rate = " << mutation_rate << "):" << '\n';
    for(int i=0; i<10; i++){
        std::cout << "population[" << i << "]=" << population.chrosomes[i] << '\n';
    }

    std::cout << '\n' << "End of test." << '\n';
    return 0;
}