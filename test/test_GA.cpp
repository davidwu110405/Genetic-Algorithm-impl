#include "GA.hpp"

int main(){
    std::cout << "Basic chromosome initialization:" << '\n';
    GA::Chromosome<8> chromo;
    std::cout << chromo.bits << "\n\n";

    float mutation_rate = 0.05;
    std::cout << "Chromosome mutation test" << '(' << mutation_rate << "):" << '\n';
    GA::mutation(chromo, mutation_rate);
    std::cout << chromo.bits << "\n\n";

    int population_size = 10;
    std::cout << "Basic population initialization (size = " << population_size << "):" << '\n';
    GA::Population<8> population(10);
    for(int i=0; i<10; i++){
        std::cout << "population[" << i << "]=" << population.population[i].bits << '\n';
    };

    std::cout << '\n' << "End of test." << '\n';
    return 0;
}