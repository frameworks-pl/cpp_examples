#include <../include/gtest/gtest.h>
#include <iostream>

#define ENUM_VALUES(PREFIX) PREFIX##A, PREFIX##B, PREFIX##C 
#define ENUM_CLASS_MAKER(NAME) enum class NAME { ENUM_VALUES() };
ENUM_CLASS_MAKER(MyEnum)
std::vector<MyEnum> MyEnumAllValues { ENUM_VALUES(MyEnum::) };

void displayAllMyEnumValues() {
	std::vector<MyEnum>::const_iterator it;
	for (it = MyEnumAllValues.begin(); it < MyEnumAllValues.end(); it++) {
		std::cerr << (int)*it;
	}	
}


TEST(EnumTest, simpleTest) {

	ASSERT_EQ(2, (int)MyEnumAllValues[2]);
	
}