#pragma once

#include <Common/Container/AlbaValueRange.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/Math/Matrix/AlbaMatrixDataTypes.hpp>
#include <Common/Math/Matrix/Utilities/AlbaMatrixUtilities.hpp>
#include <Common/Math/Matrix/Utilities/GaussJordanReduction.hpp>#include <Common/User/DisplayTable.hpp>

#include <cassert>
#include <functional>#include <sstream>

namespace alba
{

namespace matrix
{

template <typename DataType> bool isEqualForMathMatrixDataType(DataType const& value1, DataType const& value2);
template <typename DataType> AlbaMatrix<DataType> getIdentityMatrix(unsigned int const sideSize);

template <typename DataType>
class AlbaMatrix{
public:
    using MatrixData = AlbaMatrixData<DataType>;
    using ListOfMatrixData = ListOfAlbaMatrixData<DataType>;    using LoopFunction = std::function<void(unsigned int const x, unsigned int const y)>;
    using LoopWithValueFunction = std::function<void(unsigned int const x, unsigned int const y, DataType const& value)>;
    using MatrixIndexRange = AlbaValueRange<unsigned int>;

    // Do we have to make rows and columns as template parameter? No, its better to have this on runtime because matrix can have different dimensions on applications.
    AlbaMatrix()
        : m_numberOfColumns(0)
        , m_numberOfRows(0)
    {}

    AlbaMatrix(
            unsigned int const numberOfColumns,
            unsigned int const numberOfRows,
            DataType const initialValue={})
        : m_numberOfColumns(numberOfColumns)
        , m_numberOfRows(numberOfRows)
        , m_matrixData(numberOfColumns*numberOfRows, initialValue)
    {}

    AlbaMatrix(
            unsigned int const numberOfColumns,
            unsigned int const numberOfRows,
            MatrixData const& matrixData)
        : m_numberOfColumns(numberOfColumns)
        , m_numberOfRows(numberOfRows)
        , m_matrixData(
              matrixData.cbegin(),
              matrixData.cbegin() + std::min(static_cast<unsigned int>(matrixData.size()), numberOfColumns*numberOfRows))
    {
        fillRemainingEntriesToZeroIfNeeded(numberOfColumns, numberOfRows);
        m_matrixData.shrink_to_fit();
    }

    bool operator==(AlbaMatrix const& secondMatrix) const
    {
        bool isEqual(true);
        if(m_numberOfColumns != secondMatrix.m_numberOfColumns)
        {
            isEqual=false;
        }
        else if(m_numberOfRows != secondMatrix.m_numberOfRows)
        {
            isEqual=false;
        }
        else if(m_matrixData != secondMatrix.m_matrixData)
        {
            isEqual = std::equal(
                        m_matrixData.cbegin(),
                        m_matrixData.cend(),
                        secondMatrix.m_matrixData.cbegin(),
                        secondMatrix.m_matrixData.cend(),
                        [](DataType const& first, DataType const& second)
            {return isEqualForMathMatrixDataType(first, second);});
        }
        return isEqual;
    }

    bool operator!=(AlbaMatrix const& secondMatrix) const
    {
        return !operator==(secondMatrix);
    }

    AlbaMatrix operator+(AlbaMatrix const& secondMatrix) const
    {
        assert((m_numberOfColumns == secondMatrix.m_numberOfColumns) && (m_numberOfRows == secondMatrix.m_numberOfRows));
        return doBinaryOperationWithSameDimensions(*this, secondMatrix, BinaryFunction<DataType>(std::plus<DataType>()));
    }

    AlbaMatrix operator-(AlbaMatrix const& secondMatrix) const
    {
        assert((m_numberOfColumns == secondMatrix.m_numberOfColumns) && (m_numberOfRows == secondMatrix.m_numberOfRows));
        return doBinaryOperationWithSameDimensions(*this, secondMatrix, BinaryFunction<DataType>(std::minus<DataType>()));
    }

