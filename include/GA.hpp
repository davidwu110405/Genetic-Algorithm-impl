#ifndef GA_FUNC
#define GA_FUNC

#include <vector>
#include <iostream>
#include <bitset>
#include <random>
namespace GA{
template<size_t N>
struct Chromosome{
    std::bitset<N> bits;

    static std::mt19937& get_random_engine(){
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    };

    Chromosome(){
        auto& gen = get_random_engine();
        std::bernoulli_distribution dist(0.5);
        for(int i=0; i<N; i++){
            bits[i] = dist(gen);
        };
    };
    ~Chromosome() = default;
};/*struct Chromosome*/

template<size_t N>
struct Population{
    std::vector<Chromosome<N>> population;

    Population(int pop_size){
        for(int i=0; i<pop_size; i++){
            population.emplace_back();
        }
    };
    ~Population() = default;
};/*struct Population*/


template<size_t N>
int mutation(Chromosome<N>& chromo, float mut_rate){
    auto& gen = chromo.get_random_engine();
    std::bernoulli_distribution dist(mut_rate);
    for(int i=0; i<N; i++){
        if(dist(gen)){
            chromo.bits.flip(i);
        };
    };
    return 0;
};

}/*namespace GA*/;

#endif