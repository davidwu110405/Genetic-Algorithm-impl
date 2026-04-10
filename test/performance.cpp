#include "GA_BIN_struct.hpp"
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
    GA_BIN::Params ga_params(100, 10, population_size);
    GA_BIN::Population population(ga_params);
    std::cout << "Basic population initialization (size = " << population_size << "):" << '\n';
    // {MEASURE_SCOPE("GA_BIN::Params::Params()");
    //     GA_BIN::Params test_params(100, 10, population_size);
    // }
    // {MEASURE_SCOPE("GA_BIN::Params::print_params()");
    //     ga_params.print_params();
    // }
    // {MEASURE_SCOPE("GA_BIN::Population::Population()");
    //     GA_BIN::Population population(ga_params);
    // }
    {MEASURE_SCOPE("GA_BIN::Population::update_chromo_value()");
        population.update_chromo_value(ga_params);
    }
    {MEASURE_SCOPE("GA_BIN::Population::evaluation()");
        population.evaluation(testfunc);
    }
    {MEASURE_SCOPE("GA_BIN::Population::refresh_selection(GA_BIN::SelMethods::BEST)");
        population.refresh_selection(GA_BIN::SelMethods::BEST);
    }
    // {MEASURE_SCOPE("GA_BIN::Population::refresh_selection(GA_BIN::SelMethods::RANDOM)");
    //     population.refresh_selection(GA_BIN::SelMethods::RANDOM);
    // }
    // {MEASURE_SCOPE("GA_BIN::Population::mutation()");
    //     population.mutation(ga_params);
    // }
    // {MEASURE_SCOPE("GA_BIN::Population::print_population()");
    //     population.print_population(ga_params, 5);
    // }
    // {MEASURE_SCOPE("GA_BIN::Params::print_params()");
    //     ga_params.print_params();
    // }
    
    std::cout << '\n' << "End of test." << '\n';
    return 0;
}