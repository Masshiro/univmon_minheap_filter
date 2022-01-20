#include <iostream>
#include <fstream>
#include <limits>

#include "xxhash32.h"
#include "MinheapFilter.hpp"
#include "UnivMon.hpp"

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
//    Control_List<uint32_t, double> testFilter(10, 1);
//    testFilter.insert_element_at_level_k(501, 1, 0);
//    testFilter.insert_element_at_level_k(411, 2, 0);
//    testFilter.insert_element_at_level_k(308, 3, 0);
//    testFilter.insert_element_at_level_k(217, 8, 0);
////    testFilter.insert_element_at_level_k(103, 9, 0);
//    std::cout << "Original: "<<std::endl;
//    testFilter.print_list_at_level_k(0);
//    testFilter.insert_element_at_level_k(217, 10, 0);
//    std::cout << "The storage condition is: " << testFilter.get_storage_condition_at_level_k(0)<<std::endl;
//    std::cout << "Inserted: "<<std::endl;
//    testFilter.print_list_at_level_k(0);
//    std::cout << "The storage condition is: " << testFilter.get_storage_condition_at_level_k(0)<<std::endl;

    /*
     *  Test for the basic functionality of UnivMon structure.
     * */
    UnivMonSketch univmon(2, 5);
    univmon.update_filter_at_level_k(501, 1, 0);
    univmon.update_filter_at_level_k(321, 3, 0);
    univmon.update_filter_at_level_k(892, 6, 0);
    univmon.update_filter_at_level_k(930, 12, 0);
    univmon.update_filter_at_level_k(892, 9, 0);

    univmon.update_filter_at_level_k(2129, 31, 1);
    univmon.update_filter_at_level_k(3111, 43, 1);
    univmon.update_filter_at_level_k(4520, 23, 1);
    univmon.update_filter_at_level_k(6789, 38, 1);
    univmon.update_filter_at_level_k(8913, 51, 1);

    univmon.display_filter();

    univmon.display_filter_at_level_k(0);

    /*
     *  Test for the for loop
     * */
    for (int i = 3; i!= -1; i--){
        std::cout << "i = " << i <<std::endl;
    }

    /*
     * Test for whether bool type can be seen as number of 1 or 0
     * */
    bool one_or_zero = 1;
    std::cout << "BOOL test: "<< one_or_zero<<std::endl;
    std::cout << "Can be calculated?: " << 10-one_or_zero << std::endl;

    /*
     *  Test for the limitation of the basic data types
     * */
//    std::cout<<"The upper limit of type uint8_t: " << int(std::numeric_limits<uint8_t>::max()) <<std::endl;
//    std::cout<<"The lower limit of type uint8_t: " << int(lower_bound) <<std::endl;
//    std::cout<<"The upper limit of type char: " << int(std::numeric_limits<char>::max()) <<std::endl;
//    std::cout<<"The lower limit of type char: " << int(std::numeric_limits<char>::lowest()) <<std::endl;
//    std::cout<<"The upper limit of type double: " << double(std::numeric_limits<double>::max()) <<std::endl;
//    std::cout<<"The lower limit of type double: " << double(std::numeric_limits<double>::lowest()) <<std::endl;
//    std::cout<<"The upper limit of type float: " << float(std::numeric_limits<float>::max()) <<std::endl;
//    std::cout<<"The lower limit of type float: " << float(std::numeric_limits<float>::lowest()) <<std::endl;



    return 0;
}
