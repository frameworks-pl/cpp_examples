#include <..\include\gtest\gtest.h> 
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <math.h>

int solution(std::string &S, std::vector<int> &X, std::vector<int> &Y) {
    // write your code in C++14 (g++ 6.2.0)

    std::map<double, std::map<char, int>> radiusToLetter;
    
    for (size_t i = 0; i < S.size(); i++) {
    
      //calculate radius of the given point assuming that center of circle is in 0,0
      //TODO: increase precision ?
      double r =  ((int)(sqrt(X[i]*X[i] + Y[i]*Y[i]) * 100 + .5) / 100.0);  
        
      //build map of radius to map of letter->number of times found
      if (radiusToLetter.find(r) == radiusToLetter.end()) {
        std::map<char, int> letterToCount;
        letterToCount.insert(std::map<char, int>::value_type(S[i], 1));
        radiusToLetter.insert(std::map<double, std::map<char,int>>::value_type(r, letterToCount));
      } else {
        std::map<char, int>::iterator it = radiusToLetter[r].find(S[i]);
        if (radiusToLetter[r].end() == it) {
            radiusToLetter[r].insert(std::map<char, int>::value_type(S[i], 1));
        } else {
            it->second++;
        }              
      }             
    }
    
    int letterCounter = 0;
    std::map<char, int> alreadyIn;
    std::map<double, std::map<char, int>>::iterator it1;

    //map has radiuses sorted already so we go from smallest 
    for (it1 = radiusToLetter.begin(); it1 != radiusToLetter.end(); it1++) {      

        //if for current radius any letter appears more than once or the same letter is already in
        //we cannot add points from this radious and also cannot continue furter;
        std::map<char, int>::iterator it2;
        bool canAdd = true;
        for (it2 = it1->second.begin(); it2 != it1->second.end(); it2++) {
          if (it2->second > 1 || alreadyIn.find(it2->first) != alreadyIn.end()) {
           return letterCounter;
          }
        }

        // if we are here, no letter did repeat for the radius and all of them appeared once, we can add all of them and continue        
        for (it2 = it1->second.begin(); it2 != it1->second.end(); it2++) {
          if (alreadyIn.find(it2->first) == alreadyIn.end()) {
            letterCounter++;
            alreadyIn.insert(std::map<char, int>::value_type(it2->first, 1));
          }
        }
    } 
    
    return letterCounter;
}

TEST(PointsInCircle, FivePointsSameLocation) {

  std::vector<int> X { -1, -1, -1, -1, -1};
  std::vector<int> Y { -1, -1, -1, -1, -1};
  std::string S = "AAAAA";

  ASSERT_EQ(0, solution(S, X, Y));

}

TEST(PointsInCircle, OneGoodPointBehindTwoBad) {

  std::vector<int> X { 2, -2, 1 };
  std::vector<int> Y { 2, -2, 1 };
  std::string S = "AAC";

  ASSERT_EQ(1, solution(S, X, Y));

}
