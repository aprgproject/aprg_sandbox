#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <limits>
#include <vector>

namespace alba
{

class BooleanParenthesizationProblem
{
public:

    using Count = unsigned int;
    using Index = unsigned int;
    using Operator = char;
    using Booleans = std::vector<bool>;
    using Operators = std::vector<char>;
    using CountMatrix = matrix::AlbaMatrix<Count>;
    using CountMatrices = std::vector<CountMatrix>;
    static constexpr Count UNUSED_COUNT=std::numeric_limits<Count>::max();

    BooleanParenthesizationProblem(Booleans const& inputValues, Operators const& operators);

    Count getNumberOfWaysForTrueUsingNaiveRecursion() const;
    Count getNumberOfWaysForTrueUsingMemoizationDP() const;
    Count getNumberOfWaysForTrueUsingTabularDP() const;

private:
    Count getNumberOfWaysUsingNaiveRecursion(bool const expectedOutput, Index const left, Index const right) const;
    Count getNumberOfWaysUsingMemoizationDP(CountMatrices & countMatrices, bool const expectedOutput, Index const left, Index const right) const;

    Count convertBoolToCount(bool const booleanValue) const;
    bool areSizesCorrect() const;
    void initialize();
    Booleans m_inputValues;
    Operators m_operators;
};

}

// Given a boolean expression with following symbols.

// Symbols
// -> 'T' ---> true
// -> 'F' ---> false

// And following operators filled between symbols

// Operators
//     &   ---> boolean AND
//     |   ---> boolean OR
//     ^   ---> boolean XOR

// Count the number of ways we can parenthesize the expression so that the value of expression evaluates to true.
// Let the input be in form of two arrays one contains the symbols (T and F) in order and other contains operators (&, | and ^}

// Examples:
// Input: symbol[]    = {T, F, T}  operator[]  = {^, &}
// -> Output: 2
// -> The given expression is "T ^ F & T", it evaluates true in two ways:
// ---> "((T ^ F) & T)" and "(T ^ (F & T))"

// Input: symbol[]    = {T, F, F} operator[]  = {^, |}
// -> Output: 2
// -> The given expression is "T ^ F | F", it evaluates true
// ---> in two ways "( (T ^ F) | F )" and "( T ^ (F | F) )".

// Input: symbol[]    = {T, T, F, T} operator[]  = {|, &, ^}
// -> Output: 4
// -> The given expression is "T | T & F ^ T", it evaluates true in 4 ways:
// --->((T|T)&(F^T)), (T|(T&(F^T))), (((T|T)&F)^T)  and (T|((T&F)^T)).

