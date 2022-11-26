#include "StringHelpers.hpp"

#include <BooleanAlgebra/Constructs/TermsAggregator.hpp>
#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/EnumHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <algorithm>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace booleanAlgebra
{

bool isConstant(string const& stringObject)
{
    string allCapital(getStringWithCapitalLetters(stringObject));
    return "TRUE" == allCapital
            || "FALSE" == allCapital
            || std::all_of(stringObject.cbegin(), stringObject.cend(), [](char const c)
    {
        return isNumber(c);
    });
}

bool isOperator(string const& stringObject)
{
    return "~" == stringObject || "&" == stringObject || "|" == stringObject || "(" == stringObject || ")" == stringObject;
}

bool isPrime(char const character)
{
    return '\'' == character;
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
    stringstream ss;
    if(!wrappedTerms.empty())
    {
        ss << wrappedTerms.front();
        for(auto it=wrappedTerms.cbegin()+1; it!=wrappedTerms.cend(); it++)
        {
            ss << ", " << *it;
        }
    }
    return ss.str();
}

string createVariableTermNameForSubstitution(Term const& term)
{
    stringstream ss;
    ss << "{" << term << "}";
    return ss.str();
}

Term buildTermIfPossible(string const& termString){
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
        terms.emplace_back(Term(valueString));
    }
}

}

}
