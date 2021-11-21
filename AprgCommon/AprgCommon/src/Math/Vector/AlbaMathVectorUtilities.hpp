#pragma once

#include <Math/AlbaMathHelper.hpp>
#include <Math/Vector/AlbaMathVector.hpp>

#include <cmath>

namespace alba
{

template <typename DataType, unsigned int SIZE>
bool areVectorsPerpendicular(
        AlbaMathVector<DataType, SIZE> const& vector1,
        AlbaMathVector<DataType, SIZE> const& vector2)
{
    return mathHelper::isAlmostEqual(0, getDotProduct(vector1, vector2));
}

template <typename DataType, unsigned int SIZE>
bool areVectorsParallel(
        AlbaMathVector<DataType, SIZE> const& vector1,
        AlbaMathVector<DataType, SIZE> const& vector2)
{
    return mathHelper::isAlmostEqual(
                getDotProduct(vector1, vector2),
                vector1.getMagnitude() * vector2.getMagnitude());
}

// This is always true.
template <typename DataType, unsigned int SIZE>
bool isCauchySchwarzInequalitySatisfied(
        AlbaMathVector<DataType, SIZE> const& vector1,
        AlbaMathVector<DataType, SIZE> const& vector2)
{
    return getDotProduct(vector1, vector2) <= vector1.getMagnitude() * vector2.getMagnitude();
}

// This is always true.
template <typename DataType, unsigned int SIZE>
bool isTriangleInequalitySatisfied(
        AlbaMathVector<DataType, SIZE> const& vector1,
        AlbaMathVector<DataType, SIZE> const& vector2)
{
    return (vector1+vector2).getMagnitude() <= vector1.getMagnitude() + vector2.getMagnitude();
}

// This is always true.
template <typename DataType, unsigned int SIZE>
bool isDotProductEqualToProductOfMagnitudesWithCosineOfAngle(
        AlbaMathVector<DataType, SIZE> const& vector1,
        AlbaMathVector<DataType, SIZE> const& vector2)
{
    return mathHelper::isAlmostEqual(
                getDotProduct(vector1, vector2),
                (vector1.getMagnitude() * vector2.getMagnitude() * cos(getAngleBetweenTwoVectors(vector1, vector2))));
}

template <typename DataType, unsigned int SIZE>
AlbaMathVector<DataType, SIZE> createZeroVector()
{
    return AlbaMathVector<DataType, SIZE>();
}

template <typename DataType, unsigned int SIZE>
AlbaMathVector<DataType, SIZE> getUnitVector(
        AlbaMathVector<DataType, SIZE> const& vector)
{
    AlbaMathVector<DataType, SIZE> unitVector(vector);
    DataType magnitude(vector.getMagnitude());
    for(DataType & value : unitVector.getValuesReference())
    {
        value /= magnitude;
    }
    return unitVector;
}

template <typename DataType, unsigned int SIZE>
AlbaMathVector<DataType, SIZE> getVectorProjection(
        AlbaMathVector<DataType, SIZE> const& vectorToProjectTo,
        AlbaMathVector<DataType, SIZE> const& vectorToProjectFrom)
{
    DataType const multiplier = getDotProduct(vectorToProjectTo, vectorToProjectFrom)
            / (vectorToProjectTo.getMagnitude() * vectorToProjectTo.getMagnitude());
    return vectorToProjectTo * multiplier;
}

template <typename DataType, unsigned int SIZE>
DataType getDotProduct(
        AlbaMathVector<DataType, SIZE> const& vector1,
        AlbaMathVector<DataType, SIZE> const& vector2)
{
    DataType result(0);
    for(unsigned int i=0; i<SIZE; i++)
    {
        result += vector1.getValueAt(i) * vector2.getValueAt(i);
    }
    return result;
}

template <typename DataType>
AlbaMathVector<DataType, 3> getCrossProduct(
        AlbaMathVector<DataType, 3> const& vector1,
        AlbaMathVector<DataType, 3> const& vector2)
{
    return AlbaMathVector<DataType, 3>{
                vector1.getValueAt(1)*vector2.getValueAt(2) - vector1.getValueAt(2)*vector2.getValueAt(1),
                vector1.getValueAt(2)*vector2.getValueAt(0) - vector1.getValueAt(0)*vector2.getValueAt(2),
                vector1.getValueAt(0)*vector2.getValueAt(1) - vector1.getValueAt(1)*vector2.getValueAt(0)};
}

template <typename DataType, unsigned int SIZE>
DataType getAngleBetweenTwoVectors(
        AlbaMathVector<DataType, SIZE> const& vector1,        AlbaMathVector<DataType, SIZE> const& vector2)
{
    return acos(getDotProduct(vector1, vector2) / (vector1.getMagnitude() * vector2.getMagnitude()));
}
template <typename DataType, unsigned int SIZE>
DataType getScalarProjection(
        AlbaMathVector<DataType, SIZE> const& vectorToProjectTo,
        AlbaMathVector<DataType, SIZE> const& vectorToProjectFrom)
{
    return getDotProduct(vectorToProjectTo, vectorToProjectFrom) / vectorToProjectTo.getMagnitude();
}

}
