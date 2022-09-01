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
        : x(0)
        , y(0)
        , z(0)
    {}

    AlbaXYZ(CoordinateType const& xValue, CoordinateType const& yValue, CoordinateType const& zValue)
        : x(xValue)
        , y(yValue)
        , z(zValue)
    {}

    bool isEmpty() const
    {
        return x==0 && y==0 && z==0;
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

    bool operator==(AlbaXYZ<CoordinateType> const& xyz) const
    {
        return mathHelper::isAlmostEqual(x, xyz.x)
                && mathHelper::isAlmostEqual(y, xyz.y)
                && mathHelper::isAlmostEqual(z, xyz.z);
    }

    bool operator!=(AlbaXYZ<CoordinateType> const& secondXyz) const
    {
        AlbaXYZ<CoordinateType> const& firstXyz(*this);
        return !(firstXyz==secondXyz);
    }

    bool operator<(AlbaXYZ<CoordinateType> const& xyz) const // this is added so it can be used in map
    {
        bool result(false);
        if(x < xyz.x)
        {
            result = true;
        }
        else if(x == xyz.x)
        {
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

    AlbaXYZ<CoordinateType> operator+(AlbaXYZ<CoordinateType> const& secondXyz) const
    {
        return AlbaXYZ<CoordinateType>(x+secondXyz.x, y+secondXyz.y, z+secondXyz.z);
    }

    AlbaXYZ<CoordinateType> operator-(AlbaXYZ<CoordinateType> const& secondXyz) const
    {
        return AlbaXYZ<CoordinateType>(x-secondXyz.x, y-secondXyz.y, z-secondXyz.z);
    }

    AlbaXYZ<CoordinateType> operator+() const
    {
        return *this;
    }

    AlbaXYZ<CoordinateType> operator-() const
    {
        return AlbaXYZ<CoordinateType>(-x, -y, -z);
    }

    AlbaXYZ<CoordinateType>& operator+=(AlbaXYZ<CoordinateType> const& secondXyz)
    {
        x+=secondXyz.x; y+=secondXyz.y; z+=secondXyz.z;
        return *this;
    }

    AlbaXYZ<CoordinateType>& operator-=(AlbaXYZ<CoordinateType> const& secondXyz)
    {
        x-=secondXyz.x; y-=secondXyz.y; z-=secondXyz.z;
        return *this;
    }

    std::string getDisplayableString() const
    {
        std::stringstream ss;
        ss<<"("<<x<<","<<y<<","<<z<<")";
        return ss.str();
    }

    void setXAndYAndZ(CoordinateType const& xValue, CoordinateType const& yValue, CoordinateType const& zValue)
    {
        x = xValue;
        y = yValue;
        z = zValue;
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

    void setNegativeToZero()
    {
        if(x < 0)
        {
            x = 0;
        }
        if(y < 0)
        {
            y = 0;
        }
        if(z < 0)
        {
            z = 0;
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
