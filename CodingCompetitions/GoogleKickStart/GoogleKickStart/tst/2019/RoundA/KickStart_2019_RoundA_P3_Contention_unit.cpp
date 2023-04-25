#include "KickStart_2019_RoundA_P3_Contention.hpp"
#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace KickStart_2019_RoundA_P3_Contention {

TEST(KickStart_2019_RoundA_P3_ContentionTest, Test1) {
    stringstream& inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream& outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream << "3    "
                         "\n"
                      << "5 3  "
                         "\n"
                      << "1 2  "
                         "\n"
                      << "3 4  "
                         "\n"
                      << "2 5  "
                         "\n"
                      << "30 3 "
                         "\n"
                      << "10 11"
                         "\n"
                      << "10 10"
                         "\n"
                      << "11 11"
                         "\n"
                      << "10 4 "
                         "\n"
                      << "1 8  "
                         "\n"
                      << "4 5  "
                         "\n"
                      << "3 6  "
                         "\n"
                      << "2 7  "
                         "\n"
                      << endl;

    main();

    EXPECT_EQ(
        "Case #1: 1"
        "\n"
        "Case #2: 0"
        "\n"
        "Case #3: 2"
        "\n",
        outputStringStream.str());
}

TEST(KickStart_2019_RoundA_P3_ContentionTest, Test2) {
    stringstream& inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream& outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream << "1  "
                         "\n"
                      << "8 3"
                         "\n"
                      << "1 2"
                         "\n"
                      << "4 5"
                         "\n"
                      << "7 8"
                         "\n"
                      << endl;

    main();

    EXPECT_EQ(
        "Case #1: 2"
        "\n",
        outputStringStream.str());
}

TEST(KickStart_2019_RoundA_P3_ContentionTest, Test3) {
    stringstream& inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream& outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream << "1  "
                         "\n"
                      << "10 5"
                         "\n"
                      << "1 5"
                         "\n"
                      << "3 8"
                         "\n"
                      << "3 10"
                         "\n"
                      << "6 7"
                         "\n"
                      << "4 7"
                         "\n"
                      << endl;

    main();

    EXPECT_EQ(
        "Case #1: 2"
        "\n",
        outputStringStream.str());
}

}  // namespace KickStart_2019_RoundA_P3_Contention
