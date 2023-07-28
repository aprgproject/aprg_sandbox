
// Set external output stream file path
// #define ALBA_PRINT_EXTERNAL_OUTPUT_STREAM_FILE_PATH APRG_DIR "/Log.txt"

// Set external output stream object
#include <sstream>
namespace {
std::stringstream s_debugStringStream;  // make this inline if needed on the header file
}
#define ALBA_PRINT_EXTERNAL_OUTPUT_STREAM_OBJECT s_debugStringStream

// Start of test file
#include <Common/Debug/AlbaDebug.hpp>

#include <gtest/gtest.h>

#include <map>
#include <memory>

using namespace std;

namespace alba {

TEST(AlbaDebugTest, PrintingSingleParametersWorks) {
    s_debugStringStream.str(string());
    s_debugStringStream.clear();
    int singleParameter1 = 12, singleParameter2 = 345, singleParameter3 = 6789;

    ALBA_PRINT3(singleParameter1, singleParameter2, singleParameter3);

    EXPECT_EQ(
        R"(ALBA_PRINT in line:  29 in TestBody(...): singleParameter1 : [12] singleParameter2 : [345] singleParameter3 : [6789])"
        "\n",
        s_debugStringStream.str());
}

TEST(AlbaDebugTest, PrintingStringsWorks) {
    s_debugStringStream.str(string());
    s_debugStringStream.clear();
    string stringToTest = "std::string to test";

    ALBA_PRINT2(stringToTest, "string literal to test");

    EXPECT_EQ(
        R"(ALBA_PRINT in line:  42 in TestBody(...): stringToTest : ["std::string to test"] ["string literal to test"])"
        "\n",
        s_debugStringStream.str());
}

TEST(AlbaDebugTest, PrintingPointersWorks) {
    s_debugStringStream.str(string());
    s_debugStringStream.clear();
    unique_ptr<int> uniquePointer(make_unique<int>(695));    int const* nullPointer = nullptr;
    int const* rawPointer = uniquePointer.get();

    ALBA_PRINT3(nullPointer, rawPointer, uniquePointer);

    EXPECT_EQ(
        R"(ALBA_PRINT in line:  57 in TestBody(...): nullPointer : [nullptr] *rawPointer : [695] *uniquePointer : [695])"
        "\n",
        s_debugStringStream.str());
}

TEST(AlbaDebugTest, PrintingContainersWorks) {
    s_debugStringStream.str(string());
    s_debugStringStream.clear();
    vector<int> container1{454, 6, 512, 315};    map<int, char> container2{{1, 'A'}, {5, 'E'}, {7, 'G'}, {8, 'H'}};

    ALBA_PRINT2(container1, container2);

    EXPECT_EQ(
        R"(ALBA_PRINT in line:  71 in TestBody(...): container1 : [{size: 4 | 454, 6, 512, 315, }] container2 : [{size: 4 | (1, A), (5, E), (7, G), (8, H), }])"
        "\n",
        s_debugStringStream.str());
}
TEST(AlbaDebugTest, ManipulateOutputStreamsWorks) {
    s_debugStringStream.str(string());
    s_debugStringStream.clear();    int singleParameter1 = 12, singleParameter2 = 345, singleParameter3 = 6789;

    ALBA_PRINT_MANIPULATE_OUTPUT(uppercase);
    ALBA_PRINT_MANIPULATE_OUTPUT(hex);
    ALBA_PRINT3(singleParameter1, singleParameter2, singleParameter3);
    ALBA_PRINT_MANIPULATE_OUTPUT(dec);

    EXPECT_EQ(
        R"(ALBA_PRINT in line:  56 in TestBody(...): singleParameter1 : [C] singleParameter2 : [159] singleParameter3 : [1A85])"
        "\n",
        s_debugStringStream.str());
}
namespace {
class SampleClass {
public:    SampleClass(int parameter1, int parameter2) : m_parameter1(parameter1), m_parameter2(parameter2) {}

    int getSum() const { return m_parameter1 + m_parameter2; }

    // Note that "friend" keyword is added here.
    friend ALBA_DEBUG_CLASS_OUTPUT_OPERATOR_DEFINITION(
        SampleClass const& object, "(parameter1:" << object.m_parameter1 << ",parameter2:" << object.m_parameter2
                                                  << ",sum:" << object.getSum() << ")");

private:
    int m_parameter1;
    int m_parameter2;
};
}  // namespace

TEST(AlbaDebugTest, DebugClassOutputOperatorsWorks) {
    s_debugStringStream.str(string());
    s_debugStringStream.clear();

    SampleClass object(1234, 7777);

    ALBA_PRINT1(object);

    EXPECT_EQ(
        R"(ALBA_PRINT in line: 119 in TestBody(...): object : [(parameter1:1234,parameter2:7777,sum:9011)])"
        "\n",
        s_debugStringStream.str());
}
}  // namespace alba