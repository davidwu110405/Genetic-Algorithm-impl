#include "GA_BIN_struct.hpp"
#include <cmath>

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
    GA_BIN::Params ga_params(60, 10, 6, 10, 0.6, GA_BIN::CrossMethods::SINGLE_POINT, 0.05, GA_BIN::MutMethods::CONST, 1.0, -1.0);
    ga_params.print_params();
    GA_BIN::Population population(ga_params);
    population._update_chromo_value(ga_params);

    population._evaluation(rastrigin_func);
    population._refresh_selection(GA_BIN::SelMethods::BEST);
    population.print_population(ga_params, 0);

    population._mutation(ga_params);
    population._update_chromo_value(ga_params);

    population._evaluation(rastrigin_func);
    population._refresh_selection(GA_BIN::SelMethods::RANDOM);
    population.print_population(ga_params, 0);

    population._refresh_selection(GA_BIN::SelMethods::BEST);
    population.print_population(ga_params, 100);
    population._crossover(ga_params);
    population._update_chromo_value(ga_params);
    population.print_population(ga_params, 100);

    return 0;
}