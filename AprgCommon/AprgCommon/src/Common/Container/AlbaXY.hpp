#pragma once

#include <Common/Math/Helpers/PrecisionHelpers.hpp>

#include <sstream>
#include <string>

namespace alba
{

template <typename CoordinateType>
class AlbaXY
{
public:
    using XyType = AlbaXY<CoordinateType>;

    AlbaXY()
        : x{}
        , y{}
    {}

    AlbaXY(CoordinateType const& xValue, CoordinateType const& yValue)
        : x(xValue)
        , y(yValue)
    {}

    bool operator==(XyType const& xy) const
    {
        return mathHelper::isAlmostEqual(x, xy.x) && mathHelper::isAlmostEqual(y, xy.y);
    }

    bool operator!=(XyType const& secondXy) const
    {
        XyType const& firstXy(*this);
        return !(firstXy==secondXy);
    }

    bool operator<(XyType const& xy) const // this is added so it can be used in map
    {
        bool result(false);
        if(x < xy.x)
        {
            result = true;
        }
        else if(x == xy.x)
        {
            result = (y < xy.y);
        }
        return result;
    }

    XyType operator+() const
    {
        return *this;
    }

    XyType operator-() const
    {
        return XyType(-x, -y);
    }

    XyType operator+(XyType const& secondXy) const
    {
        return XyType(x+secondXy.x, y+secondXy.y);
    }

    XyType operator-(XyType const& secondXy) const
    {
        return XyType(x-secondXy.x, y-secondXy.y);
    }

    XyType operator*(CoordinateType const& multiplier) const
    {
        return XyType(x*multiplier, y*multiplier);
    }

    XyType operator/(CoordinateType const& divisor) const
    {
        return XyType(x/divisor, y/divisor);
    }

    XyType& operator+=(XyType const& secondXy)
    {
        x+=secondXy.x; y+=secondXy.y;
        return *this;
    }

    XyType& operator-=(XyType const& secondXy)
    {
        x-=secondXy.x; y-=secondXy.y;
        return *this;
    }

    bool isEmpty() const
    {
        return CoordinateType{}==x && CoordinateType{}==y;
    }

    CoordinateType getX() const
    {
        return x;
    }

    CoordinateType getY() const
    {
        return y;
    }

    CoordinateType getXTimesY() const
    {
        return x*y;
    }

    std::string getDisplayableString() const
    {
        std::stringstream ss;
        ss.precision(30);
        ss<<"("<<x<<","<<y<<")";
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

    void setXAndY(CoordinateType const& xValue, CoordinateType const& yValue)
    {
        x = xValue;
        y = yValue;
    }

    void saveMinimumXAndY(AlbaXY const xy)
    {
        if(x > xy.x)
        {
            x = xy.x;
        }
        if(y > xy.y)
        {
            y = xy.y;
        }
    }

    void saveMaximumXAndY(AlbaXY const xy)
    {
        if(x < xy.x)
        {
            x = xy.x;
        }
        if(y < xy.y)
        {
            y = xy.y;
        }
    }

private:
    CoordinateType x;
    CoordinateType y;
};

template <typename CoordinateType>
std::ostream & operator<<(std::ostream & out, AlbaXY<CoordinateType> const& xy)
{
    out << xy.getDisplayableString();
    return out;
}

}
