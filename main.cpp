#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

#include "bit_walker.h"
#include "field_walker.h"

void bit_walker_input_test()
{
    char input[] = "ab";
    char output[] = "1234567812345678";

    char * input_ptr = input;
    char * output_ptr = output;

    //std::copy(bit_walker<char>(input_ptr),
    //          bit_walker<char>(input_ptr+2),
    //          output_ptr);

    //if (output != "")
    //    std::cout << "Error in bit_walker_input_test()" << std::endl;
}

void field_walker_input_test()
{
    struct ABC {
        int a;
        short b;
        char c;
    } input[] = 
    {
        {1,5,'e'},
        {2,4,'a'},
        {3,3,'c'},
        {4,2,'b'},
        {5,1,'d'}
    };

    ABC * input_ptr = input;
    
    std::sort(field_walker(input_ptr, fieldof(ABC,b)),
              field_walker(input_ptr+2, fieldof(ABC,b)));

    for (int i = 0; i < 5; i++)
    {
        if (input[i].b != i+1)
            std::cout << "Error 1 in field_walker_input_test()" << std::endl;
    }

    std::sort(field_walker(input_ptr, fieldof(ABC,c)),
              field_walker(input_ptr+2, fieldof(ABC,c)));

    for (int i = 0; i < 5; i++)
    {
        if (input[i].c != i+'a')
            std::cout << "Error 2 in field_walker_input_test()" << std::endl;
    }
}

int main()
{
    bit_walker_input_test();
}