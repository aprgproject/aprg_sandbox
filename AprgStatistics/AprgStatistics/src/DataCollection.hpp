#pragma once

namespace alba
{

template <typename DataType>
class DataCollection
{
public:
    DataCollection()
        : m_minimum(0)
        , m_maximum(0)
        , m_theCountForMinimum(0)
        , m_theCountForMaximum(0)
        , m_total(0)
        , m_count(0)
    {}
    DataType getMinimum() const
    {
        return m_minimum;
    }
    DataType getMaximum() const
    {
        return m_maximum;
    }
    DataType getTheCountForMinimum() const
    {
        return m_theCountForMinimum;
    }
    DataType getTheCountForMaximum() const
    {
        return m_theCountForMaximum;
    }
    DataType getTotal() const
    {
        return m_total;
    }
    unsigned int getCount() const
    {
        return m_count;
    }
    DataType getAverage() const
    {
        return m_total/m_count;
    }
    double getAverageWithDoubleFormat() const
    {
        return (double)m_total/m_count;
    }
    void addData(DataType dataValue)
    {
        if(m_count==0)
        {
            m_minimum = dataValue;
            m_maximum = dataValue;
        }
        else
        {//no std::min, std::max because algorithm header is needed
            if(m_minimum > dataValue)
            {
                m_minimum = dataValue;
                m_theCountForMinimum = m_count;
            }
            if(m_maximum < dataValue)
            {
                m_maximum = dataValue;
                m_theCountForMaximum = m_count;
            }
        }
        m_total+=dataValue;
        m_count++;
    }
    void clear()
    {
        m_minimum = 0;
        m_maximum = 0;
        m_total = 0;
        m_count = 0;
    }
private:
    DataType m_minimum;
    DataType m_maximum;
    DataType m_theCountForMinimum;
    DataType m_theCountForMaximum;
    DataType m_total;
    unsigned int m_count;
};

}
