#include "MultiplicationAndDivisionOfRadicals.hpp"

#include <Algebra/Constructs/TermRaiseToANumber.hpp>
#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Operations/AccumulateOperations.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/SegregateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <algorithm>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{
namespace algebra
{

MultiplicationAndDivisionOfRadicals::MultiplicationAndDivisionOfRadicals()
{}

MultiplicationAndDivisionOfRadicals::MultiplicationAndDivisionOfRadicals(
        TermsWithDetails const& termsWithDetails)
    : m_termsWithDetails(termsWithDetails)
{}

Term MultiplicationAndDivisionOfRadicals::getCombinedTerm() const
{
    Expression combinedExpression;
    combinedExpression.setCommonOperatorLevel(OperatorLevel::MultiplicationAndDivision);
    combinedExpression.putTermsWithDetails(m_termsWithDetails);
    Term combinedTerm(combinedExpression);
    combinedTerm.simplify();
    return combinedTerm;
}

TermsWithDetails const& MultiplicationAndDivisionOfRadicals::getTermsWithDetails() const{
    return m_termsWithDetails;
}

void MultiplicationAndDivisionOfRadicals::simplify()
{
    combineRadicalsInMultiplicationAndDivision(m_termsWithDetails);
    combineMonomialAndFirstRadicalInMultiplicationAndDivision(m_termsWithDetails);
}

void MultiplicationAndDivisionOfRadicals::combineRadicalsInMultiplicationAndDivision(
        TermsWithDetails & termsWithDetails)
{
    //refactor
    ListOfTermRaiseToANumber termRaiseToNumbers;
    termRaiseToNumbers.reserve(termsWithDetails.size());
    AlbaNumber gcfOfExponents;
    unsigned int radicalCount(0);
    bool isFirst(true);
    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        Term const& termToConvert(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromTerm(termToConvert));
        if(termRaiseToANumber.isRadical())
        {
            if(isFirst)
            {
                gcfOfExponents = termRaiseToANumber.getExponent();
                isFirst = false;
            }
            else
            {
                gcfOfExponents = getGreatestCommonFactorForAlbaNumber(gcfOfExponents, termRaiseToANumber.getExponent());
            }
            radicalCount++;
        }
        termRaiseToNumbers.emplace_back(termRaiseToANumber);
    }
    if(gcfOfExponents != 1 && radicalCount > 1)
    {
        Expression combinedRadicalBase;
        combinedRadicalBase.setCommonOperatorLevel(OperatorLevel::MultiplicationAndDivision);
        for(unsigned int i=0; i<termRaiseToNumbers.size(); )
        {
            TermRaiseToANumber const& termRaiseToNumber(termRaiseToNumbers.at(i));
            if(termRaiseToNumber.isRadical())
            {
                Expression newBaseForRadical(termRaiseToNumber.getBase());
                newBaseForRadical.putTermWithRaiseToPowerIfNeeded(Term(termRaiseToNumber.getExponent()/gcfOfExponents));
                combinedRadicalBase.putTerm(Term(newBaseForRadical), termsWithDetails.at(i).association);
                termRaiseToNumbers.erase(termRaiseToNumbers.begin()+i);
                termsWithDetails.erase(termsWithDetails.begin()+i);
            }
            else
            {
                i++;
            }
        }
        combinedRadicalBase.putTermWithRaiseToPowerIfNeeded(Term(gcfOfExponents));
        termsWithDetails.emplace_back(Term(combinedRadicalBase), TermAssociationType::Positive);
    }
}

void MultiplicationAndDivisionOfRadicals::combineMonomialAndFirstRadicalInMultiplicationAndDivision(
        TermsWithDetails & termsWithDetails)
{
    //refactor
    TermsWithDetails monomials;
    TermsWithDetails remainingTerms;
    segregateMonomialsAndNonMonomials(termsWithDetails, monomials, remainingTerms);

    TermsWithDetails::iterator firstRadicalIt = find_if(
                remainingTerms.begin(), remainingTerms.end(),
                [](TermWithDetails const& remainingTerm)
    {
            Term const& termToCheck(getTermConstReferenceFromSharedPointer(remainingTerm.baseTermSharedPointer));
            return isRadicalTerm(termToCheck);});
    if(firstRadicalIt != remainingTerms.end())
    {
        Term combinedMonomialTerm(1);
        accumulateTermsForMultiplicationAndDivision(combinedMonomialTerm, monomials);
        TermRaiseToANumber termRaiseToANumber(
                    createTermRaiseToANumberFromTerm(
                        getTermConstReferenceFromSharedPointer(firstRadicalIt->baseTermSharedPointer)));
        remainingTerms.erase(firstRadicalIt);
        TermAssociationType radicalAssociationType(firstRadicalIt->association);
        Monomial combinedMonomial(createMonomialIfPossible(combinedMonomialTerm));
        combinedMonomial.raiseToPowerNumber(AlbaNumber(1)/termRaiseToANumber.getExponent());
        Expression newRadical(getTermConstReferenceFromBaseTerm(Term(combinedMonomial)));
        if(TermAssociationType::Positive == radicalAssociationType)
        {
            newRadical.putTermWithMultiplicationIfNeeded(getTermConstReferenceFromBaseTerm(termRaiseToANumber.getBase()));
        }
        else
        {
            newRadical.putTermWithDivisionIfNeeded(getTermConstReferenceFromBaseTerm(termRaiseToANumber.getBase()));
        }
        newRadical.putTermWithRaiseToPowerIfNeeded(Term(termRaiseToANumber.getExponent()));
        remainingTerms.emplace(remainingTerms.begin(), Term(newRadical), TermAssociationType::Positive);
        termsWithDetails = remainingTerms;
    }
}

}
}
