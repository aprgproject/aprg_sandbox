#include "PerformOperations.hpp"

#include <Algebra/Term/Operators/TermTypeOperators.hpp>

using namespace std;

namespace alba {

namespace algebra {

Term performOperation(Operator const& operatorTerm, Term const& term) {
    Term newTerm;
    if (operatorTerm.isAddition()) {
        newTerm = performUnaryPlus(term);
    } else if (operatorTerm.isSubtraction()) {
        newTerm = performUnaryMinus(term);
    }
    return newTerm;
}

Term performOperation(Operator const& operatorTerm, Term const& term1, Term const& term2) {
    Term newTerm;
    if (operatorTerm.isAddition()) {
        newTerm = performAddition(term1, term2);
    } else if (operatorTerm.isSubtraction()) {
        newTerm = performSubtraction(term1, term2);
    } else if (operatorTerm.isMultiplication()) {
        newTerm = performMultiplication(term1, term2);
    } else if (operatorTerm.isDivision()) {
        newTerm = performDivision(term1, term2);
    } else if (operatorTerm.isRaiseToPower()) {
        newTerm = performRaiseToPower(term1, term2);
    }
    return newTerm;
}

#define TERM_UNARY_OPERATION_MACRO(operation)        \
    Term newTerm;                                    \
    if (term.isEmpty()) {                            \
        newTerm.clear();                             \
    } else if (term.isConstant()) {                  \
        newTerm = operation(term.getAsConstant());   \
    } else if (term.isVariable()) {                  \
        newTerm = operation(term.getAsVariable());   \
    } else if (term.isMonomial()) {                  \
        newTerm = operation(term.getAsMonomial());   \
    } else if (term.isPolynomial()) {                \
        newTerm = operation(term.getAsPolynomial()); \
    } else if (term.isExpression()) {                \
        newTerm = operation(term.getAsExpression()); \
    } else if (term.isFunction()) {                  \
        newTerm = operation(term.getAsFunction());   \
    }                                                \
    return newTerm;

#define TERM_BINARY_OPERATION_MACRO(operation)                                   \
    Term newTerm;                                                                \
    if (term1.isEmpty()) {                                                       \
        if (term2.isEmpty()) {                                                   \
            newTerm.clear();                                                     \
        } else if (term2.isConstant()) {                                         \
            newTerm = Constant(0) operation term2.getAsConstant();               \
        } else if (term2.isVariable()) {                                         \
            newTerm = Constant(0) operation term2.getAsVariable();               \
        } else if (term2.isMonomial()) {                                         \
            newTerm = Constant(0) operation term2.getAsMonomial();               \
        } else if (term2.isPolynomial()) {                                       \
            newTerm = Constant(0) operation term2.getAsPolynomial();             \
        } else if (term2.isExpression()) {                                       \
            newTerm = Constant(0) operation term2.getAsExpression();             \
        } else if (term2.isFunction()) {                                         \
            newTerm = Constant(0) operation term2.getAsFunction();               \
        }                                                                        \
    } else if (term1.isConstant()) {                                             \
        if (term2.isEmpty()) {                                                   \
            newTerm = term1.getAsConstant() operation Constant(0);               \
        } else if (term2.isConstant()) {                                         \
            newTerm = term1.getAsConstant() operation term2.getAsConstant();     \
        } else if (term2.isVariable()) {                                         \
            newTerm = term1.getAsConstant() operation term2.getAsVariable();     \
        } else if (term2.isMonomial()) {                                         \
            newTerm = term1.getAsConstant() operation term2.getAsMonomial();     \
        } else if (term2.isPolynomial()) {                                       \
            newTerm = term1.getAsConstant() operation term2.getAsPolynomial();   \
        } else if (term2.isExpression()) {                                       \
            newTerm = term1.getAsConstant() operation term2.getAsExpression();   \
        } else if (term2.isFunction()) {                                         \
            newTerm = term1.getAsConstant() operation term2.getAsFunction();     \
        }                                                                        \
    } else if (term1.isVariable()) {                                             \
        if (term2.isEmpty()) {                                                   \
            newTerm = term1.getAsVariable() operation Constant(0);               \
        } else if (term2.isConstant()) {                                         \
            newTerm = term1.getAsVariable() operation term2.getAsConstant();     \
        } else if (term2.isVariable()) {                                         \
            newTerm = term1.getAsVariable() operation term2.getAsVariable();     \
        } else if (term2.isMonomial()) {                                         \
            newTerm = term1.getAsVariable() operation term2.getAsMonomial();     \
        } else if (term2.isPolynomial()) {                                       \
            newTerm = term1.getAsVariable() operation term2.getAsPolynomial();   \
        } else if (term2.isExpression()) {                                       \
            newTerm = term1.getAsVariable() operation term2.getAsExpression();   \
        } else if (term2.isFunction()) {                                         \
            newTerm = term1.getAsVariable() operation term2.getAsFunction();     \
        }                                                                        \
    } else if (term1.isMonomial()) {                                             \
        if (term2.isEmpty()) {                                                   \
            newTerm = term1.getAsMonomial() operation Constant(0);               \
        } else if (term2.isConstant()) {                                         \
            newTerm = term1.getAsMonomial() operation term2.getAsConstant();     \
        } else if (term2.isVariable()) {                                         \
            newTerm = term1.getAsMonomial() operation term2.getAsVariable();     \
        } else if (term2.isMonomial()) {                                         \
            newTerm = term1.getAsMonomial() operation term2.getAsMonomial();     \
        } else if (term2.isPolynomial()) {                                       \
            newTerm = term1.getAsMonomial() operation term2.getAsPolynomial();   \
        } else if (term2.isExpression()) {                                       \
            newTerm = term1.getAsMonomial() operation term2.getAsExpression();   \
        } else if (term2.isFunction()) {                                         \
            newTerm = term1.getAsMonomial() operation term2.getAsFunction();     \
        }                                                                        \
    } else if (term1.isPolynomial()) {                                           \
        if (term2.isEmpty()) {                                                   \
            newTerm = term1.getAsPolynomial() operation Constant(0);             \
        } else if (term2.isConstant()) {                                         \
            newTerm = term1.getAsPolynomial() operation term2.getAsConstant();   \
        } else if (term2.isVariable()) {                                         \
            newTerm = term1.getAsPolynomial() operation term2.getAsVariable();   \
        } else if (term2.isMonomial()) {                                         \
            newTerm = term1.getAsPolynomial() operation term2.getAsMonomial();   \
        } else if (term2.isPolynomial()) {                                       \
            newTerm = term1.getAsPolynomial() operation term2.getAsPolynomial(); \
        } else if (term2.isExpression()) {                                       \
            newTerm = term1.getAsPolynomial() operation term2.getAsExpression(); \
        } else if (term2.isFunction()) {                                         \
            newTerm = term1.getAsPolynomial() operation term2.getAsFunction();   \
        }                                                                        \
    } else if (term1.isExpression()) {                                           \
        if (term2.isEmpty()) {                                                   \
            newTerm = term1.getAsExpression() operation Constant(0);             \
        } else if (term2.isConstant()) {                                         \
            newTerm = term1.getAsExpression() operation term2.getAsConstant();   \
        } else if (term2.isVariable()) {                                         \
            newTerm = term1.getAsExpression() operation term2.getAsVariable();   \
        } else if (term2.isMonomial()) {                                         \
            newTerm = term1.getAsExpression() operation term2.getAsMonomial();   \
        } else if (term2.isPolynomial()) {                                       \
            newTerm = term1.getAsExpression() operation term2.getAsPolynomial(); \
        } else if (term2.isExpression()) {                                       \
            newTerm = term1.getAsExpression() operation term2.getAsExpression(); \
        } else if (term2.isFunction()) {                                         \
            newTerm = term1.getAsExpression() operation term2.getAsFunction();   \
        }                                                                        \
    } else if (term1.isFunction()) {                                             \
        if (term2.isEmpty()) {                                                   \
            newTerm = term1.getAsFunction() operation Constant(0);               \
        } else if (term2.isConstant()) {                                         \
            newTerm = term1.getAsFunction() operation term2.getAsConstant();     \
        } else if (term2.isVariable()) {                                         \
            newTerm = term1.getAsFunction() operation term2.getAsVariable();     \
        } else if (term2.isMonomial()) {                                         \
            newTerm = term1.getAsFunction() operation term2.getAsMonomial();     \
        } else if (term2.isPolynomial()) {                                       \
            newTerm = term1.getAsFunction() operation term2.getAsPolynomial();   \
        } else if (term2.isExpression()) {                                       \
            newTerm = term1.getAsFunction() operation term2.getAsExpression();   \
        } else if (term2.isFunction()) {                                         \
            newTerm = term1.getAsFunction() operation term2.getAsFunction();     \
        }                                                                        \
    }                                                                            \
    return newTerm;

Term performUnaryPlus(Term const& term){TERM_UNARY_OPERATION_MACRO(+)}

Term performUnaryMinus(Term const& term){TERM_UNARY_OPERATION_MACRO(-)}

Term performAddition(Term const& term1, Term const& term2){TERM_BINARY_OPERATION_MACRO(+)}

Term performSubtraction(Term const& term1, Term const& term2){TERM_BINARY_OPERATION_MACRO(-)}

Term performMultiplication(Term const& term1, Term const& term2){TERM_BINARY_OPERATION_MACRO(*)}

Term performDivision(Term const& term1, Term const& term2){TERM_BINARY_OPERATION_MACRO(/)}

Term performRaiseToPower(Term const& term1, Term const& term2) {
    TERM_BINARY_OPERATION_MACRO(^)
}

}  // namespace algebra

}  // namespace alba
