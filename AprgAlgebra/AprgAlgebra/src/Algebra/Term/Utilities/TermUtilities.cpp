#include "TermUtilities.hpp"

#include <Algebra/Factorization/Factorization.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Macros/AlbaMacros.hpp>
#include <Math/AlbaMathHelper.hpp>

using namespace alba::algebra::Factorization;
using namespace alba::mathHelper;
using namespace alba::stringHelper;
using namespace std;
using TermWithDetails=alba::algebra::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::algebra::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace algebra
{

bool isOperator(string const& stringAsParameter)
{
    return "+" == stringAsParameter || "-" == stringAsParameter || "*" == stringAsParameter || "/" == stringAsParameter
            || "^" == stringAsParameter || "(" == stringAsParameter || ")" == stringAsParameter;
}

bool isFunction(string const& stringAsParameter)
{
    return "abs" == stringAsParameter;
}

bool canBeMergedInAMonomialByAdditionOrSubtraction(Term const& term1, Term const& term2)
{
    bool result(false);
    if(term1.isConstant() && term2.isConstant())
    {
        result = true;
    }
    else if(term1.isVariable() && term2.isVariable())
    {
        result = canBeMergedInAMonomialByAdditionOrSubtraction(term1.getVariableConstReference(), term2.getVariableConstReference());
    }
    else if(term1.isMonomial() && term2.isMonomial())
    {
        result = canBeMergedInAMonomialByAdditionOrSubtraction(term1.getMonomialConstReference(), term2.getMonomialConstReference());
    }
    else if(term1.isMonomial() && term2.isVariable())
    {
        result = canBeMergedInAMonomialByAdditionOrSubtraction(term1.getMonomialConstReference(), term2.getVariableConstReference());
    }
    else if(term1.isVariable() && term2.isMonomial())
    {
        result = canBeMergedInAMonomialByAdditionOrSubtraction(term2.getMonomialConstReference(), term1.getVariableConstReference());
    }
    return result;
}

bool canBeMergedInAMonomialByAdditionOrSubtraction(Monomial const& monomial1, Monomial const& monomial2)
{
    Monomial::VariablesToExponentsMap const& variablesMap1(monomial1.getVariablesToExponentsMapConstReference());
    Monomial::VariablesToExponentsMap const& variablesMap2(monomial2.getVariablesToExponentsMapConstReference());
    bool result(false);
    if(variablesMap1.size() == variablesMap2.size())
    {
        using MapConstIterator=Monomial::VariablesToExponentsMap::const_iterator;
        using MismatchResultType=pair<MapConstIterator, MapConstIterator>;
        MismatchResultType mismatchResult = mismatch(variablesMap1.cbegin(), variablesMap1.end(), variablesMap2.cbegin());
        result = mismatchResult.first == variablesMap1.cend();
    }
    return result;
}

bool canBeMergedInAMonomialByAdditionOrSubtraction(Monomial const& monomial, Variable const& variable)
{
    Monomial::VariablesToExponentsMap const& variablesMap(monomial.getVariablesToExponentsMapConstReference());
    string variableName(variable.getVariableName());
    bool result(false);
    if(variablesMap.size() == 1)
    {
        if(variablesMap.find(variableName) != variablesMap.cend())
        {
            result = variablesMap.at(variableName)==1;
        }
    }
    return result;
}

bool canBeMergedInAMonomialByAdditionOrSubtraction(Variable const& variable1, Variable const& variable2)
{
    return variable1.getVariableName() == variable2.getDisplayableString();
}

bool willHaveNoEffectOnAdditionOrSubtraction(Term const& term)
{
    return term.isEmpty() || term.isTheValueZero();
}

bool willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term const& term)
{
    return term.isEmpty() || term.isTheValueOne();
}

