#include "pch.h"
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

class Rectangle {
    public:
        Rectangle(const std::vector<std::pair<int,int>>& _points) {
            this->points = _points;
        }
        
        std::vector<std::pair<int, int>> getSortedPts() {
            
            std::sort(points.begin(), points.end(), Rectangle::compareByXY);
            return points;
        }
        
        static bool compareByXY(const std::pair<int, int>& a, const std::pair<int, int>& b) {
            if (a.first != b.first) { return a.first < b.first; }
            
            return a.second < b.second;
        }
    
    protected:
        std::vector<std::pair<int, int>> points;

};

void buildRectangles(const std::vector<int>& pointsA, const std::vector<int>& pointsB, int xA, int xB, std::vector<Rectangle>& rectangles) {
   
    for (int i = 0; i < (int)pointsA.size()-1; i++) {
        for (int j = i+1; j < (int)pointsA.size(); j++) {     
      
          if (pointsA[i] == pointsB[i] &&
              pointsA[j] == pointsB[j]) {

              std::vector<std::pair<int, int>> pts;
              pts.push_back(std::pair<int, int>(xA, pointsA[i]));
              pts.push_back(std::pair<int, int>(xB, pointsB[i]));
              pts.push_back(std::pair<int, int>(xA, pointsA[j]));
              pts.push_back(std::pair<int, int>(xB, pointsB[j]));
              rectangles.push_back(Rectangle(pts));                
          }
        }

    }
}

std::vector<Rectangle> findRectangles(std::vector<std::pair<int, int>>& points) {

    std::vector<Rectangle> rectangles;
    std::sort(points.begin(), points.end(), Rectangle::compareByXY);
       
    //map of all points on given x
    std::map<int, std::vector<int>> xPoints;
    std::vector<int> keys;
    
    int i = 0;
    while (i < (int)points.size()) {
    
        std::vector<int> currYPoints;
        do {
            currYPoints.push_back(points[i].second);
            i++;        
        } while (i < (int)points.size() && points[i-1].first == points[i].first);
                
        xPoints.insert(std::map<int, std::vector<int>>::value_type(points[i-1].first, currYPoints));
        keys.push_back(points[i-1].first);             
    } 
   
    
    for (int j = 0; j < (int)keys.size()-1; j++) {
        for (int k = j+1; k < (int)keys.size(); k++) {
           buildRectangles(xPoints[keys[j]], xPoints[keys[k]], keys[j], keys[k], rectangles);
        }  
    }
    
    return rectangles;
} 





TEST(FindRectangles, ThreeRectanglesSortedInY) {

    std::vector<std::pair<int, int>> points = { std::pair<int, int>(2, 4), std::pair<int, int>(2, 2), std::pair<int, int>(4, 2), std::pair<int, int>(4, 4),
        std::pair<int, int>(6, 4), std::pair<int, int>(6, 2)};
        
    std::vector<Rectangle> rectangles = findRectangles(points);
    
    ASSERT_EQ(3, rectangles.size());
    std::vector<std::pair<int, int>> rect1 = rectangles[0].getSortedPts();
    std::vector<std::pair<int, int>> rect2 = rectangles[1].getSortedPts();
    std::vector<std::pair<int, int>> rect3 = rectangles[2].getSortedPts();
    
    ASSERT_TRUE((std::pair<int, int>(2,2) == rect1[0]));
    ASSERT_TRUE((std::pair<int, int>(2,4) == rect1[1]));
    ASSERT_TRUE((std::pair<int, int>(4,2) == rect1[2]));
    ASSERT_TRUE((std::pair<int, int>(4,4) == rect1[3]));
    
    
    ASSERT_TRUE((std::pair<int, int>(2,2) == rect2[0]));
    ASSERT_TRUE((std::pair<int, int>(2,4) == rect2[1]));
    ASSERT_TRUE((std::pair<int, int>(6,2) == rect2[2]));
    ASSERT_TRUE((std::pair<int, int>(6,4) == rect2[3]));
    
    ASSERT_TRUE((std::pair<int, int>(4,2) == rect3[0]));
    ASSERT_TRUE((std::pair<int, int>(4,4) == rect3[1]));
    ASSERT_TRUE((std::pair<int, int>(6,2) == rect3[2]));
    ASSERT_TRUE((std::pair<int, int>(6,4) == rect3[3]));        
    

}