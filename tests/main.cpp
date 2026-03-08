#include <gtest/gtest.h>
#include "../include/victim_of_LAaG.h"

TEST(matrix_test, computes_rref_correctly) {
    v_of_LAaG a (3, 4, {1, 2, -1, -4, 2, 3, -1, -11, -2, 0, -3, 22});
    v_of_LAaG const ans (3, 4, {1, 0, 0, -8, 0, 1, 0, 1, 0, 0, 1, -2});
    v_of_LAaG f = a.rref();
    EXPECT_EQ(ans, f);
}

TEST(matrix_test, computes_det_correctly) {
    v_of_LAaG a (3, 3, {1, 2, -1, -4, 2, 3, -1, -11, -2});
    double ans = -39.0;
    double d = a.det();
    EXPECT_EQ(ans, d);
    a = v_of_LAaG(3, 3, {1, 2, -1, -4, 2, 3, 1, 2, -1});
    d = a.det();
    ans = 0;
    EXPECT_EQ(ans, d);
}

TEST(matrix_test, throws_det_correctly) {
    v_of_LAaG a (3, 4, {1, 2, -1, -4, 2, 3, -1, -11, -2, 0, -3, 22});
    EXPECT_THROW(double d = a.det(), std::runtime_error);
}

TEST(matrix_test, computes_inverse_correctly) {
    v_of_LAaG a (3, 3, {1, 2, 1, 2, 2, 3, -1, 1, -2});
    v_of_LAaG const ans (3, 3, {7, -5, -4, -1, 1, 1, -4, 3, 2});
    v_of_LAaG f = a.inverse();
    EXPECT_EQ(ans, f);
}

TEST (matrix_test, arithmetic_operations) {
    v_of_LAaG a, b, wrong_b;



    a = v_of_LAaG(4, 3, {1, 2, -1, -4, 2, 3, -1, -11, -2, 0, -3, 22});
    b = v_of_LAaG(3, 3, {1, 2, -1, -4, 2, 3, -1, -11, -2});
    wrong_b = v_of_LAaG(4, 3, {{1, 2, -1, 5, 2, 3, -1, -11, -2, 0, -3, 22}});
    EXPECT_THROW(a*wrong_b, std::runtime_error);
    EXPECT_EQ(a*b, v_of_LAaG(4, 3, {-6, 17, 7, -15, -37, 4, 45, -2, -28, -10, -248, -53}));
    EXPECT_EQ(a*Identity(3), v_of_LAaG(4, 3, {1, 2, -1, -4, 2, 3, -1, -11, -2, 0, -3, 22}));
}