#include <Algorithm/Sort/SpecialSorters/BitonicSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>

#include <gtest/gtest.h>

#include <list>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Characters = vector<char>;
using ListOfCharacters = list<char>;
using Integers = vector<int>;
using Doubles = vector<double>;
using Strings = vector<string>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharactersSorter = BitonicSorter<Characters>;
using ListOfCharactersSorter = BitonicSorter<ListOfCharacters>;
using IntegersSorter = BitonicSorter<Integers>;
using DoublesSorter = BitonicSorter<Doubles>;
using StringsSorter = BitonicSorter<Strings>;
using StabilityCheckObjectsSorter = BitonicSorter<StabilityCheckObjects>;
}  // namespace

TEST(BitonicSorterTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter sorter;
    Characters emptyContainer;

    sorter.sort(emptyContainer);

    EXPECT_TRUE(emptyContainer.empty());
}

TEST(BitonicSorterTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter sorter;
    Characters valuesToSort{'E'};

    sorter.sort(valuesToSort);

    Characters valuesToExpect{'E'};
    EXPECT_EQ(valuesToExpect, valuesToSort);
}

TEST(BitonicSorterTest, SortWorksOnCharactersUsingExample1) {
    CharactersSorter sorter;
    Characters valuesToSort{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    sorter.sort(valuesToSort);

    Characters valuesToExpect{'A', 'E', 'M', 'O', 'R', 'S', 'T', 'X', 'P', 'L', 'E'};
    EXPECT_EQ(valuesToExpect, valuesToSort);
}

TEST(BitonicSorterTest, SortWorksOnCharactersUsingExample2) {
    CharactersSorter sorter;
    Characters valuesToSort{'C', 'O', 'M', 'P', 'L', 'I', 'C', 'A', 'T', 'E', 'D', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    sorter.sort(valuesToSort);

    Characters valuesToExpect{'A', 'A', 'C', 'C', 'D', 'E', 'E', 'I', 'L', 'M', 'M', 'O', 'P', 'P', 'T', 'X', 'L', 'E'};
    EXPECT_EQ(valuesToExpect, valuesToSort);
}

// CANNOT SORT STD::LIST
// Implementation does not work with lists

TEST(BitonicSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1) {
    IntegersSorter sorter;
    Integers valuesToSort{-5, -10, 0, -3, 8, 5, -1, 10};

    sorter.sort(valuesToSort);

    Integers valuesToExpect{-10, -5, -3, -1, 0, 5, 8, 10};
    EXPECT_EQ(valuesToExpect, valuesToSort);
}

TEST(BitonicSorterTest, SortWorksOnDoublesUsingExample1) {
    DoublesSorter sorter;
    Doubles valuesToSort{0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};

    sorter.sort(valuesToSort);

    Doubles valuesToExpect{0.1234, 0.565, 0.656, 0.897, 0.665, 0.3434};
    EXPECT_EQ(valuesToExpect, valuesToSort);
}

TEST(BitonicSorterTest, SortWorksOnStringsUsingExample1) {
    StringsSorter sorter;
    Strings valuesToSort{"spongebob", "patrick", "mr. crabs", "squidward", "sandy",
                         "ms. puff",  "pearl",   "larry",     "plankton"};

    sorter.sort(valuesToSort);

    Strings valuesToExpect{"larry", "mr. crabs", "ms. puff",  "patrick", "pearl",
                           "sandy", "spongebob", "squidward", "plankton"};
    EXPECT_EQ(valuesToExpect, valuesToSort);
}

TEST(BitonicSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1) {
    StabilityCheckObjectsSorter sorter;
    StabilityCheckObjects valuesToSort{{'A', 1}, {'C', 1}, {'D', 1}, {'A', 2}, {'B', 1}, {'A', 3}, {'F', 1},
                                       {'E', 1}, {'B', 2}, {'D', 2}, {'D', 3}, {'B', 3}, {'A', 4}};

    sorter.sort(valuesToSort);

    StabilityCheckObjects valuesToExpect{{'A', 1}, {'A', 2}, {'A', 3}, {'B', 1}, {'C', 1}, {'D', 1}, {'E', 1},
                                         {'F', 1}, {'D', 2}, {'D', 3}, {'B', 2}, {'B', 3}, {'A', 4}};
    bool isSortedButNotStable = std::equal(
        valuesToSort.cbegin(), valuesToSort.cend(), valuesToExpect.cbegin(), valuesToExpect.cend(),
        areObjectsEqualOnVisibleOnly);
    EXPECT_TRUE(isSortedButNotStable);
}

}  // namespace algorithm

}  // namespace alba
