#include <stdexcept>

#define CArray_EnableChecks

namespace CArrayImpl
{
    namespace ToString
    {
        size_t constexpr constexprStrlen(
            const char* _string
          )
        {
            return _string ?
                (*_string ? 1 + constexprStrlen(_string + 1) : 0) :
                0;
        }
        
        static constexpr const char* delimiterCString = ", ";
        static constexpr size_t delimiterCStringStrlen = constexprStrlen(delimiterCString);
        
        static constexpr const char* emptyArrayCString = "<empty-array>";
        static constexpr size_t emptyArrayCStringStrlen = constexprStrlen(emptyArrayCString);        
    }
    
    template <typename TData>
    struct Details
    {
    protected:
        constexpr static unsigned int minimalDataSize = 1;
        constexpr static unsigned int reallocationFactor = 2;
        
        void initData(
            const unsigned int _initialDataSize
          );

        void reallocateData(
            const unsigned int _newDataSize,
            const unsigned int _elementsNumToCopy
          );

        void clearData();
        
        void expandDataIfNeeded();
        void shrinkDataIfNeeded();

        void invalidate();
    
        void checkIndex(
            const unsigned int _index
          ) const;
    
        TData* data{ nullptr };
        unsigned int dataSize{ 0 };
        unsigned int usedSize{ 0 };    
    };
}

// -----------------

namespace CArrayImpl
{
    template <typename TData>
    void Details<TData>::initData(
        const unsigned int _initialDataSize
      )
    {
        data = new TData[_initialDataSize];
        dataSize = _initialDataSize;
    }

    template <typename TData>
    void Details<TData>::reallocateData(
        const unsigned int _newDataSize,
        const unsigned int _elementsNumToCopy
      )
    {
#ifdef CArray_EnableChecks
        if (_elementsNumToCopy > _newDataSize)
        {
            throw std::invalid_argument{ "To big elementToCopy" };
            return;
        }
#endif
            
        if (_newDataSize != dataSize)
        {
            if (_newDataSize > 0)
            {
                const TData* const oldData = data;
                data = new TData[_newDataSize];
                
                if (oldData)
                {
                    for (unsigned int indexToCopy = 0; indexToCopy < _elementsNumToCopy; ++indexToCopy)
                        data[indexToCopy] = std::move(oldData[indexToCopy]);
                    delete[] oldData;
                }
                
                dataSize = _newDataSize;
            }
            else
            {
                clearData();
            }
        }
    }

    template <typename TData>
    void Details<TData>::clearData()
    {
        if (data)
            delete[] data;
        data = nullptr;
        
        dataSize = 0;
    }

    template <typename TData>
    void Details<TData>::expandDataIfNeeded()
    {
        if (usedSize == dataSize)
        {
            const auto newDataSize = this->dataSize > 0 ?
                static_cast<unsigned int>(dataSize * reallocationFactor) : minimalDataSize;
            this->reallocateData(newDataSize, usedSize);
        }
    }

    template <typename TData>
    void Details<TData>::shrinkDataIfNeeded()
    {
        if (usedSize < dataSize / reallocationFactor)
        {
            const auto newDataSize = static_cast<unsigned int>(dataSize / reallocationFactor);
            this->reallocateData(newDataSize, usedSize);
        }
    }

    template <typename TData>
    void Details<TData>::checkIndex(
        const unsigned int _index
      ) const
    {
#ifdef CArray_EnableChecks
        if (_index >= usedSize)
            throw std::out_of_range{ "Index out of range" };
#endif
    }
            
    template <typename TData>
    void Details<TData>::invalidate() {
        data = nullptr;
        dataSize = 0;
        usedSize = 0;
    }
}
