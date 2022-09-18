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

    AlbaXY()
        : x{}
        , y{}
    {}

    AlbaXY(CoordinateType const& xValue, CoordinateType const& yValue)
        : x(xValue)
        , y(yValue)
    {}

    bool operator==(AlbaXY const& xy) const
    {
        return mathHelper::isAlmostEqual(x, xy.x) && mathHelper::isAlmostEqual(y, xy.y);
    }

    bool operator!=(AlbaXY const& secondXy) const
    {
        AlbaXY const& firstXy(*this);
        return !(firstXy==secondXy);
    }

    bool operator<(AlbaXY const& xy) const // this is added so it can be used in map
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

    AlbaXY operator+() const
    {
        return *this;
    }

    AlbaXY operator-() const
    {
        return AlbaXY(-x, -y);
    }

    AlbaXY operator+(AlbaXY const& secondXy) const
    {
        return AlbaXY(x+secondXy.x, y+secondXy.y);
    }

    AlbaXY operator-(AlbaXY const& secondXy) const
    {
        return AlbaXY(x-secondXy.x, y-secondXy.y);
    }

    AlbaXY operator*(CoordinateType const& multiplier) const
    {
        return AlbaXY(x*multiplier, y*multiplier);
    }

    AlbaXY operator/(CoordinateType const& divisor) const
    {
        return AlbaXY(x/divisor, y/divisor);
    }

    AlbaXY& operator+=(AlbaXY const& secondXy)
    {
        x+=secondXy.x; y+=secondXy.y;
        return *this;
    }

    AlbaXY& operator-=(AlbaXY const& secondXy)
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
