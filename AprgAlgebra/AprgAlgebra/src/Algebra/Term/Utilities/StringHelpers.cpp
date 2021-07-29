#include "StringHelpers.hpp"

#include <Algebra/Term/Utilities/EnumHelpers.hpp>
#include <String/AlbaStringHelper.hpp>

using namespace alba::stringHelper;
using namespace std;
using TermsWithDetails=alba::algebra::TermsWithAssociation::TermsWithDetails;
using TermWithDetails=alba::algebra::TermsWithAssociation::TermWithDetails;

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

Term constructTermFromValueString(string const& valueTerm)
{
    Term result;
    if(isNumber(valueTerm.at(0)))
    {
        result = Term(convertStringToAlbaNumber(valueTerm));
    }
    else
    {
        result = Term(valueTerm);
    }
    return result;
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
        terms.emplace_back(constructTermFromValueString(valueTerm));
    }
}

}

}
