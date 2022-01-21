#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

//Unary plus: +a
Term operator+(Constant const& constant);
Term operator+(Variable const& variable);
Term operator+(Monomial const& monomial);
Term operator+(Polynomial const& polynomial);
Term operator+(Expression const& expression);
Term operator+(Function const& functionObject);

//Unary minus: -a
Term operator-(Constant const& constant);
Term operator-(Variable const& variable);
Term operator-(Monomial const& monomial);
Term operator-(Polynomial const& polynomial);
Term operator-(Expression const& expression);
Term operator-(Function const& functionObject);

//Addition: a + b
Term operator+(Constant const& constant1, Constant const& constant2);
Term operator+(Constant const& constant, Variable const& variable);
Term operator+(Constant const& constant, Monomial const& monomial);
Term operator+(Constant const& constant, Polynomial const& polynomial);
Term operator+(Constant const& constant, Expression const& expression);
Term operator+(Constant const& constant, Function const& functionObject);
Term operator+(Constant const& constant, Term const& term);
Term operator+(Variable const& variable, Constant const& constant);
Term operator+(Variable const& variable1, Variable const& variable2);
Term operator+(Variable const& variable, Monomial const& monomial);
Term operator+(Variable const& variable, Polynomial const& polynomial);
Term operator+(Variable const& variable, Expression const& expression);
Term operator+(Variable const& variable, Function const& functionObject);
Term operator+(Variable const& variable, Term const& term);
Term operator+(Monomial const& monomial, Constant const& constant);
Term operator+(Monomial const& monomial, Variable const& variable);
Term operator+(Monomial const& monomial1, Monomial const& monomial2);
Term operator+(Monomial const& monomial, Polynomial const& polynomial);
Term operator+(Monomial const& monomial, Expression const& expression);
Term operator+(Monomial const& monomial, Function const& functionObject);
Term operator+(Monomial const& monomial, Term const& term);
Term operator+(Polynomial const& polynomial, Constant const& constant);
Term operator+(Polynomial const& polynomial, Variable const& variable);
Term operator+(Polynomial const& polynomial, Monomial const& monomial);
Term operator+(Polynomial const& polynomial1, Polynomial const& polynomial2);
Term operator+(Polynomial const& polynomial, Expression const& expression);
Term operator+(Polynomial const& polynomial, Function const& functionObject);
Term operator+(Polynomial const& polynomial, Term const& term);
Term operator+(Expression const& expression, Constant const& constant);
Term operator+(Expression const& expression, Variable const& variable);
Term operator+(Expression const& expression, Monomial const& monomial);
Term operator+(Expression const& expression, Polynomial const& polynomial);
Term operator+(Expression const& expression1, Expression const& expression2);
Term operator+(Expression const& expression, Function const& functionObject);
Term operator+(Expression const& expression, Term const& term);
Term operator+(Function const& functionObject, Constant const& constant);
Term operator+(Function const& functionObject, Variable const& variable);
Term operator+(Function const& functionObject, Monomial const& monomial);
Term operator+(Function const& functionObject, Polynomial const& polynomial);
Term operator+(Function const& functionObject, Expression const& expression);
Term operator+(Function const& function1, Function const& function2);
Term operator+(Function const& functionObject, Term const& term);
Term operator+(Term const& term, Constant const& constant);
Term operator+(Term const& term, Variable const& variable);
Term operator+(Term const& term, Monomial const& monomial);
Term operator+(Term const& term, Polynomial const& polynomial);
Term operator+(Term const& term, Expression const& expression);
Term operator+(Term const& term, Function const& functionObject);

