#pragma once

#include <string>

template<typename TType>
size_t expectedToStringSize(
    TType value
  )
{
    return sizeof(TType);
}

size_t expectedToStringSize(
    const std::string & _value
  );

std::string toString(
    const std::string & _value
  );

size_t expectedToStringSize(
    const int _value
  );

std::string toString(
    const int _value
  );
