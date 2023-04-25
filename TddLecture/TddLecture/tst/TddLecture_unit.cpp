#include <TddLecture.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(SampleTest, DISABLED_SampleTest1) { TddLecture entity; }

TEST(SampleTest, SampleTest1) {
    TddLecture entity;
    TddLecture::UnsignedInts oneToTen(entity.getUnsignedIntsOneToTen());

    // ASSERT_EQ(10, oneToTen.size()); // this will fail
}

}  // namespace alba
