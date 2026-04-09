#ifndef LIB_GA_BIN_FUNC
#define LIB_GA_BIN_FUNC
#pragma once

#include <vector>
#include <cassert>

namespace GA_BIN{
u_long vector_bool2ulong(const std::vector<bool>&, const size_t, const size_t);
std::vector<double> roulette_prob(const std::vector<double>);

};

#endif