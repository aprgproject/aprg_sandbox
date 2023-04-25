#include "ComplexNumberHelpers.hpp"

using namespace std;

namespace alba
{
namespace mathHelper
{
template <typename NumberType>
AlbaNumber createNumberFromComplexNumber(AlbaComplexNumber<NumberType> const& complexNumber)
{
    return AlbaNumber::createComplexNumber(complexNumber.getRealPart(), complexNumber.getImaginaryPart());
}
template AlbaNumber createNumberFromComplexNumber<double>(AlbaComplexNumber<double> const& value);

void saveToComplexNumberData(AlbaNumber::ComplexNumberData& data, AlbaComplexNumber<float> const& number)
{
    data.realPart = number.getRealPart();
    data.imaginaryPart = number.getImaginaryPart();
}

}  // namespace mathHelper

}  // namespace alba
