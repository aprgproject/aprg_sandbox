#include "Term.hpp"

#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/EnumHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <cassert>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace algebra {

Term::Term() : m_type(TermType::Empty), m_isSimplified(false), m_baseTermDataPointer(nullptr) {}

Term::Term(TermType const type, bool const isSimplified, BaseTermDataPointer&& baseTermDataPointer)  // for move
    : m_type(type), m_isSimplified(isSimplified), m_baseTermDataPointer(move(baseTermDataPointer)) {}

Term::Term(AlbaNumber const& number)
    : m_type(TermType::Constant), m_isSimplified(false), m_baseTermDataPointer(make_unique<Constant>(number)) {}

Term::Term(char const* const characterString)
    : m_type(TermType::Empty), m_isSimplified(false), m_baseTermDataPointer(nullptr) {
    initializeBasedOnString(string(characterString));
}

Term::Term(string const& stringAsParameter)
    : m_type(TermType::Empty), m_isSimplified(false), m_baseTermDataPointer(nullptr) {
    initializeBasedOnString(stringAsParameter);
}

Term::Term(Constant const& constant)
    : m_type(TermType::Constant), m_isSimplified(false), m_baseTermDataPointer(make_unique<Constant>(constant)) {}

Term::Term(Variable const& variable)
    : m_type(TermType::Variable), m_isSimplified(false), m_baseTermDataPointer(make_unique<Variable>(variable)) {}

Term::Term(Operator const& operatorTerm)
    : m_type(TermType::Operator), m_isSimplified(false), m_baseTermDataPointer(make_unique<Operator>(operatorTerm)) {}

Term::Term(Monomial const& monomial)
    : m_type(TermType::Monomial), m_isSimplified(false), m_baseTermDataPointer(make_unique<Monomial>(monomial)) {}

Term::Term(Polynomial const& polynomial)
    : m_type(TermType::Polynomial), m_isSimplified(false), m_baseTermDataPointer(make_unique<Polynomial>(polynomial)) {}

Term::Term(Expression const& expression)
    : m_type(TermType::Expression), m_isSimplified(false), m_baseTermDataPointer(make_unique<Expression>(expression)) {}

Term::Term(Function const& function)
    : m_type(TermType::Function), m_isSimplified(false), m_baseTermDataPointer(make_unique<Function>(function)) {}

Term::Term(Term const& term)
    : m_type(term.m_type),
      m_isSimplified(term.m_isSimplified),
      m_baseTermDataPointer(createANewDataPointerFrom(term)) {}

Term& Term::operator=(Term const& term) {
    m_type = term.m_type;
    m_isSimplified = term.m_isSimplified;
    m_baseTermDataPointer = createANewDataPointerFrom(term);
    return *this;
}

bool Term::operator==(Term const& second) const {
    bool result(false);
    if (m_type == second.m_type) {
        if (m_type == TermType::Empty) {
            result = true;
        } else if (m_type == TermType::Constant) {
            result = getAsConstant() == second.getAsConstant();
        } else if (m_type == TermType::Variable) {
            result = getAsVariable() == second.getAsVariable();
        } else if (m_type == TermType::Operator) {
            result = getAsOperator() == second.getAsOperator();
        } else if (m_type == TermType::Monomial) {
            result = getAsMonomial() == second.getAsMonomial();
        } else if (m_type == TermType::Polynomial) {
            result = getAsPolynomial() == second.getAsPolynomial();
        } else if (m_type == TermType::Expression) {
            result = getAsExpression() == second.getAsExpression();
        } else if (m_type == TermType::Function) {
            result = getAsFunction() == second.getAsFunction();
        }
    }
    return result;}

bool Term::operator!=(Term const& second) const { return !(operator==(second)); }
bool Term::operator<(Term const& second) const {
    bool result(false);
    if (m_type == second.m_type) {
        if (m_type == TermType::Empty) {
            result = false;
        } else if (m_type == TermType::Constant) {
            result = getAsConstant() < second.getAsConstant();
        } else if (m_type == TermType::Variable) {
            result = getAsVariable() < second.getAsVariable();
        } else if (m_type == TermType::Operator) {
            result = getAsOperator() < second.getAsOperator();
        } else if (m_type == TermType::Monomial) {
            result = getAsMonomial() < second.getAsMonomial();
        } else if (m_type == TermType::Polynomial) {
            result = getAsPolynomial() < second.getAsPolynomial();
        } else if (m_type == TermType::Expression) {
            result = getAsExpression() < second.getAsExpression();
        } else if (m_type == TermType::Function) {
            result = getAsFunction() < second.getAsFunction();
        }
    } else {
        result = getTermTypePriorityValue(m_type) < getTermTypePriorityValue(second.m_type);    }
    return result;
}
bool Term::isEmpty() const {
    bool result(false);
    if (m_type == TermType::Empty) {
        result = true;
    } else if (m_type == TermType::Polynomial) {
        result = getAsPolynomial().isEmpty();
    } else if (m_type == TermType::Expression) {
        result = getAsExpression().isEmpty();
    }
    return result;
}
bool Term::isConstant() const { return TermType::Constant == m_type; }

