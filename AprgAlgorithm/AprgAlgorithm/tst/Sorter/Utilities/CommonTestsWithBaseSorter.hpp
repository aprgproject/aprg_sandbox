#pragma once

#include <Sorter/BaseSorter.hpp>

#include <memory>
#include <vector>

namespace alba
{

namespace CommonTestsWithBaseSorter
{

using Characters = std::vector<char>;
using BaseSorterPointerForCharacters = std::unique_ptr<BaseSorter<Characters>>;

void sortCharactersUsingExample1(BaseSorterPointerForCharacters sorterPointerAsParameter);
void sortCharactersUsingExample2(BaseSorterPointerForCharacters sorterPointerAsParameter);

}

}
