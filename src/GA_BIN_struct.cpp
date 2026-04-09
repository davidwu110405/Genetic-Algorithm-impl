#include <iostream>
#include <random>
#include "GA_BIN_func.hpp"
#include "GA_BIN_struct.hpp"


namespace GA_BIN{

std::string enum2str(SelMethods method){
    switch(method){
        case SelMethods::BEST:
            return "Best";
        case SelMethods::RANDOM:
            return "Random";
        case SelMethods::ROULETTE_DEFAULT:
            return "Default roulette";
        case SelMethods::ROULETTE_RANK:
            return "Roulette by rank";
        default:
            return "Unknown";
    }
};

std::string enum2str(CrossMethods method){
    switch(method){
        case CrossMethods::SINGLE_POINT:
            return "Single point";
        case CrossMethods::MULTI_POINT:
            return "Multi point";
        default:
            return "Unknown";
    }
}

std::string enum2str(MutMethods method){
    switch(method){
        case MutMethods::CONST:
            return "Constant";
        case MutMethods::DECREASE:
            return "Decrease";
        default:
            return "Unknown";
    }
}

Params::Params(
    int chromo_len,
    int bits,
    int pop_size,
    int gen_num,
    // SelMethods sel_meth,
    float cross_prob,
    CrossMethods cross_meth,
    float mut_prob,
    MutMethods mut_meth,
    double upper,
    double lower
): 
    chromosome_length(chromo_len),
    population_size(pop_size),
    generation_num(gen_num),
    // selection_method(sel_meth),
    crossover_prob(cross_prob),
    crossover_method(cross_meth),
    mutation_prob(mut_prob),
    mutation_method(mut_meth),
    search_bound{upper, lower},
    bits_per_answer{bits}{
        answer_count = chromosome_length / bits_per_answer;
    };/*Params::Params*/

void Params::print_params(){
    std::cout << "Chromosome length    : " << chromosome_length << '\n';
    std::cout << "Population size      : " << population_size << '\n';
    std::cout << "Generation number    : " << generation_num << '\n';
    // std::cout << "Selection method     : " << enum2str(selection_method) << '\n';
    std::cout << "Crossover probability: " << crossover_prob << '\n';
    std::cout << "Crossover method     : " << enum2str(crossover_method) << '\n';
    std::cout << "Mutation probability : " << mutation_prob << '\n';
    std::cout << "Mutation method      : " << enum2str(mutation_method) << '\n';
}

Population::Population(const Params& params){
    bool random_bit;
    std::vector<bool> temp_vec_bool;
    // std::vector<double> temp_vec_double(params.answer_count, 0.0);
    int pop_size = params.population_size;
    int chromo_len = params.chromosome_length;
    std::mt19937& gen = get_random_engine();
    std::bernoulli_distribution dist(0.5);
    chromos.reserve(pop_size*2);
    chromos.resize(pop_size*2);
    for(auto& chromo: chromos){
        chromo.reserve(params.chromosome_length);
    }
    chromo_values.reserve(pop_size*2);
    chromo_values.resize(pop_size*2);
    for(auto& chromo_value: chromo_values){
        chromo_value.reserve(params.answer_count);
    }
    fitness_values.reserve(pop_size*2);
    selection_scores.reserve(pop_size*2);
    temp_vec_bool.reserve(chromo_len);

    for(int i=0; i<pop_size; i++){
        for(int j=0; j<chromo_len; j++){
            random_bit = static_cast<bool>(dist(gen));
            chromos[i].push_back(random_bit);
        };
    };
    range_chromos = static_cast<double>(std::pow(2, params.bits_per_answer));
};/*Population::Population*/

std::mt19937& Population::get_random_engine(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
};

void Population::print_population(const Params& params, int topk){
    if(topk > params.population_size){
        topk = params.population_size;
    }
    std::cout << "Number of chromos: " << params.population_size << " (Reserved capacity: " << chromos.capacity() << ')' <<'\n';
    std::cout << "Lenght of chromos: " << params.chromosome_length << '\n';
    std::cout << "Top " << topk << " chromos: " << '\n';
    for(int i=0; i<topk; i++){
        for(int j=0; j<params.chromosome_length; j++){
            if(j%params.bits_per_answer == 0){
                std::cout << '|';
            }
            std::cout << chromos[i][j];
        }
        std::cout << ":\n";
        
        for(size_t j=0; j<chromo_values[i].size(); j++){
            std::cout << '|' << chromo_values[i][j];
        }
        std::cout << "\nfitness value: " << fitness_values[i] << '\n';
        std::cout << "selection score: " << selection_scores[i] << '\n';

    };
};/*void Population::print_population*/

int Population::update_chromo_value(const Params& params){
    double tmp = 0.0;
    for(auto& chromo_value: chromo_values){
        chromo_value.clear();
    }

    for(size_t i=0; i<chromos.size(); i++){
        if(chromos[i].size() == 0){
            break;
        }
        for(int j=0; j<params.answer_count;j++){
            tmp = static_cast<double>(vector_bool2ulong(chromos[i], j*params.bits_per_answer, params.bits_per_answer));
            tmp = tmp / range_chromos * (params.search_bound[0] - params.search_bound[1]) + params.search_bound[1];
            chromo_values[i].push_back(tmp);
        }
    }
    return 0;
};/*int Population::update_chromo_value*/

int Population::mutation(const Params& params){
    std::mt19937& gen = get_random_engine();
    switch(params.mutation_method){
        case MutMethods::CONST:{
            std::bernoulli_distribution dist(params.mutation_prob);
            for(auto& chromo : chromos){
                for(size_t i=0; i<chromo.size(); i++){
                    if(dist(gen)){
                        chromo[i].flip();
                    }
                }
            }
            break;
        }
        case MutMethods::DECREASE:{
            break;
        }
        default:
            return 1;
    }
    
    return 0;
};/*int mutation*/

int Population::crossover(const Params& params, const int points){
    // std::mt19937& gen = get_random_engine();
    assert((points > 0 && points < params.chromosome_length) && "Assertion error: crossover points must be above 0 and below chromosome length.");
    switch(params.crossover_method){
        case CrossMethods::SINGLE_POINT:{
            break;
        }
        case CrossMethods::MULTI_POINT:{
            break;
        }
        default:
            return 1;
    }
    return 0;
};/*int crossover*/

int Population::refresh_selection(const SelMethods sel_method){
    std::mt19937& gen = get_random_engine();
    std::uniform_int_distribution<int> dist(-100, 100);
    selection_scores.clear();
    switch(sel_method){
        case SelMethods::BEST:{
            for(size_t i=0; i<chromos.size(); i++){
                if(chromos[i].size() == 0){
                    break;
                }
                selection_scores.push_back(0);
                for(size_t j=0; j<chromos.size(); j++){
                    if(chromos[j].size() == 0){
                        break;
                    }
                    if(fitness_values[i]>fitness_values[j]){
                        selection_scores[i] += 1;
                    }
                }
            }
            break;
        }
        case SelMethods::RANDOM:{
            for(size_t i=0; i<chromos.size(); i++){
                if(chromos[i].size() == 0){
                    break;
                }
                selection_scores.push_back(dist(gen));
            }
            break;
        }
        case SelMethods::ROULETTE_DEFAULT:{
            std::vector<double> prob = roulette_prob(fitness_values);
            break;
        }
        case SelMethods::ROULETTE_RANK:{
            break;
        }
        default:
            return 1;
    }
    return 0;
};

};