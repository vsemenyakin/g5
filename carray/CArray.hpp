#pragma once

#include <string>
#include <algorithm>//for sort(CArray<>)

#include "CArrayImpl.inl"

// ============================[ Interface ]============================

template <typename TData>
class CArray : public CArrayImpl::Details<TData>
{
public:
    CArray() = default;

    CArray( 
        const CArray & _array
      );

    CArray(
        CArray && _array
      );

    ~CArray();

    void push_back(
        const TData & _value
      );

    void insert(
        const unsigned int _index,
        const TData & _value
      );
    
    void erase(
        const unsigned int _index
      );
    
    void clear();
    
    unsigned int size() const;    
    
    TData & operator[](
        const unsigned int _index
      );
    
    const TData & operator[](
        const unsigned int _index
      ) const;

    template<typename _TData>
    friend void sort(
        CArray<_TData> & _arrayToSort
      );
};

template <typename TData>
void sort(
    CArray<TData>& _arrayToSort
  );

template <typename TData>
std::string toString(
    const CArray<TData>& _value
  );

// ============================[ Implementation ]============================

template <typename TData>    
CArray<TData>::CArray(
    const CArray & _array
  )
{
    initData(_array.dataSize);
    
    for (this->usedSize = 0; this->usedSize < _array.usedSize; ++this->usedSize)
        this->data[this->usedSize] = _array.data[this->usedSize];
}

template <typename TData>    
CArray<TData>::CArray(
    CArray && _array
  )
{
    this->data = _array.data;
    this->dataSize = _array.dataSize;
    this->usedSize = _array.usedSize;
    
    _array.invalidate();
}

template <typename TData>    
CArray<TData>::~CArray()
{
    this->clearData();
}

template <typename TData>
void CArray<TData>::push_back(
    const TData & _value
  )
{    
    this->expandDataIfNeeded();

    this->data[this->usedSize] = _value;
    
    ++this->usedSize;
}

template <typename TData>
void CArray<TData>::insert(
    const unsigned int _index,
    const TData & _value
  )
{
    this->checkIndex(_index);

    this->expandDataIfNeeded();
        
    for (unsigned int indexToRewrite = this->usedSize; indexToRewrite > _index; --indexToRewrite)
        this->data[indexToRewrite] = this->data[indexToRewrite - 1];
    this->data[_index] = _value;
    
    ++this->usedSize;
}

template <typename TData>
void CArray<TData>::erase(
    const unsigned int _index
  )
{
    this->checkIndex(_index);

    for (unsigned int indexToRewrite = _index; indexToRewrite < this->usedSize - 1; ++indexToRewrite)
        this->data[indexToRewrite] = this->data[indexToRewrite + 1];
    
    --this->usedSize;
    
    this->shrinkDataIfNeeded();
}

template <typename TData>
void CArray<TData>::clear()
{
    this->clearData();
    this->usedSize = 0;
}

template <typename TData>
unsigned int CArray<TData>::size() const
{
    return this->usedSize;
}

template <typename TData>
TData & CArray<TData>::operator[](
    const unsigned int _index
  )
{
    const TData & constResult = const_cast<const CArray*>(this)->operator[](_index);
    return const_cast<TData &>(constResult);
}

template <typename TData>
const TData & CArray<TData>::operator[](
    const unsigned int _index
  ) const
{
    this->checkIndex(_index);
    return this->data[_index];
}

template <typename TData>
void sort(
    CArray<TData> & _arrayToSort
  )
{
    std::sort(_arrayToSort.data, _arrayToSort.data + _arrayToSort.usedSize);
}

template<typename TData>
size_t expectedToStringSize(
    const CArray<TData> & value
  )
{
    using namespace CArrayImpl::ToString;
    
    const unsigned int valueSize = value.size();
    
    if (valueSize > 0)
    {
        size_t result = expectedToStringSize<TData>(value[0]);
        for (unsigned int index = 1; index < valueSize; ++index)
            result += delimiterCStringStrlen + expectedToStringSize(value[index]);
        
        return result;
    }
    else
    {
        return emptyArrayCStringStrlen;
    }
}

template <typename TData>
std::string toString(
    const CArray<TData> & _value
  )
{
    using namespace CArrayImpl::ToString;
    
    std::string result;
    result.reserve(expectedToStringSize(_value));

    const unsigned int valueSize = _value.size();
    if (valueSize > 0)
    {
        result.append(toString(_value[0]));
        for (unsigned int index = 1; index < valueSize; ++index)
        {
            result.append(delimiterCString);
            result.append(toString(_value[index]));
        }
    }
    else
    {
        result.append(emptyArrayCString);
    }
    
    result.shrink_to_fit();
    
    return result;
}
