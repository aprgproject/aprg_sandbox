#include <Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba
{

namespace CommonTestsWithBaseSorter
{

void sortCharactersUsingExample1(
        BaseSorterPointerForCharacters sorterPointerAsParameter)
{
    BaseSorterPointerForCharacters sorterPointer(std::move(sorterPointerAsParameter));
    if(sorterPointer)
    {
        Characters valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

        sorterPointer->sort(valuesToTest);

        Characters valuesToExpect{'A', 'E', 'E', 'L', 'M', 'O', 'P', 'R', 'S', 'T', 'X'};
        EXPECT_EQ(valuesToExpect, valuesToTest);
    }
}

void sortCharactersUsingExample2(
        BaseSorterPointerForCharacters sorterPointerAsParameter)
{
    BaseSorterPointerForCharacters sorterPointer(std::move(sorterPointerAsParameter));
    if(sorterPointer)
    {
        Characters valuesToTest{'C', 'O', 'M', 'P', 'L', 'I', 'C', 'A', 'T', 'E', 'D', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

        sorterPointer->sort(valuesToTest);

        Characters valuesToExpect{'A', 'A', 'C', 'C', 'D', 'E', 'E', 'E', 'I', 'L', 'L', 'M', 'M', 'O', 'P', 'P', 'T', 'X'};
        EXPECT_EQ(valuesToExpect, valuesToTest);
    }
}

}

}
