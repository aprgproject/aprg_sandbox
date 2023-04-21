#include "CodeJam_2018_Round1C_P1_AWholeNewWord.hpp"

#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace CodeJam_2018_Round1C_P1_AWholeNewWord
{

TEST(CodeJam_2018_Round1C_P1_AWholeNewWordTest, Test1)
{
    stringstream & inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream & outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
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


