#ifndef LIB_GA
#define LIB_GA

#include <vector>
#include <iostream>
#include <bitset>
#include <random>
#include <math.h>
#include <string>

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

std::string enum2str(SelMethods method);
std::string enum2str(CrossMethods method);
std::string enum2str(MutMethods method);

struct GA_Params{
                      int population_size;
                      int generation_num;
               SelMethods selection_method;
                    float crossover_prob;
             CrossMethods crossover_method;
                    float mutation_prob;
               MutMethods mutation_method;
    std::array<double, 2> search_bound;

    void print_params(){
        std::cout << "Population size      : " << population_size << '\n';
        std::cout << "Generation number    : " << generation_num << '\n';
        std::cout << "Selection method     : " << enum2str(selection_method) << '\n';
        std::cout << "Crossover probability: " << crossover_prob << '\n';
        std::cout << "Crossover method     : " << enum2str(crossover_method) << '\n';
        std::cout << "Mutation probability : " << mutation_prob << '\n';
        std::cout << "Crossover method     : " << enum2str(crossover_method) << '\n';
    }

    GA_Params(
        int pop_size = 10,
        int gen_num = 10, 
        SelMethods sel_meth = SelMethods::BEST,
        float cross_prob = 0.6f,
        CrossMethods cross_meth = CrossMethods::SINGLE_POINT,
        float mut_prob = 0.05f,
        MutMethods mut_meth = MutMethods::CONST,
        double upper = 10.0,
        double lower = -10.0
    ) : population_size(pop_size), 
        generation_num(gen_num), 
        selection_method(sel_meth),
        crossover_prob(cross_prob),
        crossover_method(cross_meth),
        mutation_prob(mut_prob),
        mutation_method(mut_meth),
        search_bound{upper, lower}{
    }
    ~GA_Params() = default;
};

template<size_t N>
struct Population{
    /*Data*/
    std::vector<std::bitset<N>> chromos;
    std::vector<double> chromo_values;
    std::vector<float> fitness_values;
    std::vector<bool> selection;
    const double range_chromos = static_cast<double>(std::pow(2, int(N)));

    /*Random generator*/
    static std::mt19937& get_random_engine(){
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    };

    Population(int pop_size){
        auto& gen = get_random_engine();
        std::bernoulli_distribution dist(0.5);
        chromos.resize(pop_size);
        for(auto& chromo : chromos){
            for(int i=0; i<chromos[0].size(); i++){
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
    for(auto& chromo : chromos.chromos){
        for(int i=0; i<chromo.size(); i++){
            if(dist(gen)){
                chromo.flip(i);
            };
        };
    };
    return 0;
};/*int mutation*/

/*single chromosome to ranged value*/
template<size_t N, typename T>
double chromosome_to_value(std::bitset<N>& chromo, u_long range_input, T bound_upper, T bound_lower){
    double range_output = static_cast<double>(bound_upper - bound_lower);
    double input = static_cast<double>(chromo.to_ulong());
    double range_input_double = static_cast<double>(range_input);
    return input / range_input_double * range_output + bound_lower;
};/*double chromosome_to_value*/

/*population to value*/
template<size_t N>
int update_population_value(Population<N>& pop, GA_Params& params){
    double tmp = 0.0f;
    pop.chromo_values.clear();
    for(int i=0; i<pop.chromos.size(); i++){
        tmp = static_cast<double>(pop.chromos[i].to_ulong());
        tmp = tmp / pop.range_chromos * (params.search_bound[0] - params.search_bound[1]) + params.search_bound[1];
        pop.chromo_values.push_back(tmp);
    }
    return 0;
};

template<typename Func, typename T>
float fitness_value(Func f, T x){
    return 1/(1+std::abs(f(x)));
};/*float fitness_value*/

};/*namespace GA*/

#endif