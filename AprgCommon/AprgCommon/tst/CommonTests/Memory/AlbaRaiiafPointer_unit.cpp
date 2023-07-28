#include <Common/Memory/AlbaRaiiafPointer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(AlbaRaiiafPointerTest, IntegerTest) {
    AlbaRaiiafPointer<int> integerPointer;
    integerPointer.setAndAllocateNewContent(0xA1BA);
    EXPECT_EQ(integerPointer.get(), 0xA1BA);
    EXPECT_EQ(integerPointer.getReference(), 0xA1BA);
    integerPointer.deAllocate();
    integerPointer.setAndAllocateNewContent(0x1234);
    EXPECT_EQ(integerPointer.get(), 0x1234);
    EXPECT_EQ(integerPointer.getReference(), 0x1234);
    integerPointer.deAllocate();
}

TEST(AlbaRaiiafPointerTest, StringTest) {
    AlbaRaiiafPointer<string> stringPointer;
    stringPointer.setAndAllocateNewContent("Allocate new object");
    EXPECT_EQ(stringPointer.get(), "Allocate new object");
    EXPECT_EQ(stringPointer.getReference(), "Allocate new object");
    stringPointer.deAllocate();
    stringPointer.setAndAllocateNewContent("Replace with new object");
    EXPECT_EQ(stringPointer.get(), "Replace with new object");
    EXPECT_EQ(stringPointer.getReference(), "Replace with new object");
    stringPointer.deAllocate();
}

}  // namespace alba