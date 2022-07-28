#include "StringHelpers.hpp"

#include <Algebra/Constructs/TermsAggregator.hpp>
#include <Algebra/Term/Utilities/EnumHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace algebra
{

bool isOperator(string const& stringObject)
{
    return "+" == stringObject || "-" == stringObject || "*" == stringObject || "/" == stringObject
            || "^" == stringObject || "(" == stringObject || ")" == stringObject;
}

bool isFunction(string const& stringObject)
{
    return "abs" == stringObject;
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
    string result;
    if(!termsWithDetails.empty())
    {
        result += getString(termsWithDetails.front());
        for(unsigned int i=1; i<termsWithDetails.size(); i++)
        {
            result += ", ";
            result += getString(termsWithDetails.at(i));
        }
    }
    return result;
}
string getString(TermWithDetails const& termWithDetails)
{
    return string("{")+termWithDetails.baseTermSharedPointer->getDisplayableString()            +"}{"+getEnumShortString(termWithDetails.association)+"}";
}

string createVariableNameForSubstitution(Term const& term)
{
    string variableName = string("{") + term.getDisplayableString() + "}";
    return variableName;
}

Term constructTermFromString(string const& valueString)
{
    Term result;
    if(!valueString.empty())
    {
        if(isNumber(valueString.at(0)))
        {
            result = Term(convertStringToAlbaNumber(valueString));
        }
        else
        {
            result = Term(valueString);
        }
    }
    return result;
}

Term buildTermIfPossible(string const& termString)
{
    Term result;
    TermsAggregator aggregator(tokenizeToTerms(termString));
    aggregator.simplifyTerms();
    Terms const& simplifiedTerms(aggregator.getTermsConstReference());
    if(simplifiedTerms.size() == 1)
    {
        result = simplifiedTerms.at(0);
    }
    return result;
}

Terms tokenizeToTerms(string const& inputString)
{
    Terms tokenizedTerms;
    string valueString;
    for(char const c : inputString)
    {
        if(!isWhiteSpace(c))
        {
            string characterString(1, c);
            if(isOperator(characterString))
            {
                addValueTermIfNotEmpty(tokenizedTerms, valueString);
                valueString.clear();
                tokenizedTerms.emplace_back(characterString);
            }
            else
            {
                valueString+=characterString;
            }
        }
    }
    addValueTermIfNotEmpty(tokenizedTerms, valueString);
    return tokenizedTerms;
}

void addValueTermIfNotEmpty(Terms & terms, string const& valueString)
{
    if(!valueString.empty())
    {
        terms.emplace_back(constructTermFromString(valueString));
    }
}

}

}