unsigned int getOperatorPriority(string const& operatorString)
{
    unsigned int result=0;
    if("(" == operatorString)
    {
        result=1;
    }
    else if(")" == operatorString)
    {
        result=2;
    }
    else if("+" == operatorString)
    {
        result=3;
    }
    else if("-" == operatorString)
    {
        result=4;
    }
    else if("*" == operatorString)
    {
        result=5;
    }
    else if("/" == operatorString)
    {
        result=6;
    }
    else if("^" == operatorString)
    {
        result=7;
    }
    return result;
}

unsigned int getAssociationPriority(TermAssociationType const association)
{
    unsigned int result(0);
    switch(association)
    {
    case TermAssociationType::Positive:
        result=1;
        break;
    case TermAssociationType::Negative:
        result=2;
        break;
    }
    return result;
}

unsigned int getOperatorLevelInversePriority(OperatorLevel const operatorLevel)
{
    unsigned int result(0);
    switch(operatorLevel)
    {
    case OperatorLevel::Unknown:
        result=0;
        break;
    case OperatorLevel::AdditionAndSubtraction:
        result=3;
        break;
    case OperatorLevel::MultiplicationAndDivision:
        result=2;
        break;
    case OperatorLevel::RaiseToPower:
        result=1;
        break;
    }
    return result;
}

unsigned int getTermTypePriorityValue(TermType const termType)
{
    unsigned int result(0);
    if(TermType::Operator == termType)
    {
        result=1;
    }
    else if(TermType::Constant == termType)
    {
        result=2;
    }
    else if(TermType::Variable == termType)
    {
        result=3;
    }
    else if(TermType::Monomial == termType)
    {
        result=4;
    }
    else if(TermType::Polynomial == termType)
    {
        result=5;
    }
    else if(TermType::Expression == termType)
    {
        result=6;
    }
    return result;
}

AlbaNumbers getRoots(Polynomial const& polynomial)
{
    AlbaNumbers result;
    VariableNamesSet variableNames;
    retrieveVariableNames(polynomial, variableNames);
    if(variableNames.size() == 1)
    {
        Polynomial polynomialToFactorize(polynomial);
        Polynomials factorizedPolynomials(factorize(polynomialToFactorize));
        for(Polynomial const& factorizedPolynomial : factorizedPolynomials)
        {
            Monomials const& monomials(factorizedPolynomial.getMonomialsConstReference());
            AlbaNumber maxDegree(factorizedPolynomial.getMaxDegree());
            if(monomials.size() == 1 && maxDegree > 0)
            {
                result.emplace_back(AlbaNumber(0));            }
            else if(monomials.size() == 2)
            {
                Monomial firstMonomial(monomials.at(0));                Monomial secondMonomial(monomials.at(1));
                if(secondMonomial.isConstantOnly())
                {
                    AlbaNumber constant(-secondMonomial.getConstantConstReference());
                    constant = constant/firstMonomial.getConstantConstReference();
                    constant = constant^(AlbaNumber(1)/firstMonomial.getMaxExponent());
                    if(constant.hasValidValue())
                    {
                        result.emplace_back(constant);
                    }
                }
            }
        }
    }
    return result;
}

string getEnumShortString(TermType const termType)
{
    switch(termType)
    {
    ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Empty, "Empty")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Constant, "Constant")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Variable, "Variable")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Operator, "Operator")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Monomial, "Monomial")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Polynomial, "Polynomial")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Expression, "Expression")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Function, "Function")
            default:
        return "default";
    }
}

string getEnumShortString(TermAssociationType const association)
{
    switch(association)
    {
    ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermAssociationType::Positive, "{POS}")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermAssociationType::Negative, "{NEG}")
            default:
        return "default";
    }
}

string getEnumShortString(OperatorLevel const operatorLevel)
{
    switch(operatorLevel)
    {
    ALBA_MACROS_CASE_ENUM_SHORT_STRING(OperatorLevel::Unknown, "{?}")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(OperatorLevel::AdditionAndSubtraction, "{+-}")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(OperatorLevel::MultiplicationAndDivision, "{*/}")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(OperatorLevel::RaiseToPower, "{^}")
            default:
        return "default";
    }
}

