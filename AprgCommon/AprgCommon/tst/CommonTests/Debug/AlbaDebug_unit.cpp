
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
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

#include <map>
#include <memory>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

TEST(AlbaDebugTest, PrintingSingleParametersWorks) {
    s_debugStringStream.str(string());
    s_debugStringStream.clear();    int singleParameter1 = 12, singleParameter2 = 345, singleParameter3 = 6789;

    ALBA_PRINT3(singleParameter1, singleParameter2, singleParameter3);

    string actualPrintString(s_debugStringStream.str());
    int runningIndex = 0;
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "singleParameter1", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "12", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "singleParameter2", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "345", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "singleParameter3", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "6789", runningIndex));
}

TEST(AlbaDebugTest, PrintingStringsWorks) {    s_debugStringStream.str(string());
    s_debugStringStream.clear();
    string stringToTest = "std::string to test";

    ALBA_PRINT2(stringToTest, "string literal to test");

    string actualPrintString(s_debugStringStream.str());
    int runningIndex = 0;
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "stringToTest", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "std::string to test", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "string literal to test", runningIndex));
}

TEST(AlbaDebugTest, PrintingPointersWorks) {    s_debugStringStream.str(string());
    s_debugStringStream.clear();
    unique_ptr<int> uniquePointer(make_unique<int>(695));
    int const* nullPointer = nullptr;
    int const* rawPointer = uniquePointer.get();

    ALBA_PRINT3(nullPointer, rawPointer, uniquePointer);

    string actualPrintString(s_debugStringStream.str());
    int runningIndex = 0;
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "nullPointer", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "nullptr", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "rawPointer", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "695", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "uniquePointer", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "695", runningIndex));
}

TEST(AlbaDebugTest, PrintingContainersWorks) {
    s_debugStringStream.str(string());
    s_debugStringStream.clear();
    vector<int> container1{454, 6, 512, 315};
    map<int, char> container2{{1, 'A'}, {5, 'E'}, {7, 'G'}};

    ALBA_PRINT2(container1, container2);

    string actualPrintString(s_debugStringStream.str());
    int runningIndex = 0;
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "container1", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "454, 6, 512, 315,", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "container2", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "(1, A), (5, E), (7, G),", runningIndex));
}

TEST(AlbaDebugTest, ManipulateOutputStreamsWorks) {    s_debugStringStream.str(string());
    s_debugStringStream.clear();
    int singleParameter1 = 12, singleParameter2 = 345, singleParameter3 = 6789;

    ALBA_PRINT_MANIPULATE_OUTPUT(uppercase);
    ALBA_PRINT_MANIPULATE_OUTPUT(hex);
    ALBA_PRINT3(singleParameter1, singleParameter2, singleParameter3);
    ALBA_PRINT_MANIPULATE_OUTPUT(dec);

    string actualPrintString(s_debugStringStream.str());
    int runningIndex = 0;
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "singleParameter1", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "C", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "singleParameter2", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "159", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "singleParameter3", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "1A85", runningIndex));
}

namespace {class SampleClass {
public:
    SampleClass(int parameter1, int parameter2) : m_parameter1(parameter1), m_parameter2(parameter2) {}

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

    string actualPrintString(s_debugStringStream.str());
    int runningIndex = 0;
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "parameter1", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "1234", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "parameter2", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "7777", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "sum", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "9011", runningIndex));
}

#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)

TEST(AlbaDebugTest, PrintingWithoutSpecifyNumberOfParametersWorks) {
    s_debugStringStream.str(string());
    s_debugStringStream.clear();
    int singleParameter1 = 12, singleParameter2 = 345, singleParameter3 = 6789;

    ALBA_PRINT_ALL(singleParameter1, singleParameter2, singleParameter3);

    string actualPrintString(s_debugStringStream.str());
    int runningIndex = 0;
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "singleParameter1", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "12", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "singleParameter2", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "345", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "singleParameter3", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "6789", runningIndex));
}

#endif
}  // namespace alba
