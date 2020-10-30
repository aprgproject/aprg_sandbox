#pragma once

#include <array>
#include <functional>
#include <initializer_list>

namespace alba
{

template <typename DataType, unsigned int size>
class DataSample
{
public:
    using SimplifiedType = DataSample<DataType, size>;
    using BufferType = std::array<DataType, size>;

    DataSample()
    {
        for (unsigned int index=0; index<size; index++)
        {
            m_data[index]=0;
        }
    }

    DataSample(std::initializer_list<DataType> dataSampleValues)
    {
        unsigned int limit = std::min(size, dataSampleValues.size());
        for (unsigned int index=0; index<limit; index++)
        {
            m_data[index]=*(dataSampleValues.begin()+index);
        }
    }

    bool isIndexValid(unsigned int index) const
    {
        return index < size;
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

    void setValueAt(unsigned int index, DataType const dataSampleValue)
    {
        if(isIndexValid(index))
        {
            m_data[index] = dataSampleValue;
        }
    }

    SimplifiedType operator+(SimplifiedType const& value) const
    {
        return performDataTypeAndDataTypeFunction(value, std::plus<DataType>());
    }

    SimplifiedType operator-(SimplifiedType const& value) const
    {
        return performDataTypeAndDataTypeFunction(value, std::minus<DataType>());
    }

    SimplifiedType operator*(SimplifiedType const& value) const
    {
        return performDataTypeAndDataTypeFunction(value, std::multiplies<DataType>());
    }

    SimplifiedType operator/(SimplifiedType const& value) const
    {
        return performDataTypeAndDataTypeFunction(value, std::divides<DataType>());
    }

    SimplifiedType operator+(DataType const value) const
    {
        return performDataTypeAndConstantFunction(value, std::plus<DataType>());
    }

    SimplifiedType operator-(DataType const value) const
    {
        return performDataTypeAndConstantFunction(value, std::minus<DataType>());
    }

    SimplifiedType operator*(DataType const value) const
    {
        return performDataTypeAndConstantFunction(value, std::multiplies<DataType>());
    }

    SimplifiedType operator/(DataType const value) const
    {
        return performDataTypeAndConstantFunction(value, std::divides<DataType>());
    }

private:

    SimplifiedType performDataTypeAndDataTypeFunction(SimplifiedType const& value, std::function<DataType(DataType, DataType)> binaryFunction) const
    {
        SimplifiedType sample;
        for (unsigned int index=0; index<size; index++)
        {
            sample.m_data.at(index) = binaryFunction(m_data.at(index), value.m_data.at(index));
        }
        return sample;
    }

    SimplifiedType performDataTypeAndConstantFunction(DataType const& value, std::function<DataType(DataType, DataType)> binaryFunction) const
    {
        SimplifiedType sample;
        for (unsigned int index=0; index<size; index++)
        {
            sample.m_data.at(index) = binaryFunction(m_data.at(index), value);
        }
        return sample;
    }

    BufferType m_data;
};

}
