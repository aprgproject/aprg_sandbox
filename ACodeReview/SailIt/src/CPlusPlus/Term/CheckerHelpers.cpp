#include "CheckerHelpers.hpp"

#include "TermChecker.hpp"
#include <String/AlbaStringHelper.hpp>

#include <algorithm>

using namespace alba::stringHelper;

namespace codeReview {

bool CheckerHelpers::isAssignmentOperator(Term const& term) {
    vector<string> operators{"=", "+=", "-=", "*=", "/=", "%=", "<<=", ">>=", "&=", "^=", "|="};
    return isIncludedInTheList(operators, term.getString());
}

bool CheckerHelpers::isBiDirectionalOperator(Term const& term) {
    vector<string> operators{".*", "->*", "*",  "/",  "%",  "+", "-", "<<", ">>", "<",
                             "<=", ">",   ">=", "==", "!=", "&", "^", "|",  "&&", "||"};
    return isIncludedInTheList(operators, term.getString());
}

bool CheckerHelpers::isConstant(TermType const termType) {
    return TermType::Constant_Boolean == termType || TermType::Constant_Number == termType ||
           TermType::Constant_Character == termType || TermType::Constant_String == termType;
}

bool CheckerHelpers::isConstant(Term const& term) { return isConstant(term.getTermType()); }

bool CheckerHelpers::isIgnorable(TermType const termType) {
    return TermType::Comment == termType || TermType::MultiLine_Comment == termType ||
           TermType::SingleLine_Comment == termType || TermType::CPlusPlusIgnorableIdentifier == termType;
}

bool CheckerHelpers::isIgnorable(Term const& term) { return isIgnorable(term.getTermType()); }

bool CheckerHelpers::isIgnorable(TermChecker const& termChecker) {
    return isIgnorable(termChecker.getTerm().getTermType());
}

bool CheckerHelpers::isIgnorable(string const& stringToCheck) {
    string firstTwoCharacters(stringToCheck.substr(0, 2));
    return "//" == firstTwoCharacters || "/*" == firstTwoCharacters;
}

bool CheckerHelpers::isEmpty(TermType const termType) { return TermType::Empty == termType; }

bool CheckerHelpers::isEmpty(Term const& term) { return isEmpty(term.getTermType()); }

bool CheckerHelpers::isIncrementDecrementOperator(Term const& term) {
    vector<string> operators{"++", "--"};
    return isIncludedInTheList(operators, term.getString());
}

bool CheckerHelpers::isLValue(TermType const termType) {
    return TermType::Variable == termType || TermType::Value_LValue == termType;
}

bool CheckerHelpers::isNewLine(string const& stringToCheck) { return "\n" == stringToCheck; }

bool CheckerHelpers::isNewLine(Term const& term) { return TermType::NewLine == term.getTermType(); }

bool CheckerHelpers::isNewLine(TermChecker const& termChecker) {
    return TermType::NewLine == termChecker.getTerm().getTermType();
}

bool CheckerHelpers::isOtherMacro(Term const& term) {
    if (TermType::Macro == term.getTermType()) {
        vector<string> operators{"#ifdef", "#ifndef", "#if", "#endif", "#else", "#elif", "#line", "#error", "#pragma"};
        return isIncludedInTheList(operators, term.getString());
    }
    return false;
}

bool CheckerHelpers::isProcessed(Term const& term) { return isProcessed(term.getTermType()); }

bool CheckerHelpers::isProcessed(TermType const termType) {
    return TermType::ProcessedTerm == termType || TermType::MultiLine_IfElseIfStartChain_Ignorable == termType ||
           TermType::Comment == termType || TermType::SingleLine_Comment == termType ||
           TermType::MultiLine_Comment == termType || TermType::CPlusPlusIgnorableIdentifier == termType;
}

bool CheckerHelpers::isPrefixOperator(Term const& term) {
    vector<string> operators{"++", "--", "+", "-", "!", "~", "*", "&"};
    return isIncludedInTheList(operators, term.getString());
}

bool CheckerHelpers::isRelationalBiDirectionalOperator(Term const& term) {
    vector<string> operators{"<", "<=", ">", ">=", "==", "!=", "&&", "||"};
    return isIncludedInTheList(operators, term.getString());
}

bool CheckerHelpers::isRelationalPrefixOperator(Term const& term) {
    vector<string> operators{"!"};
    return isIncludedInTheList(operators, term.getString());
}

bool CheckerHelpers::isRValue(TermType const termType) {
    return isConstant(termType) || TermType::Value_RValue == termType || TermType::Value_RValue_CanBeALine == termType;
}

bool CheckerHelpers::isSingleLineOrMultiLineComment(TermType const termType) {
    return TermType::SingleLine_Comment == termType || TermType::MultiLine_Comment == termType;
}

bool CheckerHelpers::isStopForTermSimplification(Term const& term) {
    if (TermType::Macro == term.getTermType()) return true;
    vector<string> operators{";", ")", "}"};
    return isIncludedInTheList(operators, term.getString());
}

bool CheckerHelpers::isCPlusPlusType(TermType const termType) {
    return TermType::Type == termType || TermType::Class == termType;
}

bool CheckerHelpers::isValue(TermType const termType) { return isLValue(termType) || isRValue(termType); }

bool CheckerHelpers::isValue(Term const& term) { return isValue(term.getTermType()); }

bool CheckerHelpers::isWhiteSpace(string const& stringToCheck) { return " " == stringToCheck; }

bool CheckerHelpers::isWhiteSpace(Term const& term) { return TermType::WhiteSpace == term.getTermType(); }

bool CheckerHelpers::isWhiteSpace(TermChecker const& termChecker) {
    return TermType::WhiteSpace == termChecker.getTerm().getTermType();
}

bool CheckerHelpers::isWhiteSpaceOrNewLine(TermType const termType) {
    return TermType::WhiteSpace == termType || TermType::NewLine == termType;
}

bool CheckerHelpers::isIncludedInTheList(VectorOfStrings strings, string const& termString) {
    return any_of(strings.begin(), strings.end(), [termString](string string1) { return termString == string1; });
}

}  // namespace codeReview