string getOperatingString(
        OperatorLevel const operatorLevel,
        TermAssociationType const association)
{
    string result;
    if(TermAssociationType::Positive == association)
    {
        switch(operatorLevel)
        {
        case OperatorLevel::AdditionAndSubtraction:
            result = "+";
            break;
        case OperatorLevel::MultiplicationAndDivision:
            result = "*";
            break;
        case OperatorLevel::RaiseToPower:
            result = "^";
            break;
        default:
            break;
        }
    }
    else if(TermAssociationType::Negative == association)
    {
        switch(operatorLevel)
        {
        case OperatorLevel::AdditionAndSubtraction:
            result = "-";
            break;
        case OperatorLevel::MultiplicationAndDivision:
            result = "/";
            break;
        default:
            break;
        }
    }
    return result;
}

string getFirstStringIfNegativeAssociation(
        OperatorLevel const operatorLevel,
        TermAssociationType const association)
{
    string result;
    if(TermAssociationType::Negative == association)
    {
        if(OperatorLevel::AdditionAndSubtraction == operatorLevel)
        {
            result = "-";
        }
        else if(OperatorLevel::MultiplicationAndDivision == operatorLevel)
        {
            result = "1/";
        }
    }
    return result;
}

string getString(TermsWithDetails const& termsWithDetails)
{
    bool isFirst(true);
    string result;
    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        if(!isFirst)
        {
            result += ", ";
        }
        isFirst=false;
        result += getString(termWithDetails);
    }
    return result;
}

string getString(TermWithDetails const& termWithDetails)
{
    return string("{")+termWithDetails.baseTermSharedPointer->getDisplayableString()
            +"}{"+getEnumShortString(termWithDetails.association)+"}";
}

string createVariableNameForSubstitution(Polynomial const& polynomial)
{
    string variableName = string("{") + polynomial.getDisplayableString() + "}";
    return variableName;
}

AlbaNumbersSet getNumbers(Term const& term)
{
    AlbaNumbersSet result;
    retrieveNumbers(term, result);
    return result;
}

void retrieveNumbers(Term const& term, AlbaNumbersSet & numbers)
{
    if(term.isConstant())
    {
        retrieveNumbers(term.getConstantConstReference(), numbers);
    }
    else if(term.isMonomial())
    {
        retrieveNumbers(term.getMonomialConstReference(), numbers);
    }
    else if(term.isPolynomial())
    {
        retrieveNumbers(term.getPolynomialConstReference(), numbers);
    }
    else if(term.isExpression())
    {
        retrieveNumbers(term.getExpressionConstReference(), numbers);
    }
    else if(term.isFunction())
    {
        retrieveNumbers(term.getFunctionConstReference(), numbers);
    }
}

void retrieveNumbers(Constant const& constant, AlbaNumbersSet & numbers)
{
    numbers.emplace(constant.getNumberConstReference());
}

void retrieveNumbers(Monomial const& monomial, AlbaNumbersSet & numbers)
{
    numbers.emplace(monomial.getConstantConstReference());
    for(Monomial::VariableExponentPair const& variableExponentsPair
        : monomial.getVariablesToExponentsMapConstReference())
    {
        numbers.emplace(variableExponentsPair.second);
    }
}

void retrieveNumbers(Polynomial const& polynomial, AlbaNumbersSet & numbers)
{
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        retrieveNumbers(monomial, numbers);
    }
}

void retrieveNumbers(Expression const& expression, AlbaNumbersSet & numbers)
{
    for(TermsWithAssociation::TermWithDetails const& termWithDetails
        : expression.getTermsWithAssociation().getTermsWithDetails())
    {
        retrieveNumbers(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer), numbers);
    }
}

void retrieveNumbers(Function const& functionTerm, AlbaNumbersSet & numbers)
{
    retrieveNumbers(functionTerm.getInputExpressionConstReference(), numbers);
}

