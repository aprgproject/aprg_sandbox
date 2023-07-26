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

TEST(KnuthShuffleTest, ShuffleWhileMovingForwardWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersShuffler shuffler;
    Characters emptyContainer;

    shuffler.shuffleWhileMovingForward(emptyContainer);

    EXPECT_TRUE(emptyContainer.empty());
}

TEST(KnuthShuffleTest, ShuffleWhileMovingForwardWorksOnCharactersUsingOneValueExample) {
    CharactersShuffler shuffler;
    Characters valuesToShuffle{'E'};

    shuffler.shuffleWhileMovingForward(valuesToShuffle);

    Characters valuesToExpect{'E'};
    EXPECT_EQ(valuesToExpect, valuesToShuffle);
}

TEST(KnuthShuffleTest, ShuffleWhileMovingForwardWorksOnCharactersUsingExample1) {
    CharactersShuffler shuffler;
    Characters givenValues{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
    Characters valuesToShuffle(givenValues);

    shuffler.shuffleWhileMovingForward(valuesToShuffle);

    CharactersSet valuesSetToExpect{'A', 'E', 'E', 'L', 'M', 'O', 'P', 'R', 'S', 'T', 'X'};
    EXPECT_NE(givenValues, valuesToShuffle);
    EXPECT_EQ(valuesSetToExpect, CharactersSet(valuesToShuffle.cbegin(), valuesToShuffle.cend()));
}

TEST(KnuthShuffleTest, ShuffleWhileMovingBackwardWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersShuffler shuffler;
    Characters emptyContainer;

    shuffler.shuffleWhileMovingBackward(emptyContainer);

    EXPECT_TRUE(emptyContainer.empty());
}

TEST(KnuthShuffleTest, ShuffleWhileMovingBackwardWorksOnCharactersUsingOneValueExample) {
    CharactersShuffler shuffler;
    Characters valuesToShuffle{'E'};

    shuffler.shuffleWhileMovingBackward(valuesToShuffle);

    Characters valuesToExpect{'E'};
    EXPECT_EQ(valuesToExpect, valuesToShuffle);
}

TEST(KnuthShuffleTest, ShuffleWhileMovingBackwardWorksOnCharactersUsingExample1) {
    CharactersShuffler shuffler;
    Characters givenValues{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
    Characters valuesToShuffle(givenValues);

    shuffler.shuffleWhileMovingBackward(valuesToShuffle);

    CharactersSet valuesSetToExpect{'A', 'E', 'E', 'L', 'M', 'O', 'P', 'R', 'S', 'T', 'X'};
    EXPECT_NE(givenValues, valuesToShuffle);
    EXPECT_EQ(valuesSetToExpect, CharactersSet(valuesToShuffle.cbegin(), valuesToShuffle.cend()));
}

}  // namespace algorithm

}  // namespace alba
