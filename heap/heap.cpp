#include "pch.h"
#include <vector>
#include <algorithm>


int findMax(std::vector<int>& unsortedNumbers) {
  
  std::make_heap(unsortedNumbers.begin(), unsortedNumbers.end());
  return unsortedNumbers[0];  
    
};

int lessThan(int a, int b) {
    return a < b;
}

int greaterThan(int a, int b) {
    return a >= b;
}

TEST(GenericSuite, findMaxTest) {

    std::vector<int> unsortedNumbers = { 20, 10, 15, 23 };
    int result = findMax(unsortedNumbers);
    
    ASSERT_EQ(23, result);
    
    std::sort_heap(unsortedNumbers.begin(), unsortedNumbers.end(), lessThan);
    ASSERT_EQ(10, unsortedNumbers[0]);
    
    std::sort_heap(unsortedNumbers.begin(), unsortedNumbers.end(), greaterThan);
    ASSERT_EQ(23, unsortedNumbers[0]); 
 

}