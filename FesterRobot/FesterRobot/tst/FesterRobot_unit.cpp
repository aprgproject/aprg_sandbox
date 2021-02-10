#include <FesterRobot.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(SampleTest, SampleTest1)
{
    FesterRobot festerRobot(R"(C:\Users\malba\Desktop\DSS\outputFester.txt)");
    festerRobot.run();
}