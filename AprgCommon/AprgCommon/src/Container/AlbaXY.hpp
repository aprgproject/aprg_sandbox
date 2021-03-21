#pragma once

#include <Math/AlbaMathHelper.hpp>

#include <sstream>
#include <string>

using namespace alba::mathHelper;

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

    AlbaXY(CoordinateType const& xValue, CoordinateType const& yValue)
        : x(xValue)
        , y(yValue)
    {}
    bool isEmpty() const
    {
        return x==0 && y==0;
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

    bool operator==(AlbaXY<CoordinateType> const& xy) const
    {
        return isConsideredEqual(x, xy.x) && isConsideredEqual(y, xy.y);
    }

    bool operator!=(AlbaXY<CoordinateType> const& secondXy) const
    {
        AlbaXY<CoordinateType> const& firstXy(*this);
        return !(firstXy==secondXy);
    }

    bool operator<(AlbaXY<CoordinateType> const& xy) const // this is added so it can be used in map
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
        else
        {
            result = false;
        }
        return result;
    }

    std::string getDisplayableString() const
    {
        std::stringstream ss;
        ss<<"("<<x<<","<<y<<")";
        return ss.str();
    }

    void setXAndY(CoordinateType const& xValue, CoordinateType const& yValue)
    {
        x = xValue;
        y = yValue;
    }

    void setX(CoordinateType const& xValue)
    {
        x = xValue;
    }

    void setY(CoordinateType const& yValue)
    {
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
    }

private:
    CoordinateType x;
    CoordinateType y;
};

}
