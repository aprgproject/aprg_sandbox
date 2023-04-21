#include "CodeJam_2021_Round3_P3_Ropes.hpp"

#include <Fake/FakeObjects.hpp>
#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace CodeJam_2021_Round3_P3_Ropes
{

TEST(CodeJam_2021_Round3_P3_RopesTest, Test1)
{
    stringstream & inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream & outputStringStream(FakeObjects::getInstance().outputStringStream);    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream
            << "" "\n"
            << "" "\n"
            << "" "\n"
            << "" "\n"
            << endl;

    main();

    EXPECT_EQ(
                "" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                , outputStringStream.str());
}

}

