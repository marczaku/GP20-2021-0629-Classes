#include <string>
#include "vector3_test.hpp"

using namespace class_library;
using namespace std;

vector3_test::vector3_test() {
}

vector3_test::~vector3_test() {
};

void vector3_test::SetUp() {
};

void vector3_test::TearDown() {
}

void EXPECT_VECTOR3_EQ(const Vector3& vector3, float x, float y, float z){

    EXPECT_FLOAT_EQ(x, vector3.x);
    EXPECT_FLOAT_EQ(y, vector3.y);
    EXPECT_FLOAT_EQ(z, vector3.z);
}

TEST_F(vector3_test, ConstructorShouldAssignPassedValues) {
    Vector3 vector3(2, 3, 5);
    EXPECT_VECTOR3_EQ(vector3, 2, 3, 5);
}

#ifdef REMOVE_THIS_WHEN_YOU_HAVE_IMPLEMENTED_THE_PLUS_OPERATOR
TEST_F(vector3_test, PlusOperatorReturnsSumOfPassedValues1) {
    Vector3 a(1, 2, 3);
    Vector3 b(4, 5, 6);
    EXPECT_VECTOR3_EQ(a+b, 5, 7, 9);
}
TEST_F(vector3_test, PlusOperatorReturnsSumOfPassedValues2) {
    Vector3 a(1, -2, 3);
    Vector3 b(-4, 5, -6);
    EXPECT_VECTOR3_EQ(a+b, -3, 3, -3);
}
TEST_F(vector3_test, PlusOperatorDoesNotAffectAOrB) {
    Vector3 a(1, -2, 3);
    Vector3 b(-4, 5, -6);
    a+b;
    EXPECT_VECTOR3_EQ(a, 1, -2, 3);
    EXPECT_VECTOR3_EQ(b, -4, 5, -6);
}
#endif

#ifdef REMOVE_THIS_WHEN_YOU_HAVE_IMPLEMENTED_THE_SUBTRACT_OPERATOR
TEST_F(vector3_test, SubtractOperatorReturnsDifferenceOfPassedValues1) {
    Vector3 a(1, 2, 3);
    Vector3 b(4, 5, 6);
    EXPECT_VECTOR3_EQ(a-b, -3, -3, -3);
}
TEST_F(vector3_test, SubtractOperatorReturnsDifferenceOfPassedValues2) {
    Vector3 a(1, -2, 3);
    Vector3 b(-4, 5, -6);
    EXPECT_VECTOR3_EQ(a-b, 5, -7, 9);
}
TEST_F(vector3_test, SubtractOperatorDoesNotAffectAOrB) {
    Vector3 a(1, -2, 3);
    Vector3 b(-4, 5, -6);
    a-b;
    EXPECT_VECTOR3_EQ(a, 1, -2, 3);
    EXPECT_VECTOR3_EQ(b, -4, 5, -6);
}
#endif

#ifdef REMOVE_THIS_WHEN_YOU_HAVE_IMPLEMENTED_THE_DOT_OPERATOR
TEST_F(vector3_test, MultiplyOperatorReturnsDotProductOfPassedValues1) {
    Vector3 a(1, 2, 3);
    Vector3 b(4, 5, 6);
    EXPECT_FLOAT_EQ(a*b, 32);
}
TEST_F(vector3_test, MultiplyOperatorReturnsDotProductOfPassedValues2) {
    Vector3 a(1, -2, 3);
    Vector3 b(-4, 5, -6);
    EXPECT_FLOAT_EQ(a*b, -32);
}
TEST_F(vector3_test, MultiplyOperatorDoesNotAffectAOrB) {
    Vector3 a(1, -2, 3);
    Vector3 b(-4, 5, -6);
    a*b;
    EXPECT_VECTOR3_EQ(a, 1, -2, 3);
    EXPECT_VECTOR3_EQ(b, -4, 5, -6);
}
#endif

#ifdef REMOVE_THIS_WHEN_YOU_HAVE_IMPLEMENTED_THE_CROSS_OPERATOR
TEST_F(vector3_test, XorOperatorReturnsCrossProductOfPassedValues1) {
    Vector3 a(1, 2, 3);
    Vector3 b(4, 5, 6);
    EXPECT_VECTOR3_EQ(a^b, -3, 6, -3);
}
TEST_F(vector3_test, XorOperatorReturnsCrossProductOfPassedValues2) {
    Vector3 a(1, -2, 3);
    Vector3 b(-4, 5, -6);
    EXPECT_VECTOR3_EQ(a^b, -3, -6, -3);
}
TEST_F(vector3_test, XorOperatorDoesNotAffectAOrB) {
    Vector3 a(1, -2, 3);
    Vector3 b(-4, 5, -6);
    a^b;
    EXPECT_VECTOR3_EQ(a, 1, -2, 3);
    EXPECT_VECTOR3_EQ(b, -4, 5, -6);
}
#endif