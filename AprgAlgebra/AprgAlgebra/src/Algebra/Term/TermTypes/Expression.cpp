#include "Expression.hpp"

#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/EnumHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <sstream>

using namespace alba::algebra::Simplification;
using namespace std;

namespace alba {

namespace algebra {

Expression::Expression()
    : m_commonOperatorLevel(OperatorLevel::Unknown), m_termsWithAssociation(), m_isSimplified(false) {}

Expression::Expression(BaseTerm const& baseTerm)
    : m_commonOperatorLevel(OperatorLevel::Unknown),
      m_termsWithAssociation(TermsWithDetails{{baseTerm, TermAssociationType::Positive}}),
      m_isSimplified(false) {}

Expression::Expression(BaseTerm&& baseTerm)
    : m_commonOperatorLevel(OperatorLevel::Unknown),
      m_termsWithAssociation(TermsWithDetails{{move(baseTerm), TermAssociationType::Positive}}),
      m_isSimplified(false) {}

Expression::Expression(OperatorLevel const operatorLevel, TermsWithDetails const& termsWithDetails)
    : m_commonOperatorLevel(termsWithDetails.empty() ? OperatorLevel::Unknown : operatorLevel),
      m_termsWithAssociation(termsWithDetails),
      m_isSimplified(false) {}

Expression::Expression(OperatorLevel const operatorLevel, TermsWithDetails&& termsWithDetails)
    : m_commonOperatorLevel(termsWithDetails.empty() ? OperatorLevel::Unknown : operatorLevel),
      m_termsWithAssociation(move(termsWithDetails)),
      m_isSimplified(false) {}

bool Expression::operator==(Expression const& second) const {
    return m_commonOperatorLevel == second.m_commonOperatorLevel &&
           m_termsWithAssociation == second.m_termsWithAssociation;
}

bool Expression::operator!=(Expression const& second) const { return !(operator==(second)); }

bool Expression::operator<(Expression const& second) const {
    bool result(false);
    if (m_commonOperatorLevel == second.m_commonOperatorLevel) {
        return m_termsWithAssociation < second.m_termsWithAssociation;
    } else {
        result = getOperatorLevelInversePriority(m_commonOperatorLevel) <
                 getOperatorLevelInversePriority(second.m_commonOperatorLevel);
    }
    return result;
}

bool Expression::isEmpty() const { return m_termsWithAssociation.isEmpty(); }

bool Expression::containsOnlyOnePositivelyAssociatedTerm() const {
    return 1 == m_termsWithAssociation.getSize() && getFirstAssociationType() == TermAssociationType::Positive;
}

bool Expression::isSimplified() const { return m_isSimplified; }

OperatorLevel Expression::getCommonOperatorLevel() const { return m_commonOperatorLevel; }

BaseTerm const& Expression::getFirstTerm() const { return m_termsWithAssociation.getFirstTerm(); }

TermAssociationType Expression::getFirstAssociationType() const {
    return m_termsWithAssociation.getFirstAssociationType();}

TermsWithAssociation const& Expression::getTermsWithAssociation() const { return m_termsWithAssociation; }
string Expression::getDebugString() const {
    stringstream ss;
    TermsWithDetails const& termsWithDetails(m_termsWithAssociation.getTermsWithDetails());
    ss << "( " << getEnumShortString(m_commonOperatorLevel) << "||";
    if (!termsWithDetails.empty()) {
        TermWithDetails const& firstTermWithDetails(termsWithDetails.front());
        ss << getFirstStringIfNegativeAssociation(m_commonOperatorLevel, firstTermWithDetails.association)
           << getTermConstReferenceFromUniquePointer(firstTermWithDetails.baseTermPointer).getDebugString()
           << getEnumShortString(firstTermWithDetails.association);
        for (auto it = termsWithDetails.cbegin() + 1; it != termsWithDetails.cend(); it++) {
            TermWithDetails const& termWithDetails(*it);
            ss << getOperatingString(m_commonOperatorLevel, termWithDetails.association)
               << getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer).getDebugString()
               << getEnumShortString(termWithDetails.association);
        }
    }
    ss << " )";
    return ss.str();
}

TermsWithAssociation& Expression::getTermsWithAssociationReference() {
    clearSimplifiedFlag();
    return m_termsWithAssociation;
}

void Expression::clear() {
    m_commonOperatorLevel = OperatorLevel::Unknown;
    m_termsWithAssociation.clear();
    clearSimplifiedFlag();
}

void Expression::clearAndPutTermInTermsWithAssociation(BaseTerm const& baseTerm) {
    m_commonOperatorLevel = OperatorLevel::Unknown;
    m_termsWithAssociation = TermsWithDetails{{baseTerm, TermAssociationType::Positive}};
    clearSimplifiedFlag();
}

void Expression::putTermWithAdditionIfNeeded(BaseTerm const& baseTerm) {
    Term const& term(getTermConstReferenceFromBaseTerm(baseTerm));
    if (willHaveNoEffectOnAdditionOrSubtraction(term)) {
        if (isEmpty()) {
            setTerm(Term(0));
        }
    } else {
        if (willHaveNoEffectOnAdditionOrSubtraction(*this)) {
            setTerm(baseTerm);
        } else {
            putTermWithAddition(baseTerm);
        }
    }
    clearSimplifiedFlag();
}

void Expression::putTermWithSubtractionIfNeeded(BaseTerm const& baseTerm) {
    Term const& term(getTermConstReferenceFromBaseTerm(baseTerm));
    if (willHaveNoEffectOnAdditionOrSubtraction(term)) {
        if (isEmpty()) {
            setTerm(Term(0));
        }
    } else {
        if (willHaveNoEffectOnAdditionOrSubtraction(*this)) {
            clear();
            m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
            putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Negative);
        } else {
            putTermWithSubtraction(baseTerm);
        }
    }
    clearSimplifiedFlag();
}

