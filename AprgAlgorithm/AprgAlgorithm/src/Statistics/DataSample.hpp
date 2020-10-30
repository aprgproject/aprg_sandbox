#pragma once

#include <Container/AlbaContainerHelper.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <functional>#include <initializer_list>

namespace alba
{

template <typename DataType, unsigned int dimensions>
class DataSample
{
public:
    using Sample = DataSample<DataType, dimensions>;
    using BufferType = std::array<DataType, dimensions>;

    DataSample()
    {
        std::fill(m_data.begin(), m_data.end(), 0);
    }

    DataSample(std::initializer_list<DataType> dataSampleValues)
    {
        unsigned int limit = std::min(dimensions, dataSampleValues.size());
        std::copy(dataSampleValues.begin(), dataSampleValues.begin()+limit, m_data.begin());
    }

    bool isIndexValid(unsigned int index) const    {
        return index < dimensions;
    }

    DataType getValueAt(unsigned int index) const
    {
        DataType result(0);
        if(isIndexValid(index))
        {
            result = m_data[index];
        }
        return result;
    }

    DataType getSum() const
    {
        DataType result(0);
        for (unsigned int index=0; index<dimensions; index++)
        {
            result += m_data.at(index);
        }
        return result;
    }

    std::string getDisplayableString() const
    {
        return containerHelper::getStringFromContentsOfContainer(m_data, ", ");
    }

    void setValueAt(unsigned int index, DataType const dataSampleValue)    {
        if(isIndexValid(index))
        {
            m_data[index] = dataSampleValue;
        }
    }

    bool operator==(Sample const& value) const
    {
        return std::equal(m_data.cbegin(), m_data.cend(), value.m_data.cbegin());
    }

    bool operator!=(Sample const& value) const
    {
        return !(*this==value);
    }

    Sample operator+(Sample const& value) const
    {
        return performDataTypeAndDataTypeFunction(value, std::plus<DataType>());    }

    Sample operator-(Sample const& value) const
    {
        return performDataTypeAndDataTypeFunction(value, std::minus<DataType>());
    }

    Sample operator*(Sample const& value) const
    {
        return performDataTypeAndDataTypeFunction(value, std::multiplies<DataType>());
    }

    Sample operator/(Sample const& value) const
    {
        return performDataTypeAndDataTypeFunction(value, std::divides<DataType>());
    }

    Sample operator+(DataType const value) const
    {
        return performDataTypeAndConstantFunction(value, std::plus<DataType>());
    }

    Sample operator-(DataType const value) const
    {
        return performDataTypeAndConstantFunction(value, std::minus<DataType>());
    }

    Sample operator*(DataType const value) const
    {
        return performDataTypeAndConstantFunction(value, std::multiplies<DataType>());
    }

    Sample operator/(DataType const value) const
    {
        return performDataTypeAndConstantFunction(value, std::divides<DataType>());
    }

    Sample calculateRaiseToPower(DataType const value) const
    {
        return performDataTypeAndConstantFunction(value, [](DataType value1, DataType value2)->DataType
        {
            return (DataType)pow((double)value1, (double)value2);
        });
    }

    Sample calculateRaiseToInversePower(DataType const value) const
    {
        return performDataTypeAndConstantFunction(value, [](DataType value1, DataType value2)->DataType
        {
            return (DataType)pow((double)value1, (double)1/value2);
        });
    }

private:

    Sample performDataTypeAndDataTypeFunction(Sample const& value, std::function<DataType(DataType, DataType)> binaryFunction) const
    {
        Sample result;
        std::transform(m_data.cbegin(), m_data.cend(), value.m_data.cbegin(), result.m_data.begin(), binaryFunction);
        return result;
    }

    Sample performDataTypeAndConstantFunction(DataType const value, std::function<DataType(DataType, DataType)> binaryFunction) const
    {
        Sample result;
        std::transform(m_data.begin(), m_data.cend(), result.m_data.begin(), [&](DataType const data)->DataType
        {
            return binaryFunction(data, value);
        });
        return result;
    }
    BufferType m_data;
};

}
