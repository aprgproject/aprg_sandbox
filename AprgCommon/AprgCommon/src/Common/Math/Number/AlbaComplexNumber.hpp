#pragma once

#include <Common/Types/AlbaTypeHelper.hpp>

#include <ostream>

namespace alba{

template <typename DataType>
class AlbaComplexNumber
{
public:

    static_assert(typeHelper::isArithmeticType<DataType>(), "DataType should be an arithmetic type.");

    AlbaComplexNumber();
    AlbaComplexNumber(
            DataType const realPart,
            DataType const imaginaryPart);

    // rule of zero

    bool operator==(AlbaComplexNumber const& second) const;
    AlbaComplexNumber<DataType> operator+(AlbaComplexNumber<DataType> const& second) const;
    AlbaComplexNumber<DataType> operator-(AlbaComplexNumber<DataType> const& second) const;    AlbaComplexNumber<DataType> operator+() const;
    AlbaComplexNumber<DataType> operator-() const;
    AlbaComplexNumber<DataType> operator*(AlbaComplexNumber<DataType> const& second) const;
    AlbaComplexNumber<DataType> operator/(AlbaComplexNumber<DataType> const& second) const;    AlbaComplexNumber<DataType> operator^(DataType const exponent) const;
    AlbaComplexNumber<DataType>& operator+=(AlbaComplexNumber<DataType> const& second);
    AlbaComplexNumber<DataType>& operator-=(AlbaComplexNumber<DataType> const& second);
    AlbaComplexNumber<DataType>& operator*=(AlbaComplexNumber<DataType> const& second);
    AlbaComplexNumber<DataType>& operator/=(AlbaComplexNumber<DataType> const& second);
    DataType getRealPart() const;
    DataType getImaginaryPart() const;
    DataType getModulus() const;
    DataType getModulusWithSignOfRealPart() const;
    DataType getModulusSquared() const;
    double getAngleInRadians() const;
    double getBestAngleInRaiseToPowerInRadians(DataType const exponent) const;
    AlbaComplexNumber<DataType> getConjugate() const;
    AlbaComplexNumber<DataType> getNthRoot(
            unsigned int const rootIndex,
            unsigned int const rootDegree) const;

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

    friend std::ostream & operator<<(std::ostream & out, AlbaComplexNumber<DataType> const& complexNumber)
    {
        out << "(" << complexNumber.m_realPart << " + " << complexNumber.m_imaginaryPart << "i)";
        return out;
    }

    DataType m_realPart;
    DataType m_imaginaryPart;
};

}
