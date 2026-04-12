#include "GA_BIN_struct.hpp"
#include "tools.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>
double testfunc(std::vector<double>& input){
    double tmp=0.0;
    for(auto& x: input){
        tmp += x;
    }
    return tmp;
}

double rastrigin_func(std::vector<double>& input){
    double output = 0.0;
    int n_var = input.size();
    output += 10 * n_var;
    for(int i=0; i<n_var; i++){
        output += std::pow(input[i], 2) - 10 * std::cos(2 * input[i] * std::acos(-1));
    }
    return output;
}

int main(){
    //init
    GA_BIN::Params ga_params(300, 50, 1000, 10000, 0.8, GA_BIN::CrossMethods::SINGLE_POINT, 0.05, GA_BIN::MutMethods::CONST, 1.0, -1.0);
    ga_params.print_params();
    GA_BIN::Population population(ga_params);
    population.print_population(ga_params, 5);
    population._update_chromo_value(ga_params);
    population.print_population(ga_params, 5);

    //eval
    population._evaluation(rastrigin_func);
    auto idx = std::max_element(population.fitness_values.begin(), population.fitness_values.end());
    std::cout << "Max fitness value: " << *idx << '\n';
    {MEASURE_SCOPE("GA");
        double max=0.0;
    for(int i=0; i<ga_params.generation_num; i++){
        std::cout << '(' << i << '/' << ga_params.generation_num << ")--";
        //select parents
        population._refresh_selection(GA_BIN::SelMethods::BEST);

        //crossover
        population._crossover(ga_params);
        
        //mutation
        population._mutation(ga_params);
        population._update_chromo_value(ga_params);

        //eval
        population._evaluation(rastrigin_func);
        
        auto idx = std::max_element(population.fitness_values.begin(), population.fitness_values.end());
        std::cout << "Max fitness value: " << *idx << ", Best fitness value: " << max << '\n';
        if(*idx>max){
            max = *idx;
        }
        //select next generation
        population._refresh_selection(GA_BIN::SelMethods::BEST);
        population._prepare_next_generation(ga_params);
        // population.print_population(ga_params, 100);
    }
    std::cout << "Best fitness value: " << max << '\n';
    }
    
    // population.print_population(ga_params, 10);
    // population._prepare_next_generation(ga_params);

    // population.print_population(ga_params, 100);
    // population._update_chromo_value(ga_params);
    // population._evaluation(rastrigin_func);
    // population.print_population(ga_params, 100);

    
    // population._update_chromo_value(ga_params);
    // population._evaluation(rastrigin_func);
    // population.print_population(ga_params, 0);

    return 0;
}