void Expression::putTermWithMultiplicationIfNeeded(BaseTerm const& baseTerm) {
    Term const& term(getTermConstReferenceFromBaseTerm(baseTerm));
    if (term.isExpression()) {
        putExpressionWithMultiplication(term.getAsExpression());
    } else {
        putOnlyTermWithMultiplicationIfNeeded(baseTerm);
    }    clearSimplifiedFlag();
}

void Expression::putTermWithDivisionIfNeeded(BaseTerm const& baseTerm) {    Term const& term(getTermConstReferenceFromBaseTerm(baseTerm));
    if (willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(term)) {
        if (isEmpty()) {
            setTerm(Term(1));
        }
    } else {
        if (willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(*this)) {
            clear();
            m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
            putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Negative);
        } else {
            putTermWithDivision(baseTerm);
        }
    }
    clearSimplifiedFlag();
}

void Expression::putTermWithRaiseToPowerIfNeeded(BaseTerm const& baseTerm) {
    Term const& term(getTermConstReferenceFromBaseTerm(baseTerm));
    if (!willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(term)) {
        if (isEmpty()) {
            setTerm(baseTerm);
        } else {
            putTermWithRaiseToPower(baseTerm);
        }
    }
    clearSimplifiedFlag();
}

void Expression::putPolynomialFirstWithMultiplication(Polynomial const& polynomial) {
    if (OperatorLevel::AdditionAndSubtraction == m_commonOperatorLevel) {
        TermsWithDetails termsWithDetails(m_termsWithAssociation.getTermsWithDetails());
        clear();
        distributeAndMultiply(polynomial, termsWithDetails);
    } else {
        Expression expressionCopy(*this);
        clear();
        distributeAndMultiply(polynomial, expressionCopy);
    }
    clearSimplifiedFlag();
}

void Expression::putPolynomialSecondWithMultiplication(Polynomial const& polynomial) {
    if (OperatorLevel::AdditionAndSubtraction == m_commonOperatorLevel) {
        TermsWithDetails termsWithDetails(m_termsWithAssociation.getTermsWithDetails());
        clear();
        distributeAndMultiply(termsWithDetails, polynomial);
    } else {
        Expression expressionCopy(*this);
        clear();
        distributeAndMultiply(expressionCopy, polynomial);
    }
    clearSimplifiedFlag();
}

void Expression::putExpressionWithMultiplication(Expression const& secondExpression) {
    if (willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(*this)) {
        putOnlyTermWithMultiplicationIfNeeded(Term(secondExpression));
    } else if (
        OperatorLevel::AdditionAndSubtraction == m_commonOperatorLevel &&
        OperatorLevel::AdditionAndSubtraction == secondExpression.getCommonOperatorLevel()) {
        TermsWithDetails termsWithDetails1(m_termsWithAssociation.getTermsWithDetails());
        TermsWithDetails termsWithDetails2(secondExpression.getTermsWithAssociation().getTermsWithDetails());
        clear();
        distributeAndMultiply(termsWithDetails1, termsWithDetails2);
    } else if (OperatorLevel::AdditionAndSubtraction == m_commonOperatorLevel) {
        TermsWithDetails termsWithDetails(m_termsWithAssociation.getTermsWithDetails());
        clear();
        distributeAndMultiply(termsWithDetails, Term(secondExpression));
    } else if (OperatorLevel::AdditionAndSubtraction == secondExpression.getCommonOperatorLevel()) {
        Term thisExpressionTerm(*this);
        clear();
        distributeAndMultiply(thisExpressionTerm, secondExpression.getTermsWithAssociation().getTermsWithDetails());
    } else {
        putOnlyTermWithMultiplicationIfNeeded(Term(secondExpression));
    }
    clearSimplifiedFlag();
}

