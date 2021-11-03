#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

class Summation
{
public:
    Summation(
            Term const& termToSum,
            std::string const& variableToSubstitute);

    Term getSummationModelWithKnownConstant(AlbaNumber const& startNumber) const;
    Term getSummationModelWithUnknownConstant() const;

    Term getSum(Term const& start, Term const& end) const;

private:
    void calculateSumFromANumberToANumber(
            Term & result,
            AlbaNumber const& startNumber,
            AlbaNumber const& endNumber) const;
    void calculateSumStartingFromANumber(
            Term & result,
            AlbaNumber const& startNumber,
            Term const& end) const;
    void calculateSumUsingEachTerm(
            Term & result,
            AlbaNumber const& startNumber,
            AlbaNumber const& endNumber) const;
    void calculateSumUsingModel(
            Term & result,
            AlbaNumber const& startNumber,
            AlbaNumber const& endNumber) const;
    Term getSummationModel() const;

    Term m_termToSum;
    std::string m_variableToSubstitute;
    Term m_summationModel;
};

}

}
