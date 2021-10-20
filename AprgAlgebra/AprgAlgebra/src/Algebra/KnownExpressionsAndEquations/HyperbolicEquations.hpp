#pragma once

#include <Algebra/Equation/Equation.hpp>

namespace alba
{

namespace algebra
{

Term getEToTheX(Term const& term);
Term getEToTheNegativeX(Term const& term);
Term getEToTheXPlusEToTheNegativeX(Term const& term);
Term getEToTheXMinusEToTheNegativeX(Term const& term);

Equation getHyperbolicSineDefinition(Term const& term);
Equation getHyperbolicCosineDefinition(Term const& term);
Equation getHyperbolicTangentDefinition(Term const& term);
Equation getHyperbolicCosecantDefinition(Term const& term);
Equation getHyperbolicSecantDefinition(Term const& term);
Equation getHyperbolicCotangentDefinition(Term const& term);
Equation getHyperbolicFunctionIdentityEquation(Term const& term);
Equation getEToTheXFromHyperbolicFunctionsEquation(Term const& term);
Equation getEToTheNegativeXFromHyperbolicFunctionsEquation(Term const& term);
Term getHyperbolicSineOfSumOfTwoTerms(Term const& term1, Term const& term2);
Term getHyperbolicCosineOfSumOfTwoTerms(Term const& term1, Term const& term2);
Term getHyperbolicSineOfDoubledValue(Term const& term);
Term getHyperbolicCosineOfDoubledValue(Term const& term);
Term getHyperbolicSineOfHalvedValue(Term const& term, bool const isPositiveRoot);
Term getHyperbolicCosineOfHalvedValue(Term const& term);

Equation getHyperbolicArcSineDefinition(Term const& term);
Equation getHyperbolicArcCosineDefinition(Term const& term);
Equation getHyperbolicArcTangentDefinition(Term const& term);
Equation getHyperbolicArcCotangentDefinition(Term const& term);

}

}