    AlbaMatrix operator*(DataType const& scalarMultiplier) const //scalar multiplication
    {
        std::function<DataType(DataType const&)> scalarMultiplication = std::bind(std::multiplies<DataType>(), std::placeholders::_1, scalarMultiplier);
        return doUnaryOperation(*this, scalarMultiplication);
    }

    AlbaMatrix operator*(AlbaMatrix const& secondMatrix) const //matrix multiplication
    {
        // Using a straightforward algorithm, we can calculate the product of two nxn matrices in O(n^3) time.
        // There are also more efficient algorithms for matrix multiplication,
        // but they are mostly of theoretical interest and such algorithms are not practical.

        assert(m_numberOfColumns == secondMatrix.m_numberOfRows);
        AlbaMatrix result(m_numberOfRows, secondMatrix.m_numberOfColumns);
        ListOfMatrixData rowsOfFirstMatrix;        ListOfMatrixData columnsOfSecondMatrix;
        retrieveRows(rowsOfFirstMatrix);
        secondMatrix.retrieveColumns(columnsOfSecondMatrix);
        unsigned int y=0;        for(MatrixData const& rowOfFirstMatrix : rowsOfFirstMatrix)
        {
            unsigned int x=0;
            for(MatrixData const& columnOfSecondMatrix : columnsOfSecondMatrix)
            {
                result.setEntry(x, y, multiplyEachItemAndGetSum(rowOfFirstMatrix, columnOfSecondMatrix));
                x++;
            }
            y++;
        }
        return result;
    }

    AlbaMatrix& operator+=(AlbaMatrix const& secondMatrix)
    {
        doBinaryAssignmentOperationWithSameDimensions(*this, secondMatrix, BinaryFunction<DataType>(std::plus<DataType>()));
        return *this;
    }

    AlbaMatrix& operator-=(AlbaMatrix const& secondMatrix)
    {
        doBinaryAssignmentOperationWithSameDimensions(*this, secondMatrix, BinaryFunction<DataType>(std::minus<DataType>()));
        return *this;
    }

    AlbaMatrix& operator*=(DataType const& scalarMultiplier)
    {
        std::function<DataType(DataType const&)> scalarMultiplication = std::bind(std::multiplies<DataType>(), std::placeholders::_1, scalarMultiplier);
        doUnaryAssignmentOperation(*this, scalarMultiplication);
        return *this;
    }

    AlbaMatrix& operator*=(AlbaMatrix const& secondMatrix)
    {
        AlbaMatrix & self(*this);
        self = self * secondMatrix;
        return self;
    }

    bool isInside(unsigned int const x, unsigned int const y) const
    {
        return (x < m_numberOfColumns) && (y < m_numberOfRows);    }

    unsigned int getNumberOfColumns() const
    {
        return m_numberOfColumns;    }

    unsigned int getNumberOfRows() const
    {
        return m_numberOfRows;
    }

    unsigned int getNumberOfCells() const
    {
        return m_numberOfColumns*m_numberOfRows;
    }

    unsigned int getMatrixIndex(unsigned int const x, unsigned int const y) const
    {
        return getMatrixIndex(x, y, m_numberOfColumns);
    }

    DataType getEntry(unsigned int const x, unsigned int const y) const
    {
        assert(isInside(x, y));
        return m_matrixData.at(getMatrixIndex(x, y));
    }

    DataType const& getEntryConstReference(unsigned int const x, unsigned int const y) const
    {
        assert(isInside(x, y));
        return m_matrixData.at(getMatrixIndex(x, y));
    }

    MatrixData const& getMatrixData() const
    {
        return m_matrixData;
    }

    std::string getString() const
    {
        DisplayTable table;
        table.setBorders("-","|");
        for(unsigned int y=0; y<m_numberOfRows; y++)
        {
            table.addRow();
            for(unsigned int x=0; x<m_numberOfColumns; x++)
            {
                std::stringstream ss;
                ss << getEntry(x, y);
                table.getLastRow().addCell(ss.str());
            }
        }
        std::string firstLine("Matrix output:\n");
        return firstLine + table.drawOutput();
    }

