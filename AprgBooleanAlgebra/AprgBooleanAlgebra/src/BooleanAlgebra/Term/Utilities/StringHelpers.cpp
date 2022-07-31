#include "StringHelpers.hpp"

#include <BooleanAlgebra/Constructs/TermsAggregator.hpp>
#include <BooleanAlgebra/Term/Utilities/EnumHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace booleanAlgebra
{

bool isOperator(string const& stringObject)
{
    return "~" == stringObject || "&" == stringObject || "|" == stringObject || "(" == stringObject || ")" == stringObject;
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
    else if("~" == operatorString)
    {
        result=3;
    }
    else if("&" == operatorString)
    {
        result=4;
    }
    else if("|" == operatorString)
    {
        result=5;
    }
    return result;
}

string getString(
        OperatorType const operatorType)
{
    string result;
    switch(operatorType)
    {
    case OperatorType::Not:
        result = "~";
        break;
    case OperatorType::And:
        result = "&";
        break;
    case OperatorType::Or:
        result = "|";
        break;
    default:
        break;
    }
    return result;
}

string getString(
        OperatorLevel const operatorLevel)
{
    string result;
    switch(operatorLevel)
    {
    case OperatorLevel::And:
        result = "&";
        break;
    case OperatorLevel::Or:
        result = "|";
        break;
    default:
        break;
    }
    return result;
}

string getString(WrappedTerms const& wrappedTerms)
{
    string result;
    if(!wrappedTerms.empty())
    {
        result += getString(wrappedTerms.front());
        for(unsigned int i=1; i<wrappedTerms.size(); i++)
        {
            result += ", ";
            result += getString(wrappedTerms.at(i));
        }
    }
    return result;
}

string getString(WrappedTerm const& wrappedTerm)
{
    return string("{")+wrappedTerm.baseTermSharedPointer->getDisplayableString()+"}";
}

string createVariableTermNameForSubstitution(Term const& term)
{
    string variableName = string("{") + term.getDisplayableString() + "}";
    return variableName;
}

Term constructTermFromString(string const& valueString)
{
    Term result;
    if(!valueString.empty())
    {
        string allCapital(getStringWithCapitalLetters(valueString));
        if("TRUE" == allCapital || "FALSE" == allCapital || isNumber(valueString.front()))
        {
            result = Term(convertStringToBool(valueString));
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
