#pragma once

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace CommonTestsWithSelector {

template <typename Selector, typename Values>
void testDoNthElementUsingExample1WithCharacters(Selector const& selector) {
    Values valuesToSelect{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    selector.doNthElement(valuesToSelect, 5);

    Values valuesToExpect{'A', 'L', 'M', 'E', 'E', 'O', 'P', 'R', 'S', 'X', 'T'};
    EXPECT_EQ(valuesToExpect, valuesToSelect);
}

template <typename Selector, typename Values>
void testDoNthElementUsingExample1WithPositiveAndNegativeIntegers(Selector const& selector) {
    Values valuesToSelect{-5, -10, 0, -3, 8, 5, -1, 10};

    selector.doNthElement(valuesToSelect, 3);

    Values valuesToExpect{-10, -5, -3, -1, 0, 5, 8, 10};
    EXPECT_EQ(valuesToExpect, valuesToSelect);
}

template <typename Selector, typename Values>
void testGetNthElementUsingExample1WithCharacters(Selector const& selector) {
    Values valuesToSelect{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    EXPECT_EQ('O', selector.getNthSelect(valuesToSelect, 5));
}

template <typename Selector, typename Values>
void testGetNthElementUsingExample1WithPositiveAndNegativeIntegers(Selector const& selector) {
    Values valuesToSelect{-5, -10, 0, -3, 8, 5, -1, 10};

    EXPECT_EQ(-1, selector.getNthSelect(valuesToSelect, 3));
}

}  // namespace CommonTestsWithSelector
}  // namespace algorithm

}  // namespace alba