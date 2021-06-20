#include <Equation/Constructs/TermsOverTerms.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba{

namespace equation
{

TEST(TermsOverTermsTest, ConstructionWorks)
{
    TermsOverTerms(Terms{}, Terms{});
}

}

}
