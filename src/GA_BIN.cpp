#include "GA_BIN.hpp"

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
        case SelMethods::TOURNAMENT:
            return "Tournament";
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

unsigned long long vector_bool2ulong
    (const std::vector<bool>& chromo,
     const size_t begin_idx,
     const size_t offset){
    assert((begin_idx + offset) <= chromo.size() && "Assertion error: Iterator calculation out of bounds!");
    unsigned long long tmp = 0;
    
    for(size_t i=0; i<offset; i++){
        if (chromo[begin_idx + i]){
            tmp |= (1ULL << static_cast<int>(offset-1-i));
        }
    }
    return tmp;
};/*unsigned long long vector_bool2ulong*/

Params::Params(
    int chromo_len,
    int bits,
    int pop_size,
    int gen_num,
    SelMethods parent_sel_meth,
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
    parent_selection_method(parent_sel_meth),
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
    std::cout << "Crossover probability: " << crossover_prob << '\n';
    std::cout << "Crossover method     : " << enum2str(crossover_method) << '\n';
    std::cout << "Mutation probability : " << mutation_prob << '\n';
    std::cout << "Mutation method      : " << enum2str(mutation_method) << '\n';
    std::cout << "Answer count         : " << answer_count << '\n';
}

Population::Population(const Params& params){
    bool random_bit;
    std::vector<bool> temp_vec_bool;
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
    temp_vec_bool.reserve(chromo_len);

    for(int i=0; i<pop_size; i++){
        for(int j=0; j<chromo_len; j++){
            random_bit = static_cast<bool>(dist(gen));
            chromos[i].push_back(random_bit);
        };
    };
    range_chromos = static_cast<double>(std::pow(2, params.bits_per_answer));
    generation_count = 0;
    current_chromo_count = pop_size;
};/*Population::Population*/

std::mt19937& Population::get_random_engine(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
};

void Population::print_population(const Params& params, int topk){
    if(topk > current_chromo_count){
        topk = current_chromo_count;
    }
    std::cout << "Current size of chromos: " << current_chromo_count << " (Reserved capacity: " << chromos.capacity() << ')' <<'\n';
    std::cout << "Lenght of chromos: " << params.chromosome_length << '\n';
    std::cout << "Top " << topk << " chromos: " << '\n';
    for(int i=0; i<topk; i++){
        for(int j=0; j<params.chromosome_length; j++){
            if(j % params.bits_per_answer == 0){
                std::cout << ": " << chromo_values[i][j] << '\n';
            }
            std::cout << chromos[i][j];
        }
        std::cout << "\nfitness value: " << fitness_values[i] << '\n';
    };
};/*void Population::print_population*/

int Population::_update_chromo_value(const Params& params){
    double tmp = 0.0;
    for(size_t i=0; i<chromos.capacity(); i++){
        if(chromos[i].size() == 0){
            current_chromo_count = i;
            break;
        }
    }
    for(auto& chromo_value: chromo_values){
        chromo_value.clear();
    }
    for(int i=0; i<current_chromo_count; i++){
        for(int j=0; j<params.answer_count;j++){
            tmp = static_cast<double>(vector_bool2ulong(chromos[i], j*params.bits_per_answer, params.bits_per_answer));
            tmp = tmp / range_chromos * (params.search_bound[0] - params.search_bound[1]) + params.search_bound[1];
            chromo_values[i].push_back(tmp);
        }
    }
    return 0;
};/*int Population::_update_chromo_value*/

int Population::_mutation(const Params& params){
    std::mt19937& gen = get_random_engine();
    switch(params.mutation_method){
        case MutMethods::CONST:{
            std::bernoulli_distribution dist(params.mutation_prob);
            for(int i = params.population_size; i < current_chromo_count; i++){
                for(size_t j=0; j < chromos[i].size(); j++){
                    if(dist(gen)){
                        chromos[i][j].flip();
                    }
                }
            }
            break;
        }
        case MutMethods::DECREASE:{
            std::cout << "Mutation with decreasing probability is not available yet.";
            break;
        }
        default:
            return 1;
    }
    
    return 0;
};/*int Population::_mutation*/

int Population::_init_selection(const Params& params){
    /*Gemini 修正版*/
    switch(params.parent_selection_method){
        case SelMethods::ROULETTE_DEFAULT:{
            // 直接利用 fitness_values 建立輪盤 (注意：fitness 必須 >= 0)
            current_roulette_dist = std::discrete_distribution<int>(
                fitness_values.begin(), 
                fitness_values.begin() + params.population_size
            );
            break;
        }
        case SelMethods::ROULETTE_RANK:{
            int pop_size = params.population_size;
            std::vector<int> indices(pop_size);
            std::iota(indices.begin(), indices.end(), 0); 
            
            // 依據適應度由小到大排序索引
            std::sort(indices.begin(), indices.end(), 
                [this](int i1, int i2) { return fitness_values[i1] < fitness_values[i2]; });
            
            // 給予權重：最差的給 1，最好的給 pop_size
            std::vector<double> rank_weights(pop_size, 0.0);
            for (int i = 0; i < pop_size; ++i) {
                rank_weights[indices[i]] = static_cast<double>(i + 1); 
            }
            
            // 建立排名輪盤
            current_roulette_dist = std::discrete_distribution<int>(rank_weights.begin(), rank_weights.end());
            break;
        }
        case SelMethods::TOURNAMENT:
        case SelMethods::RANDOM:
        case SelMethods::BEST:
            // 這些方法不需要預先計算總和或分佈，所以這裡什麼都不用做
            break;
        default:
            return 1;
    }
    return 0;
};

