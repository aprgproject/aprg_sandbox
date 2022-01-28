#pragma once

#include <Queue/BaseQueue.hpp>

namespace alba
{

namespace CommonTestsWithBaseQueue
{

using BaseQueueForUnsignedInt = BaseQueue<unsigned int>;

void performIsEmptyTestWhenEmpty(BaseQueueForUnsignedInt & queue);
void performIsEmptyTestWhenNotEmpty(BaseQueueForUnsignedInt & queue);
void performGetSizeTestWhenEmpty(BaseQueueForUnsignedInt & queue);
void performGetSizeTestWhenNotEmpty(BaseQueueForUnsignedInt & queue);
void performEnqueueTest(BaseQueueForUnsignedInt & queue);
void performDequeueTest(BaseQueueForUnsignedInt & queue);
void performDequeueAssertionTestWhenEmpty(BaseQueueForUnsignedInt & queue);

}

}
