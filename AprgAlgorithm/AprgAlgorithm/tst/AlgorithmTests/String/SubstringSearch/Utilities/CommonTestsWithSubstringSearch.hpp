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
void testSearchUsingEmptyStringsAndDoesNotCrash()
{
    string emptyString;
    string nonEmptyString("NonEmptyString");
    SubstringSearch emptyStringSearch(emptyString);
    SubstringSearch nonEmptyStringSearch(nonEmptyString);

    EXPECT_EQ(Index(0), emptyStringSearch.search(emptyString));
    EXPECT_EQ(Index(0), emptyStringSearch.search(nonEmptyString));
    EXPECT_EQ(Index(string::npos), nonEmptyStringSearch.search(emptyString));
    EXPECT_EQ(Index(0), nonEmptyStringSearch.search(nonEmptyString));
}

template <typename SubstringSearch, typename Index>
void testSearchUsingExample1()
{
    SubstringSearch substringSearchWithHit("AACAA");
    SubstringSearch substringSearchWithoutHit("BBB");
    string mainString("AABRAACADABRAACAADABRA");

    EXPECT_EQ(Index(12), substringSearchWithHit.search(mainString));
    EXPECT_EQ(Index(string::npos), substringSearchWithoutHit.search(mainString));
}

}

}

}
