#include <CombineAndGrep.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(CombineAndGrepTest, DISABLED_ProcessDirectory)
{
    CombineAndGrep combineAndGrep(R"(H:\Logs\111_MessagePoolExhaustion\09_06_2018\ALL\msgQueuingTime2.txt)", R"(msgQueuingTime: )");
    combineAndGrep.processDirectory(R"(H:\Logs\111_MessagePoolExhaustion\09_06_2018\ALL\knife_test5\)");
}

}