//Subtraction: a - b
Term operator-(Constant const& constant1, Constant const& constant2);
Term operator-(Constant const& constant, Variable const& variable);
Term operator-(Constant const& constant, Monomial const& monomial);
Term operator-(Constant const& constant, Polynomial const& polynomial);
Term operator-(Constant const& constant, Expression const& expression);
Term operator-(Constant const& constant, Function const& functionObject);
Term operator-(Constant const& constant, Term const& term);
Term operator-(Variable const& variable, Constant const& constant);
Term operator-(Variable const& variable1, Variable const& variable2);
Term operator-(Variable const& variable, Monomial const& monomial);
Term operator-(Variable const& variable, Polynomial const& polynomial);
Term operator-(Variable const& variable, Expression const& expression);
Term operator-(Variable const& variable, Function const& functionObject);
Term operator-(Variable const& variable, Term const& term);
Term operator-(Monomial const& monomial, Constant const& constant);
Term operator-(Monomial const& monomial, Variable const& variable);
Term operator-(Monomial const& monomial1, Monomial const& monomial2);
Term operator-(Monomial const& monomial, Polynomial const& polynomial);
Term operator-(Monomial const& monomial, Expression const& expression);
Term operator-(Monomial const& monomial, Function const& functionObject);
Term operator-(Monomial const& monomial, Term const& term);
Term operator-(Polynomial const& polynomial, Constant const& constant);
Term operator-(Polynomial const& polynomial, Variable const& variable);
Term operator-(Polynomial const& polynomial, Monomial const& monomial);
Term operator-(Polynomial const& polynomial1, Polynomial const& polynomial2);
Term operator-(Polynomial const& polynomial, Expression const& expression);
Term operator-(Polynomial const& polynomial, Function const& functionObject);
Term operator-(Polynomial const& polynomial, Term const& term);
Term operator-(Expression const& expression, Constant const& constant);
Term operator-(Expression const& expression, Variable const& variable);
Term operator-(Expression const& expression, Monomial const& monomial);
Term operator-(Expression const& expression, Polynomial const& polynomial);
Term operator-(Expression const& expression1, Expression const& expression2);
Term operator-(Expression const& expression, Function const& functionObject);
Term operator-(Expression const& expression, Term const& term);
Term operator-(Function const& functionObject, Constant const& constant);
Term operator-(Function const& functionObject, Variable const& variable);
Term operator-(Function const& functionObject, Monomial const& monomial);
Term operator-(Function const& functionObject, Polynomial const& polynomial);
Term operator-(Function const& functionObject, Expression const& expression);
Term operator-(Function const& function1, Function const& function2);
Term operator-(Function const& functionObject, Term const& term);
Term operator-(Term const& term, Constant const& constant);
Term operator-(Term const& term, Variable const& variable);
Term operator-(Term const& term, Monomial const& monomial);
Term operator-(Term const& term, Polynomial const& polynomial);
Term operator-(Term const& term, Expression const& expression);
Term operator-(Term const& term, Function const& functionObject);

