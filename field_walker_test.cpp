#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <algorithm>
#include "field_walker.h"

TEST(field_walker, sort)
{
    //
    // 1,30    1,10
    // 2,20 => 2,20
    // 3,10    3,30
    //

    struct ABC
    {
        int a;
        short b;
    };
    
    ABC input[] = 
    {
        {1,30},
        {2,20},
        {3,10}
    };
    ABC * input_ptr = input;
    
    std::sort(field_walker(input_ptr, fieldof(ABC,b)),
              field_walker(input_ptr+3, fieldof(ABC,b)));

    EXPECT_EQ(1, input[0].a);
    EXPECT_EQ(2, input[1].a);
    EXPECT_EQ(3, input[2].a);
     
    EXPECT_EQ(10, input[0].b);
    EXPECT_EQ(20, input[1].b);
    EXPECT_EQ(30, input[2].b);
}