void Expression::putTermWithDetails(TermWithDetails const& termToSave) {
    m_termsWithAssociation.putTermWithDetails(termToSave);
    clearSimplifiedFlag();
}

void Expression::putTermsWithDetails(TermsWithDetails const& termsToSave) {
    for (TermWithDetails const& termWithDetails : termsToSave) {
        m_termsWithAssociation.putTermWithDetails(termWithDetails);
    }
    clearSimplifiedFlag();
}

void Expression::putTerm(BaseTerm const& baseTerm, TermAssociationType const overallAssociation) {
    if (TermAssociationType::Positive == overallAssociation) {
        m_termsWithAssociation.putTermWithPositiveAssociation(baseTerm);
    } else if (TermAssociationType::Negative == overallAssociation) {
        m_termsWithAssociation.putTermWithNegativeAssociation(baseTerm);
    }
    clearSimplifiedFlag();
}

void Expression::reverseTheAssociationOfTheTerms() {
    m_termsWithAssociation.reverseTheAssociationOfTheTerms();
    clearSimplifiedFlag();
}

void Expression::set(OperatorLevel const operatorLevel, TermsWithDetails const& termsWithDetails) {
    m_commonOperatorLevel = operatorLevel;
    m_termsWithAssociation.putTermsWithDetails(termsWithDetails);
    clearSimplifiedFlag();
}

void Expression::setTerm(BaseTerm const& baseTerm) {
    *this = createOrCopyExpressionFromATerm(getTermConstReferenceFromBaseTerm(baseTerm));
    clearSimplifiedFlag();
}

void Expression::setCommonOperatorLevel(OperatorLevel const operatorLevel) {
    m_commonOperatorLevel = operatorLevel;
    clearSimplifiedFlag();
}

void Expression::setCommonOperatorLevelIfStillUnknown(OperatorLevel const operatorLevel) {
    if (OperatorLevel::Unknown == m_commonOperatorLevel) {
        m_commonOperatorLevel = operatorLevel;
    }
    clearSimplifiedFlag();
}

void Expression::simplify() {
    if (!m_isSimplified) {
        SimplificationOfExpression simplification(*this);
        simplification.simplify();
        *this = simplification.getExpression();
        setAsSimplified();
    }
}

void Expression::sort() {
    m_termsWithAssociation.sort(OperatorLevel::RaiseToPower == m_commonOperatorLevel);
    clearSimplifiedFlag();
}

void Expression::setAsSimplified() { m_isSimplified = true; }

void Expression::clearSimplifiedFlag() { m_isSimplified = false; }

void Expression::clearAllInnerSimplifiedFlags() {
    for (TermWithDetails& termWithDetails : m_termsWithAssociation.getTermsWithDetailsReference()) {
        Term& term(getTermReferenceFromUniquePointer(termWithDetails.baseTermPointer));
        term.clearAllInnerSimplifiedFlags();
    }
    clearSimplifiedFlag();
}

void Expression::putTermWithAddition(BaseTerm const& baseTerm) {
    switch (m_commonOperatorLevel) {
        case OperatorLevel::Unknown:
        case OperatorLevel::AdditionAndSubtraction: {
            m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
            putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Positive);
            break;
        }
        case OperatorLevel::MultiplicationAndDivision:
        case OperatorLevel::RaiseToPower: {
            clearAndPutTermInTermsWithAssociation(Term(*this));
            m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
            putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Positive);
            break;
        }
    }
}

void Expression::putTermWithSubtraction(BaseTerm const& baseTerm) {
    switch (m_commonOperatorLevel) {
        case OperatorLevel::Unknown:
        case OperatorLevel::AdditionAndSubtraction: {
            m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
            putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Negative);
            break;
        }
        case OperatorLevel::MultiplicationAndDivision:
        case OperatorLevel::RaiseToPower: {
            clearAndPutTermInTermsWithAssociation(Term(*this));
            m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
            putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Negative);
            break;
        }
    }
}

