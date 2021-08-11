#include "AlbaComplexNumber.hpp"

#include <Math/AlbaMathHelper.hpp>

#include <sstream>

using namespace std;

namespace alba
{

template <typename DataType>
AlbaComplexNumber<DataType>::AlbaComplexNumber()
    : m_realPart(0)
    , m_imaginaryPart(0)
{}
template AlbaComplexNumber<double>::AlbaComplexNumber();


template <typename DataType>
AlbaComplexNumber<DataType>::AlbaComplexNumber(
        DataType const realPart,
        DataType const imaginaryPart)
    : m_realPart(realPart)
    , m_imaginaryPart(imaginaryPart)
{}
template AlbaComplexNumber<double>::AlbaComplexNumber(double const value1, double const value2);


template <typename DataType>
bool AlbaComplexNumber<DataType>::operator==(AlbaComplexNumber const& second) const
{
    return mathHelper::isAlmostEqual(m_realPart, second.m_realPart)
            && mathHelper::isAlmostEqual(m_imaginaryPart, second.m_imaginaryPart);
}
template bool AlbaComplexNumber<double>::operator==(AlbaComplexNumber const& second) const;


template <typename DataType>
AlbaComplexNumber<DataType> AlbaComplexNumber<DataType>::operator+(AlbaComplexNumber<DataType> const& second) const
{
    return AlbaComplexNumber<DataType>(
                m_realPart+second.m_realPart,
                m_imaginaryPart+second.m_imaginaryPart);
}
template AlbaComplexNumber<double> AlbaComplexNumber<double>::operator+(AlbaComplexNumber const& second) const;


template <typename DataType>
AlbaComplexNumber<DataType> AlbaComplexNumber<DataType>::operator-(AlbaComplexNumber<DataType> const& second) const
{
    return AlbaComplexNumber<DataType>(
                m_realPart-second.m_realPart,
                m_imaginaryPart-second.m_imaginaryPart);
}
template AlbaComplexNumber<double> AlbaComplexNumber<double>::operator-(AlbaComplexNumber const& second) const;


template <typename DataType>
AlbaComplexNumber<DataType> AlbaComplexNumber<DataType>::operator+() const
{
    return *this;
}
template AlbaComplexNumber<double> AlbaComplexNumber<double>::operator+() const;


template <typename DataType>
AlbaComplexNumber<DataType> AlbaComplexNumber<DataType>::operator-() const
{
    return AlbaComplexNumber<DataType>(-m_realPart, -m_imaginaryPart);
}
template AlbaComplexNumber<double> AlbaComplexNumber<double>::operator-() const;


template <typename DataType>
AlbaComplexNumber<DataType> AlbaComplexNumber<DataType>::operator*(AlbaComplexNumber<DataType> const& second) const
{
    return AlbaComplexNumber<DataType>(
                getRealPartInMultiplication(m_realPart, m_imaginaryPart, second.m_realPart, second.m_imaginaryPart),
                getImaginaryPartInMultiplication(m_realPart, m_imaginaryPart, second.m_realPart, second.m_imaginaryPart));
}
template AlbaComplexNumber<double> AlbaComplexNumber<double>::operator*(AlbaComplexNumber const& second) const;


template <typename DataType>
AlbaComplexNumber<DataType> AlbaComplexNumber<DataType>::operator/(AlbaComplexNumber<DataType> const& second) const
{
    DataType denominator(second.getModulusSquared());
    return AlbaComplexNumber<DataType>(
                getRealPartInDivision(m_realPart, m_imaginaryPart, second.m_realPart, second.m_imaginaryPart)/denominator,
                getImaginaryPartInDivision(m_realPart, m_imaginaryPart, second.m_realPart, second.m_imaginaryPart)/denominator);
}
template AlbaComplexNumber<double> AlbaComplexNumber<double>::operator/(AlbaComplexNumber const& second) const;


template <typename DataType>
AlbaComplexNumber<DataType>& AlbaComplexNumber<DataType>::operator+=(AlbaComplexNumber<DataType> const& second)
{
    m_realPart += second.m_realPart;
    m_imaginaryPart += second.m_imaginaryPart;
    return *this;
}
template AlbaComplexNumber<double>& AlbaComplexNumber<double>::operator+=(AlbaComplexNumber const& second);


template <typename DataType>
AlbaComplexNumber<DataType>& AlbaComplexNumber<DataType>::operator-=(AlbaComplexNumber<DataType> const& second)
{
    m_realPart -= second.m_realPart;
    m_imaginaryPart -= second.m_imaginaryPart;
    return *this;
}
template AlbaComplexNumber<double>& AlbaComplexNumber<double>::operator-=(AlbaComplexNumber const& second);


template <typename DataType>
AlbaComplexNumber<DataType>& AlbaComplexNumber<DataType>::operator*=(AlbaComplexNumber<DataType> const& second)
{
    DataType realPart = getRealPartInMultiplication(m_realPart, m_imaginaryPart, second.m_realPart, second.m_imaginaryPart);
    DataType imaginaryPart = getImaginaryPartInMultiplication(m_realPart, m_imaginaryPart, second.m_realPart, second.m_imaginaryPart);
    m_realPart = realPart;
    m_imaginaryPart = imaginaryPart;
    return *this;
}
template AlbaComplexNumber<double>& AlbaComplexNumber<double>::operator*=(AlbaComplexNumber const& second);


template <typename DataType>
AlbaComplexNumber<DataType>& AlbaComplexNumber<DataType>::operator/=(AlbaComplexNumber<DataType> const& second)
{
    DataType denominator(second.getModulusSquared());
    DataType realPart = getRealPartInDivision(m_realPart, m_imaginaryPart, second.m_realPart, second.m_imaginaryPart)/denominator;
    DataType imaginaryPart = getImaginaryPartInDivision(m_realPart, m_imaginaryPart, second.m_realPart, second.m_imaginaryPart)/denominator;
    m_realPart = realPart;
    m_imaginaryPart = imaginaryPart;
    return *this;
}
template AlbaComplexNumber<double>& AlbaComplexNumber<double>::operator/=(AlbaComplexNumber const& second);


template <typename DataType>
DataType AlbaComplexNumber<DataType>::getRealPart() const
{
    return m_realPart;
}
template double AlbaComplexNumber<double>::getRealPart() const;


template <typename DataType>
DataType AlbaComplexNumber<DataType>::getImaginaryPart() const
{
    return m_imaginaryPart;
}
template double AlbaComplexNumber<double>::getImaginaryPart() const;


template <typename DataType>
DataType AlbaComplexNumber<DataType>::getModulus() const
{
    return mathHelper::getSquareRootOfXSquaredPlusYSquared(m_realPart, m_imaginaryPart);
}
template double AlbaComplexNumber<double>::getModulus() const;


template <typename DataType>
DataType AlbaComplexNumber<DataType>::getModulusSquared() const
{
    return mathHelper::getXSquaredPlusYSquared(m_realPart, m_imaginaryPart);
}
template double AlbaComplexNumber<double>::getModulusSquared() const;


template <typename DataType>
AlbaComplexNumber<DataType> AlbaComplexNumber<DataType>::getConjugate() const
{
    return AlbaComplexNumber<DataType>(m_realPart, -m_imaginaryPart);
}
template AlbaComplexNumber<double> AlbaComplexNumber<double>::getConjugate() const;


template <typename DataType>
string AlbaComplexNumber<DataType>::getDisplayableString() const
{
    stringstream ss;
    ss << "(" << m_realPart << " + " << m_imaginaryPart << "i)";
    return ss.str();
}
template string AlbaComplexNumber<double>::getDisplayableString() const;


template <typename DataType>
DataType AlbaComplexNumber<DataType>::getRealPartInMultiplication(
        DataType const firstRealPart,
        DataType const firstImaginaryPart,
        DataType const secondRealPart,
        DataType const secondImaginaryPart) const
{
    return firstRealPart*secondRealPart - firstImaginaryPart*secondImaginaryPart;
}
template double AlbaComplexNumber<double>::getRealPartInMultiplication(
        double const firstRealPart,
        double const firstImaginaryPart,
        double const secondRealPart,
        double const secondImaginaryPart) const;


template <typename DataType>
DataType AlbaComplexNumber<DataType>::getImaginaryPartInMultiplication(
        DataType const firstRealPart,
        DataType const firstImaginaryPart,
        DataType const secondRealPart,
        DataType const secondImaginaryPart) const
{
    return firstRealPart*secondImaginaryPart + firstImaginaryPart*secondRealPart;
}
template double AlbaComplexNumber<double>::getImaginaryPartInMultiplication(
        double const firstRealPart,
        double const firstImaginaryPart,
        double const secondRealPart,
        double const secondImaginaryPart) const;


template <typename DataType>
DataType AlbaComplexNumber<DataType>::getRealPartInDivision(
        DataType const firstRealPart,
        DataType const firstImaginaryPart,
        DataType const secondRealPart,
        DataType const secondImaginaryPart) const
{
    return firstRealPart*secondRealPart + firstImaginaryPart*secondImaginaryPart;
}
template double AlbaComplexNumber<double>::getRealPartInDivision(
        double const firstRealPart,
        double const firstImaginaryPart,
        double const secondRealPart,
        double const secondImaginaryPart) const;


template <typename DataType>
DataType AlbaComplexNumber<DataType>::getImaginaryPartInDivision(
        DataType const firstRealPart,
        DataType const firstImaginaryPart,
        DataType const secondRealPart,
        DataType const secondImaginaryPart) const
{
    return firstImaginaryPart*secondRealPart - firstRealPart*secondImaginaryPart;
}
template double AlbaComplexNumber<double>::getImaginaryPartInDivision(
        double const firstRealPart,
        double const firstImaginaryPart,
        double const secondRealPart,
        double const secondImaginaryPart) const;


template <typename DataType>
ostream & operator<<(ostream & out, AlbaComplexNumber<DataType> const& complexNumber)
{
    out << complexNumber.getDisplayableString();
    return out;
}
template ostream & operator<< <double>(ostream & out, AlbaComplexNumber<double> const& complexNumber);

}
