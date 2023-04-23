#include <gtest/gtest.h>

namespace alba
{

namespace
{
int sampleFunctionWhichIsNonInitializedAndIncrementsOne()
{
    static int value;
    return value++;
}
int sampleFunctionWhichIsInitializedAndIncrementsOne()
{
    static int value=100;
    return value++;
}
}

TEST(StaticInFunctionTest, StaticValuesAreInitializedCorrectlyAndCanBeChanged)
{
    EXPECT_EQ(0, sampleFunctionWhichIsNonInitializedAndIncrementsOne());
    EXPECT_EQ(1, sampleFunctionWhichIsNonInitializedAndIncrementsOne());
    EXPECT_EQ(2, sampleFunctionWhichIsNonInitializedAndIncrementsOne());
    EXPECT_EQ(3, sampleFunctionWhichIsNonInitializedAndIncrementsOne());
    EXPECT_EQ(4, sampleFunctionWhichIsNonInitializedAndIncrementsOne());

    EXPECT_EQ(100, sampleFunctionWhichIsInitializedAndIncrementsOne());
    EXPECT_EQ(101, sampleFunctionWhichIsInitializedAndIncrementsOne());
    EXPECT_EQ(102, sampleFunctionWhichIsInitializedAndIncrementsOne());
    EXPECT_EQ(103, sampleFunctionWhichIsInitializedAndIncrementsOne());
    EXPECT_EQ(104, sampleFunctionWhichIsInitializedAndIncrementsOne());
}

}

// Static local variables

// Variables declared at block scope with the specifier static or thread_local (since C++11) have static or thread (since C++11) storage duration
// but are initialized the first time control passes through their declaration
// (unless their initialization is zero- or constant-initialization, which can be performed before the block is first entered).
// On all further calls, the declaration is skipped.

// If the initialization throws an exception, the variable is not considered to be initialized,
// and initialization will be attempted again the next time control passes through the declaration.

// If the initialization recursively enters the block in which the variable is being initialized, the behavior is undefined.

// If multiple threads attempt to initialize the same static local variable concurrently,
// the initialization occurs exactly once (similar behavior can be obtained for arbitrary functions with std::call_once).

// Note: usual implementations of this feature use variants of the double-checked locking pattern,
// which reduces runtime overhead for already-initialized local statics to a single non-atomic boolean comparison. (since C++11)

// The destructor for a block-scope static variable is called at program exit, but only if the initialization took place successfully.

// Function-local static objects in all definitions of the same inline function (which may be implicitly inline)
// all refer to the same object defined in one translation unit, as long as the function has external linkage.
