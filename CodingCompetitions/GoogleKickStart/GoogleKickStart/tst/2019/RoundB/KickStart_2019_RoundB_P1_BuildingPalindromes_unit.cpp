#include "KickStart_2019_RoundB_P1_BuildingPalindromes.hpp"
#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace KickStart_2019_RoundB_P1_BuildingPalindromes {

TEST(KickStart_2019_RoundB_P1_BuildingPalindromesTest, Test1) {
    stringstream& inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream& outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream << "2      "
                         "\n"
                      << "7 5    "
                         "\n"
                      << "ABAACCA"
                         "\n"
                      << "3 6    "
                         "\n"
                      << "4 4    "
                         "\n"
                      << "2 5    "
                         "\n"
                      << "6 7    "
                         "\n"
                      << "3 7    "
                         "\n"
                      << "3 5    "
                         "\n"
                      << "XYZ    "
                         "\n"
                      << "1 3    "
                         "\n"
                      << "1 3    "
                         "\n"
                      << "1 3    "
                         "\n"
                      << "1 3    "
                         "\n"
                      << "1 3    "
                         "\n"
                      << endl;

    main();

    EXPECT_EQ(
        "Case #1: 3"
        "\n"
        "Case #2: 0"
        "\n",
        outputStringStream.str());
}

TEST(KickStart_2019_RoundB_P1_BuildingPalindromesTest, Test2) {
    stringstream& inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream& outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream << "1      "
                         "\n"
                      << "7 1    "
                         "\n"
                      << "ABAACCA"
                         "\n"
                      << "5 7    "
                         "\n"
                      << endl;

    main();

    EXPECT_EQ(
        "Case #1: 1"
        "\n",
        outputStringStream.str());
}

}  // namespace KickStart_2019_RoundB_P1_BuildingPalindromes