VariableNamesSet getVariableNames(Term const& term)
{
    VariableNamesSet result;    retrieveVariableNames(term, result);
    return result;
}
void retrieveVariableNames(Term const& term, VariableNamesSet & variableNames)
{
    if(term.isVariable())
    {
        retrieveVariableNames(term.getVariableConstReference(), variableNames);
    }
    else if(term.isMonomial())
    {
        retrieveVariableNames(term.getMonomialConstReference(), variableNames);
    }
    else if(term.isPolynomial())
    {
        retrieveVariableNames(term.getPolynomialConstReference(), variableNames);
    }
    else if(term.isExpression())
    {
        retrieveVariableNames(term.getExpressionConstReference(), variableNames);
    }
    else if(term.isFunction())
    {
        retrieveVariableNames(term.getFunctionConstReference(), variableNames);
    }
}

void retrieveVariableNames(Variable const& variable, VariableNamesSet & variableNames)
{
    variableNames.emplace(variable.getVariableName());
}

void retrieveVariableNames(Monomial const& monomial, VariableNamesSet & variableNames)
{
    for(Monomial::VariableExponentPair const& variableExponentsPair
        : monomial.getVariablesToExponentsMapConstReference())
    {
        variableNames.emplace(variableExponentsPair.first);
    }
}

void retrieveVariableNames(Polynomial const& polynomial, VariableNamesSet & variableNames)
{
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        retrieveVariableNames(monomial, variableNames);
    }
}

void retrieveVariableNames(Expression const& expression, VariableNamesSet & variableNames)
{
    for(TermsWithAssociation::TermWithDetails const& termWithDetails
        : expression.getTermsWithAssociation().getTermsWithDetails())
    {
        retrieveVariableNames(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer), variableNames);
    }
}

void retrieveVariableNames(Function const& functionTerm, VariableNamesSet & variableNames)
{
    retrieveVariableNames(functionTerm.getInputExpressionConstReference(), variableNames);
}

AlbaNumber getGcfCoefficientInMonomials(Monomials const& monomials)
{
    AlbaNumber commonCoefficient(1);
    bool isFirst(true);
    for(Monomial const& monomial : monomials)
    {
        AlbaNumber const& coefficient(monomial.getConstantConstReference());
        if(coefficient.isIntegerOrFractionType())
        {
            if(isFirst)
            {
                commonCoefficient = coefficient;
                isFirst = false;
            }
            else
            {
                commonCoefficient = getGreatestCommonFactor(commonCoefficient, coefficient);
            }
        }
    }
    return commonCoefficient;
}

AlbaNumber getLcmCoefficientInMonomials(Monomials const& monomials)
{
    AlbaNumber commonCoefficient(1);
    bool isFirst(true);
    for(Monomial const& monomial : monomials)
    {
        AlbaNumber const& coefficient(monomial.getConstantConstReference());
        if(coefficient.isIntegerOrFractionType())
        {
            if(isFirst)
            {
                commonCoefficient = coefficient;
                isFirst = false;
            }
            else
            {
                commonCoefficient = getLeastCommonMultiple(commonCoefficient, coefficient);
            }
        }
    }
    return commonCoefficient;
}

AlbaNumber getCommonSignInMonomials(Monomials const& monomials)
{
    bool isFirst(true);
    bool isFirstMonomialNegative(false);
    unsigned int negativeSignCount(0);
    for(Monomial const& monomial : monomials)
    {
        if(monomial.getConstantConstReference() < AlbaNumber(0))
        {
            negativeSignCount++;
            if(isFirst)
            {
                isFirstMonomialNegative = true;
            }
        }
        isFirst=false;
    }
    return (isFirstMonomialNegative||(negativeSignCount>0 && negativeSignCount == monomials.size())) ? -1 : 1;
}

Monomial getGcfMonomialInMonomials(Monomials const& monomials)
{
    AlbaNumber commonCoefficient(getGcfCoefficientInMonomials(monomials));
    Monomial minExponentMonomial(getMonomialWithMinimumExponentsInMonomials(monomials));
    if(commonCoefficient != 1)
    {
        commonCoefficient = getCommonSignInMonomials(monomials)*commonCoefficient;
    }
    minExponentMonomial.setConstant(commonCoefficient);
    minExponentMonomial.simplify();
    return minExponentMonomial;
}

