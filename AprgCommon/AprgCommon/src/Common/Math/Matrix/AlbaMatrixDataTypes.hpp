#pragma once

#include <vector>

namespace alba
{

template <typename DataType> using AlbaMatrixData = std::vector<DataType>;
template <typename DataType> using ListOfAlbaMatrixData = std::vector<AlbaMatrixData<DataType>>;

}//namespace alba
