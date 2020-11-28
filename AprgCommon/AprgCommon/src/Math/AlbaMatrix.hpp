#pragma once

#include <functional>
#include <vector>

namespace alba
{

template <typename DataType>
class AlbaMatrix
{
    using MatrixData = std::vector<DataType>;
public:
    AlbaMatrix()
        : m_numberOfColumns(0)
        , m_numberOfRows(0)
        , m_size(0)
    {}
    AlbaMatrix(unsigned int const numberOfColumns, unsigned int const numberOfRows)
        : m_numberOfColumns(numberOfColumns)
        , m_numberOfRows(numberOfRows)
        , m_size(numberOfColumns*numberOfRows)
        , m_matrixData(m_size, 0)
    {}
    unsigned int getColumns() const
    {
        return m_numberOfColumns;
    }
    unsigned int getRows() const
    {
        return m_numberOfRows;
    }
    DataType get(unsigned int const x, unsigned int const y) const
    {
        return m_matrixData.at(getMatrixIndex(x, y));
    }
    void set(unsigned int const x, unsigned int const y, DataType const value)
    {
        m_matrixData[getMatrixIndex(x, y)] = value;
    }
    void traverse(std::function<void(unsigned int const, unsigned int const, DataType const)> doFunction)
    {
        unsigned int x=0, y=0;
        for(DataType const value : m_matrixData)
        {
            doFunction(x, y, value);
            x++;
            if(x>=m_numberOfColumns)
            {
                x=0;
                y++;
            }
        }
    }
    void clearAndResize(unsigned int const numberOfColumns, unsigned int const numberOfRows)
    {
        m_numberOfColumns = numberOfColumns;
        m_numberOfRows = numberOfRows;
        m_size = numberOfColumns*numberOfRows;
        m_matrixData.clear();
        m_matrixData.resize(m_size, 0);
    }
    void transpose()
    {
        unsigned int oldColumns(m_numberOfColumns);
        unsigned int oldRows(m_numberOfRows);
        MatrixData oldMatrixData(m_matrixData);
        clearAndResize(oldRows, oldColumns);
        for(unsigned int y=0; y<oldRows; y++)
        {
            for(unsigned int x=0; x<oldColumns; x++)
            {
                m_matrixData[getMatrixIndex(y, x)] = oldMatrixData[getMatrixIndex(x, y, oldColumns)];
            }
        }
    }
    /*AlbaMatrix operator+(AlbaMatrix const& secondMatrix) const
    {
    }
    AlbaMatrix operator-(AlbaMatrix const& secondMatrix) const
    {
    }*/

private:
    unsigned int getMatrixIndex(unsigned int const x, unsigned int const y) const
    {
        return (y*m_numberOfColumns)+x;
    }
    unsigned int getMatrixIndex(unsigned int const x, unsigned int const y, unsigned int const numberOfColumns) const
    {
        return (y*numberOfColumns)+x;
    }
    unsigned int m_numberOfColumns;
    unsigned int m_numberOfRows;
    unsigned int m_size;
    MatrixData m_matrixData;
};

}//namespace alba
