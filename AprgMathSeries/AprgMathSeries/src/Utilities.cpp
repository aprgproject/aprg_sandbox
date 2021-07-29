#include "Utilities.hpp"

namespace alba
{

namespace MathSeries
{

double getSumUsingFirstAndLastTerm(
        double const value1,
        double const value2,
        int const count)
{
    return (value1 + value2) * count / 2;
}

}

}
