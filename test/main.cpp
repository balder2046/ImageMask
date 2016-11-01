//
// Created by 赵磊 on 2016/10/25.
//
#include <gtest/gtest.h>
#include "../src/MaskManager.h"

class  MaskManagerTest: public ::testing::Test {
    MaskManager *maskManager;
protected:
    virtual void TearDown() {
        if (maskManager != 0)
        {
            delete maskManager;
            maskManager = 0;
        }
    }

    virtual void SetUp() {
        maskManager = new MaskManager();
    }
};
TEST(MaskManagerTest,Circle)
{
}
