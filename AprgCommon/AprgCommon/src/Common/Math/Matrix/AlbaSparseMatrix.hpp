#pragma once

#include <Common/String/AlbaStringHelper.hpp>
#include <Common/User/DisplayTable.hpp>

#include <cassert>
#include <functional>
#include <set>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace alba::matrix {

template <typename DataType>
bool isEqualForMathMatrixDataType(DataType const& value1, DataType const& value2);

template <typename DataType>
class AlbaSparseMatrix {
public:
    using MatrixData = std::unordered_map<size_t, DataType>;
    using ListedMatrixData = std::vector<DataType>;
    using UniqueIndexes = std::set<size_t>;
    using UnaryFunction = std::function<DataType(DataType const&)>;
    using BinaryFunction = std::function<DataType(DataType const&, DataType const&)>;

    AlbaSparseMatrix() : m_numberOfColumns(0), m_numberOfRows(0) {}

    AlbaSparseMatrix(size_t const numberOfColumns, size_t const numberOfRows)
        : m_numberOfColumns(numberOfColumns), m_numberOfRows(numberOfRows), m_matrixData() {}

    AlbaSparseMatrix(size_t const numberOfColumns, size_t const numberOfRows, ListedMatrixData const& matrixData)
        : m_numberOfColumns(numberOfColumns), m_numberOfRows(numberOfRows), m_matrixData() {
        setEntries(matrixData);
    }

    // rule of zero

    bool operator==(AlbaSparseMatrix const& secondMatrix) const {
        bool isEqual(true);
        if (m_numberOfColumns != secondMatrix.m_numberOfColumns) {
            isEqual = false;
        } else if (m_numberOfRows != secondMatrix.m_numberOfRows) {
            isEqual = false;
        } else if (m_matrixData != secondMatrix.m_matrixData) {
            UniqueIndexes allIndexes(getAllIndexes(m_matrixData, secondMatrix.m_matrixData));
            for (size_t const index : allIndexes) {
                if (getEntry(index) != secondMatrix.getEntry(index)) {
                    isEqual = false;
                    break;
                }
            }
        }
        return isEqual;
    }

    bool operator!=(AlbaSparseMatrix const& secondMatrix) const { return !operator==(secondMatrix); }

    AlbaSparseMatrix operator+(AlbaSparseMatrix const& secondMatrix) const {
        assert(
            (m_numberOfColumns == secondMatrix.m_numberOfColumns) && (m_numberOfRows == secondMatrix.m_numberOfRows));
        return doBinaryOperation(*this, secondMatrix, BinaryFunction(std::plus<DataType>()));
    }

    AlbaSparseMatrix operator-(AlbaSparseMatrix const& secondMatrix) const {
        assert(
            (m_numberOfColumns == secondMatrix.m_numberOfColumns) && (m_numberOfRows == secondMatrix.m_numberOfRows));
        return doBinaryOperation(*this, secondMatrix, BinaryFunction(std::minus<DataType>()));
    }

    AlbaSparseMatrix operator*(DataType const& scalarMultiplier) const  // scalar multiplication
    {
        return doUnaryOperation(*this, [&scalarMultiplier](DataType const& data) { return scalarMultiplier * data; });
    }

    AlbaSparseMatrix operator*(AlbaSparseMatrix const& secondMatrix) const  // matrix multiplication
    {
        assert(m_numberOfColumns == secondMatrix.m_numberOfRows);
        size_t size(std::min(m_numberOfColumns, secondMatrix.m_numberOfRows));
        AlbaSparseMatrix result(m_numberOfRows, secondMatrix.m_numberOfColumns);
        for (size_t y = 0; y < m_numberOfRows; y++) {
            for (size_t x = 0; x < secondMatrix.m_numberOfColumns; x++) {
                DataType cellValue{};
                for (size_t k = 0; k < size; k++) {
                    cellValue += getEntry(k, y) * secondMatrix.getEntry(x, k);
                }
                result.setEntry(x, y, cellValue);
            }
        }
        return result;
    }

    size_t getNumberOfColumns() const { return m_numberOfColumns; }

    size_t getNumberOfRows() const { return m_numberOfRows; }

    size_t getMatrixIndex(size_t const x, size_t const y) const { return getMatrixIndex(x, y, m_numberOfColumns); }

    DataType getEntry(size_t const x, size_t const y) const {
        assert((x < m_numberOfColumns) && (y < m_numberOfRows));
        return getEntry(getMatrixIndex(x, y));
    }