//Multiplication: a * b
Term operator*(Constant const& constant1, Constant const& constant2);
Term operator*(Constant const& constant, Variable const& variable);
Term operator*(Constant const& constant, Monomial const& monomial);
Term operator*(Constant const& constant, Polynomial const& polynomial);
Term operator*(Constant const& constant, Expression const& expression);
Term operator*(Constant const& constant, Function const& functionObject);
Term operator*(Constant const& constant, Term const& term);
Term operator*(Variable const& variable, Constant const& constant);
Term operator*(Variable const& variable1, Variable const& variable2);
Term operator*(Variable const& variable, Monomial const& monomial);
Term operator*(Variable const& variable, Polynomial const& polynomial);
Term operator*(Variable const& variable, Expression const& expression);
Term operator*(Variable const& variable, Function const& functionObject);
Term operator*(Variable const& variable, Term const& term);
Term operator*(Monomial const& monomial, Constant const& constant);
Term operator*(Monomial const& monomial, Variable const& variable);
Term operator*(Monomial const& monomial1, Monomial const& monomial2);
Term operator*(Monomial const& monomial, Polynomial const& polynomial);
Term operator*(Monomial const& monomial, Expression const& expression);
Term operator*(Monomial const& monomial, Function const& functionObject);
Term operator*(Monomial const& monomial, Term const& term);
Term operator*(Polynomial const& polynomial, Constant const& constant);
Term operator*(Polynomial const& polynomial, Variable const& variable);
Term operator*(Polynomial const& polynomial, Monomial const& monomial);
Term operator*(Polynomial const& polynomial1, Polynomial const& polynomial2);
Term operator*(Polynomial const& polynomial, Expression const& expression);
Term operator*(Polynomial const& polynomial, Function const& functionObject);
Term operator*(Polynomial const& polynomial, Term const& term);
Term operator*(Expression const& expression, Constant const& constant);
Term operator*(Expression const& expression, Variable const& variable);
Term operator*(Expression const& expression, Monomial const& monomial);
Term operator*(Expression const& expression, Polynomial const& polynomial);
Term operator*(Expression const& expression1, Expression const& expression2);
Term operator*(Expression const& expression, Function const& functionObject);
Term operator*(Expression const& expression, Term const& term);
Term operator*(Function const& functionObject, Constant const& constant);
Term operator*(Function const& functionObject, Variable const& variable);
Term operator*(Function const& functionObject, Monomial const& monomial);
Term operator*(Function const& functionObject, Polynomial const& polynomial);
Term operator*(Function const& functionObject, Expression const& expression);
Term operator*(Function const& function1, Function const& function2);
Term operator*(Function const& functionObject, Term const& term);
Term operator*(Term const& term, Constant const& constant);
Term operator*(Term const& term, Variable const& variable);
Term operator*(Term const& term, Monomial const& monomial);
Term operator*(Term const& term, Polynomial const& polynomial);
Term operator*(Term const& term, Expression const& expression);
Term operator*(Term const& term, Function const& functionObject);

//Divsion: a / b
Term operator/(Constant const& constant1, Constant const& constant2);
Term operator/(Constant const& constant, Variable const& variable);
Term operator/(Constant const& constant, Monomial const& monomial);
Term operator/(Constant const& constant, Polynomial const& polynomial);
Term operator/(Constant const& constant, Expression const& expression);
Term operator/(Constant const& constant, Function const& functionObject);
Term operator/(Constant const& constant, Term const& term);
Term operator/(Variable const& variable, Constant const& constant);
Term operator/(Variable const& variable1, Variable const& variable2);
Term operator/(Variable const& variable, Monomial const& monomial);
Term operator/(Variable const& variable, Polynomial const& polynomial);
Term operator/(Variable const& variable, Expression const& expression);
Term operator/(Variable const& variable, Function const& functionObject);
Term operator/(Variable const& variable, Term const& term);
Term operator/(Monomial const& monomial, Constant const& constant);
Term operator/(Monomial const& monomial, Variable const& variable);
Term operator/(Monomial const& monomial1, Monomial const& monomial2);
Term operator/(Monomial const& monomial, Polynomial const& polynomial);
Term operator/(Monomial const& monomial, Expression const& expression);
Term operator/(Monomial const& monomial, Function const& functionObject);
Term operator/(Monomial const& monomial, Term const& term);
Term operator/(Polynomial const& polynomial, Constant const& constant);
Term operator/(Polynomial const& polynomial, Variable const& variable);
Term operator/(Polynomial const& polynomial, Monomial const& monomial);
Term operator/(Polynomial const& polynomial1, Polynomial const& polynomial2);
Term operator/(Polynomial const& polynomial, Expression const& expression);
Term operator/(Polynomial const& polynomial, Function const& functionObject);
Term operator/(Polynomial const& polynomial, Term const& term);
Term operator/(Expression const& expression, Constant const& constant);
Term operator/(Expression const& expression, Variable const& variable);
Term operator/(Expression const& expression, Monomial const& monomial);
Term operator/(Expression const& expression, Polynomial const& polynomial);
Term operator/(Expression const& expression1, Expression const& expression2);
Term operator/(Expression const& expression, Function const& functionObject);
Term operator/(Expression const& expression, Term const& term);
Term operator/(Function const& functionObject, Constant const& constant);
Term operator/(Function const& functionObject, Variable const& variable);
Term operator/(Function const& functionObject, Monomial const& monomial);
Term operator/(Function const& functionObject, Polynomial const& polynomial);
Term operator/(Function const& functionObject, Expression const& expression);
Term operator/(Function const& function1, Function const& function2);
Term operator/(Function const& functionObject, Term const& term);
Term operator/(Term const& term, Constant const& constant);
Term operator/(Term const& term, Variable const& variable);
Term operator/(Term const& term, Monomial const& monomial);
Term operator/(Term const& term, Polynomial const& polynomial);
Term operator/(Term const& term, Expression const& expression);
Term operator/(Term const& term, Function const& functionObject);

