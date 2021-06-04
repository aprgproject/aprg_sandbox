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
    else if(term1.isVariable() && term2.isOperator() && term3.isVariable())
    {
        result = combineVariableOperatorVariable(term1.getVariableConstReference(), term2.getOperatorConstReference(), term3.getVariableConstReference());
    }
    else if(term1.isMonomial() && term2.isOperator() && term3.isConstant())
    {
        result = combineMonomialOperatorConstant(term1.getMonomialConstReference(), term2.getOperatorConstReference(), term3.getConstantConstReference());
    }
    else if(term1.isMonomial() && term2.isOperator() && term3.isVariable())
    {
        result = combineMonomialOperatorVariable(term1.getMonomialConstReference(), term2.getOperatorConstReference(), term3.getVariableConstReference());
    }
    else if(term1.isConstant() && term2.isOperator() && term3.isMonomial())
    {
        result = combineConstantOperatorMonomial(term1.getConstantConstReference(), term2.getOperatorConstReference(), term3.getMonomialConstReference());
    }
    else if(term1.isVariable() && term2.isOperator() && term3.isMonomial())
    {
        result = combineVariableOperatorMonomial(term1.getVariableConstReference(), term2.getOperatorConstReference(), term3.getMonomialConstReference());
    }
    return result;
}
AlbaOptional<Term> TermsSimplificator::combineConstantOperatorConstant(
        Constant const& constant1,
        Operator const& operatorTerm,        Constant const& constant2) const
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
                                 Monomial(1, {{variable.getVariableName(), 1}})
                             }));
    }
    else if(operatorTerm.isSubtraction())    {
        result.setValue(Term(Polynomial{
                                 Monomial(constant.getNumberConstReference(), {}),
                                 Monomial(-1, {{variable.getVariableName(), 1}})
                             }));
    }
    else if(operatorTerm.isMultiplication())    {
        result.setValue(Term(Monomial(constant.getNumberConstReference(), {{variable.getVariableName(), 1}})));
    }
    else if(operatorTerm.isDivision())    {
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
                                 Monomial(1, {{variable.getVariableName(), 1}}),
                                 Monomial(constant.getNumberConstReference(), {})
                             }));
    }    else if(operatorTerm.isSubtraction())
    {
        result.setValue(Term(Polynomial{
                                 Monomial(1, {{variable.getVariableName(), 1}}),
                                 Monomial(constant.getNumberConstReference()*-1, {})
                             }));
    }    else if(operatorTerm.isMultiplication())
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

AlbaOptional<Term> TermsSimplificator::combineVariableOperatorVariable(
        Variable const& variable1,
        Operator const& operatorTerm,
        Variable const& variable2) const
{
    AlbaOptional<Term> result;
    if(variable1.getVariableName() == variable2.getVariableName())
    {
        result = combineVariableOperatorVariableSameVariable(variable1, operatorTerm);
    }
    else
    {
        result = combineVariableOperatorVariableDifferentVariable(variable1, operatorTerm, variable2);
    }
    return result;
}

AlbaOptional<Term> TermsSimplificator::combineVariableOperatorVariableSameVariable(
        Variable const& variable,
        Operator const& operatorTerm) const
{
    AlbaOptional<Term> result;
    if(operatorTerm.isAddition())
    {
        result.setValue(Term(Monomial(2, {{variable.getVariableName(), 1}})));
    }
    else if(operatorTerm.isSubtraction())
    {
        result.setValue(Term(AlbaNumber(0)));
    }
    else if(operatorTerm.isMultiplication())
    {
        result.setValue(Term(Monomial(1, {{variable.getVariableName(), 2}})));
    }
    else if(operatorTerm.isDivision())
    {
        result.setValue(Term(AlbaNumber(1)));
    }
    else if(operatorTerm.isRaiseToPower())
    {
        result.setValue(Term(createExpression(Terms{Term(variable), Term(operatorTerm), Term(variable)})));
    }
    return result;
}

AlbaOptional<Term> TermsSimplificator::combineVariableOperatorVariableDifferentVariable(
        Variable const& variable1,
        Operator const& operatorTerm,
        Variable const& variable2) const
{
    AlbaOptional<Term> result;
    if(operatorTerm.isAddition())
    {
        result.setValue(Term(Polynomial{
                                 Monomial(1, {{variable1.getVariableName(), 1}}),
                                 Monomial(1, {{variable2.getVariableName(), 1}})
                             }));
    }
    else if(operatorTerm.isSubtraction())
    {
        result.setValue(Term(Polynomial{
                                 Monomial(1, {{variable1.getVariableName(), 1}}),
                                 Monomial(-1, {{variable2.getVariableName(), 1}})
                             }));
    }
    else if(operatorTerm.isMultiplication())
    {
        result.setValue(Term(Monomial(1, {{variable1.getVariableName(), 1}, {variable2.getVariableName(), 1}})));
    }
    else if(operatorTerm.isDivision())
    {
        result.setValue(Term(Monomial(1, {{variable1.getVariableName(), 1}, {variable2.getVariableName(), -1}})));
    }
    else if(operatorTerm.isRaiseToPower())
    {
        result.setValue(Term(createExpression(Terms{Term(variable1), Term(operatorTerm), Term(variable2)})));
    }
    return result;
}

