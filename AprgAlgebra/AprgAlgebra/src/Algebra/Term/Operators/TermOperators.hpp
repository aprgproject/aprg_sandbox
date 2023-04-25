#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba {

namespace algebra {

// Unary plus: +a
Term operator+(Term const& term);

// Unary minus: -a
Term operator-(Term const& term);

// Addition: a + b
Term operator+(Term const& term1, Term const& term2);
Term& operator+=(Term& term1, Term const& term2);

// Subtraction: a - b
Term operator-(Term const& term1, Term const& term2);
Term& operator-=(Term& term1, Term const& term2);

// Multiplication: a * b
Term operator*(Term const& term1, Term const& term2);
Term& operator*=(Term& term1, Term const& term2);

// Divsion: a / b
Term operator/(Term const& term1, Term const& term2);
Term& operator/=(Term& term1, Term const& term2);

// RaiseToThePower: a ^ b
Term operator^(Term const& term1, Term const& term2);
Term& operator^=(Term& term1, Term const& term2);

}  // namespace algebra

}  // namespace alba
