#pragma once

#include <Common/Optional/AlbaOptional.hpp>
#include <Geometry/ThreeDimensions/Point.hpp>

#include <vector>
namespace alba
{

namespace ThreeDimensions
{

class Line
{
public:
    Line();
    Line(Point const& first, Point const& second);
    Line(double const aCoefficient,
         double const bCoefficient,
         double const cCoefficient,
         double const xInitialValue,
         double const yInitialValue,
         double const zInitialValue);
    Line(double const aCoefficient,
         double const bCoefficient,
         double const cCoefficient,
         Point const& point);
    bool isInvalid() const;
    bool operator==(Line const& line) const;
    bool operator!=(Line const& line) const;
    double getXInitialValue() const;
    double getYInitialValue() const;
    double getZInitialValue() const;
    double getACoefficient() const;
    double getBCoefficient() const;
    double getCCoefficient() const;
    AlbaOptional<double> calculateXFromY(double const y) const;
    AlbaOptional<double> calculateXFromZ(double const z) const;
    AlbaOptional<double> calculateYFromX(double const x) const;
    AlbaOptional<double> calculateYFromZ(double const z) const;
    AlbaOptional<double> calculateZFromX(double const x) const;
    AlbaOptional<double> calculateZFromY(double const y) const;

    std::string getDisplayableString() const;

private:
    void calculateAndSaveInitialValuesIfPossible(Point const& first);
    AlbaOptional<double> calculateOtherCoordinate(double const& initialValue1, double const coefficient1, double const& initialValue2, double const coefficient2, double const coordinate2) const;
    bool areAllCoefficientsZero() const;
    double m_aCoefficient; //form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    double m_bCoefficient; //form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    double m_cCoefficient; //form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    double m_xInitialValue; //form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    double m_yInitialValue; //form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    double m_zInitialValue; //form: (x-x0)/a = (y-y0)/b = (z-z0)/c
};

using Lines = std::vector<Line>;

std::ostream & operator<<(std::ostream & out, Line const& line);

}
}