void Expression::putOnlyTermWithMultiplicationIfNeeded(BaseTerm const& baseTerm) {
    Term const& term(getTermConstReferenceFromBaseTerm(baseTerm));
    if (willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(term)) {
        if (isEmpty()) {
            setTerm(Term(1));
        }
    } else {
        if (willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(*this)) {
            setTerm(baseTerm);
        } else {
            putTermWithMultiplication(baseTerm);
        }
    }
}

void Expression::putTermWithMultiplication(BaseTerm const& baseTerm) {
    switch (m_commonOperatorLevel) {
        case OperatorLevel::Unknown:
        case OperatorLevel::MultiplicationAndDivision: {
            m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
            putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Positive);
            break;
        }
        case OperatorLevel::AdditionAndSubtraction: {
            TermsWithDetails termsWithDetails(m_termsWithAssociation.getTermsWithDetails());
            clear();
            distributeAndMultiply(termsWithDetails, getTermConstReferenceFromBaseTerm(baseTerm));
            break;
        }
        case OperatorLevel::RaiseToPower: {
            clearAndPutTermInTermsWithAssociation(Term(*this));
            m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
            putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Positive);
            break;
        }
    }
}

void Expression::putTermWithDivision(BaseTerm const& baseTerm) {
    switch (m_commonOperatorLevel) {
        case OperatorLevel::Unknown:
        case OperatorLevel::MultiplicationAndDivision: {
            m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
            putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Negative);
            break;
        }
        case OperatorLevel::AdditionAndSubtraction:
        case OperatorLevel::RaiseToPower: {
            clearAndPutTermInTermsWithAssociation(Term(*this));
            m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
            putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Negative);
            break;
        }
    }
}

void Expression::putTermWithRaiseToPower(BaseTerm const& baseTerm) {
    switch (m_commonOperatorLevel) {
        case OperatorLevel::Unknown:
        case OperatorLevel::RaiseToPower: {
            m_commonOperatorLevel = OperatorLevel::RaiseToPower;
            putTermWithRaiseToPowerForExpressionAndNonExpressions(baseTerm, TermAssociationType::Positive);
            break;
        }
        case OperatorLevel::AdditionAndSubtraction:
        case OperatorLevel::MultiplicationAndDivision: {
            clearAndPutTermInTermsWithAssociation(Term(*this));
            m_commonOperatorLevel = OperatorLevel::RaiseToPower;
            putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Positive);
            break;
        }
    }
}

void Expression::putTermForExpressionAndNonExpressions(
    BaseTerm const& baseTerm, TermAssociationType const overallAssociation) {
    Term const& term(getTermConstReferenceFromBaseTerm(baseTerm));
    if (term.isExpression()) {
        Expression const& expression(term.getAsExpression());
        if (!expression.isEmpty()) {
            if (m_commonOperatorLevel == expression.getCommonOperatorLevel() ||
                OperatorLevel::Unknown == expression.getCommonOperatorLevel()) {                putTermsWithAssociation(expression.getTermsWithAssociation(), overallAssociation);
            } else {
                putTerm(baseTerm, overallAssociation);
            }        }
    } else if (isNonEmptyOrNonOperatorOrNonExpressionType(term)) {
        putTerm(baseTerm, overallAssociation);
    }
}

void Expression::putTermWithRaiseToPowerForExpressionAndNonExpressions(
    BaseTerm const& baseTerm, TermAssociationType const overallAssociation) {
    Term const& term(getTermConstReferenceFromBaseTerm(baseTerm));
    if (term.isExpression()) {
        Expression const& expression(term.getAsExpression());
        TermsWithAssociation const& termsWithAssociation(expression.getTermsWithAssociation());
        if (1 == termsWithAssociation.getSize() &&
            TermAssociationType::Positive == termsWithAssociation.getTermsWithDetails().front().association) {
            putTerm(termsWithAssociation.getFirstTerm(), overallAssociation);
        } else {
            putTerm(baseTerm, overallAssociation);
        }    } else if (isNonEmptyOrNonOperatorOrNonExpressionType(term)) {
        putTerm(baseTerm, overallAssociation);
    }
}
void Expression::putTermsWithAssociation(
    TermsWithAssociation const& termsWithAssociation, TermAssociationType const overallAssociation) {
    TermsWithAssociation newTermsWithAssociation(termsWithAssociation);
    if (TermAssociationType::Negative == overallAssociation) {
        newTermsWithAssociation.reverseTheAssociationOfTheTerms();
    }
    for (TermWithDetails const& termWithDetails : newTermsWithAssociation.getTermsWithDetails()) {
        m_termsWithAssociation.putTermWithDetails(termWithDetails);
    }
}

