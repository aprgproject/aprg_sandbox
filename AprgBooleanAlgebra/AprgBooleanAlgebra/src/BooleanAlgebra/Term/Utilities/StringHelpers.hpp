#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

#include <string>

namespace alba
{

namespace booleanAlgebra
{

bool isOperator(std::string const& stringObject);

unsigned int getOperatorPriority(std::string const& operatorString);

std::string getString(
        OperatorType const operatorType);
std::string getString(
        OperatorLevel const operatorLevel);
std::string getString(
        WrappedTerms const& wrappedTerms);
std::string getString(
        WrappedTerm const& wrappedTerm);
std::string createVariableTermNameForSubstitution(Term const& term);

Term constructTermFromString(std::string const& valueString);
Term buildTermIfPossible(std::string const& termString);

Terms tokenizeToTerms(std::string const& inputString);
void addValueTermIfNotEmpty(Terms & terms, std::string const& valueString);

}

}
