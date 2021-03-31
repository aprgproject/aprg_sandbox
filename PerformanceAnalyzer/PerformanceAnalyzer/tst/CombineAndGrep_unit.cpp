#include <CombineAndGrep.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(CombineAndGrepTest, DISABLED_ProcessDirectory)
{
    CombineAndGrep combineAndGrep(R"(H:\Logs\111_MessagePoolExhaustion\09_06_2018\ALL\msgQueueingTime2.txt)", R"(msgQueueingTime: )");
    combineAndGrep.processDirectory(R"(H:\Logs\111_MessagePoolExhaustion\09_06_2018\ALL\knife_test5\)");
}
}