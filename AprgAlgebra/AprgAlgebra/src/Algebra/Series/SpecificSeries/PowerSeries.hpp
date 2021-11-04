#pragma once

#include <Algebra/Series/GeneralSeries/SeriesBasedOnSummation.hpp>
#include <Math/Number/Interval/AlbaNumberInterval.hpp>

namespace alba
{

namespace algebra
{

class PowerSeries : public SeriesBasedOnSummation
{
public:
    PowerSeries(
            Term const& multiplierForEachTerm,
            std::string const& nName,
            std::string const& xName,
            AlbaNumber const& aValue);

    AlbaNumberIntervals getIntervalsOfConvergence() const;
    AlbaNumber getRadiusOfConvergence() const;

    void differentiate();
    void integrate();

private:
    Term getFormula(
            Term const& multiplierForEachTerm,
            std::string const& nName,
            std::string const& xName,
            AlbaNumber const& aValue) const;
    std::string const m_nName;
    std::string const m_xName;


};

}

}
