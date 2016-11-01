//
// Created by 赵磊 on 2016/10/27.
//
#include <gtest/gtest.h>
#include "MathUtil.h"

TEST(MathUtilCatmulRomTest, FloatTest) {
    EXPECT_EQ(1.0f, CatmullRom(0.0f, 1.0f, 2.0f, 3.0f, 0.0f));
    EXPECT_EQ(2.0f, CatmullRom(0.0f, 1.0f, 2.0f, 3.0f, 1.0f));
    EXPECT_EQ(1.5f, CatmullRom(0.0f, 1.0f, 2.0f, 3.0f, 0.5f));
}