bool Term::isVariable() const { return TermType::Variable == m_type; }
bool Term::isOperator() const { return TermType::Operator == m_type; }

bool Term::isMonomial() const { return TermType::Monomial == m_type; }

bool Term::isPolynomial() const { return TermType::Polynomial == m_type; }

bool Term::isExpression() const { return TermType::Expression == m_type; }

bool Term::isFunction() const { return TermType::Function == m_type; }

bool Term::isSimplified() const { return m_isSimplified; }

TermType Term::getTermType() const { return m_type; }

Constant const& Term::getAsConstant() const {
    assert(m_type == TermType::Constant);
    return *static_cast<Constant const*>(m_baseTermDataPointer.get());
}

Variable const& Term::getAsVariable() const {
    assert(m_type == TermType::Variable);
    return *static_cast<Variable const*>(m_baseTermDataPointer.get());
}

Operator const& Term::getAsOperator() const {
    assert(m_type == TermType::Operator);
    return *static_cast<Operator const*>(m_baseTermDataPointer.get());
}

Monomial const& Term::getAsMonomial() const {
    assert(m_type == TermType::Monomial);
    return *static_cast<Monomial const*>(m_baseTermDataPointer.get());
}

Polynomial const& Term::getAsPolynomial() const {
    assert(m_type == TermType::Polynomial);
    return *static_cast<Polynomial const*>(m_baseTermDataPointer.get());
}

Expression const& Term::getAsExpression() const {
    assert((m_type == TermType::Expression));
    return *static_cast<Expression const*>(m_baseTermDataPointer.get());
}

Function const& Term::getAsFunction() const {
    assert((m_type == TermType::Function));
    return *static_cast<Function const*>(m_baseTermDataPointer.get());
}

AlbaNumber const& Term::getAsNumber() const {
    return getAsConstant().getNumber();
}

string Term::getDebugString() const {    stringstream ss;
    ss.precision(16);
    switch (m_type) {
        case TermType::Empty:
            ss << "{EmptyTerm}";
            break;
        case TermType::Constant:
            ss << getAsConstant();
            break;
        case TermType::Variable:
            ss << getAsVariable();
            break;
        case TermType::Operator:
            ss << getAsOperator();
            break;
        case TermType::Monomial:
            ss << getAsMonomial();
            break;
        case TermType::Polynomial:
            ss << getAsPolynomial();
            break;
        case TermType::Expression:
            ss << getAsExpression().getDebugString();
            break;
        case TermType::Function:
            ss << getAsFunction().getDebugString();
            break;
        default:
            break;    }
    ss << "{" << getEnumShortString(m_type) << "}";
    return ss.str();
}

Constant& Term::getAsConstantReference() {
    clearSimplifiedFlag();
    assert(m_type == TermType::Constant);
    return *static_cast<Constant*>(m_baseTermDataPointer.get());
}

Variable& Term::getAsVariableReference() {
    clearSimplifiedFlag();
    assert(m_type == TermType::Variable);
    return *static_cast<Variable*>(m_baseTermDataPointer.get());
}

Operator& Term::getAsOperatorReference() {
    clearSimplifiedFlag();
    assert(m_type == TermType::Operator);
    return *static_cast<Operator*>(m_baseTermDataPointer.get());
}

Monomial& Term::getAsMonomialReference() {
    clearSimplifiedFlag();
    assert(m_type == TermType::Monomial);
    return *static_cast<Monomial*>(m_baseTermDataPointer.get());
}

Polynomial& Term::getAsPolynomialReference() {
    clearSimplifiedFlag();
    assert(m_type == TermType::Polynomial);
    return *static_cast<Polynomial*>(m_baseTermDataPointer.get());
}

Expression& Term::getAsExpressionReference() {
    clearSimplifiedFlag();
    assert((m_type == TermType::Expression));
    return *static_cast<Expression*>(m_baseTermDataPointer.get());
}

Function& Term::getAsFunctionReference() {
    clearSimplifiedFlag();
    assert((m_type == TermType::Function));
    return *static_cast<Function*>(m_baseTermDataPointer.get());}

