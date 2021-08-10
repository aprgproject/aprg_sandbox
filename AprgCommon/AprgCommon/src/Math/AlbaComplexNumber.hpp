#pragma once

#include <string>

namespace alba
{

template <typename DataType>
class AlbaComplexNumber
{
public:
    AlbaComplexNumber();
    AlbaComplexNumber(
            DataType const realPart,
            DataType const imaginaryPart);

    bool operator==(AlbaComplexNumber const& second) const;
    AlbaComplexNumber<DataType> operator+(AlbaComplexNumber const& second) const;
    AlbaComplexNumber<DataType> operator-(AlbaComplexNumber const& second) const;
    AlbaComplexNumber<DataType> operator*(AlbaComplexNumber const& second) const;
    AlbaComplexNumber<DataType> operator/(AlbaComplexNumber const& second) const;
    DataType getRealPart() const;
    DataType getImaginaryPart() const;
    DataType getModulus() const;
    DataType getModulusSquared() const;
    AlbaComplexNumber<DataType> getConjugate() const;
    std::string getDisplayableString() const;

private:
    DataType getRealPartInMultiplication(
            DataType const firstRealPart,
            DataType const firstImaginaryPart,
            DataType const secondRealPart,
            DataType const secondImaginaryPart) const;
    DataType getImaginaryPartInMultiplication(
            DataType const firstRealPart,
            DataType const firstImaginaryPart,
            DataType const secondRealPart,
            DataType const secondImaginaryPart) const;
    DataType getRealPartInDivision(
            DataType const firstRealPart,
            DataType const firstImaginaryPart,
            DataType const secondRealPart,
            DataType const secondImaginaryPart) const;
    DataType getImaginaryPartInDivision(
            DataType const firstRealPart,
            DataType const firstImaginaryPart,
            DataType const secondRealPart,
            DataType const secondImaginaryPart) const;

    DataType m_realPart;
    DataType m_imaginaryPart;
};

template <typename DataType>
std::ostream & operator<<(std::ostream & out, AlbaComplexNumber<DataType> const& complexNumber);

}
