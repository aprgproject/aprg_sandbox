#pragma once

#include <Constant.hpp>
#include <Monomial.hpp>
#include <Polynomial.hpp>
#include <Term.hpp>
#include <Variable.hpp>

namespace alba
{

namespace equation
{

//Unary plus: +a
Term operator+(Constant const& constant);
Term operator+(Variable const& variable);
Term operator+(Monomial const& monomial);
Term operator+(Polynomial const& polynomial);

//Unary minus: -a
Term operator-(Constant const& constant);
Term operator-(Variable const& variable);
Term operator-(Monomial const& monomial);
Term operator-(Polynomial const& polynomial);

//Addition: a + b
Term operator+(Constant const& constant1, Constant const& constant2);
Term operator+(Constant const& constant, Variable const& variable);
Term operator+(Constant const& constant, Monomial const& monomial);
Term operator+(Constant const& constant, Polynomial const& polynomial);
Term operator+(Variable const& variable, Constant const& constant);
Term operator+(Variable const& variable1, Variable const& variable2);
Term operator+(Variable const& variable, Monomial const& monomial);
Term operator+(Variable const& variable, Polynomial const& polynomial);
Term operator+(Monomial const& monomial, Constant const& constant);
Term operator+(Monomial const& monomial, Variable const& variable);
Term operator+(Monomial const& monomial1, Monomial const& monomial2);
Term operator+(Monomial const& monomial, Polynomial const& polynomial);
Term operator+(Polynomial const& polynomial, Constant const& constant);
Term operator+(Polynomial const& polynomial, Variable const& variable);
Term operator+(Polynomial const& polynomial, Monomial const& monomial);
Term operator+(Polynomial const& polynomial1, Polynomial const& polynomial2);

//Subtraction: a - b
Term operator-(Constant const& constant1, Constant const& constant2);
Term operator-(Constant const& constant, Variable const& variable);
Term operator-(Constant const& constant, Monomial const& monomial);
Term operator-(Constant const& constant, Polynomial const& polynomial);
Term operator-(Variable const& variable, Constant const& constant);
Term operator-(Variable const& variable1, Variable const& variable2);
Term operator-(Variable const& variable, Monomial const& monomial);
Term operator-(Variable const& variable, Polynomial const& polynomial);
Term operator-(Monomial const& monomial, Constant const& constant);
Term operator-(Monomial const& monomial, Variable const& variable);
Term operator-(Monomial const& monomial1, Monomial const& monomial2);
Term operator-(Monomial const& monomial, Polynomial const& polynomial);
Term operator-(Polynomial const& polynomial, Constant const& constant);
Term operator-(Polynomial const& polynomial, Variable const& variable);
Term operator-(Polynomial const& polynomial, Monomial const& monomial);
Term operator-(Polynomial const& polynomial1, Polynomial const& polynomial2);

//Multiplication: a * b
Term operator*(Constant const& constant1, Constant const& constant2);
Term operator*(Constant const& constant, Variable const& variable);
Term operator*(Constant const& constant, Monomial const& monomial);
Term operator*(Constant const& constant, Polynomial const& polynomial);
Term operator*(Variable const& variable, Constant const& constant);
Term operator*(Variable const& variable1, Variable const& variable2);
Term operator*(Variable const& variable, Monomial const& monomial);
Term operator*(Variable const& variable, Polynomial const& polynomial);
Term operator*(Monomial const& monomial, Constant const& constant);
Term operator*(Monomial const& monomial, Variable const& variable);
Term operator*(Monomial const& monomial1, Monomial const& monomial2);
Term operator*(Monomial const& monomial, Polynomial const& polynomial);
Term operator*(Polynomial const& polynomial, Constant const& constant);
Term operator*(Polynomial const& polynomial, Variable const& variable);
Term operator*(Polynomial const& polynomial, Monomial const& monomial);
Term operator*(Polynomial const& polynomial1, Polynomial const& polynomial2);

//Divsion: a / b
Term operator/(Constant const& constant1, Constant const& constant2);
Term operator/(Constant const& constant, Variable const& variable);
Term operator/(Constant const& constant, Monomial const& monomial);
Term operator/(Constant const& constant, Polynomial const& polynomial);
Term operator/(Variable const& variable, Constant const& constant);
Term operator/(Variable const& variable1, Variable const& variable2);
Term operator/(Variable const& variable, Monomial const& monomial);
Term operator/(Variable const& variable, Polynomial const& polynomial);
Term operator/(Monomial const& monomial, Constant const& constant);
Term operator/(Monomial const& monomial, Variable const& variable);
Term operator/(Monomial const& monomial1, Monomial const& monomial2);
Term operator/(Monomial const& monomial, Polynomial const& polynomial);
Term operator/(Polynomial const& polynomial, Constant const& constant);
Term operator/(Polynomial const& polynomial, Variable const& variable);
Term operator/(Polynomial const& polynomial, Monomial const& monomial);
Term operator/(Polynomial const& polynomial1, Polynomial const& polynomial2);

//RaiseToThePower: a ^ b
Term operator^(Constant const& constant1, Constant const& constant2);
Term operator^(Constant const& constant, Variable const& variable);
Term operator^(Constant const& constant, Monomial const& monomial);
Term operator^(Constant const& constant, Polynomial const& polynomial);
Term operator^(Variable const& variable, Constant const& constant);
Term operator^(Variable const& variable1, Variable const& variable2);
Term operator^(Variable const& variable, Monomial const& monomial);
Term operator^(Variable const& variable, Polynomial const& polynomial);
Term operator^(Monomial const& monomial, Constant const& constant);
Term operator^(Monomial const& monomial, Variable const& variable);
Term operator^(Monomial const& monomial1, Monomial const& monomial2);
Term operator^(Monomial const& monomial, Polynomial const& polynomial);
Term operator^(Polynomial const& polynomial, Constant const& constant);
Term operator^(Polynomial const& polynomial, Variable const& variable);
Term operator^(Polynomial const& polynomial, Monomial const& monomial);
Term operator^(Polynomial const& polynomial1, Polynomial const& polynomial2);

}
}