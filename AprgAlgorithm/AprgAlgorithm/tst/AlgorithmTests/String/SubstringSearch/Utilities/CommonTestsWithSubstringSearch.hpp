#pragma once

#include <gtest/gtest.h>

#include <string>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithSubstringSearch
{

template <typename SubstringSearch>
void testSearchUsingExample1()
{
    SubstringSearch substringSearch;
    std::string mainString("AABRAACADABRAACAADABRA");
    std::string stringToSearch("AACAA");

    EXPECT_EQ(12U, substringSearch.search(mainString, stringToSearch));
}

}

}

}
