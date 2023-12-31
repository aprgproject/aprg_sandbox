#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>

namespace alba {

namespace algebra {

bool isOperator(std::string const& stringObject);
bool isFunction(std::string const& stringObject);

int getOperatorPriority(std::string const& operatorString);

std::string getOperatingString(OperatorLevel const operatorLevel, TermAssociationType const association);
std::string getFirstStringIfNegativeAssociation(
    OperatorLevel const operatorLevel, TermAssociationType const association);
std::string createVariableNameForSubstitution(Term const& term);

Term buildTermIfPossible(std::string const& termString);

Terms tokenizeToTerms(std::string const& inputString);
void addValueTermIfNotEmpty(Terms& terms, std::string const& valueString);

}  // namespace algebra

}  // namespace alba
