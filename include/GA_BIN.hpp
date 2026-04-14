#ifndef LIB_GA_BIN
#define LIB_GA_BIN
#pragma once

#include <vector>
#include <cmath>
#include <random>
#include <cassert>
#include <array>
#include <iostream>
#include <algorithm>

namespace GA_BIN{

enum struct SelMethods{
    BEST,
    RANDOM,
    ROULETTE_DEFAULT,
    ROULETTE_RANK,
    TOURNAMENT
};

enum struct CrossMethods{
    SINGLE_POINT,
    MULTI_POINT,
};

enum struct MutMethods{
    CONST,
    DECREASE,
};

std::string enum2str(SelMethods method);
std::string enum2str(CrossMethods method);
std::string enum2str(MutMethods method);

uint64_t vector_bool2ulong(const std::vector<bool>&, const size_t, const size_t);

struct Params{
    int chromosome_length;
    int population_size;
    int generation_num;
    SelMethods parent_selection_method;
    float crossover_prob;
    CrossMethods crossover_method;
    float mutation_prob;
    MutMethods mutation_method;
    std::array<double, 2> search_bound;
    int bits_per_answer;
    int answer_count;

    void print_params();

    Params( const int chromo_len = 300,
            const int bits = 50,
            const int pop_size = 50,
            const int gen_num = 1000,
            SelMethods parent_sel_meth= SelMethods::TOURNAMENT,
            const float cross_prob = 0.8f,
            const CrossMethods cross_meth = CrossMethods::SINGLE_POINT,
            const float mut_prob = 0.1f,
            const MutMethods mut_meth = MutMethods::CONST,
            const double upper = 5.12,
            const double lower = -5.12
    );
    ~Params() = default;
};



struct Population{
    /*Data*/
    std::vector<std::vector<bool>> chromos;
    std::vector<std::vector<double>> chromo_values;
    std::vector<double> function_values;
    std::vector<double> fitness_values;
    std::discrete_distribution<int> current_roulette_dist;
    double range_chromos;
    int generation_count;
    int current_chromo_count;

    Population(const Params&);
    ~Population() = default;

    /*sub functions*/
    static std::mt19937& get_random_engine();
    void print_population(const Params&, int);
    
    /*main functions*/
    int _update_chromo_value(const Params&);
    int _mutation(const Params&);
    template<typename Func> int _evaluation(Func f){
        fitness_values.clear();
        function_values.clear(); // 清空舊的原始值
        for(size_t i=0; i<chromos.size();i++){
            if(chromos[i].size() == 0){
                break;
            };
            double function_value = f(chromo_values[i]);
            function_values.push_back(function_value);
            
            fitness_values.push_back(1.0 / (1.0 + std::abs(function_value)));
        }
        return 0;
    }/*int _evaluation*/
    int _init_selection(const Params& params);
    std::pair<int, int> _select2parents(const Params& params);
    int _crossover(const Params&, int points=1);
    int _prepare_next_generation(const Params&);
};/*struct Population*/

}

#endif
