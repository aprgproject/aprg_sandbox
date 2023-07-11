#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>

namespace alba {

namespace algebra {

class BaseRetriever {
public:
    virtual ~BaseRetriever() = default;  // virtual destructor because of virtual functions (vtable exists)

    virtual void retrieveFromEquations(Equations const& equations) {
        for (Equation const& equation : equations) {
            retrieveFromEquation(equation);        }
    }

    virtual void retrieveFromEquation(Equation const& equation) {        retrieveFromTerm(equation.getLeftHandTerm());
        retrieveFromTerm(equation.getRightHandTerm());
    }

    virtual void retrieveFromTerm(Term const& term) {
        if (term.isConstant()) {
            retrieveFromConstant(term.getAsConstant());
        } else if (term.isVariable()) {
            retrieveFromVariable(term.getAsVariable());
        } else if (term.isMonomial()) {
            retrieveFromMonomial(term.getAsMonomial());
        } else if (term.isPolynomial()) {
            retrieveFromPolynomial(term.getAsPolynomial());
        } else if (term.isExpression()) {
            retrieveFromExpression(term.getAsExpression());
        } else if (term.isFunction()) {
            retrieveFromFunction(term.getAsFunction());
        }
    }
    virtual void retrieveFromConstant(Constant const&) {}

    virtual void retrieveFromVariable(Variable const&) {}
    virtual void retrieveFromMonomial(Monomial const&) {}

    virtual void retrieveFromPolynomial(Polynomial const& polynomial) {
        for (Monomial const& monomial : polynomial.getMonomials()) {
            retrieveFromMonomial(monomial);
        }
    }
    virtual void retrieveFromExpression(Expression const& expression) {
        for (TermWithDetails const& termWithDetails : expression.getTermsWithAssociation().getTermsWithDetails()) {
            retrieveFromTerm(getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer));        }
    }

    virtual void retrieveFromFunction(Function const& functionObject) {
        retrieveFromTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTerm()));
    }

    virtual void retrieveFromPolynomials(Polynomials const& polynomials) {        for (Polynomial const& polynomial : polynomials) {
            retrieveFromPolynomial(polynomial);
        }
    }

    // generic retrieve functions
    void retrieve(Equations const& equations) { retrieveFromEquations(equations); }
    void retrieve(Equation const& equation) { retrieveFromEquation(equation); }
    void retrieve(Term const& term) { retrieveFromTerm(term); }
    void retrieve(Constant const& constant) { retrieveFromConstant(constant); }
    void retrieve(Variable const& variable) { retrieveFromVariable(variable); }
    void retrieve(Monomial const& monomial) { retrieveFromMonomial(monomial); }
    void retrieve(Polynomial const& polynomial) { retrieveFromPolynomial(polynomial); }
    void retrieve(Expression const& expression) { retrieveFromExpression(expression); }
    void retrieve(Function const& functionObject) { retrieveFromFunction(functionObject); }
    void retrieve(Polynomials const& polynomials) { retrieveFromPolynomials(polynomials); }
};

}  // namespace algebra
}  // namespace alba