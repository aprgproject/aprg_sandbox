#include <FesterRobot.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(SampleTest, SampleTest1)
{
    FesterRobot festerRobot(R"(C:\Users\malba\Desktop\DSS\outputFester.txt)");
    festerRobot.run();
}

}
