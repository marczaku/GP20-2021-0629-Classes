#include <string>
#include "gtest/gtest.h"
#include "vector3.hpp"

#define ALL_TESTS

using namespace class_library;
using namespace std;

void EXPECT_VECTOR3_EQ(const Vector3& vector3, float x, float y, float z){

    EXPECT_FLOAT_EQ(x, vector3.x);
    EXPECT_FLOAT_EQ(y, vector3.y);
    EXPECT_FLOAT_EQ(z, vector3.z);
}

#if defined ALL_TESTS || REMOVE_THIS_WHEN_YOU_HAVE_IMPLEMENTED_THE_CONSTRUCTORS
TEST(vector3, hello_this_is_a_test) {
    Vector3 vector3(2, 3, 5);
    EXPECT_VECTOR3_EQ(vector3, 2, 3, 5);
}
#endif

#if defined ALL_TESTS || REMOVE_THIS_WHEN_YOU_HAVE_IMPLEMENTED_THE_PLUS_OPERATOR
TEST(plus_operator, returns_the_sum_of_passed_values) {
    Vector3 a(1, 2, 3);
    Vector3 b(4, 5, 6);
    EXPECT_VECTOR3_EQ(a+b, 5, 7, 9);
}
TEST(plus_operator, returns_the_sum_of_passed_values_2) {
    Vector3 a(1, -2, 3);
    Vector3 b(-4, 5, -6);
    EXPECT_VECTOR3_EQ(a+b, -3, 3, -3);
}
TEST(plus_operator, does_not_affect_a_or_b) {
    Vector3 a(1, -2, 3);
    Vector3 b(-4, 5, -6);
    a+b;
    EXPECT_VECTOR3_EQ(a, 1, -2, 3);
    EXPECT_VECTOR3_EQ(b, -4, 5, -6);
}
#endif

#if defined ALL_TESTS || REMOVE_THIS_WHEN_YOU_HAVE_IMPLEMENTED_THE_SUBTRACT_OPERATOR
TEST(vector3, SubtractOperatorReturnsDifferenceOfPassedValues1) {
    Vector3 a(1, 2, 3);
    Vector3 b(4, 5, 6);
    EXPECT_VECTOR3_EQ(a-b, -3, -3, -3);
}
TEST(vector3, SubtractOperatorReturnsDifferenceOfPassedValues2) {
    Vector3 a(1, -2, 3);
    Vector3 b(-4, 5, -6);
    EXPECT_VECTOR3_EQ(a-b, 5, -7, 9);
}
TEST(vector3, SubtractOperatorDoesNotAffectAOrB) {
    Vector3 a(1, -2, 3);
    Vector3 b(-4, 5, -6);
    a-b;
    EXPECT_VECTOR3_EQ(a, 1, -2, 3);
    EXPECT_VECTOR3_EQ(b, -4, 5, -6);
}
#endif

#if defined ALL_TESTS || REMOVE_THIS_WHEN_YOU_HAVE_IMPLEMENTED_THE_DOT_OPERATOR
TEST(vector3, MultiplyOperatorReturnsDotProductOfPassedValues1) {
    Vector3 a(1, 2, 3);
    Vector3 b(4, 5, 6);
    EXPECT_FLOAT_EQ(a*b, 32);
}
TEST(vector3, MultiplyOperatorReturnsDotProductOfPassedValues2) {
    Vector3 a(1, -2, 3);
    Vector3 b(-4, 5, -6);
    EXPECT_FLOAT_EQ(a*b, -32);
}
TEST(vector3, MultiplyOperatorDoesNotAffectAOrB) {
    Vector3 a(1, -2, 3);
    Vector3 b(-4, 5, -6);
    a*b;
    EXPECT_VECTOR3_EQ(a, 1, -2, 3);
    EXPECT_VECTOR3_EQ(b, -4, 5, -6);
}
#endif

#if defined ALL_TESTS || REMOVE_THIS_WHEN_YOU_HAVE_IMPLEMENTED_THE_CROSS_OPERATOR
TEST(vector3, XorOperatorReturnsCrossProductOfPassedValues1) {
    Vector3 a(1, 2, 3);
    Vector3 b(4, 5, 6);
    EXPECT_VECTOR3_EQ(a^b, -3, 6, -3);
}
TEST(vector3, XorOperatorReturnsCrossProductOfPassedValues2) {
    Vector3 a(1, -2, 3);
    Vector3 b(-4, 5, -6);
    EXPECT_VECTOR3_EQ(a^b, -3, -6, -3);
}
TEST(vector3, XorOperatorDoesNotAffectAOrB) {
    Vector3 a(1, -2, 3);
    Vector3 b(-4, 5, -6);
    a^b;
    EXPECT_VECTOR3_EQ(a, 1, -2, 3);
    EXPECT_VECTOR3_EQ(b, -4, 5, -6);
}
#endif