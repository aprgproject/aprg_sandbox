#pragma once

#include <Common/Math/Number/AlbaNumber.hpp>

namespace alba::mathHelper {

template <typename NumberType>
AlbaNumber createNumberFromComplexNumber(AlbaComplexNumber<NumberType> const& number);
void saveToComplexNumberData(AlbaNumber::ComplexNumberData& data, AlbaComplexNumber<float> const& number);

}  // namespace alba::mathHelper
