#pragma once

#include <Common/Math/Angle/AlbaAngle.hpp>
#include <Common/Math/Vector/AlbaMathVector.hpp>

namespace alba
{

template <typename DataType>
bool isEqualForMathVectorDataType(DataType const& value1, DataType const& value2);

template <typename DataType, unsigned int SIZE>
bool areVectorsPerpendicular(
        AlbaMathVector<DataType, SIZE> const& vector1,
        AlbaMathVector<DataType, SIZE> const& vector2);

template <typename DataType, unsigned int SIZE>
bool areVectorsParallel(
        AlbaMathVector<DataType, SIZE> const& vector1,
        AlbaMathVector<DataType, SIZE> const& vector2);

// This is always true.
template <typename DataType, unsigned int SIZE>
bool isCauchySchwarzInequalitySatisfied(
        AlbaMathVector<DataType, SIZE> const& vector1,
        AlbaMathVector<DataType, SIZE> const& vector2);

// This is always true.
template <typename DataType, unsigned int SIZE>
bool isTriangleInequalitySatisfied(
        AlbaMathVector<DataType, SIZE> const& vector1,
        AlbaMathVector<DataType, SIZE> const& vector2);

// This is always true.
template <typename DataType, unsigned int SIZE>
bool isDotProductEqualToProductOfMagnitudesWithCosineOfAngle(
        AlbaMathVector<DataType, SIZE> const& vector1,
        AlbaMathVector<DataType, SIZE> const& vector2);

template <typename DataType, unsigned int SIZE>
AlbaMathVector<DataType, SIZE> createZeroVector();

template <typename DataType, unsigned int SIZE>
AlbaMathVector<DataType, SIZE> getUnitVector(
        AlbaMathVector<DataType, SIZE> const& vector);

template <typename DataType, unsigned int SIZE>
AlbaMathVector<DataType, SIZE> getVectorProjection(
        AlbaMathVector<DataType, SIZE> const& vectorToProjectTo,
        AlbaMathVector<DataType, SIZE> const& vectorToProjectFrom);

template <typename DataType, unsigned int SIZE>
DataType getDotProduct(
        AlbaMathVector<DataType, SIZE> const& vector1,
        AlbaMathVector<DataType, SIZE> const& vector2);

// cross product on 2D results in vector on the Z axis
template <typename DataType>
DataType getCrossProduct(
        AlbaMathVector<DataType, 2U> const& vector1,
        AlbaMathVector<DataType, 2U> const& vector2);

template <typename DataType>
AlbaMathVector<DataType, 3U> getCrossProduct(
        AlbaMathVector<DataType, 3U> const& vector1,
        AlbaMathVector<DataType, 3U> const& vector2);

template <typename DataType, unsigned int SIZE>
AlbaAngle getAngleBetweenTwoVectors(
        AlbaMathVector<DataType, SIZE> const& vector1,
        AlbaMathVector<DataType, SIZE> const& vector2);

template <typename DataType, unsigned int SIZE>
DataType getScalarProjection(
        AlbaMathVector<DataType, SIZE> const& vectorToProjectTo,
        AlbaMathVector<DataType, SIZE> const& vectorToProjectFrom);

template <typename DataType>
AlbaMathVector<DataType, 2U> rotateVectorCounterClockwise(
        AlbaMathVector<DataType, 2U> const& vectorToBeRotated,
        AlbaAngle const& angle);

}