AlbaOptional<Term> TermsSimplificator::combineMonomialOperatorConstant(
        Monomial const& monomial,
        Operator const& operatorTerm,
        Constant const& constant) const
{
    AlbaOptional<Term> result;
    if(operatorTerm.isAddition())
    {
        result.setValue(Term(Polynomial{
                                 monomial,
                                 Monomial(constant.getNumberConstReference(), {})
                             }));
    }
    else if(operatorTerm.isSubtraction())
    {
        result.setValue(Term(Polynomial{
                                 monomial,
                                 Monomial(constant.getNumberConstReference()*-1, {})
                             }));
    }
    else if(operatorTerm.isMultiplication())
    {
        result.setValue(Term(Monomial(monomial.getConstantConstReference()*constant.getNumberConstReference(), monomial.getVariablesToExponentsMapConstReference())));
    }
    else if(operatorTerm.isDivision())
    {
        result.setValue(Term(Monomial(monomial.getConstantConstReference()/constant.getNumberConstReference(), monomial.getVariablesToExponentsMapConstReference())));
    }
    else if(operatorTerm.isRaiseToPower())
    {
        Monomial::VariablesToExponentsMap variablesMap(monomial.getVariablesToExponentsMapConstReference());
        performChangeForVariables(variablesMap, [&constant](string const &, AlbaNumber & exponent)
        {
            exponent=exponent*constant.getNumberConstReference();
        });
        result.setValue(Term(Monomial(monomial.getConstantConstReference()^constant.getNumberConstReference(), variablesMap)));
    }
    return result;
}

AlbaOptional<Term> TermsSimplificator::combineMonomialOperatorVariable(
        Monomial const& monomial,
        Operator const& operatorTerm,
        Variable const& variable) const
{
    AlbaOptional<Term> result;
    if(canBeAddedOrSubtracted(monomial, variable))
    {
        result = combineMonomialOperatorVariableSameMonomialVariable(monomial, operatorTerm, variable);
    }
    else
    {
        result = combineMonomialOperatorVariableDifferentMonomialVariable(monomial, operatorTerm, variable);
    }
    return result;
}

AlbaOptional<Term> TermsSimplificator::combineMonomialOperatorVariableSameMonomialVariable(
        Monomial const& monomial,
        Operator const& operatorTerm,
        Variable const& variable) const
{
    AlbaOptional<Term> result;
    if(operatorTerm.isAddition())
    {
        result.setValue(Term(Monomial(monomial.getConstantConstReference()+1, {{variable.getVariableName(), 1}})));
    }
    else if(operatorTerm.isSubtraction())
    {
        result.setValue(Term(Monomial(monomial.getConstantConstReference()-1, {{variable.getVariableName(), 1}})));
    }
    else if(operatorTerm.isMultiplication())
    {
        result.setValue(Term(Monomial(monomial.getConstantConstReference(), {{variable.getVariableName(), 2}})));
    }
    else if(operatorTerm.isDivision())
    {
        result.setValue(Term(monomial.getConstantConstReference()));
    }
    else if(operatorTerm.isRaiseToPower())
    {
        result.setValue(Term(createExpression(Terms{Term(monomial), Term(operatorTerm), Term(variable)})));
    }
    return result;
}

AlbaOptional<Term> TermsSimplificator::combineMonomialOperatorVariableDifferentMonomialVariable(
        Monomial const& monomial,
        Operator const& operatorTerm,
        Variable const& variable) const
{
    AlbaOptional<Term> result;
    if(operatorTerm.isAddition())
    {
        result.setValue(Term(Polynomial{
                                 monomial,
                                 Monomial(1, {{variable.getVariableName(), 1}})
                             }));
    }
    else if(operatorTerm.isSubtraction())
    {
        result.setValue(Term(Polynomial{
                                 monomial,
                                 Monomial(-1, {{variable.getVariableName(), 1}})
                             }));
    }
    else if(operatorTerm.isMultiplication())
    {
        string variableName(variable.getVariableName());
        Monomial newMonomial(monomial);
        Monomial::VariablesToExponentsMap & variablesMap(newMonomial.getVariablesToExponentsMapReference());
        variablesMap[variableName]=variablesMap[variableName]+1;
        result.setValue(Term(newMonomial));
    }
    else if(operatorTerm.isDivision())
    {
        string variableName(variable.getVariableName());
        Monomial newMonomial(monomial);
        Monomial::VariablesToExponentsMap & variablesMap(newMonomial.getVariablesToExponentsMapReference());
        variablesMap[variableName]=variablesMap[variableName]-1;
        result.setValue(Term(newMonomial));
    }
    else if(operatorTerm.isRaiseToPower())
    {
        result.setValue(Term(createExpression(Terms{Term(monomial), Term(operatorTerm), Term(variable)})));
    }
    return result;
}

