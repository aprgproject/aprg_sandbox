#pragma once

#include <functional>
#include <vector>

namespace alba
{

namespace matrix
{

template <typename DataType> using AlbaMatrixData = std::vector<DataType>;
template <typename DataType> using ListOfAlbaMatrixData = std::vector<AlbaMatrixData<DataType>>;
template <typename DataType> using BoolUnaryFunction = std::function<bool(DataType const&)>;
template <typename DataType> using UnaryFunction = std::function<DataType(DataType const&)>;
template <typename DataType> using BinaryFunction = std::function<DataType(DataType const&, DataType const&)>;
template <typename DataType> class AlbaMatrix;
}

}//namespace alba