#pragma once

#include <Common/Container/AlbaValueRange.hpp>
#include <Common/Math/AlbaMathHelper.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/User/DisplayTable.hpp>

#include <algorithm>
#include <cassert>
#include <functional>
#include <sstream>
#include <vector>

//this is done, but refactor this code, extract till you drop! -> maybe create a helper function
//next stop determinants vectors vector spaces
//This is based on "Introductory Linear Algebra with Applications"

namespace alba
{

template <typename DataType>
class AlbaMatrix
{
public:
    using MatrixData = std::vector<DataType>;
    using ListOfMatrixData = std::vector<MatrixData>;
    using BinaryFunction = std::function<DataType(DataType const&, DataType const&)>;
    using UnaryFunction = std::function<DataType(DataType const&)>;
    using LoopFunction = std::function<void(unsigned int const x, unsigned int const y)>;
    using LoopWithValueFunction = std::function<void(unsigned int const x, unsigned int const y,DataType const& value)>;
    using MatrixIndexRange = AlbaValueRange<unsigned int>;

    AlbaMatrix()
        : m_numberOfColumns(0) // can we make this as template parameter?
        , m_numberOfRows(0)
    {}

    AlbaMatrix(
            unsigned int const numberOfColumns,
            unsigned int const numberOfRows)
        : m_numberOfColumns(numberOfColumns)
        , m_numberOfRows(numberOfRows)
        , m_matrixData(numberOfColumns*numberOfRows, 0)
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
            {
                    return mathHelper::isAlmostEqual(first, second);
        });
        }
        return isEqual;
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
        assert(m_numberOfColumns == secondMatrix.m_numberOfRows);
        AlbaMatrix result(m_numberOfRows, secondMatrix.m_numberOfColumns);
        ListOfMatrixData rowsOfFirstMatrix;
        ListOfMatrixData columnsOfSecondMatrix;
        retrieveRows(rowsOfFirstMatrix);
        secondMatrix.retrieveColumns(columnsOfSecondMatrix);
        unsigned int y=0;
        for(MatrixData const& rowOfFirstMatrix : rowsOfFirstMatrix)
        {
            unsigned int x=0;
            for(MatrixData const& columnOfSecondMatrix : columnsOfSecondMatrix)
            {
                result.setEntry(x,y,multiplyEachItemAndGetSum(rowOfFirstMatrix, columnOfSecondMatrix));
                x++;
            }
            y++;
        }
        return result;
    }

    bool isSquare() const
    {
        return m_numberOfColumns == m_numberOfRows;
    }

    bool isZeroMatrix() const
    {
        return std::all_of(m_matrixData.cbegin(), m_matrixData.cend(), [](DataType const& data)
        {
            return mathHelper::isAlmostEqual(data, static_cast<DataType>(0));
        });
    }

    bool isIdentityMatrix() const
    {
        bool isIdentityMatrix(m_numberOfColumns==m_numberOfRows);
        for(unsigned int y=0; isIdentityMatrix && y<m_numberOfRows; y++)
        {
            for(unsigned int x=0; isIdentityMatrix && x<m_numberOfColumns; x++)
            {
                if(x==y)
                {
                    isIdentityMatrix = isIdentityMatrix && getEntry(x, y) == 1;
                }
                else
                {
                    isIdentityMatrix = isIdentityMatrix && getEntry(x, y) == 0;
                }
            }
        }
        return isIdentityMatrix;
    }

    bool isSingular() const // means the its non invertible
    {
        auto inverseOfInverse = *this;
        inverseOfInverse.invert();
        inverseOfInverse.invert();
        return !(*this == inverseOfInverse);
    }

    bool isReducedRowEchelonForm() const
    {
        return areRowsWithAllZeroInTheBottom() && areLeadingEntriesInReducedRowEchelonForm();
    }

    unsigned int getColumns() const
    {
        return m_numberOfColumns;
    }

    unsigned int getRows() const
    {
        return m_numberOfRows;
    }

    unsigned int getMatrixIndex(unsigned int const x, unsigned int const y) const
    {
        return getMatrixIndex(x, y, m_numberOfColumns);
    }

    DataType getDeterminant() const
    {
        assert(m_numberOfColumns == m_numberOfRows);
        DataType determinant(0);

        if(m_numberOfColumns==1)
        {
            determinant = getEntry(0,0);
        }
        else if(m_numberOfColumns==2)
        {
            determinant = getEntry(0,0)*getEntry(1,1) - getEntry(0,1)*getEntry(1,0);
        }
        else
        {
            determinant = getDeterminantWhenSideIsMoreThan2();
        }
        return determinant;
    }

    DataType getValueUsingCramerRule(
            unsigned int const columnIndex,
            MatrixData const& newColumnValues) const
    {
        assert(m_numberOfColumns == m_numberOfRows);
        AlbaMatrix matrixWithNewColumn(*this);
        matrixWithNewColumn.setColumn(columnIndex, newColumnValues);
        return matrixWithNewColumn.getDeterminant()/getDeterminant();
    }

    DataType getEntry(unsigned int const x, unsigned int const y) const
    {
        assert((x < m_numberOfColumns) && (y < m_numberOfRows));
        return m_matrixData.at(getMatrixIndex(x, y));
    }

    MatrixData const& getMatrixData() const
    {
        return m_matrixData;
    }

    AlbaMatrix getMatrixWithOneColumnAndOneRowRemoved(
            unsigned int const columnIndex,
            unsigned int const rowIndex) const
    {
        assert((columnIndex < m_numberOfColumns) && (rowIndex < m_numberOfRows));
        AlbaMatrix result(m_numberOfColumns-1, m_numberOfRows-1);
        iterateAllThroughYAndThenX([&](unsigned int const x, unsigned int const y)
        {
            if(columnIndex != x && rowIndex != y)
            {
                unsigned int newX = (x >= columnIndex) ? x-1 : x;
                unsigned int newY = (y >= rowIndex) ? y-1 : y;
                result.setEntry(newX, newY, getEntry(x , y));
            }
        });
        return result;
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
                table.getLastRow().addCell(converter.convert(getEntry(x, y)));
            }
        }
        return table.drawOutput();
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

    void setEntry(unsigned int const x, unsigned int const y, DataType const& value)
    {
        assert((x < m_numberOfColumns) && (y < m_numberOfRows));
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

    void clearAndResize(unsigned int const numberOfColumns, unsigned int const numberOfRows)
    {
        m_numberOfColumns = numberOfColumns;
        m_numberOfRows = numberOfRows;
        m_matrixData.clear();
        m_matrixData.resize(numberOfColumns*numberOfRows, 0);
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
        tempMatrix.transformToReducedEchelonFormUsingGaussJordanReduction();
        iterateAllThroughYAndThenX([&](unsigned int const x, unsigned int const y)
        {
            m_matrixData[getMatrixIndex(x, y)] = tempMatrix.m_matrixData.at(getMatrixIndex(m_numberOfColumns+x, y, newColumns));
        });
    }

    void transformToReducedEchelonFormUsingGaussJordanReduction()
    {
        unsigned int yWithLeadingEntry = 0;
        for(unsigned int x=0; x<m_numberOfColumns; x++)
        {
            for(unsigned int y=yWithLeadingEntry; y<m_numberOfRows; y++)
            {
                if(!mathHelper::isAlmostEqual(getEntry(x, y), static_cast<DataType>(0)))
                {
                    interchangeRows(y, yWithLeadingEntry);
                    multiplyValueInRowAndPutProductInAnotherRow(
                                yWithLeadingEntry,
                                static_cast<DataType>(1)/getEntry(x, yWithLeadingEntry),
                                yWithLeadingEntry);
                    for(unsigned int yToZero=0; yToZero<m_numberOfRows; yToZero++)
                    {
                        if(yToZero != yWithLeadingEntry
                                && !mathHelper::isAlmostEqual(getEntry(x, yToZero), static_cast<DataType>(0)))
                        {
                            subtractRowsWithMultiplierPutDifferenceInAnotherRow(
                                        yToZero,
                                        yWithLeadingEntry,
                                        getEntry(x, yToZero)/getEntry(x, yWithLeadingEntry),
                                        yToZero);
                        }
                    }
                    yWithLeadingEntry++;
                    break;
                }
            }
        }
    }

    void interchangeRows(unsigned int const y1, unsigned int const y2)
    {
        assert((y1 < m_numberOfRows) && (y2 < m_numberOfRows));
        for(unsigned int x=0; x<m_numberOfColumns; x++)
        {
            std::swap(m_matrixData[getMatrixIndex(x, y1)], m_matrixData[getMatrixIndex(x, y2)]);
        }
    }

    void addTwoRowsAndPutSumInAnotherRow(unsigned int const yInput1, unsigned int const yInput2, unsigned int const yOutput)
    {
        assert((yInput1 < m_numberOfRows) && (yInput2 < m_numberOfRows) && (yOutput < m_numberOfRows));
        traverseWithBinaryOperationForDifferentRows(yInput1, yInput2, yOutput, std::plus<DataType>());
    }

    void multiplyValueInRowAndPutProductInAnotherRow(unsigned int const yInput, DataType const& multiplierForInput, unsigned int const yOutput)
    {
        assert((yInput < m_numberOfRows) && (yOutput < m_numberOfRows));
        traverseWithUnaryOperationForDifferentRows(yInput, yOutput, [&](DataType const& input)
        {
            return input*multiplierForInput;
        });
    }

    void subtractRowsWithMultiplierPutDifferenceInAnotherRow(unsigned int const yInput1, unsigned int const yInput2, DataType const& multiplierForInput2, unsigned int const yOutput)
    {
        assert((yInput1 < m_numberOfRows) && (yInput2 < m_numberOfRows) && (yOutput < m_numberOfRows));
        traverseWithBinaryOperationForDifferentRows(yInput1, yInput2, yOutput, [&](DataType const& input1, DataType const& input2)
        {
            return input1-(input2*multiplierForInput2);
        });
    }

private:
    bool areRowsWithAllZeroInTheBottom() const
    {
        bool isRowWithNonZeroEncountered(false);
        for(unsigned int yPlusOne=m_numberOfRows; yPlusOne>0; yPlusOne--)
        {
            unsigned int y(yPlusOne-1);
            bool isRowWithAllZero(true);
            for(unsigned int x=0; x<m_numberOfColumns; x++)
            {
                if(isRowWithAllZero && !mathHelper::isAlmostEqual(getEntry(x, y), static_cast<DataType>(0)))
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
                if(mathHelper::isAlmostEqual(getEntry(x, y), static_cast<DataType>(0))) {}
                else if(mathHelper::isAlmostEqual(getEntry(x, y), static_cast<DataType>(1)))
                {
                    if(currentLeadingEntryColumn < static_cast<int>(x))
                    {
                        for(unsigned int yZeroCheck=0; yZeroCheck<m_numberOfRows; yZeroCheck++)
                        {
                            if(yZeroCheck!=y && !mathHelper::isAlmostEqual(getEntry(x, yZeroCheck), static_cast<DataType>(0)))
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

    unsigned int getMatrixIndex(unsigned int const x, unsigned int const y, unsigned int const numberOfColumns) const
    {
        return (y*numberOfColumns)+x;
    }

    unsigned int getBestIndexForCoFactorExpansion(ListOfMatrixData const& rowsAndColumns) const
    {
        unsigned int i=0;
        unsigned int bestIndex=0;
        unsigned int highestNumberOfZeros=0;
        for(MatrixData const& rowOrColumn : rowsAndColumns)
        {
            unsigned int numberOfZeros = std::count_if(rowOrColumn.cbegin(), rowOrColumn.cend(), [](DataType const& value)
            {
                    return mathHelper::isAlmostEqual(value, 0);
        });
            if(highestNumberOfZeros < numberOfZeros)
            {
                highestNumberOfZeros = numberOfZeros;
                bestIndex = i;
            }
            i++;
        }

        return bestIndex;
    }

    DataType multiplyEachItemAndGetSum(MatrixData const& first, MatrixData const& second) const
    {
        DataType result(0);
        unsigned int minSize = std::min(first.size(), second.size());
        for(unsigned int i=0; i<minSize; i++)
        {
            result+=first.at(i)*second.at(i);
        }
        return result;
    }

    DataType getValueFromCoFactorExpansion(unsigned int x, unsigned int y) const
    {
        DataType value(0);
        DataType entry = getEntry(x,y);
        if(!mathHelper::isAlmostEqual(entry, 0))
        {
            int sign = mathHelper::isEven(x+y) ? 1 : -1;
            DataType subDeterminant = getMatrixWithOneColumnAndOneRowRemoved(x,y).getDeterminant();
            value = entry*subDeterminant*sign;
        }
        return value;
    }

    DataType getDeterminantWhenSideIsMoreThan2() const
    {
        DataType determinant(0);

        ListOfMatrixData rowsAndColumns;
        retrieveRows(rowsAndColumns);
        retrieveColumns(rowsAndColumns);

        unsigned int bestIndex(getBestIndexForCoFactorExpansion(rowsAndColumns));
        if(bestIndex < m_numberOfRows)
        {
            unsigned int y = bestIndex;
            for(unsigned int x=0; x<m_numberOfColumns; x++)
            {
                determinant += getValueFromCoFactorExpansion(x, y);
            }
        }
        else
        {
            unsigned int x = bestIndex-m_numberOfRows;
            for(unsigned int y=0; y<m_numberOfRows; y++)
            {
                determinant += getValueFromCoFactorExpansion(x, y);
            }
        }
        return determinant;
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
            std::fill(m_matrixData.begin()+originalSize, m_matrixData.end(), 0);
        }
    }

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
        iterateAllThroughYAndThenX([&](unsigned int const x, unsigned int const y)
        {
            resultMatrix.m_matrixData[getMatrixIndex(x, y)]
                    = binaryFunction(firstMatrix.getEntry(x, y),
                                     secondMatrix.getEntry(x, y));
        });
    }

    void traverseWithUnaryOperationWithSameDimensions(
            AlbaMatrix const& inputMatrix,
            AlbaMatrix & resultMatrix,
            UnaryFunction const& unaryFunction) const
    {
        assert((inputMatrix.m_numberOfColumns == resultMatrix.m_numberOfColumns) &&
               (inputMatrix.m_numberOfRows == resultMatrix.m_numberOfRows));
        iterateAllThroughYAndThenX([&](unsigned int const x, unsigned int const y)
        {
            resultMatrix.m_matrixData[getMatrixIndex(x, y)]
                    = unaryFunction(inputMatrix.getEntry(x, y));
        });
    }

    void traverseWithBinaryOperationForDifferentRows(
            unsigned int const yInput1,
            unsigned int const yInput2,
            unsigned int const yOutput,
            BinaryFunction const& binaryFunction)
    {
        assert((yInput1 < m_numberOfRows) && (yInput2 < m_numberOfRows) && (yOutput < m_numberOfRows));
        for(unsigned int x=0; x<m_numberOfColumns; x++)
        {
            m_matrixData[getMatrixIndex(x, yOutput)]
                    = binaryFunction(getEntry(x, yInput1),
                                     getEntry(x, yInput2));
        }
    }

    void traverseWithUnaryOperationForDifferentRows(
            unsigned int const yInput,
            unsigned int const yOutput,
            UnaryFunction const& unaryFunction)
    {
        assert((yInput < m_numberOfRows) && (yOutput < m_numberOfRows));
        for(unsigned int x=0; x<m_numberOfColumns; x++)
        {
            m_matrixData[getMatrixIndex(x, yOutput)]
                    = unaryFunction(getEntry(x, yInput));
        }
    }

    void iterateAllThroughYAndThenX(LoopFunction const& loopFunction) const
    {
        for(unsigned int y=0; y<m_numberOfRows; y++)
        {
            for(unsigned int x=0; x<m_numberOfColumns; x++)
            {
                loopFunction(x, y);
            }
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

}//namespace alba
