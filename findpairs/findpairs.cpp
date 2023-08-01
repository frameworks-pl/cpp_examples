#include "../include/gtest/gtest.h"
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>


std::vector<std::pair<int, int>> findPairs(const std::vector<int>& sourceNumbers, const int expectedSum) {

	std::vector<std::pair<int, int>> result;

	std::vector<int> sourceNumbersSorted = sourceNumbers;
	std::sort(sourceNumbersSorted.begin(), sourceNumbersSorted.end(), 
		[](const int& a, const int& b) -> bool {
			return a < b;
		}
	);


	int forwardIdx = 0;
	int backwardIdx = (int)sourceNumbersSorted.size()-1;

	while (forwardIdx < sourceNumbersSorted.size() && backwardIdx >= 0 && forwardIdx != backwardIdx) {

		int currentSum = sourceNumbers[forwardIdx] + sourceNumbersSorted[backwardIdx];
		if (currentSum == expectedSum) {
			result.push_back(std::pair<int, int>(sourceNumbersSorted[forwardIdx], sourceNumbersSorted[backwardIdx]));
			forwardIdx++;
			backwardIdx--;
		} else {
			if (currentSum < expectedSum) { forwardIdx++; } else { backwardIdx--;}
		}
	
	}

	return result;

}

TEST(FindPairs, simpleCase) {

	const int EXPECTED_SUM = 8;
	std::vector<int> sourceNumbers{ 1, 1, 3, 4, 5, 6, 7 };
	std::vector<std::pair<int, int>> resultPairs = findPairs(sourceNumbers, EXPECTED_SUM);

	ASSERT_EQ(2, resultPairs.size());

	ASSERT_EQ(1, resultPairs[0].first);
	ASSERT_EQ(7, resultPairs[0].second);

	ASSERT_EQ(3, resultPairs[1].first);
	ASSERT_EQ(5, resultPairs[1].second);	
}

TEST(FindParis, simpleCase2) {

	const int EXPECTED_SUM = 8;
	std::vector<int> sourceNumbers{ 1, 2, 3, 4, 5, 7, 6 };
	std::vector<std::pair<int, int>> resultPairs = findPairs(sourceNumbers, EXPECTED_SUM);

	ASSERT_EQ(3, resultPairs.size());

	// ASSERT_EQ(1, resultPairs[0].first);
	// ASSERT_EQ(7, resultPairs[0].second);

	// ASSERT_EQ(3, resultPairs[1].first);
	// ASSERT_EQ(5, resultPairs[1].second);	
}

TEST(FindPairs, foursInTheMiddle) {
	const int EXPECTED_SUM = 8;
	std::vector<int> sourceNumbers{ 1, 1, 3, 4, 4, 4, 5, 6, 7 };
	std::vector<std::pair<int, int>> resultPairs = findPairs(sourceNumbers, EXPECTED_SUM);

	ASSERT_EQ(3, resultPairs.size());

	ASSERT_EQ(1, resultPairs[0].first);
	ASSERT_EQ(7, resultPairs[0].second);

	ASSERT_EQ(3, resultPairs[1].first);
	ASSERT_EQ(5, resultPairs[1].second);		
}

TEST(FindPairs, foursAtTheEnd) {

	const int EXPECTED_SUM = 8;
	std::vector<int> sourceNumbers{ 1, 1, 3, 4, 4, 4 };
	std::vector<std::pair<int, int>> resultPairs = findPairs(sourceNumbers, EXPECTED_SUM);

	ASSERT_EQ(1, resultPairs.size());
	
	ASSERT_EQ(4, resultPairs[0].first);
	ASSERT_EQ(4, resultPairs[0].second);			
}