    MatrixData const& getMatrixData() const { return m_matrixData; }

    DataType& getEntryReference(size_t const x, size_t const y) {
        assert((x < m_numberOfColumns) && (y < m_numberOfRows));
        return m_matrixData.at(getMatrixIndex(x, y));
    }

    void setEntry(size_t const x, size_t const y, DataType const& value) {
        assert((x < m_numberOfColumns) && (y < m_numberOfRows));
        m_matrixData[getMatrixIndex(x, y)] = value;
    }

    void setEntries(ListedMatrixData const& dataSampleValues) {
        size_t limit = std::min<size_t>(dataSampleValues.size(), m_numberOfColumns * m_numberOfRows);
        for (size_t i = 0; i < limit; i++) {
            if (!isEqualForMathMatrixDataType(dataSampleValues.at(i), static_cast<DataType>(0))) {
                m_matrixData[i] = dataSampleValues.at(i);
            }
        }
    }

    void clearAndResize(size_t const numberOfColumns, size_t const numberOfRows) {
        m_numberOfColumns = numberOfColumns;
        m_numberOfRows = numberOfRows;
        m_matrixData.clear();
    }

    void negate() {
        for (auto& [index, value] : m_matrixData) {
            value *= -1;
        }
    }

    void transpose() {
        MatrixData newMatrixData;
        for (auto const& [index, value] : m_matrixData) {
            newMatrixData.try_emplace(getTranposeIndex(index), value);
        }
        clearAndResize(m_numberOfRows, m_numberOfColumns);
        m_matrixData = newMatrixData;
    }

private:
    size_t getMatrixIndex(size_t const x, size_t const y, size_t const numberOfColumns) const {
        return (y * numberOfColumns) + x;
    }

    size_t getTranposeIndex(size_t const index) const {
        return getMatrixIndex(index / m_numberOfColumns, index % m_numberOfColumns, m_numberOfRows);
    }

    DataType getEntry(size_t const index) const {
        DataType result{};
        auto it = m_matrixData.find(index);
        if (it != m_matrixData.cend()) {
            result = it->second;
        }
        return result;
    }

    UniqueIndexes getAllIndexes(MatrixData const& data1, MatrixData const& data2) const {
        UniqueIndexes result;
        for (auto const& [index, value] : data1) {
            result.emplace(index);
        }
        for (auto const& [index, value] : data2) {
            result.emplace(index);
        }
        return result;
    }

    AlbaSparseMatrix doUnaryOperation(AlbaSparseMatrix const& inputMatrix, UnaryFunction const& unaryFunction) const {
        AlbaSparseMatrix resultMatrix(inputMatrix.getNumberOfColumns(), inputMatrix.getNumberOfRows());
        for (auto const& [index, value] : m_matrixData) {
            resultMatrix.m_matrixData[index] = unaryFunction(value);
        }
        return resultMatrix;
    }

    AlbaSparseMatrix doBinaryOperation(
        AlbaSparseMatrix const& firstMatrix, AlbaSparseMatrix const& secondMatrix,
        BinaryFunction const& binaryFunction) const {
        assert(
            (firstMatrix.getNumberOfColumns() == secondMatrix.getNumberOfColumns()) &&
            (firstMatrix.getNumberOfRows() == secondMatrix.getNumberOfRows()));
        AlbaSparseMatrix resultMatrix(firstMatrix.getNumberOfColumns(), firstMatrix.getNumberOfRows());
        UniqueIndexes allIndexes(getAllIndexes(m_matrixData, secondMatrix.m_matrixData));
        for (size_t const index : allIndexes) {
            resultMatrix.m_matrixData[index] =
                binaryFunction(firstMatrix.getEntry(index), secondMatrix.getEntry(index));
        }
        return resultMatrix;
    }

    friend std::ostream& operator<<(std::ostream& out, AlbaSparseMatrix<DataType> const& matrix) {
        DisplayTable table;
        table.setBorders("-", "|");
        for (size_t y = 0; y < matrix.m_numberOfRows; y++) {
            table.addRow();
            for (size_t x = 0; x < matrix.m_numberOfColumns; x++) {
                table.getLastRow().addCell(alba::stringHelper::convertToString(matrix.getEntry(x, y)));
            }
        }

        out << "Matrix output:\n" << table;
        return out;
    }

    size_t m_numberOfColumns;
    size_t m_numberOfRows;
    MatrixData m_matrixData;
};

}  // namespace alba::matrix
