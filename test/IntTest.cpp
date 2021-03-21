#include "IntTest.hpp"
#include "../utils/ToString.hpp"
#include "../carray/CArray.hpp"
#include "utils/TestUtils.hpp"
#include <iostream>

namespace IntTestsDetails
{    
    inline int generateTestRandomValue()
    {
        const unsigned int maxValue = 100;
        return TestUtils::generateRandomPositiveNumber(maxValue);
    }
        
    namespace Caption
    {
        constexpr const char* header = "--- Int tests ---";
        constexpr const char* beforeFilling = "(0) Before filling:";
        constexpr const char* afterFilling = "(1) After filling with random elements with values 0..100:";
        constexpr const char* afterSorting = "(2) After sorting:";
        constexpr const char* afterErasing = "(3) After erasing each second element:";
        constexpr const char* afterInserting = "(4) After inserting 10 random elements:";
        constexpr const char* afterClearing = "(5) After clearing:";
    }
}

void performIntTests()
{
    using namespace IntTestsDetails;

    std::cout << Caption::header << std::endl;

    //0
    CArray<int> array;

    std::cout << Caption::beforeFilling << std::endl;
    std::cout << toString(array) << std::endl;

    //1
    const unsigned int testElementsNum = 20;
    for (unsigned int index = 0; index < testElementsNum; ++index)
        array.push_back(generateTestRandomValue());

    std::cout << Caption::afterFilling << std::endl;
    std::cout << toString(array) << std::endl;

    //2
    sort(array);
    
    std::cout << Caption::afterSorting << std::endl;
    std::cout << toString(array) << std::endl;

    //3
    for (unsigned int index = 1; index < array.size(); ++index)
        array.erase(index);
    
    std::cout << Caption::afterErasing << std::endl;
    std::cout << toString(array) << std::endl;
    
    //4
    constexpr size_t insertingsNum = 10;
    for (size_t index = 0; index < insertingsNum; ++index)
    {
        const unsigned int insertingsIndex = TestUtils::generateRandomPositiveNumber(array.size() - 1);
        const int insertingsValue = generateTestRandomValue();

        array.insert(insertingsIndex, insertingsValue);
    }

    std::cout << Caption::afterInserting << std::endl;
    std::cout << toString(array) << std::endl;
    
    //5
    array.clear();
    
    std::cout << Caption::afterClearing << std::endl;
    std::cout << toString(array) << std::endl;
}