    void retrieveColumn(MatrixData & column, unsigned int const x) const
    {
        column.reserve(m_numberOfRows);
        for(unsigned int y=0; y<m_numberOfRows; y++)
        {
            column.emplace_back(getEntry(x, y));
        }
    }

    void retrieveRow(MatrixData & row, unsigned int const y) const
    {
        row.reserve(m_numberOfColumns);
        for(unsigned int x=0; x<m_numberOfColumns; x++)
        {
            row.emplace_back(getEntry(x, y));
        }
    }

    void retrieveColumns(ListOfMatrixData & columns) const
    {
        for(unsigned int x=0; x<m_numberOfColumns; x++)
        {
            columns.emplace_back();
            retrieveColumn(columns.back(), x);
        }
    }

    void retrieveRows(ListOfMatrixData & rows) const
    {
        for(unsigned int y=0; y<m_numberOfRows; y++)
        {
            rows.emplace_back();
            retrieveRow(rows.back(), y);
        }
    }

    void retrieveXAndYFromIndex(unsigned int& x, unsigned int& y, unsigned int index) const
    {
        x = index % m_numberOfColumns;
        y = index / m_numberOfColumns;
    }

    DataType & getEntryReference(unsigned int const x, unsigned int const y)
    {
        assert(isInside(x, y));
        return m_matrixData.at(getMatrixIndex(x, y));
    }

    void setEntry(unsigned int const x, unsigned int const y, DataType const& value)
    {
        assert(isInside(x, y));
        m_matrixData[getMatrixIndex(x, y)] = value;
    }

    void setEntries(MatrixData const& dataSampleValues)
    {
        unsigned int limit = std::min(m_matrixData.size(), dataSampleValues.size());
        std::copy(dataSampleValues.begin(), dataSampleValues.begin()+limit, m_matrixData.begin());
    }

    void setColumn(unsigned int const columnIndex, MatrixData const& dataSampleValues)
    {
        unsigned int limit = std::min(m_numberOfRows, static_cast<unsigned int>(dataSampleValues.size()));
        for(unsigned int y=0; y<limit; y++)
        {
            setEntry(columnIndex, y, dataSampleValues.at(y));
        }
    }

    void setRow(unsigned int const rowIndex, MatrixData const& dataSampleValues)
    {
        unsigned int limit = std::min(m_numberOfColumns, static_cast<unsigned int>(dataSampleValues.size()));
        for(unsigned int x=0; x<limit; x++)
        {
            setEntry(x, rowIndex, dataSampleValues.at(x));
        }
    }

    void clearAndResize(unsigned int const numberOfColumns, unsigned int const numberOfRows, DataType const initialValue={})
    {
        m_numberOfColumns = numberOfColumns;
        m_numberOfRows = numberOfRows;
        m_matrixData.clear();
        m_matrixData.resize(numberOfColumns*numberOfRows, initialValue);
        m_matrixData.shrink_to_fit();
    }

    void negate()
    {
        for(DataType & value : m_matrixData)
        {
            value *= -1;
        }
    }

    void transpose()
    {
        unsigned int oldColumns(m_numberOfColumns);
        unsigned int oldRows(m_numberOfRows);
        MatrixData oldMatrixData(m_matrixData);
        clearAndResize(oldRows, oldColumns);
        MatrixIndexRange yRange(0, oldRows-1, 1);
        MatrixIndexRange xRange(0, oldColumns-1, 1);
        iterateThroughYAndThenXWithRanges(yRange, xRange, [&](unsigned int const x, unsigned int const y)
        {
            m_matrixData[getMatrixIndex(y, x)] = oldMatrixData[getMatrixIndex(x, y, oldColumns)];
        });
    }

