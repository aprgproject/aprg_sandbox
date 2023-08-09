#pragma once

#include <Sorter/BaseSorter.hpp>

#include <vector>

namespace alba
{

namespace CommonTestsWithBaseSorter
{

using Characters = std::vector<char>;
using BaseSorterForCharacters = BaseSorter<Characters>;

void performSortTestUsingExample1(BaseSorterForCharacters & sorter);
void performSortTestUsingExample2(BaseSorterForCharacters & sorter);

}

}
