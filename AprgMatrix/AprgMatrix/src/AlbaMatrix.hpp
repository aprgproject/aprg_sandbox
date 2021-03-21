#pragma once

#include <Math/AlbaMathHelper.hpp>
#include <User/DisplayTable.hpp>
#include <String/AlbaStringHelper.hpp>

#include <cassert>
#include <functional>
#include <sstream>
#include <vector>

namespace alba{

template <typename DataType>
class AlbaMatrix
{
    using MatrixData = std::vector<DataType>;
    using BinaryFunction = std::function<DataType(DataType const&, DataType const&)>;
    using UnaryFunction = std::function<DataType(DataType const&)>;
public:
    AlbaMatrix()
        : m_numberOfColumns(0) // can we make this as template parameter?
        , m_numberOfRows(0)
    {}
    AlbaMatrix(unsigned int const numberOfColumns, unsigned int const numberOfRows)
        : m_numberOfColumns(numberOfColumns)
        , m_numberOfRows(numberOfRows)
        , m_matrixData(numberOfColumns*numberOfRows, 0)
    {}
    unsigned int getColumns() const
    {        return m_numberOfColumns;
    }
    unsigned int getRows() const
    {
        return m_numberOfRows;
    }
    DataType get(unsigned int const x, unsigned int const y) const
    {
        return m_matrixData.at(getMatrixIndex(x, y));
    }
    std::string getString() const
    {
        stringHelper::NumberToStringConverter converter;
        DisplayTable table;
        table.setBorders("-","|");
        for(unsigned int y=0; y<m_numberOfRows; y++)
        {
            table.addRow();
            for(unsigned int x=0; x<m_numberOfColumns; x++)
            {
                table.getLastRow().addCell(converter.convert<DataType>(m_matrixData.at(getMatrixIndex(x, y))));
            }
        }
        return table.drawOutput();
    }
    void set(unsigned int const x, unsigned int const y, DataType const& value)
    {
        m_matrixData[getMatrixIndex(x, y)] = value;
    }
    void set(std::initializer_list<DataType> dataSampleValues)
    {
        unsigned int limit = std::min(m_matrixData.size(), dataSampleValues.size());
        std::copy(dataSampleValues.begin(), dataSampleValues.begin()+limit, m_matrixData.begin());
    }
    void clearAndResize(unsigned int const numberOfColumns, unsigned int const numberOfRows)
    {
        m_numberOfColumns = numberOfColumns;
        m_numberOfRows = numberOfRows;
        m_matrixData.clear();
        m_matrixData.resize(numberOfColumns*numberOfRows, 0);
    }
    void interchangeRows(unsigned int const y1, unsigned int const y2)
    {
        for(unsigned int x=0; x<m_numberOfColumns; x++)
        {
            std::swap(m_matrixData[getMatrixIndex(x, y1)], m_matrixData[getMatrixIndex(x, y2)]);
        }
    }
    void addRows(unsigned int const yInput1, unsigned int const yInput2, unsigned int const yOutput)
    {
        traverseWithBinaryOperationForDifferentRows(yInput1, yInput2, yOutput, std::plus<DataType>());
    }
    void multiplyValueInRow(unsigned int const yInput, DataType const& multiplierForInput, unsigned int const yOutput)
    {
        traverseWithUnaryOperationForDifferentRows(yInput, yOutput, [&](DataType const& input)
        {
            return input*multiplierForInput;
        });
    }
    void subtractRowsWithMultiplier(unsigned int const yInput1, unsigned int const yInput2, DataType const& multiplierForInput2, unsigned int const yOutput)
    {
        traverseWithBinaryOperationForDifferentRows(yInput1, yInput2, yOutput, [&](DataType const& input1, DataType const& input2)
        {
            return input1-(input2*multiplierForInput2);
        });
    }
    void transpose()
    {
        unsigned int oldColumns(m_numberOfColumns);        unsigned int oldRows(m_numberOfRows);
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
    bool isReducedRowEchelonForm() const
    {
        return areRowsWithAllZeroInTheBottom() && areLeadingEntriesInReducedRowEchelonForm();
    }
    void transformToReducedEchelonForm()
    {
        unsigned int yWithLeadingEntry = 0;
        for(unsigned int x=0; x<m_numberOfColumns; x++)
        {
            for(unsigned int y=yWithLeadingEntry; y<m_numberOfRows; y++)
            {
                if(!mathHelper::isConsideredEqual(m_matrixData.at(getMatrixIndex(x, y)), static_cast<DataType>(0)))
                {
                    interchangeRows(y, yWithLeadingEntry);
                    multiplyValueInRow(yWithLeadingEntry, static_cast<DataType>(1)/m_matrixData.at(getMatrixIndex(x, yWithLeadingEntry)), yWithLeadingEntry);
                    for(unsigned int yToZero=0; yToZero<m_numberOfRows; yToZero++)
                    {
                        if(yToZero != yWithLeadingEntry && !mathHelper::isConsideredEqual(m_matrixData.at(getMatrixIndex(x, yToZero)), static_cast<DataType>(0)))
                        {
                            subtractRowsWithMultiplier(
                                        yToZero,
                                        yWithLeadingEntry,
                                        m_matrixData.at(getMatrixIndex(x, yToZero))/m_matrixData.at(getMatrixIndex(x, yWithLeadingEntry)),
                                        yToZero);
                        }
                    }
                    yWithLeadingEntry++;
                    break;
                }
            }
        }
    }
    AlbaMatrix operator+(AlbaMatrix const& secondMatrix) const
    {
        assert((m_numberOfColumns == secondMatrix.m_numberOfColumns) && (m_numberOfRows == secondMatrix.m_numberOfRows));
        AlbaMatrix result(m_numberOfColumns, m_numberOfRows);
        traverseWithBinaryOperationWithSameDimensions(*this, secondMatrix, result, std::plus<DataType>());
        return result;
    }
    AlbaMatrix operator-(AlbaMatrix const& secondMatrix) const
    {
        assert((m_numberOfColumns == secondMatrix.m_numberOfColumns) && (m_numberOfRows == secondMatrix.m_numberOfRows));
        AlbaMatrix result(m_numberOfColumns, m_numberOfRows);
        traverseWithBinaryOperationWithSameDimensions(*this, secondMatrix, result, std::minus<DataType>());
        return result;
    }
    AlbaMatrix operator*(DataType const& scalarMultiplier) const //scalar multiplication
    {
        AlbaMatrix result(m_numberOfColumns, m_numberOfRows);
        std::function<DataType(DataType const&)> scalarMultiplication = std::bind(std::multiplies<DataType>(), std::placeholders::_1, scalarMultiplier);
        traverseWithUnaryOperationWithSameDimensions(*this, result, scalarMultiplication);
        return result;
    }
    AlbaMatrix operator*(AlbaMatrix const& secondMatrix) const //matrix multiplication
    {
        assert((m_numberOfColumns == secondMatrix.m_numberOfRows) && (m_numberOfRows == secondMatrix.m_numberOfColumns));
        AlbaMatrix result(m_numberOfColumns, m_numberOfRows);
        AlbaMatrix secondTransposedMatrix(secondMatrix);
        secondTransposedMatrix.transpose();
        traverseWithBinaryOperationWithSameDimensions(*this, secondTransposedMatrix, result, std::multiplies<DataType>());
        return result;
    }
    bool operator==(AlbaMatrix const& secondMatrix) const //matrix multiplication
    {
        if(m_numberOfColumns != secondMatrix.m_numberOfColumns)
        {
            return false;
        }
        else if(m_numberOfRows != secondMatrix.m_numberOfRows)
        {
            return false;
        }
        else if(m_matrixData != secondMatrix.m_matrixData)
        {
            return false;
        }
        return true;
    }

private:
    void traverseWithBinaryOperationWithSameDimensions(
            AlbaMatrix const& firstMatrix,
            AlbaMatrix const& secondMatrix,
            AlbaMatrix & resultMatrix,
            BinaryFunction const& binaryFunction) const
    {
        assert((firstMatrix.m_numberOfColumns == secondMatrix.m_numberOfColumns) &&
               (firstMatrix.m_numberOfRows == secondMatrix.m_numberOfRows) &&
               (firstMatrix.m_numberOfColumns == resultMatrix.m_numberOfColumns) &&
               (firstMatrix.m_numberOfRows == resultMatrix.m_numberOfRows));
        for(unsigned int y=0; y<firstMatrix.m_numberOfRows; y++)
        {
            for(unsigned int x=0; x<firstMatrix.m_numberOfColumns; x++)
            {
                resultMatrix.m_matrixData[getMatrixIndex(x, y)]
                        = binaryFunction(firstMatrix.m_matrixData.at(getMatrixIndex(x, y)),
                                         secondMatrix.m_matrixData.at(getMatrixIndex(x, y)));
            }
        }
    }
    void traverseWithUnaryOperationWithSameDimensions(
            AlbaMatrix const& inputMatrix,
            AlbaMatrix & resultMatrix,
            UnaryFunction const& unaryFunction) const
    {
        assert((inputMatrix.m_numberOfColumns == resultMatrix.m_numberOfColumns) &&
               (inputMatrix.m_numberOfRows == resultMatrix.m_numberOfRows));
        for(unsigned int y=0; y<inputMatrix.m_numberOfRows; y++)
        {
            for(unsigned int x=0; x<inputMatrix.m_numberOfColumns; x++)
            {
                resultMatrix.m_matrixData[getMatrixIndex(x, y)]
                        = unaryFunction(inputMatrix.m_matrixData.at(getMatrixIndex(x, y)));
            }
        }
    }
    void traverseWithBinaryOperationForDifferentRows(
            unsigned int const yInput1,
            unsigned int const yInput2,
            unsigned int const yOutput,
            BinaryFunction const& binaryFunction)
    {
        for(unsigned int x=0; x<m_numberOfColumns; x++)
        {
            m_matrixData[getMatrixIndex(x, yOutput)]
                    = binaryFunction(m_matrixData.at(getMatrixIndex(x, yInput1)),
                                     m_matrixData.at(getMatrixIndex(x, yInput2)));
        }
    }
    void traverseWithUnaryOperationForDifferentRows(
            unsigned int const yInput,
            unsigned int const yOutput,
            UnaryFunction const& unaryFunction)
    {
        for(unsigned int x=0; x<m_numberOfColumns; x++)
        {
            m_matrixData[getMatrixIndex(x, yOutput)]
                    = unaryFunction(m_matrixData.at(getMatrixIndex(x, yInput)));
        }
    }
    bool areRowsWithAllZeroInTheBottom() const
    {
        bool isRowWithNonZeroEncountered(false);
        for(unsigned int yPlusOne=m_numberOfRows; yPlusOne>0; yPlusOne--)
        {
            unsigned int y(yPlusOne-1);
            bool isRowWithAllZero(true);
            for(unsigned int x=0; x<m_numberOfColumns; x++)
            {
                if(isRowWithAllZero && !mathHelper::isConsideredEqual(m_matrixData.at(getMatrixIndex(x, y)), static_cast<DataType>(0)))
                {
                    isRowWithAllZero = false;
                    break;
                }
            }
            if(!isRowWithNonZeroEncountered)
            {
                isRowWithNonZeroEncountered = !isRowWithAllZero;
            }
            if(isRowWithNonZeroEncountered && isRowWithAllZero)
            {
                //1. All rows consisting entirely of zeros, if any, are at the bottom of the matrix.
                return false;
            }
        }
        return true;
    }
    bool areLeadingEntriesInReducedRowEchelonForm() const
    {
        int currentLeadingEntryColumn(-1);
        for(unsigned int y=0; y<m_numberOfRows; y++)
        {
            for(unsigned int x=0; x<m_numberOfColumns; x++)
            {
                if(mathHelper::isConsideredEqual(m_matrixData.at(getMatrixIndex(x, y)), static_cast<DataType>(0))) {}
                else if(mathHelper::isConsideredEqual(m_matrixData.at(getMatrixIndex(x, y)), static_cast<DataType>(1)))
                {
                    if(currentLeadingEntryColumn < static_cast<int>(x))
                    {
                        for(unsigned int yZeroCheck=0; yZeroCheck<m_numberOfRows; yZeroCheck++)
                        {
                            if(yZeroCheck!=y && !mathHelper::isConsideredEqual(m_matrixData.at(getMatrixIndex(x, yZeroCheck)), static_cast<DataType>(0)))
                            {
                                //4. If a column contains a leading entry of some row, then all other entries in that column are zero
                                return false;
                            }
                        }
                    }
                    else
                    {
                        //3. If rows i and i+1 are two successive rows that do not consist entirely of zeros, then the leading entry of row i+1 is to the right of the leading entry of row i.
                        return false;
                    }
                    currentLeadingEntryColumn = static_cast<int>(x);
                    break;
                }
                else
                {
                    //2. By reading from left to right, the first nonzero entry in each row that does not consist entirely of zeros is a 1, called the leading entry of its row.
                    return false;
                }
            }
        }
        return true;
    }
    unsigned int getMatrixIndex(unsigned int const x, unsigned int const y) const
    {
        return getMatrixIndex(x, y, m_numberOfColumns);    }
    unsigned int getMatrixIndex(unsigned int const x, unsigned int const y, unsigned int const numberOfColumns) const
    {
        return (y*numberOfColumns)+x;
    }
    unsigned int m_numberOfColumns;
    unsigned int m_numberOfRows;
    MatrixData m_matrixData;
};
}//namespace alba