    void invert()
    {
        assert((m_numberOfColumns == m_numberOfRows));
        unsigned int newColumns = m_numberOfColumns*2;
        AlbaMatrix tempMatrix(newColumns, m_numberOfRows);
        iterateAllThroughYAndThenX([&](unsigned int const x, unsigned int const y)
        {
            tempMatrix.m_matrixData[getMatrixIndex(x, y, newColumns)] = getEntry(x, y);
        });
        unsigned int minValueForDiagonal = std::min(m_numberOfColumns, m_numberOfRows);
        for(unsigned int d=0; d<minValueForDiagonal; d++)
        {
            tempMatrix.m_matrixData[getMatrixIndex(m_numberOfColumns+d, d, newColumns)] = 1;
        }
        transformToReducedEchelonFormUsingGaussJordanReduction(tempMatrix);
        iterateAllThroughYAndThenX([&](unsigned int const x, unsigned int const y)
        {
            m_matrixData[getMatrixIndex(x, y)] = tempMatrix.m_matrixData.at(getMatrixIndex(m_numberOfColumns+x, y, newColumns));
        });
    }

    void raiseToScalarPower(unsigned int const exponent)
    {
        assert((m_numberOfColumns == m_numberOfRows));

        AlbaMatrix result(getIdentityMatrix<DataType>(m_numberOfColumns));
        AlbaMatrix newBase(*this);
        unsigned int newExponent(exponent);
        while(newExponent > 0)
        {
            if(mathHelper::isEven(newExponent))
            {
                newBase *= newBase;
                newExponent /= 2;
            }
            else
            {
                result *= newBase;
                newExponent--;
            }
        }
        return result;
    }

    void iterateAllThroughYAndThenX(LoopFunction const& loopFunction) const
    {
        for(unsigned int y=0; y<m_numberOfRows; y++)        {
            for(unsigned int x=0; x<m_numberOfColumns; x++)
            {
                loopFunction(x, y);            }
        }
    }

    void iterateThroughYAndThenXWithRanges(
            MatrixIndexRange const& yRange,
            MatrixIndexRange const& xRange,
            LoopFunction const& loopFunction) const
    {
        yRange.traverse([&](unsigned int const yValue)
        {
            xRange.traverse([&](unsigned int const xValue)
            {
                loopFunction(xValue, yValue);
            });
        });
    }

    void iterateThroughXAndThenYWithRanges(
            MatrixIndexRange const& xRange,
            MatrixIndexRange const& yRange,
            LoopFunction const& loopFunction) const
    {
        xRange.traverse([&](unsigned int const xValue)
        {
            yRange.traverse([&](unsigned int const yValue)
            {
                loopFunction(xValue, yValue);
            });
        });
    }

private:

    unsigned int getMatrixIndex(unsigned int const x, unsigned int const y, unsigned int const numberOfColumns) const
    {
        return (y*numberOfColumns)+x;
    }

    DataType multiplyEachItemAndGetSum(MatrixData const& first, MatrixData const& second) const
    {
        DataType result{};
        unsigned int minSize = std::min(first.size(), second.size());
        for(unsigned int i=0; i<minSize; i++)
        {
            result+=first.at(i)*second.at(i);
        }
        return result;
    }

    void fillRemainingEntriesToZeroIfNeeded(
            unsigned int const numberOfColumns,
            unsigned int const numberOfRows)
    {
        unsigned int targetSize = numberOfColumns*numberOfRows;
        if(m_matrixData.size() != targetSize)
        {
            unsigned int originalSize = m_matrixData.size();
            m_matrixData.resize(targetSize);
            std::fill(m_matrixData.begin()+originalSize, m_matrixData.end(), DataType{});
        }
    }

    unsigned int m_numberOfColumns;
    unsigned int m_numberOfRows;
    MatrixData m_matrixData;
};

template <typename DataType>
std::ostream & operator<<(std::ostream & out, AlbaMatrix<DataType> const& matrix)
{
    out << matrix.getString();
    return out;
}

}

}//namespace alba
