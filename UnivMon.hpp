//
// Created by masshiro on 1/18/22.
//

#ifndef UNIVMON_MINHEAP_FILTER_UNIVMON_HPP
#define UNIVMON_MINHEAP_FILTER_UNIVMON_HPP

#include "UnivmonUtils.hpp"

class UnivMonSketch{
private:
    Control_List<uint32_t, double> filter;
    uint32_t m_level_count;
    uint32_t m_filter_size;
    std::vector<double> moment_for_each_level;

public:
    UnivMonSketch(uint32_t level, int filter_size): filter(filter_size, level){
        m_filter_size = filter_size;
        m_level_count = level;
    }

    uint32_t get_level_num (){
        return m_filter_size;
    }

    uint32_t get_filter_size(){
        return m_level_count;
    }

    void display_filter(){
        for (int i = 0; i < filter.get_level_num(); i++){
            std::cout << "---------- Level "<<i<<" ----------  Storage condition: "<<filter.get_storage_condition_at_level_k(i)<<std::endl;
            filter.print_list_at_level_k(i);
        }
    }

    void update_filter_at_level_k(uint32_t ID, double card, int k){
        filter.insert_element_at_level_k(ID, card, k);
    }

    void display_filter_at_level_k(uint32_t k){
        std::pair<uint32_t, double>* ptr_level_k;
        ptr_level_k = filter.get_elements_at_level_k(k);
        std::cout << "---------- Using pointer method ----------" << std::endl;
        for (int j = 0; j < filter.get_level_capacity(); j++){
            std::cout << "ID:\t" << ptr_level_k[j].first <<"\t\t Cardinality:\t"<<ptr_level_k[j].second<<std::endl;
        }
    }

    void update(uint32_t ID, double card){
        // Decide sample levels
        uint32_t sample_levels = get_length_of_ones(ID, m_level_count -1);
        std::cout<<"Inserting <"<<ID<<", "<<card<<">\t"<<"levels: "<<sample_levels<<std::endl;
        for(int k = sample_levels; k != -1; k--){
            update_filter_at_level_k(ID, card, k);
        }
    }

    double calculate_moment_power(double (*f)(double, uint8_t), uint8_t power){
        double below_level_moment = 0.0;
        std::pair<uint32_t, double>* ptr_level_k;

        // For level l (0...l-1)
        ptr_level_k = filter.get_elements_at_level_k(m_level_count-1);
        for (int i=0; i < filter.get_storage_condition_at_level_k(m_level_count -1); i++){
            below_level_moment += f(ptr_level_k[i].second, power);
            moment_for_each_level.insert(moment_for_each_level.begin(), below_level_moment);
        }

        // For other levels
        for (int i =m_level_count-2; i != -1; i-- ){
            std::cout << "\n----- Level "<<i<<" -----"<<std::endl;
            below_level_moment *=2;
            ptr_level_k = filter.get_elements_at_level_k(i);        // get current level's elements
            for (int j=0; j < filter.get_storage_condition_at_level_k(i); j++){
                double coeff = 1 - 2 * univmon::get_hash_bit(ptr_level_k[j].first, i+1);
                below_level_moment += coeff * f(ptr_level_k[j].second, power);
                std::cout << coeff <<' '<<f(ptr_level_k[j].second, power)<<std::endl;
            }
            moment_for_each_level.insert(moment_for_each_level.begin(), below_level_moment);
        }

        return below_level_moment;
    }

    void display_moment_for_each_level(){
        for (int i = 0; i < m_level_count; ++i) {
            std::cout << "Level "<<i<<"\'s moment: \t"<<moment_for_each_level[i]<<std::endl;
        }
        std::cout<<"The final result is: \t"<<moment_for_each_level[0]<<std::endl;
    }



};

#endif //UNIVMON_MINHEAP_FILTER_UNIVMON_HPP
