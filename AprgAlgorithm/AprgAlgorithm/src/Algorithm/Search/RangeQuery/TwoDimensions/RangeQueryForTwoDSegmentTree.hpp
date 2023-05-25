#pragma once

#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithStaticSegmentTree.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

namespace alba {

namespace algorithm {

template <typename Value>
class RangeQueryForTwoDSegmentTree {
public:
    // A two-dimensional segment tree supports queries related to rectangular subarrays of a two-dimensional array.
    // Such a tree can be implemented as nested segment trees:
    // a big tree corresponds to the rows of the array, and each node contains a small tree that corresponds to a
    // column.

    // The operations of a two-dimensional segment tree take O(log(n)^2) time, because the big tree
    // and each small tree consist of O(log(n)) levels.
    // The tree requires O(n^2) memory, because each small tree contains O(n) values.

    using Index = int;
    using ValueMatrix = matrix::AlbaMatrix<Value>;
    using Values = typename ValueMatrix::MatrixData;
    using ListOfValues = typename ValueMatrix::ListOfMatrixData;
    using OneDSegmentTree = RangeQueryWithStaticSegmentTree<Values>;
    using OneDSegmentTrees = std::vector<OneDSegmentTree>;
    using TwoDSegmentTree = RangeQueryWithStaticSegmentTree<OneDSegmentTrees>;
    using OneDFunction = typename OneDSegmentTree::Function;
    using TwoDFunction = typename TwoDSegmentTree::Function;

    RangeQueryForTwoDSegmentTree(ValueMatrix const& valueMatrix, OneDFunction const& functionObject)
        : m_valueMatrix(valueMatrix),
          m_function(functionObject),
          m_twoDSegmentTree(createAllRowSegmentTrees(), getFunctionForSegmentTree2D()) {}

    Value getValueOn2DInterval(
        Index const topLeftX, Index const topLeftY, Index const bottomRightX, Index const bottomRightY) const {
        // Works on O(log(n)^2) time

        return m_twoDSegmentTree.getValueOnInterval(topLeftY, bottomRightY).getValueOnInterval(topLeftX, bottomRightX);
    }

    void changeValueAt(Index const x, Index const y, Value const& newValue) {
        m_valueMatrix.setEntry(x, y, newValue);
        m_twoDSegmentTree.changeValueAtIndex(y, createRowSegmentTree(y));
    }

private:
    OneDSegmentTree createRowSegmentTree(Index const y) const {
        Values row;
        m_valueMatrix.retrieveRow(row, y);
        return OneDSegmentTree(row, m_function);
    }

    OneDSegmentTrees createAllRowSegmentTrees() const {
        OneDSegmentTrees result;
        ListOfValues rows;
        m_valueMatrix.retrieveRows(rows);
        result.reserve(rows.size());
        for (Values const& row : rows) {
            result.emplace_back(row, m_function);
        }
        result.shrink_to_fit();
        return result;
    }

    TwoDFunction getFunctionForSegmentTree2D() const {
        return [&](OneDSegmentTree const& tree1, OneDSegmentTree const& tree2) {
            Values newValues;
            Values const& treeValues1(tree1.getTreeValues());
            Values const& treeValues2(tree2.getTreeValues());
            Index estimatedSize = std::min(
                treeValues1.size() - tree1.getStartOfChildren(), treeValues2.size() - tree2.getStartOfChildren());
            newValues.reserve(estimatedSize);
            for (Index i1 = tree1.getStartOfChildren(), i2 = tree2.getStartOfChildren();
                 i1 < static_cast<Index>(treeValues1.size()) && i2 < static_cast<Index>(treeValues2.size());
                 i1++, i2++) {
                newValues.emplace_back(m_function(treeValues1.at(i1), treeValues2.at(i2)));
            }
            newValues.shrink_to_fit();
            return OneDSegmentTree(newValues, m_function);
        };
    }

    ValueMatrix m_valueMatrix;
    OneDFunction m_function;
    TwoDSegmentTree m_twoDSegmentTree;
};

}  // namespace algorithm

}  // namespace alba
