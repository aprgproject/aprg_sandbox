#include "CodeJam_2018_WorldFinals_P4_Swordmaster.hpp"
#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace CodeJam_2018_WorldFinals_P4_Swordmaster {

TEST(CodeJam_2018_WorldFinals_P4_SwordmasterTest, Test1) {
    stringstream& inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream& outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream << ""
                         "\n"
                      << ""
                         "\n"
                      << ""
                         "\n"
                      << ""
                         "\n"
                      << endl;

    main();

    EXPECT_EQ(
        ""
        "\n"
        ""
        "\n"
        ""
        "\n"
        ""
        "\n",
        outputStringStream.str());
}

}  // namespace CodeJam_2018_WorldFinals_P4_Swordmaster
