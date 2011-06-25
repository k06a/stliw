#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <algorithm>
#include "field_walker.h"

using stliw::field_walker;

TEST(field_walker, findStructByField)
{
    //
    // What to find:        [200]           "puper"
    //
    // {100,"hello"}
    // {200,"super"} => {200,"super"}
    // {300,"puper"}                  => {300,"puper"}
    //

    struct ABC
    {
        int value;
        std::string str;
    };
    
    ABC input[] = 
    {
        {100,"hello"},
        {200,"super"},
        {300,"puper"}
    };
    ABC * input_ptr = input;
    
    int a = std::find(field_walker(input_ptr, fieldof(ABC,value)),
                      field_walker(input_ptr+3, fieldof(ABC,value)),
                      200) - input_ptr;

    int b = std::find(field_walker(input_ptr, fieldof(ABC,str)),
                      field_walker(input_ptr+3, fieldof(ABC,str)),
                      "puper") - input_ptr;

    EXPECT_EQ(1, a);
    EXPECT_EQ(2, b);
}

TEST(field_walker, sortStdPairs)
{
    //
    // (1,"cde")    (1,"abc")
    // (2,"bcd") => (2,"bcd")
    // (3,"abc")    (3,"cde")
    //

    typedef std::pair<int,std::string> TPair;

    TPair input[] = 
    {
        std::make_pair(1,"cde"),
        std::make_pair(2,"bcd"),
        std::make_pair(3,"abc")
    };
    TPair * input_ptr = input;
    
    std::sort(field_walker(input_ptr, fieldof(TPair,second)),
              field_walker(input_ptr+3, fieldof(TPair,second)));

    EXPECT_EQ(1, input[0].first);
    EXPECT_EQ(2, input[1].first);
    EXPECT_EQ(3, input[2].first);
     
    EXPECT_STREQ("abc", input[0].second.c_str());
    EXPECT_STREQ("bcd", input[1].second.c_str());
    EXPECT_STREQ("cde", input[2].second.c_str());
}

TEST(field_walker, sortFieldsInStruct)
{
    //
    // (1,30)    (1,10)
    // (2,20) => (2,20)
    // (3,10)    (3,30)
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