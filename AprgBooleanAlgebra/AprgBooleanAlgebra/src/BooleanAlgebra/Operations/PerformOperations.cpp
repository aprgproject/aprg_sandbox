#include "PerformOperations.hpp"

#include <BooleanAlgebra/Term/Operators/TermTypeOperators.hpp>

using namespace std;

namespace alba
{

namespace booleanAlgebra
{

Term performOperation(
        Operator const& operatorTerm,
        Term const& term)
{
    Term newTerm;
    if(operatorTerm.isNot())
    {
        newTerm = performNot(term);
    }
    return newTerm;
}

Term performOperation(
        Operator const& operatorTerm,
        Term const& term1,
        Term const& term2)
{
    Term newTerm;
    if(operatorTerm.isAnd())
    {
        newTerm = performAnd(term1, term2);
    }
    else if(operatorTerm.isOr())
    {
        newTerm = performOr(term1, term2);
    }
    return newTerm;
}

#define TERM_UNARY_OPERATION_MACRO(operation) \
    Term newTerm;\
    if(term.isEmpty())\
{\
    newTerm.clear();\
}\
    else if(term.isConstant())\
{\
    newTerm = operation(term.getConstantConstReference());\
}\
    else if(term.isVariableTerm())\
{\
    newTerm = operation(term.getVariableTermConstReference());\
}\
    else if(term.isExpression())\
{\
    newTerm = operation(term.getExpressionConstReference());\
}\
    return newTerm;

#define TERM_BINARY_OPERATION_MACRO(operation) \
    Term newTerm;\
    if(term1.isEmpty())\
{\
    if(term2.isEmpty())\
{\
    newTerm.clear();\
}\
    else if(term2.isConstant())\
{\
    newTerm = term2.getConstantConstReference();\
}\
    else if(term2.isVariableTerm())\
{\
    newTerm = term2.getVariableTermConstReference();\
}\
    else if(term2.isExpression())\
{\
    newTerm =  term2.getExpressionConstReference();\
}\
}\
    else if(term1.isConstant())\
{\
    if(term2.isEmpty())\
{\
    newTerm = term1.getConstantConstReference();\
}\
    else if(term2.isConstant())\
{\
    newTerm = term1.getConstantConstReference() operation term2.getConstantConstReference();\
}\
    else if(term2.isVariableTerm())\
{\
    newTerm = term1.getConstantConstReference() operation term2.getVariableTermConstReference();\
}\
    else if(term2.isExpression())\
{\
    newTerm = term1.getConstantConstReference() operation term2.getExpressionConstReference();\
}\
}\
    else if(term1.isVariableTerm())\
{\
    if(term2.isEmpty())\
{\
    newTerm = term1.getVariableTermConstReference();\
}\
    else if(term2.isConstant())\
{\
    newTerm = term1.getVariableTermConstReference() operation term2.getConstantConstReference();\
}\
    else if(term2.isVariableTerm())\
{\
    newTerm = term1.getVariableTermConstReference() operation term2.getVariableTermConstReference();\
}\
    else if(term2.isExpression())\
{\
    newTerm = term1.getVariableTermConstReference() operation term2.getExpressionConstReference();\
}\
}\
    else if(term1.isExpression())\
{\
    if(term2.isEmpty())\
{\
    newTerm = term1.getExpressionConstReference();\
}\
    else if(term2.isConstant())\
{\
    newTerm = term1.getExpressionConstReference() operation term2.getConstantConstReference();\
}\
    else if(term2.isVariableTerm())\
{\
    newTerm = term1.getExpressionConstReference() operation term2.getVariableTermConstReference();\
}\
    else if(term2.isExpression())\
{\
    newTerm = term1.getExpressionConstReference() operation term2.getExpressionConstReference();\
}\
}\
    return newTerm;


Term performNot(Term const& term)
{
    TERM_UNARY_OPERATION_MACRO(~)
}

Term performAnd(Term const& term1, Term const& term2)
{
    TERM_BINARY_OPERATION_MACRO(&)
}

Term performOr(Term const& term1, Term const& term2)
{
    TERM_BINARY_OPERATION_MACRO(|)
}


}

}
