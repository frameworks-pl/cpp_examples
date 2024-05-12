#include "pch.h"
#include <string>
#include <vector>
#include <queue>

class SimpleClass {

    int value2;
    int value1;

    public:
        SimpleClass(int _value1) : value1(_value1), value2(_value1+1) {

        }

        std::string getString() {
            return std::to_string(value1) + " " + std::to_string(value2);
        }

};


TEST(ClassInitialization, membersInitialization) {

    SimpleClass sc(5);
    ASSERT_EQ("5 6", sc.getString());

}