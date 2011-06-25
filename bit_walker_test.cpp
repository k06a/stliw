#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <algorithm>
#include "bit_walker.h"

using stliw::bit_walker;

TEST(bit_walker, countBitsInAAAA)
{
    //
    // 0A       0A       0A       0A
    // 0   A    0   A    0   A    0   A
    // 00001010 00001010 00001010 00001010
    //
    
    char input[] = "\x0A\x0A\x0A\x0A";
    char * input_ptr = input;
    
    /*
    int a = std::count(bit_walker(input_ptr),
                       bit_walker(input_ptr+4), 1);

    EXPECT_EQ(4*2, a);
    */
}