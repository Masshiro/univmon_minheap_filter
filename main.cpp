#include <iostream>
#include <fstream>

#include "xxhash32.h"
#include "MinheapFilter.hpp"

const std::string inputFileName = "../test.groundtruth";
const std::uint32_t TOP_K = 128;
const std::uint8_t LEVEL_NUM = 10;

int main() {
    std::cout << "Hello, World!" << std::endl;

    /*
     *  Test for basic functionality of Control_List
    */
    // Make sure the file can be properly opened
//    std::ifstream infs(inputFileName);
//    std::string srcIP;
//    double cardinality;
//    if (!infs){
//        std::cout<<"Something Wrong Happened When Opening the Files!"<<std::endl;
//        infs.close();
//    }
//    infs.clear();
//    infs.seekg(0);
//
//    // Configure the data structure
//    Control_List<uint32_t, double> minheapFilter(TOP_K, LEVEL_NUM);
//    uint32_t flowID;
//
//    // Start inserting
//    while(infs.good()){
//        infs >> srcIP >> cardinality;
//        XXHash32 hash32(1);
//        hash32.add(srcIP.c_str(), srcIP.length());
//        flowID = hash32.hash();
//
//        for (int k = 0; k < 10; k ++){
//            minheapFilter.insert_element_at_level_k(flowID, cardinality, k);
//        }
//    }
//    infs.close();
//
//    // Check the filter's content
//    std::cout << "Level 1: " << std::endl;
//    minheapFilter.print_list_at_level_k(1);
//    std::cout << "Level 6: " << std::endl;
//    minheapFilter.print_list_at_level_k(6);

    /*
     *  Test for bitset
     * */
    std::bitset<32> binstr;
    binstr = 255;
    std::cout << binstr << std::endl;
    std::cout << binstr[0] << std::endl;
    std::cout << binstr[1] << std::endl;

    /*
     *  Test for the functionality of minheapfilter to deduplicate
     * */
    Control_List<uint32_t, double> testFilter(10, 1);
    testFilter.insert_element_at_level_k(501, 1, 0);
    testFilter.insert_element_at_level_k(411, 2, 0);
    testFilter.insert_element_at_level_k(308, 3, 0);
    testFilter.insert_element_at_level_k(217, 8, 0);
//    testFilter.insert_element_at_level_k(103, 9, 0);
    std::cout << "Original: "<<std::endl;
    testFilter.print_list_at_level_k(0);
    testFilter.insert_element_at_level_k(217, 10, 0);
    std::cout << "The storage condition is: " << testFilter.get_storage_condition_at_level_k(0)<<std::endl;
    std::cout << "Inserted: "<<std::endl;
    testFilter.print_list_at_level_k(0);
    std::cout << "The storage condition is: " << testFilter.get_storage_condition_at_level_k(0)<<std::endl;


    return 0;
}
