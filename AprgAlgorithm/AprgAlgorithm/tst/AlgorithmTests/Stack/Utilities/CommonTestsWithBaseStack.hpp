#pragma once

#include <Algorithm/Stack/BaseStack.hpp>

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithBaseStack
{

using BaseStackForUnsignedInt = BaseStack<unsigned int>;

void performIsEmptyTestWhenEmpty(BaseStackForUnsignedInt & stack);
void performIsEmptyTestWhenNotEmpty(BaseStackForUnsignedInt & stack);
void performGetSizeTestWhenEmpty(BaseStackForUnsignedInt & stack);
void performGetSizeTestWhenNotEmpty(BaseStackForUnsignedInt & stack);
void performPushTest(BaseStackForUnsignedInt & stack);
void performPopTest(BaseStackForUnsignedInt & stack);
void performPopAssertionTestWhenEmpty(BaseStackForUnsignedInt & stack);

}

}

}
