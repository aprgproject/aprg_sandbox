#pragma once

#include <Optional/AlbaOptional.hpp>
#include <ThreeDimensions/Point.hpp>

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
    Line(double const xInitialValue,
         double const yInitialValue,
         double const zInitialValue,
         double const aCoefficient,
         double const bCoefficient,
         double const cCoefficient);
    bool isInvalid() const;
    bool operator==(Line const& line) const;
    bool operator!=(Line const& line) const;
    AlbaOptional<double> getXInitialValue() const;
    AlbaOptional<double> getYInitialValue() const;
    AlbaOptional<double> getZInitialValue() const;
    double getACoefficient() const;
    double getBCoefficient() const;
    double getCCoefficient() const;
    AlbaOptional<double> calculateXFromY(double const y) const;
    AlbaOptional<double> calculateXFromZ(double const z) const;
    AlbaOptional<double> calculateYFromX(double const x) const;
    AlbaOptional<double> calculateYFromZ(double const z) const;
    AlbaOptional<double> calculateZFromX(double const x) const;
    AlbaOptional<double> calculateZFromY(double const y) const;

private:
    AlbaOptional<double> calculateInitialValueFrom2Coordinates(
            double const coordinateWithIntecept,
            double const coordinate1,
            double const coordinate2,
            double const coefficientWithInitialValue,
            double const coefficient1,
            double const coefficient2) const;
    AlbaOptional<double> calculateInitialValue(double const coordinate1, double const coordinate2, double const coefficient1, double const coefficient2) const;
    AlbaOptional<double> calculateOtherCoordinate(AlbaOptional<double> const& initialValue1, double const coefficient1, AlbaOptional<double> const& initialValue2, double const coefficient2, double const coordinate2) const;
    AlbaOptional<double> m_xInitialValue; //form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    AlbaOptional<double> m_yInitialValue; //form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    AlbaOptional<double> m_zInitialValue; //form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    double m_aCoefficient; //form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    double m_bCoefficient; //form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    double m_cCoefficient; //form: (x-x0)/a = (y-y0)/b = (z-z0)/c
};

using Lines = std::vector<Line>;

}
}
