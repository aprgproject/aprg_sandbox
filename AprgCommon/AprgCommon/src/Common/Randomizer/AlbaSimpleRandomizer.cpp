#include "AlbaSimpleRandomizer.hpp"

#include <Common/Time/AlbaLocalTimeHelper.hpp>

using namespace std;

namespace alba{

AlbaSimpleRandomizer::AlbaSimpleRandomizer()
{    resetRandomSeed();
}

void AlbaSimpleRandomizer::resetRandomSeed()
{
    srand(getCurrentDateTime().getMicroSeconds()); // srand is not thread safe
}

int AlbaSimpleRandomizer::getRandomIntegerInUniformDistribution(int const minimum, int const maximum) const
{
    int deltaInclusive = maximum-minimum+1;
    double randomValue = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX)+1);
    return static_cast<int>(minimum + randomValue*deltaInclusive); // implicit floor conversion from double to int

    // randomValue looks like this:
    // | 0-value possibility | 1-value possibility | ... | RAND_MAX-1 value possibility | RAND_MAX value possibility |    // randomValue with delta inclusive looks like this:
    // | minimum value possibility | minimum+1 value possibility | ... | maximum-1 value possibility | maximum value possibility |
    // so we get the floor to have the final value
}

double AlbaSimpleRandomizer::getRandomFloatingValueInUniformDistribution(double const minimum, double const maximum) const
{
    double delta = maximum-minimum;
    double randomValue = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
    return minimum + randomValue*delta;
}

}

// Notes on rand():
// It is implementation-defined whether rand() is thread-safe.
// Output has equal possibility between 0 to RAND_MAX (inclusive)

// Source: https://en.cppreference.com/w/cpp/numeric/random/rand
// There are no guarantees as to the quality of the random sequence produced.
// In the past, some implementations of rand() have had serious shortcomings in the randomness,// distribution and period of the sequence produced (in one well-known example,
// the low-order bit simply alternated between 1 and 0 between calls).

// The function rand() is not recommended for serious random-number generation needs.// It is recommended to use C++11's random number generation facilities to replace rand(). (since C++11)
