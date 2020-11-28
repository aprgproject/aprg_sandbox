#include <TddLecture.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(SampleTest, DISABLED_SampleTest1)
{
    TddLecture entity;
}

TEST(SampleTest, SampleTest1)
{
    TddLecture entity;
    TddLecture::UnsignedInts oneToTen(entity.getUnsignedIntsOneToTen());

    ASSERT_EQ(10, oneToTen.size());
}
