#pragma once

#include <cstdlib>//for std::rand()
#include <stdexcept>

#define TestUtils_EnableChecks

namespace TestUtils
{
    template<typename T>
    T generateRandomPositiveNumber(
        const T _maxNumber
      )
    {
#ifdef TestUtils_EnableChecks
        if (_maxNumber < 0 || _maxNumber + 1 > RAND_MAX)
            throw std::invalid_argument{ "invalid maxNumber provided" };
#endif        
        
        return std::rand() % (_maxNumber + 1);
    }
}
