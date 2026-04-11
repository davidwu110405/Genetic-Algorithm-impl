#include "GA_BIN_func.hpp"

namespace GA_BIN{
unsigned long vector_bool2ulong
    (const std::vector<bool>& chromo,
     const size_t begin_idx,
     const size_t offset){
    assert((begin_idx + offset) <= chromo.size() && "Assertion error: Iterator calculation out of bounds!");
    unsigned long tmp = 0;
    
    for(size_t i=0; i<offset; i++){
        if (chromo[begin_idx + i]){
            tmp += static_cast<unsigned long>(std::pow(2, static_cast<int>(offset-1-i)));
        }
    }
    return tmp;
};/*unsigned long vector_bool2ulong*/
std::vector<double> roulette_prob(const std::vector<double> input){
    std::vector<double> output;
    output.reserve(input.size());
    double sum = 0.0;

    for(double v: input){
        sum += v;
    }
    for(size_t i=0; i<input.size(); i++){
        output.push_back(input[i]/sum);
    }
    return output;
};/*std::vector<double> roullete*/

}/*namespaace GA_BIN*/