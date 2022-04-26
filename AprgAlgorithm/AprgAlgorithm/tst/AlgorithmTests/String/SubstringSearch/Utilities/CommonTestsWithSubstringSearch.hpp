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

template <typename SubstringSearch, typename Index>
void testSearchUsingExample1()
{
    SubstringSearch substringSearchWithHit("AACAA");
    //SubstringSearch substringSearchWithoutHit("BBB");
    std::string mainString("AABRAACADABRAACAADABRA");

    EXPECT_EQ(Index(12), substringSearchWithHit.search(mainString));
    //EXPECT_EQ(Index(std::string::npos), substringSearchWithoutHit.search(mainString));
}

}

}

}
