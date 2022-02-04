#pragma once

#include <Algorithm/Sorter/BaseSorter.hpp>

#include <vector>

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithBaseSorter
{

using Characters = std::vector<char>;
using BaseSorterForCharacters = BaseSorter<Characters>;

void performSortTestUsingExample1(BaseSorterForCharacters & sorter);
void performSortTestUsingExample2(BaseSorterForCharacters & sorter);

}

}

}
