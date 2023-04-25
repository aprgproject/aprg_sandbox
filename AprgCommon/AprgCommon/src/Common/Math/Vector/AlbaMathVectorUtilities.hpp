#pragma once

#include <Common/Math/Vector/AlbaMathVectorUtilitiesHeaders.hpp>

#include <cmath>

namespace alba {

template <typename DataType>
bool isEqualForMathVectorDataType(DataType const& value1, DataType const& value2);

template <typename DataType, unsigned int SIZE>
bool areVectorsPerpendicular(
    AlbaMathVector<DataType, SIZE> const& vector1, AlbaMathVector<DataType, SIZE> const& vector2) {
    return isEqualForMathVectorDataType(getDotProduct(vector1, vector2), DataType(0));
}

template <typename DataType, unsigned int SIZE>
bool areVectorsParallel(AlbaMathVector<DataType, SIZE> const& vector1, AlbaMathVector<DataType, SIZE> const& vector2) {
    return isEqualForMathVectorDataType(
        getDotProduct(vector1, vector2), vector1.getMagnitude() * vector2.getMagnitude());
}

// This is always true.
template <typename DataType, unsigned int SIZE>
bool isCauchySchwarzInequalitySatisfied(
    AlbaMathVector<DataType, SIZE> const& vector1, AlbaMathVector<DataType, SIZE> const& vector2) {
    return getDotProduct(vector1, vector2) <= vector1.getMagnitude() * vector2.getMagnitude();
}

// This is always true.
template <typename DataType, unsigned int SIZE>
bool isTriangleInequalitySatisfied(
    AlbaMathVector<DataType, SIZE> const& vector1, AlbaMathVector<DataType, SIZE> const& vector2) {
    return (vector1 + vector2).getMagnitude() <= vector1.getMagnitude() + vector2.getMagnitude();
}

// This is always true.
template <typename DataType, unsigned int SIZE>
bool isDotProductEqualToProductOfMagnitudesWithCosineOfAngle(
    AlbaMathVector<DataType, SIZE> const& vector1, AlbaMathVector<DataType, SIZE> const& vector2) {
    return isEqualForMathVectorDataType(
        getDotProduct(vector1, vector2), (vector1.getMagnitude() * vector2.getMagnitude() *
                                          cos(getAngleBetweenTwoVectors(vector1, vector2).getRadians())));
}

template <typename DataType, unsigned int SIZE>
AlbaMathVector<DataType, SIZE> createZeroVector() {
    return AlbaMathVector<DataType, SIZE>();
}

template <typename DataType, unsigned int SIZE>
AlbaMathVector<DataType, SIZE> getUnitVector(AlbaMathVector<DataType, SIZE> const& vector) {
    AlbaMathVector<DataType, SIZE> unitVector(vector);
    DataType magnitude(vector.getMagnitude());
    for (DataType& value : unitVector.getValuesReference()) {
        value /= magnitude;
    }
    return unitVector;
}

template <typename DataType, unsigned int SIZE>
AlbaMathVector<DataType, SIZE> getVectorProjection(
    AlbaMathVector<DataType, SIZE> const& vectorToProjectTo,
    AlbaMathVector<DataType, SIZE> const& vectorToProjectFrom) {
    DataType const multiplier = getDotProduct(vectorToProjectTo, vectorToProjectFrom) /
                                (vectorToProjectTo.getMagnitude() * vectorToProjectTo.getMagnitude());
    return vectorToProjectTo * multiplier;
}

template <typename DataType, unsigned int SIZE>
DataType getDotProduct(AlbaMathVector<DataType, SIZE> const& vector1, AlbaMathVector<DataType, SIZE> const& vector2) {
    DataType result(0);
    for (unsigned int i = 0; i < SIZE; i++) {
        result += vector1.getValueAt(i) * vector2.getValueAt(i);
    }
    return result;
}

// cross product on 2D results in vector on the Z axis
template <typename DataType>
DataType getCrossProduct(AlbaMathVector<DataType, 2U> const& vector1, AlbaMathVector<DataType, 2U> const& vector2) {
    return vector1.getValueAt(0) * vector2.getValueAt(1) - vector1.getValueAt(1) * vector2.getValueAt(0);
}

template <typename DataType>
AlbaMathVector<DataType, 3U> getCrossProduct(
    AlbaMathVector<DataType, 3U> const& vector1, AlbaMathVector<DataType, 3U> const& vector2) {
    return AlbaMathVector<DataType, 3U>{
        vector1.getValueAt(1) * vector2.getValueAt(2) - vector1.getValueAt(2) * vector2.getValueAt(1),
        vector1.getValueAt(2) * vector2.getValueAt(0) - vector1.getValueAt(0) * vector2.getValueAt(2),
        vector1.getValueAt(0) * vector2.getValueAt(1) - vector1.getValueAt(1) * vector2.getValueAt(0)};
}

template <typename DataType, unsigned int SIZE>
AlbaAngle getAngleBetweenTwoVectors(
    AlbaMathVector<DataType, SIZE> const& vector1, AlbaMathVector<DataType, SIZE> const& vector2) {
    // In 2D, in c++ complex number class this is same with arg(v).
    return AlbaAngle(
        AngleUnitType::Radians,
        acos(getDotProduct(vector1, vector2) / (vector1.getMagnitude() * vector2.getMagnitude())));
}

template <typename DataType, unsigned int SIZE>
DataType getScalarProjection(
    AlbaMathVector<DataType, SIZE> const& vectorToProjectTo,
    AlbaMathVector<DataType, SIZE> const& vectorToProjectFrom) {
    return getDotProduct(vectorToProjectTo, vectorToProjectFrom) / vectorToProjectTo.getMagnitude();
}

template <typename DataType>
AlbaMathVector<DataType, 2U> rotateVectorCounterClockwise(
    AlbaMathVector<DataType, 2U> const& vectorToBeRotated, AlbaAngle const& angle) {
    double magnitude = vectorToBeRotated.getMagnitude();
    double newAngleInRadians = angle.getRadians() + acos(vectorToBeRotated.getValueAt(0) / magnitude);
    return AlbaMathVector<DataType, 2U>{magnitude * cos(newAngleInRadians), magnitude * sin(newAngleInRadians)};
}

}  // namespace alba