AlbaOptional<Term> TermsSimplificator::combineConstantOperatorMonomial(
        Constant const& constant,
        Operator const& operatorTerm,
        Monomial const& monomial) const
{
    AlbaOptional<Term> result;
    if(operatorTerm.isAddition())
    {
        result.setValue(Term(Polynomial{
                                 Monomial(constant.getNumberConstReference(), {}),
                                 monomial
                             }));
    }
    else if(operatorTerm.isSubtraction())
    {
        result.setValue(Term(Polynomial{
                                 Monomial(constant.getNumberConstReference(), {}),
                                 Monomial(monomial.getConstantConstReference()*-1, monomial.getVariablesToExponentsMapConstReference())
                             }));
    }
    else if(operatorTerm.isMultiplication())
    {
        result.setValue(Term(Monomial(constant.getNumberConstReference()*monomial.getConstantConstReference(), monomial.getVariablesToExponentsMapConstReference())));
    }
    else if(operatorTerm.isDivision())
    {
        Monomial::VariablesToExponentsMap variablesMap(monomial.getVariablesToExponentsMapConstReference());
        performChangeForVariables(variablesMap, [&constant](string const &, AlbaNumber & exponent)
        {
            exponent=exponent*-1;
        });
        result.setValue(Term(Monomial(constant.getNumberConstReference()/monomial.getConstantConstReference(), variablesMap)));
    }
    else if(operatorTerm.isRaiseToPower())
    {
        result.setValue(Term(createExpression(Terms{Term(constant), Term(operatorTerm), Term(monomial)})));
    }
    return result;
}

AlbaOptional<Term> TermsSimplificator::combineVariableOperatorMonomial(
        Variable const& variable,
        Operator const& operatorTerm,
        Monomial const& monomial) const
{
    AlbaOptional<Term> result;
    if(canBeAddedOrSubtracted(monomial, variable))
    {
        result = combineVariableOperatorMonomialSameMonomialVariable(variable, operatorTerm, monomial);
    }
    else
    {
        result = combineVariableOperatorMonomialDifferentMonomialVariable(variable, operatorTerm, monomial);
    }
    return result;
}

AlbaOptional<Term> TermsSimplificator::combineVariableOperatorMonomialSameMonomialVariable(
        Variable const& variable,
        Operator const& operatorTerm,
        Monomial const& monomial) const
{
    AlbaOptional<Term> result;
    if(operatorTerm.isAddition())
    {
        result.setValue(Term(Monomial(monomial.getConstantConstReference()+1, {{variable.getVariableName(), 1}})));
    }
    else if(operatorTerm.isSubtraction())
    {
        result.setValue(Term(Monomial(AlbaNumber(1)-monomial.getConstantConstReference(), {{variable.getVariableName(), 1}})));
    }
    else if(operatorTerm.isMultiplication())
    {
        result.setValue(Term(Monomial(monomial.getConstantConstReference(), {{variable.getVariableName(), 2}})));
    }
    else if(operatorTerm.isDivision())
    {
        result.setValue(Term(AlbaNumber(1)/monomial.getConstantConstReference()));
    }
    else if(operatorTerm.isRaiseToPower())
    {
        result.setValue(Term(createExpression(Terms{Term(variable), Term(operatorTerm), Term(monomial)})));
    }
    return result;
}

AlbaOptional<Term> TermsSimplificator::combineVariableOperatorMonomialDifferentMonomialVariable(
        Variable const& variable,
        Operator const& operatorTerm,
        Monomial const& monomial) const
{
    AlbaOptional<Term> result;
    if(operatorTerm.isAddition())
    {
        result.setValue(Term(Polynomial{
                                 Monomial(1, {{variable.getVariableName(), 1}}),
                                 monomial
                             }));
    }
    else if(operatorTerm.isSubtraction())
    {
        result.setValue(Term(Polynomial{
                                 Monomial(1, {{variable.getVariableName(), 1}}),
                                 Monomial(monomial.getConstantConstReference()*-1, monomial.getVariablesToExponentsMapConstReference())
                             }));
    }
    else if(operatorTerm.isMultiplication())
    {
        string variableName(variable.getVariableName());
        Monomial newMonomial(monomial);
        Monomial::VariablesToExponentsMap & variablesMap(newMonomial.getVariablesToExponentsMapReference());
        variablesMap[variableName]=variablesMap[variableName]+1;
        result.setValue(Term(newMonomial));
    }
    else if(operatorTerm.isDivision())
    {
        string variableName(variable.getVariableName());
        Monomial::VariablesToExponentsMap variablesMap(monomial.getVariablesToExponentsMapConstReference());
        performChangeForVariables(variablesMap, [](string const &, AlbaNumber & exponent)
        {
            exponent=exponent*-1;
        });
        variablesMap[variableName]=variablesMap[variableName]+1;
        result.setValue(Term(Monomial(AlbaNumber(1)/monomial.getConstantConstReference(), variablesMap)));
    }
    else if(operatorTerm.isRaiseToPower())
    {
        result.setValue(Term(createExpression(Terms{Term(variable), Term(operatorTerm), Term(monomial)})));
    }
    return result;
}

void TermsSimplificator::eraseTermsInclusive(
        unsigned int const firstIndex,
        unsigned int const secondIndex){
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