BaseTermUniquePointer Term::createBasePointerByMove() {
    return static_cast<BaseTermUniquePointer>(make_unique<Term>(m_type, m_isSimplified, move(m_baseTermDataPointer)));}

void Term::clear() {
    m_type = TermType::Empty;
    m_baseTermDataPointer.reset();
    clearSimplifiedFlag();
}

void Term::simplify() {
    if (!m_isSimplified) {
        if (m_type == TermType::Monomial) {
            *this = simplifyAndConvertMonomialToSimplestTerm(getAsMonomial());
        } else if (m_type == TermType::Polynomial) {
            *this = simplifyAndConvertPolynomialToSimplestTerm(getAsPolynomial());
        } else if (m_type == TermType::Expression) {
            *this = simplifyAndConvertExpressionToSimplestTerm(getAsExpression());
        } else if (m_type == TermType::Function) {
            *this = simplifyAndConvertFunctionToSimplestTerm(getAsFunction());
        }
        setAsSimplified();
    }}

void Term::sort() {
    if (isPolynomial()) {
        getAsPolynomialReference().sortMonomialsWithInversePriority();
    } else if (isExpression()) {
        getAsExpressionReference().sort();
    }
    clearAllInnerSimplifiedFlags();
}
void Term::setAsSimplified() { m_isSimplified = true; }

void Term::clearSimplifiedFlag() { m_isSimplified = false; }

void Term::clearAllInnerSimplifiedFlags() {
    if (m_type == TermType::Monomial) {
        getAsMonomialReference().clearSimplifiedFlag();
    } else if (m_type == TermType::Polynomial) {
        getAsPolynomialReference().clearSimplifiedFlag();
    } else if (m_type == TermType::Expression) {
        getAsExpressionReference().clearAllInnerSimplifiedFlags();
    } else if (m_type == TermType::Function) {
        getAsFunctionReference().clearAllInnerSimplifiedFlags();
    }
    clearSimplifiedFlag();
}
Term::BaseTermDataPointer Term::createANewDataPointerFrom(Term const& term) {
    BaseTermDataPointer result;
    switch (term.getTermType()) {
        case TermType::Empty:
            break;
        case TermType::Constant:
            result = make_unique<Constant>(term.getAsConstant());
            break;
        case TermType::Variable:
            result = make_unique<Variable>(term.getAsVariable());
            break;
        case TermType::Operator:
            result = make_unique<Operator>(term.getAsOperator());
            break;
        case TermType::Monomial:
            result = make_unique<Monomial>(term.getAsMonomial());
            break;
        case TermType::Polynomial:
            result = make_unique<Polynomial>(term.getAsPolynomial());
            break;
        case TermType::Expression:
            result = make_unique<Expression>(term.getAsExpression());
            break;
        case TermType::Function:
            result = make_unique<Function>(term.getAsFunction());
            break;
    }
    return result;}

void Term::initializeBasedOnString(string const& stringAsParameter) {
    if (stringAsParameter.empty()) {        // do nothing
    } else if (isNumber(stringAsParameter.front())) {
        m_type = TermType::Constant;
        m_baseTermDataPointer = make_unique<Constant>(convertStringToAlbaNumber(stringAsParameter));
    } else if (algebra::isOperator(stringAsParameter)) {
        m_type = TermType::Operator;
        m_baseTermDataPointer = make_unique<Operator>(stringAsParameter);
    } else if (algebra::isFunction(stringAsParameter)) {
        m_type = TermType::Function;
        m_baseTermDataPointer = make_unique<Function>(createFunctionWithEmptyInputExpression(stringAsParameter));
    } else {
        m_type = TermType::Variable;
        m_baseTermDataPointer = make_unique<Variable>(stringAsParameter);
    }
}

ostream& operator<<(ostream& out, Term const& term) {
    switch (term.m_type) {
        case TermType::Empty:
            out << "{EmptyTerm}";
            break;
        case TermType::Constant:
            out << term.getAsConstant();
            break;
        case TermType::Variable:
            out << term.getAsVariable();
            break;
        case TermType::Operator:
            out << term.getAsOperator();
            break;
        case TermType::Monomial:
            out << term.getAsMonomial();
            break;
        case TermType::Polynomial:
            out << term.getAsPolynomial();
            break;
        case TermType::Expression:
            out << term.getAsExpression();
            break;
        case TermType::Function:
            out << term.getAsFunction();
            break;
        default:
            break;    }
    return out;
}
}  // namespace algebra

}  // namespace alba
