#ifndef LIB_GA
#define LIB_GA

#include <vector>
#include <iostream>
#include <bitset>
#include <random>
namespace GA{
template<size_t N>
struct Population{
    std::vector<std::bitset<N>> chrosomes;
    std::vector<float> fitness_values;

    static std::mt19937& get_random_engine(){
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    };

    Population(int pop_size){
        auto& gen = get_random_engine();
        std::bernoulli_distribution dist(0.5);
        chrosomes.resize(pop_size);
        for(auto& chromo : chrosomes){
            for(int i=0; i<chrosomes[0].size(); i++){
                chromo[i] = dist(gen);
            };
        }
    };
    ~Population() = default;
};/*struct Population*/

template<size_t N>
int mutation(Population<N>& chromos, float mut_rate){
    auto& gen = chromos.get_random_engine();
    std::bernoulli_distribution dist(mut_rate);
    for(auto& chromo : chromos.chrosomes){
        for(int i=0; i<chromo.size(); i++){
            if(dist(gen)){
                chromo.flip(i);
            };
        }
    };
    return 0;
};/*int mutation*/

}/*namespace GA*/;

#endif