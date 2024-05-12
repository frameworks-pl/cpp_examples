#include "pch.h"
#include <string>
#include <vector>

/****************************************************
 * Find the biggest number of zeros between two
 * ones in binary representation of decimal number
 ****************************************************/

void intToBin(int N,std::vector<int>& bits ) {
    
    if ((N % 2) == 0) {
        bits.insert(bits.begin(), 0);
    } else {
        bits.insert(bits.begin(), 1);
    }
        
    N = N / 2;
    if (N > 0) {
        intToBin(N, bits);
    }
}

int solution(int N) {
    
    std::vector<int> bits;
    intToBin(N, bits);
    
    int maxGap = 0;
    int currGap = 0;
    int* pCurrGap = NULL;
    
    for (size_t i = 0; i < bits.size(); i++) {
        
        if (bits[i] == 1) {
            if (pCurrGap == NULL) {
                pCurrGap = &currGap;
            } else {
                if (*pCurrGap > maxGap) {
                    maxGap = *pCurrGap;
                }
                currGap = 0;
            }
        } else if (bits[i] == 0) {
            if (pCurrGap) {
                (*pCurrGap)++;
            }
        }
        
    }
    
    return maxGap;
    
}

TEST(BinaryGap, simpleTest) {
    ASSERT_EQ((int)1, solution(5));
}

TEST(BinaryGap, differentNumbers) {
    ASSERT_EQ(0, solution(6)); //n=6=110_2
    ASSERT_EQ(2, solution(328)); //n=328=101001000_2
    ASSERT_EQ(3, solution(1162)); //n=1162=10010001010_2
    ASSERT_EQ(2, solution(51712)); //n=51712=110010100000000_2
    ASSERT_EQ(9, solution(66561)); //n=66561=10000010000000001_2
    ASSERT_EQ(20, solution(6291457)); //n=6291457=11000000000000000000001_2
    ASSERT_EQ(25, solution(805306373)); //n=805306373=110000000000000000000000000101_2
    ASSERT_EQ(28, solution(1610612737)); //n=805306373=1100000000000000000000000000001_2
}

