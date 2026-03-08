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
}

TEST(matrix_test, computes_inverse_correctly) {
    v_of_LAaG a (3, 3, {1, 2, 1, 2, 2, 3, -1, 1, -2});
    v_of_LAaG const ans (3, 3, {7, -5, -4, -1, 1, 1, -4, 3, 2});
    v_of_LAaG f = a.inverse();
    EXPECT_EQ(ans, f);
}