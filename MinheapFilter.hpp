//
// Created by Masshiro on 2022/1/15.
//

#ifndef UNIVMON_MINHEAP_FILTER_MINHEAPFILTER_HPP
#define UNIVMON_MINHEAP_FILTER_MINHEAPFILTER_HPP

#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <queue>
#include <string>
#include <bitset>

#include "leader_zero.h"

uint32_t get_length_of_ones(uint32_t a, uint32_t max_len) {
    for (uint32_t i = max_len ; i != 0; i--){
        if (  ( a % uint32_t( std::pow(2,i) ) )== (std::pow(2,i)-1)  )
            return i;
    }
    return 0 ;
}

template<class K, class V>
struct cmpbyValue {
    bool operator() (const std::pair<K, V>& p1, std::pair<K, V>& p2){
        return p1.second < p2.second;
    }
};

template<class K, class V>
struct findHit {
    findHit(K val) : val_(val) {}
    bool operator() (const std::pair<K, V>& elem) const{
        return val_ == elem.second;
    }
private:
    K val_;
};

template<class K, class V>
class Control_List{
private:
    uint32_t TOP_K;
    uint32_t LEVEL;
    uint16_t *storage_condition;
    std::pair<K, V> ** control_list;

public:
    Control_List(uint32_t top_k, uint32_t level){
        TOP_K = top_k;
        LEVEL = level;
        control_list = new std::pair<K, V>* [LEVEL];
        for (int i = 0; i < level; i++){
            control_list[i] = new std::pair<K, V> [TOP_K];
        }
        storage_condition = new uint16_t [TOP_K];

        for (int j =0; j < TOP_K; j++){
            for (int i =0; i < LEVEL; i++){
                control_list[i][j].first = 0;
                control_list[i][j].second = 0.0;
            }
            storage_condition[j] = 0;
        }
    }

    ~Control_List(){
        for (int i =0; i < LEVEL; i++){
            delete [] control_list[i];
        }
        delete [] control_list;
        delete [] storage_condition;
    }

    void sort_list_at_level_k(int k){
        std::vector <std::pair<K, V> > tmp_list; //[TOP_K];
        for (int i = 0; i < TOP_K; i++){
            // tmp_list[i].first = control_list[k][i].first;
            // tmp_list[i].second = control_list[k][i].second;

            tmp_list.push_back(std::pair<K, V> (control_list[k][i].first, control_list[k][i].second));
            // std::pair<int, double> (control_list[k][i].first, control_list[k][i].second)
        }
        sort(tmp_list.begin(), tmp_list.end(), cmpbyValue<K, V>());
        for (int i = 0; i < TOP_K; i++){
            control_list[k][i].first = tmp_list[i].first;
            control_list[k][i].second = tmp_list[i].second;
        }
    }

    void insert_element_at_level_k (K ID, V count, int k){
        /*  Condition 1: The same hash has been inserted.   */
        for (int i = 0; i < storage_condition[k]; i++){
            if (control_list[k][i].first == ID){
                control_list[k][i].second = count;
                sort_list_at_level_k(k);
                return;
            }
        }

        /*  Condition 2: The hash value is totally new here.    */
        // List is not full yet
        if (storage_condition[k] < TOP_K){
            control_list[k][storage_condition[k]].first = ID;
            control_list[k][storage_condition[k]].second = count;
            storage_condition[k]++;
        }
        // list is full, and we need to do something
        else{
            if (storage_condition[k] > TOP_K)
            {
                std::cout << "ATTENTION: Out of Range at Level "<<k<<"!"<<std::endl;
            }
            else{
                sort_list_at_level_k(k);
                // Insert when the incoming pkt has greater cardinality
                if (count > control_list[k][0].second)
                {
                    control_list[k][0].first = ID;
                    control_list[k][0].second = count;
                }
                // or just ignore it.
            }
        }
    }

    void print_list_at_level_k(int k){
        std::bitset<32> hashvalue;
        for (int i = 0; i < TOP_K; i++) {
            hashvalue = control_list[k][i].first;
            std::cout << "Key: \t" << control_list[k][i].first
            << "  Value: \t"<< control_list[k][i].second
            << "  Hash: \t" << hashvalue
            << "  Leading 1s: \t" << get_length_of_ones(control_list[k][i].first, LEVEL)
//            << "  Leading 0s: \t" << get_leader_zero(control_list[k][i].first)
            <<std::endl;
        }
    }

    uint16_t get_storage_condition_at_level_k (int k){
        return storage_condition[k];
    }

    uint32_t get_level_num(){
        return LEVEL;
    }

    std::pair<K, V>* get_elements_at_level_k(uint32_t k){
        // Build a new one then return it
//        std::pair<K, V>* ptr_level_k = new std::pair<K, V>[TOP_K];
//        for (int j=0; j < TOP_K; j++){
//            ptr_level_k[j].first = control_list[k][j].first;
//            ptr_level_k[j].second = control_list[k][j].second;
//        }

        // Return the existing one directly
        return control_list[k];
    }

    uint32_t get_level_capacity(){
        return TOP_K;
    }

//    void output_list_at_level_k(int k, std::string path_name){
//        std::ofstream output_file(path_name);
//        for (int i = 0; i < TOP_K; i++){
//            output_file << "Key: \t" << control_list[k][i].first << "  Value: \t"<<control_list[k][i].second<<std::endl;
//        }
//    }

};



#endif //UNIVMON_MINHEAP_FILTER_MINHEAPFILTER_HPP
