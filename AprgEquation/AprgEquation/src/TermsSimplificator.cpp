#include "TermsSimplificator.hpp"

#include <Utilities.hpp>

using namespace std;

namespace alba
{

namespace equation
{

TermsSimplificator::TermsSimplificator(Terms const& terms)
    : m_terms(terms)
{}

Terms const& TermsSimplificator::getTermsConstReference() const
{
    return m_terms;
}

void TermsSimplificator::simplify()
{
    unsigned int previousTermSize = m_terms.size();
    for(unsigned int index=0; index<m_terms.size(); )
    {
        simplify(index);
        unsigned int currentTermSize = m_terms.size();
        if(previousTermSize == currentTermSize)
        {
            index++;
        }
        previousTermSize=currentTermSize;
    }
}

void TermsSimplificator::simplify(unsigned int const index)
{
    simplifyThreeTerms(index);
}

void TermsSimplificator::simplifyThreeTerms(unsigned int const index)
{
    if(index+2 < m_terms.size())
    {
        Term const& term1(m_terms[index]);
        Term const& term2(m_terms[index+1]);
        Term const& term3(m_terms[index+2]);
        AlbaOptional<Term> newTermOptional(getNewTermFromThreeTerms(term1, term2, term3));
        if(newTermOptional.hasContent())
        {
            eraseTermsInclusive(index, index+2);
            insertTerm(index, newTermOptional.getConstReference());
        }
    }
}

AlbaOptional<Term> TermsSimplificator::getNewTermFromThreeTerms(
        Term const& term1,
        Term const& term2,
        Term const& term3) const
{
    AlbaOptional<Term> result;
    if(term1.isConstant() && term2.isOperator() && term3.isConstant())
    {
        result = combineConstantOperatorConstant(term1.getConstantConstReference(), term2.getOperatorConstReference(), term3.getConstantConstReference());
    }
    else if(term1.isConstant() && term2.isOperator() && term3.isVariable())
    {
        result = combineConstantOperatorVariable(term1.getConstantConstReference(), term2.getOperatorConstReference(), term3.getVariableConstReference());
    }
    else if(term1.isVariable() && term2.isOperator() && term3.isConstant())
    {
        result = combineVariableOperatorConstant(term1.getVariableConstReference(), term2.getOperatorConstReference(), term3.getConstantConstReference());
    }
    return result;
}

AlbaOptional<Term> TermsSimplificator::combineConstantOperatorConstant(
        Constant const& constant1,
        Operator const& operatorTerm,
        Constant const& constant2) const
{
    return AlbaOptional<Term>(Term(operatorTerm.performOperation(constant1.getNumberConstReference(), constant2.getNumberConstReference())));
}

AlbaOptional<Term> TermsSimplificator::combineConstantOperatorVariable(
        Constant const& constant,
        Operator const& operatorTerm,
        Variable const& variable) const
{
    AlbaOptional<Term> result;
    if(operatorTerm.isAddition())
    {
        result.setValue(Term(Polynomial{
                                 Monomial(constant.getNumberConstReference(), {}),
                                 Monomial(AlbaNumber(1), {{variable.getVariableName(), 1}})
                             }));
    }
    else if(operatorTerm.isSubtraction())
    {
        result.setValue(Term(Polynomial{
                                 Monomial(constant.getNumberConstReference(), {}),
                                 Monomial(AlbaNumber(-1), {{variable.getVariableName(), 1}})
                             }));
    }
    else if(operatorTerm.isMultiplication())
    {
        result.setValue(Term(Monomial(constant.getNumberConstReference(), {{variable.getVariableName(), 1}})));
    }
    else if(operatorTerm.isDivision())
    {
        result.setValue(Term(Monomial(constant.getNumberConstReference(), {{variable.getVariableName(), -1}})));
    }
    else if(operatorTerm.isRaiseToPower())
    {
        result.setValue(Term(createExpression(Terms{Term(constant), Term(operatorTerm), Term(variable)})));
    }
    return result;
}

AlbaOptional<Term> TermsSimplificator::combineVariableOperatorConstant(
        Variable const& variable,
        Operator const& operatorTerm,
        Constant const& constant) const
{
    AlbaOptional<Term> result;
    if(operatorTerm.isAddition())
    {
        result.setValue(Term(Polynomial{
                                 Monomial(AlbaNumber(1), {{variable.getVariableName(), 1}}),
                                 Monomial(constant.getNumberConstReference(), {})
                             }));
    }
    else if(operatorTerm.isSubtraction())
    {
        result.setValue(Term(Polynomial{
                                 Monomial(AlbaNumber(1), {{variable.getVariableName(), 1}}),
                                 Monomial(constant.getNumberConstReference()*-1, {})
                             }));
    }
    else if(operatorTerm.isMultiplication())
    {
        result.setValue(Term(Monomial(constant.getNumberConstReference(), {{variable.getVariableName(), 1}})));
    }
    else if(operatorTerm.isDivision())
    {
        result.setValue(Term(Monomial(AlbaNumber(1)/constant.getNumberConstReference(), {{variable.getVariableName(), 1}})));
    }
    else if(operatorTerm.isRaiseToPower())
    {
        result.setValue(Term(Monomial(1, {{variable.getVariableName(), constant.getNumberConstReference()}})));
    }
    return result;
}

void TermsSimplificator::eraseTermsInclusive(
        unsigned int const firstIndex,
        unsigned int const secondIndex)
{
    m_terms.erase(m_terms.cbegin()+firstIndex, m_terms.cbegin()+secondIndex+1);
}

void TermsSimplificator::insertTerm(
        unsigned int const index,
        Term const& term)
{
    m_terms.emplace(m_terms.cbegin()+index, term);
}

}

}