void Expression::distributeAndMultiply(Polynomial const& polynomial, Expression const& expression) {
    for (Monomial const& monomial : polynomial.getMonomials()) {
        Expression monomialExpression(createExpressionIfPossible({monomial}));
        monomialExpression.putTermWithMultiplicationIfNeeded(Term(expression));
        putTermWithAdditionIfNeeded(Term(monomialExpression));    }
}

void Expression::distributeAndMultiply(Expression const& expression, Polynomial const& polynomial) {
    for (Monomial const& monomial : polynomial.getMonomials()) {
        Expression expressionTerm(expression);
        expressionTerm.putTermWithMultiplicationIfNeeded(Term(monomial));
        putTermWithAdditionIfNeeded(Term(expressionTerm));    }
}

void Expression::distributeAndMultiply(Polynomial const& polynomial, TermsWithDetails const& termsWithDetails) {
    for (Monomial const& monomial : polynomial.getMonomials()) {
        distributeAndMultiply(Term(monomial), termsWithDetails);
    }
}

void Expression::distributeAndMultiply(TermsWithDetails const& termsWithDetails, Polynomial const& polynomial) {
    for (Monomial const& monomial : polynomial.getMonomials()) {
        distributeAndMultiply(termsWithDetails, Term(monomial));
    }
}
void Expression::distributeAndMultiply(BaseTerm const& baseTerm, TermsWithDetails const& termsWithDetails) {
    for (TermWithDetails const& termWithDetails : termsWithDetails) {
        distributeAndMultiply(            createOrCopyExpressionFromATerm(getTermConstReferenceFromBaseTerm(baseTerm)),
            getBaseTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer),
            termWithDetails.hasPositiveAssociation());
    }
}

void Expression::distributeAndMultiply(TermsWithDetails const& termsWithDetails, BaseTerm const& baseTerm) {
    for (TermWithDetails const& termWithDetails : termsWithDetails) {
        distributeAndMultiply(
            createOrCopyExpressionFromATerm(getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer)),
            baseTerm, termWithDetails.hasPositiveAssociation());
    }
}

void Expression::distributeAndMultiply(
    TermsWithDetails const& termsWithDetails1, TermsWithDetails const& termsWithDetails2) {
    for (TermWithDetails const& termWithDetails1 : termsWithDetails1) {
        for (TermWithDetails const& termWithDetails2 : termsWithDetails2) {
            Term const& term1(getTermConstReferenceFromUniquePointer(termWithDetails1.baseTermPointer));
            Term const& term2(getTermConstReferenceFromUniquePointer(termWithDetails2.baseTermPointer));
            distributeAndMultiply(
                createOrCopyExpressionFromATerm(term1), term2,
                termWithDetails1.association == termWithDetails2.association);
        }
    }
}

void Expression::distributeAndMultiply(Expression const& multiplicand, BaseTerm const& multiplier, bool const isAdd) {
    Expression expressionToAddOrSubtract(multiplicand);
    expressionToAddOrSubtract.putTermWithMultiplicationIfNeeded(getTermConstReferenceFromBaseTerm(multiplier));
    if (isAdd) {
        putTermWithAdditionIfNeeded(Term(expressionToAddOrSubtract));
    } else {
        putTermWithSubtractionIfNeeded(Term(expressionToAddOrSubtract));
    }
}

ostream& operator<<(ostream& out, Expression const& expression) {
    TermsWithDetails const& termsWithDetails(expression.m_termsWithAssociation.getTermsWithDetails());
    OperatorLevel operatorLevel(expression.m_commonOperatorLevel);
    out << "(";
    if (!termsWithDetails.empty()) {
        TermWithDetails const& firstTermWithDetails(termsWithDetails.front());
        out << getFirstStringIfNegativeAssociation(operatorLevel, firstTermWithDetails.association)
            << getTermConstReferenceFromUniquePointer(firstTermWithDetails.baseTermPointer);
        for (auto it = termsWithDetails.cbegin() + 1; it != termsWithDetails.cend(); it++) {
            TermWithDetails const& termWithDetails(*it);
            out << getOperatingString(operatorLevel, termWithDetails.association)
                << getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer);
        }
    }
    out << ")";
    return out;
}

}  // namespace algebra

}  // namespace alba
