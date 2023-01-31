#pragma once

#include <limits>
#include <vector>

namespace alba
{

class UglyNumbers
{
public:
    using Index = unsigned int;
    using Number = unsigned int;
    using Numbers = std::vector<Number>;
    using Booleans = std::vector<bool>;
    static constexpr Number MAX_NUMBER = std::numeric_limits<Number>::max();

    UglyNumbers(Number const nth);

    Number getNthUglyNumberByCheckingPreviousUglyNumbersUsingTabularDP() const;
    Number getNthUglyNumberByMultiplesUsingTabularDP() const;

private:
    Number const m_nth;
};

}

// Ugly Numbers

// Ugly numbers are numbers whose only prime factors are 2, 3 or 5.
// The sequence 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15... shows the first 11 ugly numbers.
// By convention, 1 is included.
// Given a number n, the task is to find n’th Ugly number.

// Examples:
// -> Input  : n = 7
// ---> Output : 8
// -> Input  : n = 10
// ---> Output : 12
// -> Input  : n = 15
// ---> Output : 24
// -> Input  : n = 150
// ---> Output : 5832


