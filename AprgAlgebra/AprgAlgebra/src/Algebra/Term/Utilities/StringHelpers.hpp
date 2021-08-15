#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>

namespace alba
{

namespace algebra
{

bool isOperator(std::string const& stringAsParameter);
bool isFunction(std::string const& stringAsParameter);

unsigned int getOperatorPriority(std::string const& operatorString);

std::string getOperatingString(
        OperatorLevel const operatorLevel,
        TermAssociationType const association);
std::string getFirstStringIfNegativeAssociation(
        OperatorLevel const operatorLevel,
        TermAssociationType const association);
std::string getString(
        TermsWithAssociation::TermsWithDetails const& termsWithDetails);
std::string getString(
        TermsWithAssociation::TermWithDetails const& termWithDetails);
std::string createVariableNameForSubstitution(Polynomial const& polynomial);

Term constructTermFromString(std::string const& valueString);
Term buildTermIfPossible(std::string const& termString);

Terms tokenizeToTerms(std::string const& inputString);
void addValueTermIfNotEmpty(Terms & terms, std::string const& valueString);

}
}