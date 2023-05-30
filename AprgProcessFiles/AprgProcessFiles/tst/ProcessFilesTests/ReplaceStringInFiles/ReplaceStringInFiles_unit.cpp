#include <ProcessFiles/ReplaceStringInFiles/ReplaceStringInFiles.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(AlbaReplaceStringInFileTest, ReplaceCStylePrintWithCPlusPlusStylePrint) {
    ReplaceStringInFiles replacer;
    string result(replacer.getCPlusPlusStylePrintFromC(
        R"(TLH_DEBUG_PRINT("Creating new licence entry in DB for featureCode: %d.", featureCode);)"));
    EXPECT_EQ(
        R"(debug() << "Creating new licence entry in DB for featureCode: " << featureCode << "." << flush();)", result);
}

TEST(AlbaReplaceStringInFileTest, ReplaceCStylePrintWithCPlusPlusStylePrintWithPercentWithNumber) {
    ReplaceStringInFiles replacer;
    string result(replacer.getCPlusPlusStylePrintFromC(
        R"(TLH_DEBUG_PRINT("Received LMS_FEATURE_NOTIFICATION_RESP_MSG (0x%04x), featureCode: %u, successCode: %s", LMS_FEATURE_NOTIFICATION_RESP_MSG, featureCode, (successCode == EBoolean_True ? "Success" : "Fail"));)"));
    EXPECT_EQ(
        R"(debug() << "Received LMS_FEATURE_NOTIFICATION_RESP_MSG (0x" << LMS_FEATURE_NOTIFICATION_RESP_MSG << "), featureCode: " << featureCode << ", successCode: " << (successCode == EBoolean_True ? "Success" : "Fail") << flush();)",
        result);
}

TEST(AlbaReplaceStringInFileTest, ReplaceCStylePrintWithCPlusPlusStylePrintWithNoParameters) {
    ReplaceStringInFiles replacer;
    string result(replacer.getCPlusPlusStylePrintFromC(R"(TLH_DEBUG_PRINT("TLH::reset() ");)"));
    EXPECT_EQ("debug() << \"TLH::reset()\" << flush();", result);
}

TEST(AlbaReplaceStringInFileTest, DISABLED_ReplaceCStylePrintWithCPlusPlusStyleInFile) {
    ReplaceStringInFiles replacer;
    replacer.replaceCToCPlusPlusStylePrintOnFile(
        R"(D:\Branches\MODERNIZATION\TLH\C_Application\SC_TCOM\CP_TLH\srcLegacy\TLHMasterState.cpp)",
        R"(D:\Branches\MODERNIZATION\TLH\C_Application\SC_TCOM\NewTLH\srcLegacy\TLHMasterState.cpp)");
}

TEST(AlbaReplaceStringInFileTest, DISABLED_ReplaceCStylePrintWithCPlusPlusStyleInDirectories) {
    ReplaceStringInFiles replacer;
    replacer.replaceCToCPlusPlusStylePrintOnDirectories(
        R"(D:\Branches\MODERNIZATION\TLH\C_Application\SC_TCOM\CP_TLH\)",
        R"(D:\Branches\MODERNIZATION\TLH\C_Application\SC_TCOM\NewTLH\)");
}

}  // namespace alba
