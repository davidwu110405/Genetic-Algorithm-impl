#include "GA.hpp"

float Xby2(float x){
    return std::pow(x,2);
};

int main(){
    int population_size = 10000;
    std::cout << "Basic population initialization (size = " << population_size << "):" << '\n';
    GA::Population<8> population(population_size);
    for(int i=0; i<10; i++){
        std::cout << "population[" << i << "]=" << population.chrosomes[i] << '\n';
    };

    float mutation_rate = 0.05;
    GA::mutation(population, mutation_rate);
    std::cout << "\nMutation test(mutation rate = " << mutation_rate << "):" << '\n';
    for(int i=0; i<10; i++){
        std::cout << "population[" << i << "]=" << population.chrosomes[i] << '\n';
    };

    std::cout << "\nChromosome to value test:" << '\n';
    for(int i=0; i<10; i++){
        double value = GA::chromosome_to_value(population.chrosomes[i], population.range_chromosome, 10, -10);
        std::cout << "population[" << i << "]=" << value << "|fitness value:" << GA::fitness_value(Xby2, value) << '\n';
    };

    std::cout << "\nFitness value test:" << GA::fitness_value(Xby2, 2) << '\n';

    std::cout << '\n' << "End of test." << '\n';
    return 0;
}