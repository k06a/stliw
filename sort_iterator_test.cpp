#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <algorithm>
#include "sort_iterator.h"

using stliw::sorter;

TEST(sort_iterator, sortArray)
{
    int input[5] = { 5,3,2,1,4 };
    int output[5] = { 0,0,0,0,0 };
    int * input_ptr = (int *)input;
    int * output_ptr = (int *)output;

    std::copy(sorter(input_ptr,input_ptr+5),
              sorter(input_ptr+5,input_ptr+5),
              output_ptr);

    EXPECT_EQ(1, output[0]);
    EXPECT_EQ(2, output[1]);
    EXPECT_EQ(3, output[2]);
    EXPECT_EQ(4, output[3]);
    EXPECT_EQ(5, output[4]);

    /*
    // auto == stliw::sort_iterator<std::random_access_iterator_tag,int*,int>
    for (auto it = sorter(input_ptr,input_ptr+5);
         it != input_ptr+5; ++it)
    {
        output[]
    }
    */
}