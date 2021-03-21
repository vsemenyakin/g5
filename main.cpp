#include "test/IntTest.hpp"
#include "test/StringTest.hpp"
#include <iostream>

int main()
{
    performIntTests();
    std::cout << std::endl;
    performStringTests();

    return 0;
}
