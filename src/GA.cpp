#include "GA.hpp"

std::string GA::enum2str(SelMethods method){
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
}

std::string GA::enum2str(CrossMethods method){
    switch(method){
        case CrossMethods::SINGLE_POINT:
            return "Single point";
        case CrossMethods::MULTI_POINT:
            return "Multi point";
        default:
            return "Unknown";
    }
}

std::string GA::enum2str(MutMethods method){
    switch(method){
        case MutMethods::CONST:
            return "Constant";
        case MutMethods::DECREASE:
            return "Decrease";
        default:
            return "Unknown";
    }
}