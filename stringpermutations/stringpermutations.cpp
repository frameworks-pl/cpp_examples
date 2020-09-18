#include <../include/gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>


bool sortString(const std::string& stringA, const std::string& stringB) {
    return stringA < stringB;
}

std::vector<std::string> mixStrings(std::string permutationsString, std::string letter) {
    
    std::vector<std::string> permutations;
    size_t permutationsStringLen = permutationsString.size(); 
    for (int i = 0; i <= permutationsStringLen; i++) {
        std::string permutation = permutationsString;         
        permutations.push_back(permutation.insert(i, letter));
    }
    
    return permutations;
    
}

void stringPermutations(std::string inputString, std::vector<std::string>& permutations) {

    

    if (inputString.size() == 1) {
        permutations.push_back(inputString);
    }
    else if (inputString.size() == 2) {
        permutations = mixStrings(inputString.substr(0, 1), inputString.substr(1,1));        
    } else {
        stringPermutations(inputString.substr(0, inputString.size()-1), permutations);
        
        std::vector<std::string> outputPermutations;        
        std::vector<std::string>::iterator it;
        for (it = permutations.begin(); it < permutations.end(); it++) {
          std::vector<std::string> currPermutations = mixStrings(*it, inputString.substr(inputString.size()-1, 1));        
          outputPermutations.insert(outputPermutations.end(),  currPermutations.begin(), currPermutations.end());             
        }
        permutations = outputPermutations;     
    } 
    
}


TEST(StringPermutations, TwoLetters) {

    std::string inputString = "ab";
    
    std::vector<std::string> permutations;
    stringPermutations(inputString, permutations);
    ASSERT_EQ(2, permutations.size());
    
    std::sort(permutations.begin(), permutations.end(), sortString);
    ASSERT_EQ("ab", permutations[0]);
    ASSERT_EQ("ba", permutations[1]);
        
}

TEST(StringPermutations, ThreeLetters) {

    std::string inputString = "abc";
    
    std::vector<std::string> permutations;
    stringPermutations(inputString, permutations);
    ASSERT_EQ(6, permutations.size());
    
    std::sort(permutations.begin(), permutations.end(), sortString);
    ASSERT_EQ("abc", permutations[0]);
    ASSERT_EQ("acb", permutations[1]);
    ASSERT_EQ("bac", permutations[2]);
    ASSERT_EQ("bca", permutations[3]);
    ASSERT_EQ("cab", permutations[4]);
    ASSERT_EQ("cba", permutations[5]);
    
}