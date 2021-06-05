#include "PerformOperation.hpp"

#include <TermOperators.hpp>

using namespace std;

namespace alba
{

namespace equation
{

Term performOperation(
        Operator const& operatorTerm,
        Term const& term)
{
    Term newTerm;
    if(operatorTerm.isAddition())
    {
        newTerm = performUnaryPlus(term);
    }
    else if(operatorTerm.isSubtraction())
    {
        newTerm = performUnaryMinus(term);
    }
    return newTerm;
}

Term performOperation(
        Operator const& operatorTerm,
        Term const& term1,
        Term const& term2)
{
    Term newTerm;
    if(operatorTerm.isAddition())
    {
        newTerm = performAddition(term1, term2);
    }
    else if(operatorTerm.isSubtraction())
    {
        newTerm = performSubtraction(term1, term2);
    }
    else if(operatorTerm.isMultiplication())
    {
        newTerm = performMultiplication(term1, term2);
    }
    else if(operatorTerm.isDivision())
    {
        newTerm = performDivision(term1, term2);
    }
    else if(operatorTerm.isRaiseToPower())
    {
        newTerm = performRaiseToPower(term1, term2);
    }
    return newTerm;
}

#define TERM_UNARY_OPERATION_MACRO(operation) \
    Term newTerm;\
    if(term.isConstant())\
{\
    newTerm = operation(term.getConstantConstReference());\
}\
    else if(term.isVariable())\
{\
    newTerm = operation(term.getVariableConstReference());\
}\
    else if(term.isMonomial())\
{\
    newTerm = operation(term.getMonomialConstReference());\
}\
    else if(term.isPolynomial())\
{\
    newTerm = operation(term.getPolynomialConstReference());\
}\
    return newTerm;

#define TERM_BINARY_OPERATION_MACRO(operation) \
    Term newTerm;\
    if(term1.isConstant())\
{\
    if(term2.isConstant())\
{\
    newTerm = term1.getConstantConstReference() operation term2.getConstantConstReference();\
}\
    else if(term2.isVariable())\
{\
    newTerm = term1.getConstantConstReference() operation term2.getVariableConstReference();\
}\
    else if(term2.isMonomial())\
{\
    newTerm = term1.getConstantConstReference() operation term2.getMonomialConstReference();\
}\
    else if(term2.isPolynomial())\
{\
    newTerm = term1.getConstantConstReference() operation term2.getPolynomialConstReference();\
}\
}\
    else if(term1.isVariable())\
{\
    if(term2.isConstant())\
{\
    newTerm = term1.getVariableConstReference() operation term2.getConstantConstReference();\
}\
    else if(term2.isVariable())\
{\
    newTerm = term1.getVariableConstReference() operation term2.getVariableConstReference();\
}\
    else if(term2.isMonomial())\
{\
    newTerm = term1.getVariableConstReference() operation term2.getMonomialConstReference();\
}\
    else if(term2.isPolynomial())\
{\
    newTerm = term1.getVariableConstReference() operation term2.getPolynomialConstReference();\
}\
}\
    else if(term1.isMonomial())\{\
    if(term2.isConstant())\
{\
    newTerm = term1.getMonomialConstReference() operation term2.getConstantConstReference();\}\
    else if(term2.isVariable())\
{\
    newTerm = term1.getMonomialConstReference() operation term2.getVariableConstReference();\
}\
    else if(term2.isMonomial())\
{\
    newTerm = term1.getMonomialConstReference() operation term2.getMonomialConstReference();\
}\
    else if(term2.isPolynomial())\
{\
    newTerm = term1.getMonomialConstReference() operation term2.getPolynomialConstReference();\
}\
}\
    else if(term1.isPolynomial())\{\
    if(term2.isConstant())\
{\
    newTerm = term1.getPolynomialConstReference() operation term2.getConstantConstReference();\}\
    else if(term2.isVariable())\
{\
    newTerm = term1.getPolynomialConstReference() operation term2.getVariableConstReference();\
}\
    else if(term2.isMonomial())\
{\
    newTerm = term1.getPolynomialConstReference() operation term2.getMonomialConstReference();\
}\
    else if(term2.isPolynomial())\
{\
    newTerm = term1.getPolynomialConstReference() operation term2.getPolynomialConstReference();\
}\
}\
    return newTerm;


Term performUnaryPlus(Term const& term)
{
    TERM_UNARY_OPERATION_MACRO(+)
}

Term performUnaryMinus(Term const& term)
{
    TERM_UNARY_OPERATION_MACRO(-)
}

Term performAddition(Term const& term1, Term const& term2)
{
    TERM_BINARY_OPERATION_MACRO(+)
}

Term performSubtraction(Term const& term1, Term const& term2)
{
    TERM_BINARY_OPERATION_MACRO(-)
}

Term performMultiplication(Term const& term1, Term const& term2)
{
    TERM_BINARY_OPERATION_MACRO(*)
}

Term performDivision(Term const& term1, Term const& term2)
{
    TERM_BINARY_OPERATION_MACRO(/)
}

Term performRaiseToPower(Term const& term1, Term const& term2)
{
    TERM_BINARY_OPERATION_MACRO(^)
}


}

}
