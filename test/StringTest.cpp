#include "StringTest.hpp"
#include <string>
#include "../utils/ToString.hpp"
#include "../carray/CArray.hpp"
#include "utils/TestUtils.hpp"
#include <iostream>

namespace StringTestsDetails
{    
    inline std::string generateTestRandomValue()
    {
        constexpr size_t wordMaxLength = 10;
        constexpr char lettersRangeBegin = 'a';
        constexpr char lettersRangeEnd = 'z';
        static_assert(lettersRangeBegin < lettersRangeEnd, "Invalid letters range");        
        constexpr char lettersRangeSize = lettersRangeEnd - lettersRangeBegin;

        std::string result;
        
        const size_t resultLength = TestUtils::generateRandomPositiveNumber(wordMaxLength);
        result.reserve(resultLength);
        for (size_t index = 0; index < resultLength; ++index)
        {
            const char randomLetter = lettersRangeBegin + TestUtils::generateRandomPositiveNumber(lettersRangeSize);
            result.append(1, randomLetter);
        }

        return std::move(result);
    }
        
    inline bool isValueContainsLettersFromRange(
        const std::string & value,
        const char rangeBegin,
        const char rangeEnd
      )
    {
        if (rangeBegin < rangeEnd)
        {
            for (const char letter : value)
                if (letter >= rangeBegin && letter <= rangeEnd)
                    return true;
            return false;
        }
        else
        {
            return false;
        }
    }
        
    inline bool isValueShouldBeErased(
        const std::string & value
      )
    {
        constexpr char letterToEraseRangeBegin = 'a';
        constexpr char letterToEraseRangeEnd = 'e';
        static_assert(letterToEraseRangeBegin < letterToEraseRangeEnd, "Invalid letters range");
        
        return isValueContainsLettersFromRange(value, letterToEraseRangeBegin, letterToEraseRangeEnd);
    }
        
    namespace Caption
    {
        constexpr const char* header = "--- String tests ---";
        constexpr const char* beforeFilling = "(0) Before filling:";
        constexpr const char* afterFilling = "(1) After filling with random words containing letters a..z:";
        constexpr const char* afterSorting = "(2) After sorting:";
        constexpr const char* afterErasing = "(3) After erasing each element with letters a..e:";
        constexpr const char* afterInserting = "(4) After inserting 3 random elements:";
    }
}

void performStringTests()
{
    using namespace StringTestsDetails;

    std::cout << Caption::header << std::endl;

    //0
    CArray<std::string> array;

    std::cout << Caption::beforeFilling << std::endl;
    std::cout << toString(array) << std::endl;

    //1
    const unsigned int testElementsNum = 15;
    for (unsigned int index = 0; index < testElementsNum; ++index)
        array.push_back(generateTestRandomValue());

    std::cout << Caption::afterFilling << std::endl;
    std::cout << toString(array) << std::endl;

    //2
    sort(array);
    
    std::cout << Caption::afterSorting << std::endl;
    std::cout << toString(array) << std::endl;

    //3
    {
        unsigned int index = 0;
        while (index < array.size())
        {
            const std::string& value = array[index];
            if (isValueShouldBeErased(value))
                array.erase(index);
            else
                ++index;
        }
    }
    
    std::cout << Caption::afterErasing << std::endl;
    std::cout << toString(array) << std::endl;
    
    //4
    constexpr size_t insertingsNum = 3;
    for (size_t index = 0; index < insertingsNum; ++index)
    {
        const unsigned int insertingsIndex = TestUtils::generateRandomPositiveNumber(array.size() - 1);
        const std::string insertingValue = generateTestRandomValue();
        
        array.insert(insertingsIndex, insertingValue);
    }

    std::cout << Caption::afterInserting << std::endl;
    std::cout << toString(array) << std::endl;
}
