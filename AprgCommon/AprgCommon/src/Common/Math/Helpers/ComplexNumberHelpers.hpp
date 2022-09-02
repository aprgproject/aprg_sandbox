#pragma once

#include <Common/Math/Number/AlbaNumber.hpp>

namespace alba
{

namespace mathHelper
{

template <typename NumberType> AlbaNumber createNumberFromComplexNumber(AlbaComplexNumber<NumberType> const& number);
void saveToComplexNumberData(AlbaNumber::ComplexNumberData & data, AlbaComplexNumber<float> const& number);

}//namespace mathHelper

}//namespace alba
