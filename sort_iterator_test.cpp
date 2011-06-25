#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <algorithm>
#include "sort_iterator.h"

using stliw::sorter;

TEST(sort_iterator, ascSortArray)
{
    //
    // A:{ 5,3,2,1,4 } => A:{ 5,3,2,1,4 }
    // B:{ 0,0,0,0,0 } => B:{ 1,2,3,4,5 }
    //

    int input[5]  = { 5,3,2,1,4 };
    int output[5] = { 0,0,0,0,0 };
    int * input_ptr  = (int *)input;
    int * output_ptr = (int *)output;

    std::copy(sorter(input_ptr,input_ptr+5),
              sorter(input_ptr+5),
              output_ptr);

    // Expect input
    EXPECT_EQ(5, input[0]);
    EXPECT_EQ(3, input[1]);
    EXPECT_EQ(2, input[2]);
    EXPECT_EQ(1, input[3]);
    EXPECT_EQ(4, input[4]);

    // Expect output
    EXPECT_EQ(1, output[0]);
    EXPECT_EQ(2, output[1]);
    EXPECT_EQ(3, output[2]);
    EXPECT_EQ(4, output[3]);
    EXPECT_EQ(5, output[4]);
}

TEST(sort_iterator, ascSortArrayWithDuplicates)
{
    //
    // A:{ 5,2,1,2,2 } => A:{ 5,2,1,2,2 }
    // B:{ 0,0,0,0,0 } => B:{ 1,2,2,2,5 }
    //

    int input[5]  = { 5,2,1,2,2 };
    int output[5] = { 0,0,0,0,0 };
    int * input_ptr  = (int *)input;
    int * output_ptr = (int *)output;

    std::copy(sorter(input_ptr,input_ptr+5),
              sorter(input_ptr+5),
              output_ptr);

    // Expect input
    EXPECT_EQ(5, input[0]);
    EXPECT_EQ(2, input[1]);
    EXPECT_EQ(1, input[2]);
    EXPECT_EQ(2, input[3]);
    EXPECT_EQ(2, input[4]);

    // Expect output
    EXPECT_EQ(1, output[0]);
    EXPECT_EQ(2, output[1]);
    EXPECT_EQ(2, output[2]);
    EXPECT_EQ(2, output[3]);
    EXPECT_EQ(5, output[4]);
}

TEST(sort_iterator, descSortArray)
{
    //
    // A:{ 5,3,2,1,4 } => A:{ 5,3,2,1,4 }
    // B:{ 0,0,0,0,0 } => B:{ 5,4,3,2,1 }
    //

    int input[5]  = { 5,3,2,1,4 };
    int output[5] = { 0,0,0,0,0 };
    int * input_ptr  = (int *)input;
    int * output_ptr = (int *)output;

    std::copy(sorter<stliw::Descending>(input_ptr,input_ptr+5),
              sorter<stliw::Descending>(input_ptr+5),
              output_ptr);

    // Expect input
    EXPECT_EQ(5, input[0]);
    EXPECT_EQ(3, input[1]);
    EXPECT_EQ(2, input[2]);
    EXPECT_EQ(1, input[3]);
    EXPECT_EQ(4, input[4]);

    // Expect output
    EXPECT_EQ(5, output[0]);
    EXPECT_EQ(4, output[1]);
    EXPECT_EQ(3, output[2]);
    EXPECT_EQ(2, output[3]);
    EXPECT_EQ(1, output[4]);
}

TEST(sort_iterator, descSortArrayWithDuplicates)
{
    //
    // A:{ 5,2,1,2,2 } => A:{ 5,2,1,2,2 }
    // B:{ 0,0,0,0,0 } => B:{ 5,2,2,2,1 }
    //

    int input[5]  = { 5,2,1,2,2 };
    int output[5] = { 0,0,0,0,0 };
    int * input_ptr  = (int *)input;
    int * output_ptr = (int *)output;

    std::copy(sorter<stliw::Descending>(input_ptr,input_ptr+5),
              sorter<stliw::Descending>(input_ptr+5),
              output_ptr);

    // Expect input
    EXPECT_EQ(5, input[0]);
    EXPECT_EQ(2, input[1]);
    EXPECT_EQ(1, input[2]);
    EXPECT_EQ(2, input[3]);
    EXPECT_EQ(2, input[4]);

    // Expect output
    EXPECT_EQ(5, output[0]);
    EXPECT_EQ(2, output[1]);
    EXPECT_EQ(2, output[2]);
    EXPECT_EQ(2, output[3]);
    EXPECT_EQ(1, output[4]);
}