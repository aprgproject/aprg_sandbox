#pragma once

#include <Container/AlbaContainerHelper.hpp>

#include <array>
#include <cmath>
#include <functional>
#include <initializer_list>

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
        for (unsigned int index=0; index<dimensions; index++)
        {
            m_data[index]=0;
        }
    }

    DataSample(std::initializer_list<DataType> dataSampleValues)
    {
        unsigned int limit = std::min(dimensions, dataSampleValues.size());
        for (unsigned int index=0; index<limit; index++)
        {
            m_data[index]=*(dataSampleValues.begin()+index);
        }
    }

    bool isIndexValid(unsigned int index) const
    {
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
        std::stringstream ss;
        ss << "[";
        for (unsigned int index=0; index<dimensions; index++)
        {
            ss << m_data.at(index) << ", ";
        }
        ss<<"]";
        return ss.str();
        //return std::string("[") + containerHelper::getStringFromContentsOfContainerWithNumberFormat(m_data, ",") + "]\n";
    }

    void setValueAt(unsigned int index, DataType const dataSampleValue)
    {
        if(isIndexValid(index))
        {
            m_data[index] = dataSampleValue;
        }
    }

    bool operator==(Sample const& value) const
    {
        return performConditionCheckWithAnd(value, std::equal_to<DataType>());
    }

    Sample operator+(Sample const& value) const
    {
        return performDataTypeAndDataTypeFunction(value, std::plus<DataType>());
    }

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
        Sample sample;
        for (unsigned int index=0; index<dimensions; index++)
        {
            sample.m_data.at(index) = binaryFunction(m_data.at(index), value.m_data.at(index));
        }
        return sample;
    }

    Sample performDataTypeAndConstantFunction(DataType const value, std::function<DataType(DataType, DataType)> binaryFunction) const
    {
        Sample sample;
        for (unsigned int index=0; index<dimensions; index++)
        {
            sample.m_data.at(index) = binaryFunction(m_data.at(index), value);
        }
        return sample;
    }

    bool performConditionCheckWithAnd(Sample const& value, std::function<bool(DataType, DataType)> conditionFunction) const
    {
        bool result(true);
        for (unsigned int index=0; index<dimensions; index++)
        {
            result &= conditionFunction(m_data.at(index), value.m_data.at(index));
            if(result)
            {
                break;
            }
        }
        return result;
    }

    BufferType m_data;
};

}
