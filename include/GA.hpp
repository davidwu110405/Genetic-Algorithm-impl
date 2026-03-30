#ifndef LIB_GA
#define LIB_GA

#include <vector>
#include <iostream>
#include <bitset>
#include <random>
#include <math.h>

namespace GA{
enum class SelMethods{
    BEST,
    RANDOM,
    ROULETTE_DEFAULT,
    ROULETTE_RANK,
};

enum class CrossMethods{
    SINGLE_POINT,
    MULTI_POINT,
};

enum class MutMethods{
    CONST,
    DECREASE,
};

struct GA_Params{
             int population_size;
             int generation_num;
      SelMethods selection_method;
           float crossover_prob;
    CrossMethods crossover_method;
           float mutation_prob;
      MutMethods mutation_method;
};

template<size_t N>
struct Population{
    /*Data*/
    std::vector<std::bitset<N>> chrosomes;
    std::vector<float> fitness_values;
    const ulong range_chromosome = std::pow(2, int(N));

    /*Random generator*/
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
        };
    };
    return 0;
};/*int mutation*/

template<size_t N, typename T>
double chromosome_to_value(std::bitset<N>& chromo, ulong range_input, T bound_upper, T bound_lower){
    double range_output = static_cast<double>(bound_upper - bound_lower);
    double input = static_cast<double>(chromo.to_ulong());
    double range_input_double = static_cast<double>(range_input);
    return input / range_input_double * range_output + bound_lower;
};/*double chromosome_to_value*/

template<typename Func, typename T>
float fitness_value(Func f, T x){
    return 1/(1+std::abs(f(x)));
};/*float fitness_value*/
};/*namespace GA*/

#endif