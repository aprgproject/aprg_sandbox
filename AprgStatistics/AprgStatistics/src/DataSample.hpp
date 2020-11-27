#pragma once

#include <Container/AlbaContainerHelper.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <initializer_list>

namespace alba
{

template <unsigned int dimensions>
class DataSample
{
public:
    using Sample = DataSample<dimensions>;
    using BufferType = std::array<double, dimensions>;

    DataSample()
    {
        std::fill(m_data.begin(), m_data.end(), 0);
    }

    DataSample(std::initializer_list<double> dataSampleValues)
    {
        unsigned int limit = std::min(dimensions, dataSampleValues.size());
        std::copy(dataSampleValues.begin(), dataSampleValues.begin()+limit, m_data.begin());
    }

    bool isIndexValid(unsigned int index) const
    {
        return index < dimensions;
    }

    double getValueAt(unsigned int index) const
    {
        double result(0);
        if(isIndexValid(index))
        {
            result = m_data[index];
        }
        return result;
    }

    double getSum() const
    {
        double result(0);
        for (unsigned int index=0; index<dimensions; index++)
        {
            result += m_data.at(index);
        }
        return result;
    }

    std::string getDisplayableString() const
    {
        std::stringstream result;
        result.precision(20);
        for(auto const& data : m_data)
        {
            result << data << ", ";
        }
        return result.str();
    }

    void setValueAt(unsigned int index, double const dataSampleValue)
    {
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
        return performDataTypeAndDataTypeFunction(value, std::plus<double>());
    }

    Sample operator-(Sample const& value) const
    {
        return performDataTypeAndDataTypeFunction(value, std::minus<double>());
    }

    Sample operator*(Sample const& value) const
    {
        return performDataTypeAndDataTypeFunction(value, std::multiplies<double>());
    }

    Sample operator/(Sample const& value) const
    {
        return performDataTypeAndDataTypeFunction(value, std::divides<double>());
    }

    Sample operator+(double const value) const
    {
        return performDataTypeAndConstantFunction(value, std::plus<double>());
    }

    Sample operator-(double const value) const
    {
        return performDataTypeAndConstantFunction(value, std::minus<double>());
    }

    Sample operator*(double const value) const
    {
        return performDataTypeAndConstantFunction(value, std::multiplies<double>());
    }

    Sample operator/(double const value) const
    {
        return performDataTypeAndConstantFunction(value, std::divides<double>());
    }

    Sample calculateRaiseToPower(double const value) const
    {
        return performDataTypeAndConstantFunction(value, [](double value1, double value2)->double
        {
            return pow((double)value1, (double)value2);
        });
    }

    Sample calculateRaiseToInversePower(double const value) const
    {
        return performDataTypeAndConstantFunction(value, [](double value1, double value2)->double
        {
            return pow((double)value1, (double)1/value2);
        });
    }

private:

    Sample performDataTypeAndDataTypeFunction(Sample const& value, std::function<double(double, double)> binaryFunction) const
    {
        Sample result;
        std::transform(m_data.cbegin(), m_data.cend(), value.m_data.cbegin(), result.m_data.begin(), binaryFunction);
        return result;
    }

    Sample performDataTypeAndConstantFunction(double const value, std::function<double(double, double)> binaryFunction) const
    {
        Sample result;
        std::transform(m_data.begin(), m_data.cend(), result.m_data.begin(), [&](double const data)->double
        {
            return binaryFunction(data, value);
        });
        return result;
    }

    BufferType m_data;
};

}
