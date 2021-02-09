#include <FesterRobot.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(SampleTest, SampleTest1)
{
    FesterRobot festerRobot(R"(D:\Branches\Fester\Fester\output\output.txt)");
    festerRobot.run();
}
