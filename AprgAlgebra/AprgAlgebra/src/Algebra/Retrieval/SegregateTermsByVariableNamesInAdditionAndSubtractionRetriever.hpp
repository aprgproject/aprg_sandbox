#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <String/AlbaStringHelper.hpp>

#include <unordered_map>
#include <string>

namespace alba
{

namespace algebra
{

class SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever
{
public:
    using VariableNameToExpressionMap=std::unordered_map<std::string, Expression>;

    SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever();

    VariableNameToExpressionMap const& getVariableNameToExpressionMap() const;
    Expression const& getRemainingTermsExpression() const;

    void putVariableNamesToCheckInOrder(stringHelper::strings const& namesInOrder);
    void retrieveFromConstant(Constant const& constant);
    void retrieveFromVariable(Variable const& variable);
    void retrieveFromMonomial(Monomial const& monomial);
    void retrieveFromPolynomial(Polynomial const& polynomial);
    void retrieveFromExpression(Expression const& expression);
    void retrieveFromFunction(Function const& functionObject);
    void retrieveFromTerm(Term const& term);
private:
    void retrieveFromConstant(Constant const& constant, TermAssociationType const overallAssociation);
    void retrieveFromVariable(Variable const& variable, TermAssociationType const overallAssociation);
    void retrieveFromMonomial(Monomial const& monomial, TermAssociationType const overallAssociation);
    void retrieveFromPolynomial(Polynomial const& polynomial, TermAssociationType const overallAssociation);
    void retrieveFromExpression(Expression const& expression, TermAssociationType const overallAssociation);
    void retrieveFromFunction(Function const& functionObject, TermAssociationType const overallAssociation);
    void retrieveFromTerm(Term const& term, TermAssociationType const overallAssociation);
    VariableNameToExpressionMap m_variableNameExpressionMap;
    Expression m_remainingTermsExpression;
};

}

}
