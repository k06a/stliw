#include "gmock/gmock.h"
#include "gtest/gtest.h"

int main(int argc, char * argv[])
{
    ::testing::GTEST_FLAG(throw_on_failure) = true;
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}