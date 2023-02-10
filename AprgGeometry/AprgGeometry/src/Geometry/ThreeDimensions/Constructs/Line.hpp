#pragma once

#include <Geometry/ThreeDimensions/Constructs/Point.hpp>

#include <optional>
#include <vector>

namespace alba{

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
    std::optional<double> calculateXFromY(double const y) const;
    std::optional<double> calculateXFromZ(double const z) const;
    std::optional<double> calculateYFromX(double const x) const;
    std::optional<double> calculateYFromZ(double const z) const;
    std::optional<double> calculateZFromX(double const x) const;
    std::optional<double> calculateZFromY(double const y) const;

private:
    void calculateAndSaveInitialValuesIfPossible(Point const& first);
    std::optional<double> calculateOtherCoordinate(double const& initialValue1, double const coefficient1, double const& initialValue2, double const coefficient2, double const coordinate2) const;
    bool areAllCoefficientsZero() const;

    friend std::ostream & operator<<(std::ostream & out, Line const& line);
    double m_aCoefficient; //form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    double m_bCoefficient; //form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    double m_cCoefficient; //form: (x-x0)/a = (y-y0)/b = (z-z0)/c    double m_xInitialValue; //form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    double m_yInitialValue; //form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    double m_zInitialValue; //form: (x-x0)/a = (y-y0)/b = (z-z0)/c
};

using Lines = std::vector<Line>;

}
}
