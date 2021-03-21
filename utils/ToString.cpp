#include "ToString.hpp"
#include <sstream>//for expectedToStringSize(int)

size_t expectedToStringSize(
    const std::string & _value
  )
{
    return _value.size();
}

std::string toString(
    const std::string & _value
  )
{
    return _value;
}

size_t expectedToStringSize(
    const int _value
  )
{
    return std::numeric_limits<int>::digits10;
}

std::string toString(
    const int _value
  )
{
    std::ostringstream stream;
    stream << _value;
    return stream.str();
}

