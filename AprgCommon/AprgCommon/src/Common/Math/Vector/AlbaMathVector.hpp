#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cassert>
#include <numeric>
#include <sstream>
#include <string>

namespace alba
{

template <typename DataType>
bool isEqualForMathVectorDataType(DataType const& value1, DataType const& value2);

template <typename DataType>
DataType raiseToPowerForMathVectorDataType(DataType const& value1, DataType const& value2);

template <typename DataType, unsigned int SIZE>
class AlbaMathVector
{
public:
    using AlbaMathVectorType=AlbaMathVector<DataType, SIZE>;
    using ValuesInArray=std::array<DataType, SIZE>;

    AlbaMathVector()
        : m_values{}
    {}

    AlbaMathVector(ValuesInArray const& values)
        : m_values(values)
    {}

    AlbaMathVector(std::initializer_list<DataType> const& values)
        : m_values{}
    {
        unsigned int limit = std::min(SIZE, static_cast<unsigned int>(values.size()));
        std::copy(values.begin(), values.begin()+limit, m_values.begin());
    }

    bool operator==(AlbaMathVectorType const& second) const
    {
        return std::equal(m_values.cbegin(), m_values.cend(), second.m_values.cbegin(),
                          [](DataType const first, DataType const second)
        {
            return isEqualForMathVectorDataType(first, second);
        });
    }

    bool operator!=(AlbaMathVectorType const& second) const
    {
        AlbaMathVectorType const& first(*this);
        return !(first==second);
    }

    bool operator<(AlbaMathVectorType const& second) const // this is added so it can be used in map
    {
        auto mismatchPair = std::mismatch(m_values.cbegin(), m_values.cend(), second.m_values.cbegin());
        bool result(false);
        if(mismatchPair.first != m_values.cend())
        {
            result = *(mismatchPair.first) < *(mismatchPair.second);
        }
        return result;
    }

    AlbaMathVectorType operator+(AlbaMathVectorType const& second) const
    {
        AlbaMathVectorType result;
        ValuesInArray const& firstValues(m_values);
        ValuesInArray const& secondValues(second.m_values);
        ValuesInArray & resultValues(result.m_values);
        std::transform(firstValues.begin(), firstValues.end(), secondValues.begin(), resultValues.begin(), std::plus<DataType>());
        return result;
    }

    AlbaMathVectorType operator-(AlbaMathVectorType const& second) const
    {
        AlbaMathVectorType result;
        ValuesInArray const& firstValues(m_values);
        ValuesInArray const& secondValues(second.m_values);
        ValuesInArray & resultValues(result.m_values);
        std::transform(firstValues.begin(), firstValues.end(), secondValues.begin(), resultValues.begin(), std::minus<DataType>());
        return result;
    }

    AlbaMathVectorType operator+() const
    {
        return *this;
    }

    AlbaMathVectorType operator-() const
    {
        AlbaMathVectorType result;
        ValuesInArray & resultValues(result.m_values);
        std::transform(m_values.begin(), m_values.end(), resultValues.begin(), std::negate<DataType>());
        return result;
    }

    AlbaMathVectorType operator*(DataType const& scalarValue) const
    {
        AlbaMathVectorType result;
        ValuesInArray & resultValues(result.m_values);
        std::transform(m_values.begin(), m_values.end(), resultValues.begin(), [&](DataType const value)
        {
            return value*scalarValue;
        });
        return result;
    }

    AlbaMathVectorType operator/(DataType const& scalarValue) const
    {
        AlbaMathVectorType result;
        ValuesInArray & resultValues(result.m_values);
        std::transform(m_values.begin(), m_values.end(), resultValues.begin(), [&](DataType const value)
        {
            return value/scalarValue;
        });
        return result;
    }

    AlbaMathVectorType& operator+=(AlbaMathVectorType const& second)
    {
        ValuesInArray const& secondValues(second.m_values);
        std::transform(m_values.begin(), m_values.end(), secondValues.begin(), m_values.begin(), std::plus<DataType>());
        return *this;
    }

    AlbaMathVectorType& operator-=(AlbaMathVectorType const& second)
    {
        ValuesInArray const& secondValues(second.m_values);
        std::transform(m_values.begin(), m_values.end(), secondValues.begin(), m_values.begin(), std::minus<DataType>());
        return *this;
    }

    AlbaMathVectorType& operator*=(DataType const& scalarValue)
    {
        std::transform(m_values.begin(), m_values.end(), m_values.begin(), [&](DataType const value)
        {
            return value*scalarValue;
        });
        return *this;
    }

    AlbaMathVectorType& operator/=(DataType const& scalarValue)
    {
        std::transform(m_values.begin(), m_values.end(), m_values.begin(), [&](DataType const value)
        {
            return value/scalarValue;
        });
        return *this;
    }

    unsigned int getSize() const
    {
        return SIZE;
    }

    DataType const& getValueAt(unsigned int const index) const
    {
        assert(index<SIZE);
        return m_values.at(index);
    }

    DataType getMagnitude() const
    {
        DataType sumOfSquaredTerms = std::accumulate(
                    m_values.cbegin(), m_values.cend(), DataType(0), [](
                    DataType const partialResult,
                    DataType const currentValue)
        {
                return partialResult + static_cast<DataType>(raiseToPowerForMathVectorDataType(currentValue, DataType(2)));
    });
        return static_cast<DataType>(raiseToPowerForMathVectorDataType(sumOfSquaredTerms, DataType(1)/DataType(2)));
    }

    ValuesInArray const& getValues() const
    {
        return m_values;
    }

    std::string getDisplayableString() const
    {
        std::stringstream ss;
        if(!m_values.empty())
        {
            ss << "{" << m_values.front();
            for(auto it=m_values.cbegin()+1; it!=m_values.cend(); it++)
            {
                ss << ", " << *it;
            }
            ss << "}";
        }
        return ss.str();
    }

    DataType & getValueReferenceAt(unsigned int const index)
    {
        assert(index<SIZE);
        return m_values.at(index);
    }

    ValuesInArray & getValuesReference()
    {
        return m_values;
    }

private:
    ValuesInArray m_values;
};

template <typename DataType, unsigned int SIZE>
std::ostream & operator<<(std::ostream & out, AlbaMathVector<DataType, SIZE> const& mathVector)
{
    out << mathVector.getDisplayableString();
    return out;
}

}
