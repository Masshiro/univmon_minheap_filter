//
// Created by masshiro on 1/20/22.
//

#ifndef UNIVMON_MINHEAP_FILTER_UNIVMONUTILS_HPP
#define UNIVMON_MINHEAP_FILTER_UNIVMONUTILS_HPP

#include <cstdint>
#include <immintrin.h>
#include <cmath>
#include <bitset>

namespace univmon{
//--------------------------
// Calculate moments: G-sum functions
    double G_sum(double base, uint8_t power){
        return std::pow(base, power);
    }

    double G_entropy(double x){
        return x * std::log(x);
    }

    bool get_hash_bit(uint32_t hash_val, uint8_t index){
        std::bitset<32> hash_value = hash_val;
        return hash_value[index-1];
    }

}   // The end of namespace

#endif //UNIVMON_MINHEAP_FILTER_UNIVMONUTILS_HPP