//RaiseToThePower: a ^ b
Term operator^(Constant const& constant1, Constant const& constant2);
Term operator^(Constant const& constant, Variable const& variable);
Term operator^(Constant const& constant, Monomial const& monomial);
Term operator^(Constant const& constant, Polynomial const& polynomial);
Term operator^(Constant const& constant, Expression const& expression);
Term operator^(Constant const& constant, Function const& functionObject);
Term operator^(Constant const& constant, Term const& term);
Term operator^(Variable const& variable, Constant const& constant);
Term operator^(Variable const& variable1, Variable const& variable2);
Term operator^(Variable const& variable, Monomial const& monomial);
Term operator^(Variable const& variable, Polynomial const& polynomial);
Term operator^(Variable const& variable, Expression const& expression);
Term operator^(Variable const& variable, Function const& functionObject);
Term operator^(Variable const& variable, Term const& term);
Term operator^(Monomial const& monomial, Constant const& constant);
Term operator^(Monomial const& monomial, Variable const& variable);
Term operator^(Monomial const& monomial1, Monomial const& monomial2);
Term operator^(Monomial const& monomial, Polynomial const& polynomial);
Term operator^(Monomial const& monomial, Expression const& expression);
Term operator^(Monomial const& monomial, Function const& functionObject);
Term operator^(Monomial const& monomial, Term const& term);
Term operator^(Polynomial const& polynomial, Constant const& constant);
Term operator^(Polynomial const& polynomial, Variable const& variable);
Term operator^(Polynomial const& polynomial, Monomial const& monomial);
Term operator^(Polynomial const& polynomial1, Polynomial const& polynomial2);
Term operator^(Polynomial const& polynomial, Expression const& expression);
Term operator^(Polynomial const& polynomial, Function const& functionObject);
Term operator^(Polynomial const& polynomial, Term const& term);
Term operator^(Expression const& expression, Constant const& constant);
Term operator^(Expression const& expression, Variable const& variable);
Term operator^(Expression const& expression, Monomial const& monomial);
Term operator^(Expression const& expression, Polynomial const& polynomial);
Term operator^(Expression const& expression1, Expression const& expression2);
Term operator^(Expression const& expression, Function const& functionObject);
Term operator^(Expression const& expression, Term const& term);
Term operator^(Function const& functionObject, Constant const& constant);
Term operator^(Function const& functionObject, Variable const& variable);
Term operator^(Function const& functionObject, Monomial const& monomial);
Term operator^(Function const& functionObject, Polynomial const& polynomial);
Term operator^(Function const& functionObject, Expression const& expression);
Term operator^(Function const& function1, Function const& function2);
Term operator^(Function const& functionObject, Term const& term);
Term operator^(Term const& term, Constant const& constant);
Term operator^(Term const& term, Variable const& variable);
Term operator^(Term const& term, Monomial const& monomial);
Term operator^(Term const& term, Polynomial const& polynomial);
Term operator^(Term const& term, Expression const& expression);
Term operator^(Term const& term, Function const& functionObject);

}

}
