#pragma once

#include <Common/Math/Helpers/PrecisionHelpers.hpp>

#include <sstream>
#include <string>

namespace alba
{

template <typename CoordinateType>
class AlbaXYZ
{
public:

    AlbaXYZ()
        : x{}        , y{}
        , z{}
    {}
    AlbaXYZ(CoordinateType const& xValue, CoordinateType const& yValue, CoordinateType const& zValue)
        : x(xValue)
        , y(yValue)
        , z(zValue)
    {}

    bool operator==(AlbaXYZ const& xyz) const
    {
        return mathHelper::isAlmostEqual(x, xyz.x)
                && mathHelper::isAlmostEqual(y, xyz.y)                && mathHelper::isAlmostEqual(z, xyz.z);
    }

    bool operator!=(AlbaXYZ const& secondXyz) const
    {
        AlbaXYZ const& firstXyz(*this);
        return !(firstXyz==secondXyz);
    }

    bool operator<(AlbaXYZ const& xyz) const // this is added so it can be used in map
    {
        bool result(false);
        if(x < xyz.x)        {
            result = true;
        }
        else if(x == xyz.x)        {
            if(y < xyz.y)
            {
                result = true;
            }
            else if(y == xyz.y)
            {
                result = (z < xyz.z);
            }
            else
            {
                result = false;
            }
        }
        else
        {
            result = false;
        }
        return result;
    }

    AlbaXYZ operator+() const
    {
        return *this;
    }

    AlbaXYZ operator-() const
    {
        return AlbaXYZ(-x, -y, -z);
    }

    AlbaXYZ operator+(AlbaXYZ const& secondXyz) const
    {
        return AlbaXYZ(x+secondXyz.x, y+secondXyz.y, z+secondXyz.z);
    }

    AlbaXYZ operator-(AlbaXYZ const& secondXyz) const
    {
        return AlbaXYZ(x-secondXyz.x, y-secondXyz.y, z-secondXyz.z);
    }

    AlbaXYZ operator*(CoordinateType const& multiplier) const
    {
        return AlbaXYZ(x*multiplier, y*multiplier, z*multiplier);
    }

    AlbaXYZ operator/(CoordinateType const& divisor) const
    {
        return AlbaXYZ(x/divisor, y/divisor, z/divisor);
    }

    AlbaXYZ& operator+=(AlbaXYZ const& secondXyz)
    {
        x+=secondXyz.x; y+=secondXyz.y; z+=secondXyz.z;
        return *this;
    }

    AlbaXYZ& operator-=(AlbaXYZ const& secondXyz)
    {
        x-=secondXyz.x; y-=secondXyz.y; z-=secondXyz.z;
        return *this;    }

    bool isEmpty() const
    {        return CoordinateType{}==x && CoordinateType{}==y && CoordinateType{}==z;
    }

    CoordinateType getX() const
    {
        return x;
    }

    CoordinateType getY() const
    {
        return y;
    }

    CoordinateType getZ() const
    {
        return z;
    }

    CoordinateType getXTimesYTimesZ() const
    {
        return x*y*z;
    }

    std::string getDisplayableString() const
    {
        std::stringstream ss;
        ss<<"("<<x<<","<<y<<","<<z<<")";
        return ss.str();
    }

    void setX(CoordinateType const& xValue)
    {
        x = xValue;
    }

    void setY(CoordinateType const& yValue)
    {
        y = yValue;
    }

    void setZ(CoordinateType const& zValue)
    {
        z = zValue;
    }

    void setXAndYAndZ(CoordinateType const& xValue, CoordinateType const& yValue, CoordinateType const& zValue)
    {
        x = xValue;
        y = yValue;
        z = zValue;
    }

    void saveMinimumXAndYAndZ(AlbaXYZ const xyz)
    {
        if(x > xyz.x)
        {
            x = xyz.x;
        }
        if(y > xyz.y)
        {
            y = xyz.y;
        }
        if(z > xyz.z)
        {
            z = xyz.z;
        }
    }

    void saveMaximumXAndYAndZ(AlbaXYZ const xyz)
    {
        if(x < xyz.x)
        {
            x = xyz.x;
        }
        if(y < xyz.y)
        {
            y = xyz.y;
        }
        if(z < xyz.z)
        {
            z = xyz.z;
        }
    }

private:
    CoordinateType x;
    CoordinateType y;
    CoordinateType z;
};

template <typename CoordinateType>
std::ostream & operator<<(std::ostream & out, AlbaXYZ<CoordinateType> const& xyz)
{
    out << xyz.getDisplayableString();
    return out;
}

}
