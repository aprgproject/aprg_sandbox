#pragma once

#include <string>
#include <sstream>

namespace alba
{

template <typename CoordinateType>
class AlbaXY
{
public:
    AlbaXY()
        : x(0)
        , y(0)
    {}

    AlbaXY(CoordinateType xValue, CoordinateType yValue)
        : x(xValue)
        , y(yValue)
    {}

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

    bool operator==(AlbaXY<CoordinateType> const& xy) const
    {
        return (x == xy.x) && (y == xy.y);
    }

    bool operator!=(AlbaXY<CoordinateType> const& xy) const
    {
        return !((*this)==xy);
    }

    bool operator<(AlbaXY<CoordinateType> const& xy) const
    {
        bool isLessThan(false);
        if(x < xy.x)
        {
            isLessThan = true;
        }
        else if(x == xy.x)
        {
            isLessThan = (y < xy.y);
        }
        return  isLessThan;
    }

    std::string getDisplayableString() const
    {
        std::stringstream ss;
        ss<<"("<<x<<","<<y<<")";
        return ss.str();
    }

    void setXAndY(CoordinateType xValue, CoordinateType yValue)
    {
        x = xValue;
        y = yValue;
    }

    void setX(CoordinateType xValue)
    {
        x = xValue;
    }

    void setY(CoordinateType yValue)
    {
        y = yValue;
    }

    void saveAsTopLeftCorner(AlbaXY const xy)
    {
        if(x > xy.x)
        {
            x=xy.x;
        }
        if(y > xy.y)
        {
            y=xy.y;
        }
    }

    void saveAsBottomRightCorner(AlbaXY const xy)
    {
        if(x < xy.x)
        {
            x=xy.x;
        }
        if(y < xy.y)
        {
            y=xy.y;
        }
    }

private:
    CoordinateType x;
    CoordinateType y;
};

}
