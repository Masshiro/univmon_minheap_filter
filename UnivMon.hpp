//
// Created by masshiro on 1/18/22.
//

#ifndef UNIVMON_MINHEAP_FILTER_UNIVMON_HPP
#define UNIVMON_MINHEAP_FILTER_UNIVMON_HPP

class UnivMonSketch{
private:
    Control_List<uint32_t, double> filter;
    uint32_t m_level_count;
    uint32_t m_filter_size;

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
            std::cout << "---------- Level "<<i<<" ----------"<<std::endl;
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
};

#endif //UNIVMON_MINHEAP_FILTER_UNIVMON_HPP
