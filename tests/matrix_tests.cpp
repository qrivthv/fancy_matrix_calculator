#include <gtest/gtest.h>
#include "../include/victim_of_LAaG.h"

TEST(matrix_test, computes_rref_correctly) {
    v_of_LAaG a (3, 4, {1, 2, -1, -4, 2, 3, -1, -11, -2, 0, -3, 22});
    v_of_LAaG const ans (3, 4, {1, 0, 0, -8, 0, 1, 0, 1, 0, 0, 1, -2});
    v_of_LAaG f = a.rref();
    EXPECT_EQ(ans, f);
    a = v_of_LAaG(3, 3, {8, 8, -8, -8,-12, 16, -4, -8, 12});
    EXPECT_EQ(a.rref(), v_of_LAaG(3, 3, {1, 0, 1, 0, 1, -2, 0, 0, 0}));
    a = v_of_LAaG(3, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0});
    EXPECT_EQ(a.rref(), a); //that must be zero-matrix, i'm to lazy, to define it manually one more time
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
    a = v_of_LAaG(3, 4, {1, 2, -1, -4, 2, 3, -1, -11, -2, 0, -3, 22});
    EXPECT_THROW(d = a.det(), std::runtime_error);
}

TEST(matrix_test, computes_inverse_correctly) {
    v_of_LAaG a (3, 3, {1, 2, 1, 2, 2, 3, -1, 1, -2});
    v_of_LAaG const ans (3, 3, {7, -5, -4, -1, 1, 1, -4, 3, 2});
    v_of_LAaG f = a.inverse();
    EXPECT_EQ(ans, f);
}

TEST (matrix_test, arithmetic_operations) {
    v_of_LAaG a, b, wrong_b;
    // +
    a = v_of_LAaG(4, 3, {1, 2, -1, -4, 2, 3, -1, -11, -2, 0, -3, 22});
    b = v_of_LAaG(4, 3, {1, 2, -1, -4, 2, 3, -1, -11, -2, 0, -3, 22});
    wrong_b = v_of_LAaG(3, 4, {{1, 2, -1, 5, 2, 3, -1, -11, -2, 0, -3, 22}});
    b = b*-1;
    EXPECT_EQ(a+b, v_of_LAaG(4, 3, {0, 0,0,0,0,0,0,0,0,0,0,0}));
    EXPECT_THROW(a+wrong_b, std::runtime_error);
    // -
    b = v_of_LAaG(4, 3, {-1, 2, -1, 4, 2, 3, 1, -11, -2, 0, -3, 22});
    EXPECT_EQ(a - b, v_of_LAaG(4, 3, {2, 0, 0, -8, 0, 0, -2, 0, 0, 0, 0, 0}));
    EXPECT_THROW(a-wrong_b, std::runtime_error);
    // * (scalar)
    EXPECT_EQ(a*0, v_of_LAaG(4, 3, {0, 0,0,0,0,0,0,0,0,0,0,0}));
    EXPECT_EQ(0*a, v_of_LAaG(4, 3, {0, 0,0,0,0,0,0,0,0,0,0,0}));
    EXPECT_EQ(1*a, a);
    // *
    a = v_of_LAaG(4, 3, {1, 2, -1, -4, 2, 3, -1, -11, -2, 0, -3, 22});
    b = v_of_LAaG(3, 3, {1, 2, -1, -4, 2, 3, -1, -11, -2});
    wrong_b = v_of_LAaG(4, 3, {{1, 2, -1, 5, 2, 3, -1, -11, -2, 0, -3, 22}});
    EXPECT_THROW(a*wrong_b, std::runtime_error);
    EXPECT_EQ(a*b, v_of_LAaG(4, 3, {-6, 17, 7, -15, -37, 4, 45, -2, -28, -10, -248, -53}));
    EXPECT_EQ(a*Identity(3), v_of_LAaG(4, 3, {1, 2, -1, -4, 2, 3, -1, -11, -2, 0, -3, 22}));
    swap(a, b);
    EXPECT_EQ(b*a, v_of_LAaG(4, 3, {-6, 17, 7, -15, -37, 4, 45, -2, -28, -10, -248, -53}));

}

TEST(matrix_test, computes_transpose_correstly) {
    v_of_LAaG a (3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    EXPECT_EQ(a.transpose(), v_of_LAaG(3, 3, {1, 4, 7, 2, 5, 8, 3, 6, 9}));
    a = v_of_LAaG(3, 2, {1, 2, 3, 4, 5, 6});
    EXPECT_EQ(a.transpose(), v_of_LAaG(2, 3, {1, 3, 5, 2, 4, 6}));
}

TEST(matrix_test, computes_trace_correctly) {
    v_of_LAaG a (3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    EXPECT_EQ(a.trace(), 15);
    a = v_of_LAaG(3, 2, {1, 2, 3, 4, 5, 6});
    EXPECT_EQ(a.trace(), 5);
}

TEST(matrix_test, rank_calculation) {
    v_of_LAaG a (3, 4, {1, 2, -1, -4, 2, 3, -1, -11, -2, 0, -3, 22});
    v_of_LAaG const ans (3, 4, {1, 0, 0, -8, 0, 1, 0, 1, 0, 0, 1, -2});
    v_of_LAaG f = a.rref();
    EXPECT_EQ(a.rank(), 3);
    a = v_of_LAaG(3, 3, {8, 8, -8, -8,-12, 16, -4, -8, 12});
    EXPECT_EQ(a.rank(), 2);
    a = v_of_LAaG(3, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0});
    EXPECT_EQ(a.rank(), 0);
}