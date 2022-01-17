#include "leader_zero.h"

uint32_t get_leader_zero(uint32_t hash_value) {
    uint32_t mask = 1;
    uint32_t cnt = 1;
    for ( uint32_t i = 0; i < sizeof(hash_value) * 8; i++) {
        if ((mask & hash_value) != 0){
            break;
        }
        mask <<= 1;
        cnt++;
    }
    if (cnt >= 32) {
        cnt = 31;
    }
    return cnt;
}