std::pair<int, int> Population::_select2parents(const Params& params){
    /*Gemini 修正版*/
    std::mt19937& gen = get_random_engine();
    int p1 = 0, p2 = 0;

    switch(params.parent_selection_method){
        case SelMethods::ROULETTE_DEFAULT:
        case SelMethods::ROULETTE_RANK:{
            // 從剛才 _setup_selection 建立好的輪盤中抽樣
            p1 = current_roulette_dist(gen);
            p2 = current_roulette_dist(gen);
            break;
        }
        case SelMethods::TOURNAMENT:{
            // 錦標賽法：隨機抽 k 個（這裡預設 k=2），取最好的
            std::uniform_int_distribution<int> dist(0, params.population_size - 1);
            
            auto run_tournament = [&]() {
                int competitor1 = dist(gen);
                int competitor2 = dist(gen);
                return (fitness_values[competitor1] > fitness_values[competitor2]) ? competitor1 : competitor2;
            };

            p1 = run_tournament();
            p2 = run_tournament();
            break;
        }
        case SelMethods::RANDOM:{
            std::uniform_int_distribution<int> dist(0, params.population_size - 1);
            p1 = dist(gen);
            p2 = dist(gen);
            break;
        }
        case SelMethods::BEST:{
            // 通常這只做測試用，因為這會導致所有子代都由最好的兩個個體產生
            // 找出前兩名的索引
            int best1 = 0, best2 = 1;
            if(fitness_values[best2] > fitness_values[best1]) std::swap(best1, best2);
            for(int i=2; i < params.population_size; ++i){
                if(fitness_values[i] > fitness_values[best1]){
                    best2 = best1;
                    best1 = i;
                } else if(fitness_values[i] > fitness_values[best2]){
                    best2 = i;
                }
            }
            p1 = best1;
            p2 = best2;
            break;
        }
    }
    return {p1, p2};
};/*std::pair<int, int> Population::_select2parents*/

int Population::_crossover(const Params& params, const int points){
    /*Gemini修正版*/
    std::mt19937& gen = get_random_engine();
    std::bernoulli_distribution cross_prob_dist(params.crossover_prob); // 決定是否觸發交配的骰子
    
    switch(params.crossover_method){
        case CrossMethods::SINGLE_POINT:{
            std::uniform_int_distribution<int> cut_dist(1, params.chromosome_length - 1);
            int children_generated = 0;
            
            // 持續產生子代，直到補滿下一個 population_size
            while (children_generated < params.population_size) {
                
                // 1. 取得兩個父代的索引
                auto [p1_idx, p2_idx] = _select2parents(params);
                assert((chromos[current_chromo_count].size() == 0 && chromos[current_chromo_count+1].size() == 0) && "Assertion error");

                // 2. 擲骰子決定是否交配
                if (cross_prob_dist(gen)) {
                    int cut_point = cut_dist(gen);
                    for(int j=0; j<params.chromosome_length; j++){
                        if(j >= cut_point){
                            chromos[current_chromo_count].push_back(chromos[p2_idx][j]);
                            chromos[current_chromo_count+1].push_back(chromos[p1_idx][j]);
                        } else {
                            chromos[current_chromo_count].push_back(chromos[p1_idx][j]);
                            chromos[current_chromo_count+1].push_back(chromos[p2_idx][j]);
                        }
                    }
                } else {
                    // 若沒有觸發交配，直接複製父代基因 (Clone)
                    chromos[current_chromo_count] = chromos[p1_idx];
                    chromos[current_chromo_count+1] = chromos[p2_idx];
                }
                
                current_chromo_count += 2;
                children_generated += 2;
            }
            break;
        }
        case CrossMethods::MULTI_POINT:{
            std::cout << "Crossover with multipoint is not available yet.";
            break;
        }
        default:
            return 1;
    }
    return 0;
};/*int Population::_crossover*/

int Population::_prepare_next_generation(const Params& params){
    /*Gemini修正版*/
    int pop_size = params.population_size;
    
    // 1. 產生索引清單
    std::vector<int> indices(current_chromo_count);
    std::iota(indices.begin(), indices.end(), 0);

    // 2. 根據適應度由大到小排序 (越好的排越前面)
    std::sort(indices.begin(), indices.end(), 
        [this](int i1, int i2) { 
            return fitness_values[i1] > fitness_values[i2]; 
        });

    // 3. 準備新陣列
    std::vector<std::vector<bool>> next_gen_chromos;
    next_gen_chromos.reserve(pop_size * 2); 
    
    // 4. 嚴格挑選排名前 pop_size 的個體進入下一代
    for(int i = 0; i < pop_size; i++){
        next_gen_chromos.push_back(chromos[indices[i]]);
    }
    // 關鍵修復：把後面的空間補齊，確保都是乾淨的空陣列
    next_gen_chromos.resize(pop_size * 2); 
    
    // 5. 覆蓋舊世代
    chromos = std::move(next_gen_chromos);
    current_chromo_count = pop_size;

    return 0;
};/*int _prepare_next_generation*/

};