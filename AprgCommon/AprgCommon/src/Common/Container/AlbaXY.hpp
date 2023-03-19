#pragma once

#include <Common/Math/Helpers/PrecisionHelpers.hpp>

#include <ostream>

namespace alba
{

template <typename CoordinateType>
class AlbaXY
{
public:

    AlbaXY()
        : m_x{}
        , m_y{}
    {}

    AlbaXY(CoordinateType const& xValue, CoordinateType const& yValue)
        : m_x(xValue)
        , m_y(yValue)
    {}

    // rule of zero

    bool operator==(AlbaXY const& xy) const
    {
        return mathHelper::isAlmostEqual(m_x, xy.m_x) && mathHelper::isAlmostEqual(m_y, xy.m_y);    }

    bool operator!=(AlbaXY const& secondXy) const
    {        AlbaXY const& firstXy(*this);
        return !(firstXy==secondXy);
    }

    bool operator<(AlbaXY const& xy) const // this is added so it can be used in map
    {
        bool result(false);
        if(m_x < xy.m_x)
        {
            result = true;
        }
        else if(m_x == xy.m_x)
        {
            result = (m_y < xy.m_y);
        }
        return result;
    }

    AlbaXY operator+() const
    {
        return *this;
    }

    AlbaXY operator-() const
    {
        return AlbaXY(-m_x, -m_y);
    }

    AlbaXY operator+(AlbaXY const& secondXy) const
    {
        return AlbaXY(m_x+secondXy.m_x, m_y+secondXy.m_y);
    }

    AlbaXY operator-(AlbaXY const& secondXy) const
    {
        return AlbaXY(m_x-secondXy.m_x, m_y-secondXy.m_y);
    }

    AlbaXY operator*(CoordinateType const& multiplier) const
    {
        return AlbaXY(m_x*multiplier, m_y*multiplier);
    }

    AlbaXY operator/(CoordinateType const& divisor) const
    {
        return AlbaXY(m_x/divisor, m_y/divisor);
    }

    AlbaXY& operator+=(AlbaXY const& secondXy)
    {
        m_x+=secondXy.m_x; m_y+=secondXy.m_y;
        return *this;
    }

    AlbaXY& operator-=(AlbaXY const& secondXy)
    {
        m_x-=secondXy.m_x; m_y-=secondXy.m_y;
        return *this;
    }

    AlbaXY& operator*=(CoordinateType const& multiplier)
    {
        m_x*=multiplier; m_y*=multiplier;
        return *this;
    }

    AlbaXY& operator/=(CoordinateType const& divisor)
    {
        m_x/=divisor; m_y/=divisor;
        return *this;
    }

    bool isEmpty() const
    {
        return CoordinateType{}==m_x && CoordinateType{}==m_y;
    }

    CoordinateType getX() const
    {
        return m_x;
    }

    CoordinateType getY() const
    {
        return m_y;
    }

    CoordinateType getXTimesY() const
    {
        return m_x*m_y;
    }

    void setX(CoordinateType const& xValue)
    {
        m_x = xValue;
    }

    void setY(CoordinateType const& yValue)
    {
        m_y = yValue;
    }

    void setXAndY(CoordinateType const& xValue, CoordinateType const& yValue)
    {
        m_x = xValue;
        m_y = yValue;
    }

    void saveMinimumXAndY(AlbaXY const xy)
    {
        if(m_x > xy.m_x)
        {
            m_x = xy.m_x;
        }
        if(m_y > xy.m_y)
        {
            m_y = xy.m_y;
        }
    }

    void saveMaximumXAndY(AlbaXY const xy)
    {
        if(m_x < xy.m_x)
        {
            m_x = xy.m_x;
        }
        if(m_y < xy.m_y)
        {
            m_y = xy.m_y;
        }
    }

private:

    friend std::ostream & operator<<(std::ostream & out, AlbaXY<CoordinateType> const& xy)
    {
        out << "(" << xy.m_x << "," << xy.m_y << ")";
        return out;
    }

    CoordinateType m_x;
    CoordinateType m_y;
};

}
