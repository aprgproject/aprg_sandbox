#include <Algorithm/Random/KnuthShuffle.hpp>

#include <gtest/gtest.h>

#include <set>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Characters = vector<char>;
using CharactersSet = set<char>;
using CharactersShuffler = KnuthShuffle<Characters>;
}  // namespace

TEST(KnuthShuffleTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersShuffler shuffler;
    Characters emptyContainer;

    shuffler.shuffle(emptyContainer);

    EXPECT_TRUE(emptyContainer.empty());
}

TEST(KnuthShuffleTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersShuffler shuffler;
    Characters valuesToShuffle{'E'};

    shuffler.shuffle(valuesToShuffle);

    Characters valuesToExpect{'E'};
    EXPECT_EQ(valuesToExpect, valuesToShuffle);
}

TEST(KnuthShuffleTest, SortWorksOnCharactersUsingExample1) {
    CharactersShuffler shuffler;
    Characters givenValues{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
    Characters valuesToShuffle(givenValues);

    shuffler.shuffle(valuesToShuffle);

    CharactersSet valuesSetToExpect{'A', 'E', 'E', 'L', 'M', 'O', 'P', 'R', 'S', 'T', 'X'};
    EXPECT_NE(givenValues, valuesToShuffle);
    EXPECT_EQ(valuesSetToExpect, CharactersSet(valuesToShuffle.cbegin(), valuesToShuffle.cend()));
}

}  // namespace algorithm

}  // namespace alba
