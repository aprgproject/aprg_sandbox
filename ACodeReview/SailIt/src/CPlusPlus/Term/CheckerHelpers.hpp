#pragma once

#include "Term.hpp"

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace codeReview
{

class TermChecker;

namespace CheckerHelpers
{
    typedef vector<string> VectorOfStrings;
    bool isAssignmentOperator(Term const& term);
    bool isBiDirectionalOperator(Term const& term);
    bool isConstant(TermType const termType);
    bool isConstant(Term const& term);
    bool isEmpty(TermType const termType);
    bool isEmpty(Term const& term);
    bool isIncrementDecrementOperator(Term const& term);
    bool isLValue(TermType const termType);
    bool isNewLine(string const& expectedString);
    bool isNewLine(Term const& term);
    bool isNewLine(TermChecker const& termChecker);
    bool isIgnorable(TermType const termType);
    bool isIgnorable(Term const& term);
    bool isIgnorable(TermChecker const& termChecker);
    bool isIgnorable(string const& stringToCheck);
    bool isOtherMacro(Term const& term);
    bool isProcessed(Term const& term);
    bool isProcessed(TermType const termType);
    bool isPrefixOperator(Term const& term);
    bool isRelationalBiDirectionalOperator(Term const& term);
    bool isRelationalPrefixOperator(Term const& term);
    bool isRValue(TermType const termType);
    bool isSingleLineOrMultiLineComment(TermType const termType);
    bool isStopForTermSimplification(Term const& term);
    bool isCPlusPlusType(TermType const termType);
    bool isValue(TermType const termType);
    bool isValue(Term const& term);
    bool isWhiteSpace(string const& expectedString);
    bool isWhiteSpace(Term const& term);
    bool isWhiteSpace(TermChecker const& termChecker);
    bool isWhiteSpaceOrNewLine(TermType const termType);
    bool isIncludedInTheList(VectorOfStrings strings, string const& termString);
}

}


