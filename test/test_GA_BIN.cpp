#include "GA_BIN_struct.hpp"
#include "GA_BIN_func.hpp"

double testfunc(std::vector<double>& input){
    double tmp=0.0;
    for(auto& x: input){
        tmp += x;
    }
    return tmp;
}

int main(){
    GA_BIN::Params ga_params(60, 10, 5);
    ga_params.print_params();
    GA_BIN::Population population(ga_params);

    population.update_chromo_value(ga_params);
    population.evaluatiion(ga_params, testfunc);
    population.refresh_selection(GA_BIN::SelMethods::BEST);
    population.print_population(ga_params, 5);

    population.mutation(ga_params);
    population.update_chromo_value(ga_params);
    population.evaluatiion(ga_params, testfunc);
    population.refresh_selection(GA_BIN::SelMethods::RANDOM);
    population.print_population(ga_params, 5);

    


    return 0;
}