#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <algorithm>
#include "bit_walker.h"

using stliw::bit_walker;

TEST(bit_walker, countBitsInABAB)
{
    //
    // 00001010 00001011 00001010 00001011
    //     * *      * **     * *      * **
    //
    
    char input[] = "\x0A\x0B\x0A\x0B";
    char * input_ptr = input;
    
    int a = std::count(bit_walker(input_ptr),
                       bit_walker(input_ptr+1), 1);

    EXPECT_EQ(2 + 3 + 2 + 3, a);
}