#include "GA_BIN.hpp"
#include "tools.hpp"

double testfunc(std::vector<double>& input){
    double tmp=0.0;
    for(auto& x: input){
        tmp += x;
    }
    return tmp;
}

int main(){
    int population_size = 10000;
    GA_BIN::Params ga_params;
    GA_BIN::Population population(ga_params);
    std::cout << "Basic population initialization (size = " << population_size << "):" << '\n';
    {MEASURE_SCOPE("GA_BIN::Params::Params()");
        GA_BIN::Params test_params;
    }
    {MEASURE_SCOPE("GA_BIN::Params::print_params()");
        ga_params.print_params();
    }
    {MEASURE_SCOPE("GA_BIN::Population::Population()");
        GA_BIN::Population population(ga_params);
    }
    {MEASURE_SCOPE("GA_BIN::Population::_update_chromo_value()");
        population._update_chromo_value(ga_params);
    }
    {MEASURE_SCOPE("GA_BIN::Population::_update_chromo_value()");
        population._mutation(ga_params);
    }
    {MEASURE_SCOPE("GA_BIN::Population::_evaluation()");
        population._evaluation(testfunc);
    }
    {MEASURE_SCOPE("GA_BIN::Population::_init_selection()");
        population._init_selection(ga_params);
    }
    {MEASURE_SCOPE("GA_BIN::Population::_select2parents()");
        population._select2parents(ga_params);
    }
    {MEASURE_SCOPE("GA_BIN::Population::_crossover()");
        population._crossover(ga_params);
    }
    {MEASURE_SCOPE("GA_BIN::Population::_prepare_next_generation()");
        population._prepare_next_generation(ga_params);
    }
    {MEASURE_SCOPE("GA_BIN::Population::print_population()");
        population.print_population(ga_params, 1);
    }
    
    std::cout << '\n' << "End of test." << '\n';
    return 0;
}