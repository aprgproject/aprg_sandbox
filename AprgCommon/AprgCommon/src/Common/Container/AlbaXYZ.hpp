#pragma once

#include <Common/Math/Helpers/PrecisionHelpers.hpp>

#include <ostream>

namespace alba {

template <typename CoordinateType>
class AlbaXYZ {
public:
    AlbaXYZ() : m_x{}, m_y{}, m_z{} {}

    AlbaXYZ(CoordinateType const& xValue, CoordinateType const& yValue, CoordinateType const& zValue)
        : m_x(xValue), m_y(yValue), m_z(zValue) {}

    // rule of zero

    bool operator==(AlbaXYZ const& xyz) const {
        return mathHelper::isAlmostEqual(m_x, xyz.m_x) && mathHelper::isAlmostEqual(m_y, xyz.m_y) &&
               mathHelper::isAlmostEqual(m_z, xyz.m_z);
    }

    bool operator!=(AlbaXYZ const& secondXyz) const {
        AlbaXYZ const& firstXyz(*this);
        return !(firstXyz == secondXyz);
    }

    bool operator<(AlbaXYZ const& xyz) const  // this is added so it can be used in map
    {
        bool result(false);
        if (m_x < xyz.m_x) {
            result = true;
        } else if (m_x == xyz.m_x) {
            if (m_y < xyz.m_y) {
                result = true;
            } else if (m_y == xyz.m_y) {
                result = (m_z < xyz.m_z);
            } else {
                result = false;
            }
        } else {
            result = false;
        }
        return result;
    }

    AlbaXYZ operator+() const { return *this; }

    AlbaXYZ operator-() const { return AlbaXYZ(-m_x, -m_y, -m_z); }

    AlbaXYZ operator+(AlbaXYZ const& secondXyz) const {
        return AlbaXYZ(m_x + secondXyz.m_x, m_y + secondXyz.m_y, m_z + secondXyz.m_z);
    }

    AlbaXYZ operator-(AlbaXYZ const& secondXyz) const {
        return AlbaXYZ(m_x - secondXyz.m_x, m_y - secondXyz.m_y, m_z - secondXyz.m_z);
    }

    AlbaXYZ operator*(CoordinateType const& multiplier) const {
        return AlbaXYZ(m_x * multiplier, m_y * multiplier, m_z * multiplier);
    }

    AlbaXYZ operator/(CoordinateType const& divisor) const {
        return AlbaXYZ(m_x / divisor, m_y / divisor, m_z / divisor);
    }

    AlbaXYZ& operator+=(AlbaXYZ const& secondXyz) {
        m_x += secondXyz.m_x;
        m_y += secondXyz.m_y;
        m_z += secondXyz.m_z;
        return *this;
    }

    AlbaXYZ& operator-=(AlbaXYZ const& secondXyz) {
        m_x -= secondXyz.m_x;
        m_y -= secondXyz.m_y;
        m_z -= secondXyz.m_z;
        return *this;
    }

    bool isEmpty() const { return CoordinateType{} == m_x && CoordinateType{} == m_y && CoordinateType{} == m_z; }

    CoordinateType getX() const { return m_x; }

    CoordinateType getY() const { return m_y; }

    CoordinateType getZ() const { return m_z; }

    CoordinateType getXTimesYTimesZ() const { return m_x * m_y * m_z; }

    void setX(CoordinateType const& xValue) { m_x = xValue; }

    void setY(CoordinateType const& yValue) { m_y = yValue; }

    void setZ(CoordinateType const& zValue) { m_z = zValue; }

    void setXAndYAndZ(CoordinateType const& xValue, CoordinateType const& yValue, CoordinateType const& zValue) {
        m_x = xValue;
        m_y = yValue;
        m_z = zValue;
    }

    void saveMinimumXAndYAndZ(AlbaXYZ const xyz) {
        if (m_x > xyz.m_x) {
            m_x = xyz.m_x;
        }
        if (m_y > xyz.m_y) {
            m_y = xyz.m_y;
        }
        if (m_z > xyz.m_z) {
            m_z = xyz.m_z;
        }
    }

    void saveMaximumXAndYAndZ(AlbaXYZ const xyz) {
        if (m_x < xyz.m_x) {
            m_x = xyz.m_x;
        }
        if (m_y < xyz.m_y) {
            m_y = xyz.m_y;
        }
        if (m_z < xyz.m_z) {
            m_z = xyz.m_z;
        }
    }

private:
    friend std::ostream& operator<<(std::ostream& out, AlbaXYZ<CoordinateType> const& xyz) {
        out << "(" << xyz.m_x << "," << xyz.m_y << "," << xyz.m_z << ")";
        return out;
    }

    CoordinateType m_x;
    CoordinateType m_y;
    CoordinateType m_z;
};

}  // namespace alba