Monomial getLcmMonomialInMonomials(Monomials const& monomials)
{
    AlbaNumber lcmCoefficient(getLcmCoefficientInMonomials(monomials));
    Monomial maxExponentMonomial(getMonomialWithMaximumExponentsInMonomials(monomials));
    maxExponentMonomial.setConstant(getCommonSignInMonomials(monomials)*lcmCoefficient);
    maxExponentMonomial.simplify();
    return maxExponentMonomial;
}

Monomial compareMonomialsAndSaveMinimumExponentsForEachVariable(Monomial const& firstMonomial, Monomial const& secondMonomial)
{
    Monomial::VariablesToExponentsMap newVariableExponentMap;
    VariableNamesSet variableNames;
    retrieveVariableNames(firstMonomial, variableNames);
    retrieveVariableNames(secondMonomial, variableNames);
    for(string const& variableName : variableNames)
    {
        newVariableExponentMap[variableName] = min(                    firstMonomial.getExponentForVariable(variableName),
                    secondMonomial.getExponentForVariable(variableName));
    }
    return Monomial(1, newVariableExponentMap);}

Monomial compareMonomialsAndSaveMaximumExponentsForEachVariable(Monomial const& firstMonomial, Monomial const& secondMonomial)
{
    Monomial::VariablesToExponentsMap newVariableExponentMap;
    VariableNamesSet variableNames;
    retrieveVariableNames(firstMonomial, variableNames);
    retrieveVariableNames(secondMonomial, variableNames);
    for(string const& variableName : variableNames)
    {
        newVariableExponentMap[variableName] = max(                    firstMonomial.getExponentForVariable(variableName),
                    secondMonomial.getExponentForVariable(variableName));
    }
    return Monomial(1, newVariableExponentMap);}

Monomial getMonomialWithMinimumExponentsInMonomials(Monomials const& monomials)
{
    Monomial monomialWithMinimumExponents(1, {});
    bool isFirst(true);
    for(Monomial const& monomial : monomials)
    {
        if(isFirst)
        {
            monomialWithMinimumExponents = monomial;
            isFirst=false;
        }
        else
        {
            monomialWithMinimumExponents
                    = compareMonomialsAndSaveMinimumExponentsForEachVariable(monomialWithMinimumExponents, monomial);
        }
    }
    monomialWithMinimumExponents.simplify();
    return monomialWithMinimumExponents;
}

Monomial getMonomialWithMaximumExponentsInMonomials(Monomials const& monomials)
{
    Monomial monomialWithMaximumExponents(1, {});
    bool isFirst(true);
    for(Monomial const& monomial : monomials)
    {
        if(isFirst)
        {
            monomialWithMaximumExponents = monomial;
            isFirst=false;
        }
        else
        {
            monomialWithMaximumExponents
                    = compareMonomialsAndSaveMaximumExponentsForEachVariable(monomialWithMaximumExponents, monomial);
        }
    }
    monomialWithMaximumExponents.simplify();
    return monomialWithMaximumExponents;
}

Terms tokenizeToTerms(string const& inputString)
{
    Terms tokenizedTerms;
    string valueTerm;
    for(char const c : inputString)
    {
        if(!isWhiteSpace(c))
        {
            string characterString(1, c);
            if(isOperator(characterString))
            {
                addValueTermIfNotEmpty(tokenizedTerms, valueTerm);
                valueTerm.clear();
                tokenizedTerms.emplace_back(characterString);
            }
            else
            {
                valueTerm+=characterString;
            }
        }
    }
    addValueTermIfNotEmpty(tokenizedTerms, valueTerm);
    return tokenizedTerms;
}

void addValueTermIfNotEmpty(Terms & terms, string const& valueTerm)
{
    if(!valueTerm.empty())
    {
        terms.emplace_back(convertValueTermStringToTerm(valueTerm));
    }
}

}

}
