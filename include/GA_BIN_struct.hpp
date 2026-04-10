#ifndef LIB_GA_BIN
#define LIB_GA_BIN
#pragma once

#include <vector>
#include <cmath>
#include <random>
#include <cassert>
#include <array>

namespace GA_BIN{

enum struct SelMethods{
    BEST,
    RANDOM,
    ROULETTE_DEFAULT,
    ROULETTE_RANK,
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

struct Params{
    int chromosome_length;
    int population_size;
    int generation_num;
    float crossover_prob;
    CrossMethods crossover_method;
    float mutation_prob;
    MutMethods mutation_method;
    std::array<double, 2> search_bound;
    int bits_per_answer;
    int answer_count;

    void print_params();

    Params( const int chromo_len = 60,
            const int bits = 10,
            const int pop_size = 10,
            const int gen_num = 10,
            const float cross_prob = 0.6f,
            const CrossMethods cross_meth = CrossMethods::SINGLE_POINT,
            const float mut_prob = 0.05f,
            const MutMethods mut_meth = MutMethods::CONST,
            const double upper = 10.0,
            const double lower = -10.0
    );
    ~Params() = default;
};



struct Population{
    /*Data*/
    std::vector<std::vector<bool>> chromos;
    std::vector<std::vector<double>> chromo_values;
    std::vector<double> fitness_values;
    std::vector<int> selection_scores;
    double range_chromos;
    int generation_count;

    Population(const Params&);
    ~Population() = default;

    /*sub functions*/
    static std::mt19937& get_random_engine();
    void print_population(const Params&, int);
    int update_chromo_value(const Params&);
    template<typename Func> double _fitness_value(Func f, std::vector<double>& x){
        return 1/(1+std::abs(f(x)));
    }

    

    /*main functions*/
    int mutation(const Params&);
    template<typename Func> int evaluation(Func f){
        fitness_values.clear();
        for(size_t i=0; i<chromos.size();i++){
            if(chromos[i].size() == 0){
                break;
            };
            fitness_values.push_back(_fitness_value(f, chromo_values[i]));
        }
        return 0;
    }/*int evaluation*/
    int crossover(const Params&, int points=2);
    int refresh_selection(const SelMethods);
};/*struct Population*/

}

#endif
