#pragma once

#include <vector>

namespace alba
{

class FibonacciExample
{
public:
    using Number = unsigned int;
    static constexpr Number UNUSED_VALUE = 0U;

    FibonacciExample();

    Number getFibonacciUsingNaiveRecursion(Number const number) const;
    Number getFibonacciUsingMemoization(Number const number);
    Number getFibonacciUsingTabulation(Number const number);

private:
    void initialize();
    void initializeForTabulation();

    std::vector<Number> m_memoizationData;
    std::vector<Number> m_tabulationData;
};

}
