#include "../../src/CPlusPlus/Translator/TermTranslator.hpp"
#include "../Checkers.hpp"
#include "../MtDirectoryConstants.hpp"
#include "gtest/gtest.h"

#include <fstream>

using namespace codeReview;
using namespace std;

struct TermTranslatorTest : public ::testing::Test
{
    TermTranslatorTest()
        : m_findings()
        , m_terms()
        , m_termTranslator(MT_FILE_READER_TEST_FILE, m_findings, m_terms)
    {}

    void processFile()
    {
        m_termTranslator.readFile();
        //printTerms(m_terms);
        //m_findings.printFindings(cout);
    }
    Findings m_findings;
    DequeOfTerms m_terms;
    TermTranslator m_termTranslator;
};

TEST_F(TermTranslatorTest, DISABLED_ActualTest)
{
    Findings findings;
    DequeOfTerms terms;
    TermTranslator termTranslator("C:\\APRG\\SailIt\\SailIt\\tst\\Actual.txt", findings, terms);
    termTranslator.readFile();
    //printTerms(terms);
}

TEST_F(TermTranslatorTest, CheckWhiteSpace)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "   ABC   DE  GH  I JK  L MN  OPQ   \n";
    testFile << "\t\t ABC\t\t\tDE\t GH \tI\tJK\t L\tMN \tOPQ \t \n";
    testFile << "1   2\t\t\t3 \t \t  \t\t4\n";
    testFile.close();

    unsigned lineNumber(1);
    processFile();
    ASSERT_EQ(m_terms.size(), 42);
    auto it = m_terms.begin();
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "ABC", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "DE", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "GH", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "I", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "JK", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "L", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "MN", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "OPQ", lineNumber);
    CHECK_TERM_IF_NEWLINE(it, lineNumber++);

    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "ABC", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "DE", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "GH", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "I", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "JK", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "L", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "MN", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "OPQ", lineNumber);
    CHECK_TERM_IF_NEWLINE(it, lineNumber++);

    CHECK_TERM_WITH_VALUE_TYPE_THEN_WHITE_SPACE(it, TermType::Constant_Number, "1", "ConstantNumber", lineNumber);
    CHECK_TERM_WITH_VALUE_TYPE_THEN_WHITE_SPACE(it, TermType::Constant_Number, "2", "ConstantNumber", lineNumber);
    CHECK_TERM_WITH_VALUE_TYPE_THEN_WHITE_SPACE(it, TermType::Constant_Number, "3", "ConstantNumber", lineNumber);
    CHECK_TERM_WITH_VALUE_TYPE(it, TermType::Constant_Number, "4", "ConstantNumber", lineNumber);
    CHECK_TERM_IF_NEWLINE(it, lineNumber++);

    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 17);
}

TEST_F(TermTranslatorTest, CheckIncludeFiles)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "#include<iostream>\n";
    testFile << "#INCLUDE<main1.cpp>\n";
    testFile << " #include < main11.cpp > \n";
    testFile.close();

    unsigned lineNumber(1);
    processFile();
    ASSERT_EQ(m_terms.size(), 23);
    auto it = m_terms.begin();

    CHECK_TERM(it, TermType::Macro, "#include", lineNumber);
    CHECK_TERM(it, TermType::Operator, "<", lineNumber);
    CHECK_TERM(it, TermType::Identifier, "iostream", lineNumber);
    CHECK_TERM(it, TermType::Operator, ">", lineNumber);
    CHECK_TERM_IF_NEWLINE(it, lineNumber++);

    CHECK_TERM(it, TermType::Macro, "#INCLUDE", lineNumber);
    CHECK_TERM(it, TermType::Operator, "<", lineNumber);
    CHECK_TERM(it, TermType::Identifier, "main1", lineNumber);
    CHECK_TERM(it, TermType::Operator, ".", lineNumber);
    CHECK_TERM(it, TermType::Identifier, "cpp", lineNumber);
    CHECK_TERM(it, TermType::Operator, ">", lineNumber);
    CHECK_TERM_IF_NEWLINE(it, lineNumber++);

    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Macro, "#include", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Operator, "<", lineNumber);
    CHECK_TERM(it, TermType::Identifier, "main11", lineNumber);
    CHECK_TERM(it, TermType::Operator, ".", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "cpp", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Operator, ">", lineNumber);
    CHECK_TERM_IF_NEWLINE(it, lineNumber++);

    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(TermTranslatorTest, CheckIdentifiersAndConstants)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "aBcdwXyZ def1 2ghi jkl_3 4_mnop true false\n";
    testFile.close();

    unsigned lineNumber(1);
    processFile();
    ASSERT_EQ(m_terms.size(), 14);
    auto it = m_terms.begin();
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "aBcdwXyZ", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "def1", lineNumber);
    CHECK_TERM_WITH_VALUE_TYPE_THEN_WHITE_SPACE(it, TermType::Constant_Number, "2ghi", "ConstantNumber", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "jkl_3", lineNumber);
    CHECK_TERM_WITH_VALUE_TYPE_THEN_WHITE_SPACE(it, TermType::Constant_Number, "4_mnop", "ConstantNumber", lineNumber);
    CHECK_TERM_WITH_VALUE_TYPE_THEN_WHITE_SPACE(it, TermType::Constant_Boolean, "true", "bool", lineNumber);
    CHECK_TERM_WITH_VALUE_TYPE(it, TermType::Constant_Boolean, "false", "bool", lineNumber);
    CHECK_TERM_IF_NEWLINE(it, lineNumber++);

    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(TermTranslatorTest, CheckMacros)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "#define # undef #  ifdef #   ifndef #\tif #\tendif #   else #  elif # line # \t error #\t \tinclude #\t\t\tpragma\n";
    testFile.close();

    unsigned lineNumber(1);
    processFile();
    ASSERT_EQ(m_terms.size(), 24);
    auto it = m_terms.begin();
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Macro, "#define", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Macro, "#undef", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Macro, "#ifdef", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Macro, "#ifndef", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Macro, "#if", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Macro, "#endif", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Macro, "#else", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Macro, "#elif", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Macro, "#line", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Macro, "#error", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Macro, "#include", lineNumber);
    CHECK_TERM(it, TermType::Macro, "#pragma", lineNumber);
    CHECK_TERM_IF_NEWLINE(it, lineNumber++);

    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(TermTranslatorTest, CheckOperatorWords)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "typeid const_cast static_cast reinterpret_cast static_cast sizeof new delete throw\n";
    testFile.close();

    unsigned lineNumber(1);
    processFile();
    ASSERT_EQ(m_terms.size(), 18);
    auto it = m_terms.begin();
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Operator, "typeid", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Operator, "const_cast", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Operator, "static_cast", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Operator, "reinterpret_cast", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Operator, "static_cast", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Operator, "sizeof", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Operator, "new", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Operator, "delete", lineNumber);
    CHECK_TERM(it, TermType::Operator, "throw", lineNumber);
    CHECK_TERM_IF_NEWLINE(it, lineNumber++);

    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(TermTranslatorTest, CheckTypeWords)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "bool char char16_t char32_t double float int long short signed unsigned void wchar_t\n";
    testFile.close();

    unsigned lineNumber(1);
    processFile();
    ASSERT_EQ(m_terms.size(), 26);
    auto it = m_terms.begin();
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Type, "bool", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Type, "char", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Type, "char16_t", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Type, "char32_t", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Type, "double", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Type, "float", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Type, "int", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Type, "long", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Type, "short", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Type, "signed", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Type, "unsigned", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Type, "void", lineNumber)
    CHECK_TERM(it, TermType::Type, "wchar_t", lineNumber);
    CHECK_TERM_IF_NEWLINE(it, lineNumber++);

    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(TermTranslatorTest, CheckMultipleCharacterOperators)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "->* <<= >>=\n";
    testFile.close();

    unsigned lineNumber(1);
    processFile();
    ASSERT_EQ(m_terms.size(), 6);
    auto it = m_terms.begin();
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Operator, "->*", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Operator, "<<=", lineNumber);
    CHECK_TERM(it, TermType::Operator, ">>=", lineNumber);
    CHECK_TERM_IF_NEWLINE(it, lineNumber++);

    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(TermTranslatorTest, CheckPeriod)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << ". .. ...\n";
    testFile.close();

    unsigned lineNumber(1);
    processFile();
    ASSERT_EQ(m_terms.size(), 9);
    auto it = m_terms.begin();
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Operator, ".", lineNumber);
    CHECK_TERM(it, TermType::Operator, ".", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Operator, ".", lineNumber);
    CHECK_TERM(it, TermType::Operator, ".", lineNumber);
    CHECK_TERM(it, TermType::Operator, ".", lineNumber);
    CHECK_TERM(it, TermType::Operator, ".", lineNumber);
    CHECK_TERM_IF_NEWLINE(it, lineNumber++);

    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(TermTranslatorTest, CheckSingleLineComment)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "aBcdwXyZ //This is @ 1 line comment\n";
    testFile << "         \t\t    //This is @ 1 line comment with spaces and tabs before";
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 6);
    auto it = m_terms.begin();
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "aBcdwXyZ", 1);
    CHECK_TERM(it, TermType::SingleLine_Comment, "//This is @ 1 line comment", 1);
    CHECK_TERM_IF_NEWLINE(it, 1);
    CHECK_TERM(it, TermType::SingleLine_Comment, "//This is @ 1 line comment with spaces and tabs before", 2);
    CHECK_TERM_IF_NEWLINE(it, 2);

    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(TermTranslatorTest, CheckMultiLineComment)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "aBcdwXyZ /*This is @\n";
    testFile << "  Multiline\n";
    testFile << "  Comment*/ deFsTUv\n";
    testFile.close();

    unsigned lineNumber(1);
    processFile();

    ASSERT_EQ(m_terms.size(), 6);
    auto it = m_terms.begin();
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "aBcdwXyZ", lineNumber);
    lineNumber += 2;
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::MultiLine_Comment, "/*This is @\n  Multiline\n  Comment*/", lineNumber);
    CHECK_TERM(it, TermType::Identifier, "deFsTUv", lineNumber);
    CHECK_TERM_IF_NEWLINE(it, lineNumber++);

    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(TermTranslatorTest, CheckString)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "aBcdwXyZ \"This is @ simple string\" deFsTUv\n";
    testFile << "aBcdwXyZ \"This is @ string with \\\"quotation\\\"\" deFsTUv\n";
    testFile << "\'Q\' \'\"\' \'\\\'\' \'This is @character\'\n";
    testFile.close();

    unsigned lineNumber(1);
    processFile();

    ASSERT_EQ(m_terms.size(), 20);
    auto it = m_terms.begin();
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "aBcdwXyZ", lineNumber);
    CHECK_TERM_WITH_VALUE_TYPE_THEN_WHITE_SPACE(it, TermType::Constant_String, "\"This is @ simple string\"", "string", lineNumber);
    CHECK_TERM(it, TermType::Identifier, "deFsTUv", lineNumber);
    CHECK_TERM_IF_NEWLINE(it, lineNumber++);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "aBcdwXyZ", lineNumber);
    CHECK_TERM_WITH_VALUE_TYPE_THEN_WHITE_SPACE(it, TermType::Constant_String, "\"This is @ string with \\\"quotation\\\"\"", "string", lineNumber);
    CHECK_TERM(it, TermType::Identifier, "deFsTUv", lineNumber);
    CHECK_TERM_IF_NEWLINE(it, lineNumber++);
    CHECK_TERM_WITH_VALUE_TYPE_THEN_WHITE_SPACE(it, TermType::Constant_Character, "\'Q\'", "char", lineNumber);
    CHECK_TERM_WITH_VALUE_TYPE_THEN_WHITE_SPACE(it, TermType::Constant_Character, "\'\"\'", "char", lineNumber);
    CHECK_TERM_WITH_VALUE_TYPE_THEN_WHITE_SPACE(it, TermType::Constant_Character, "\'\\\'\'", "char", lineNumber);
    CHECK_TERM_WITH_VALUE_TYPE(it, TermType::Constant_Character, "\'This is @character\'", "char", lineNumber);
    CHECK_TERM_IF_NEWLINE(it, lineNumber++);

    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(TermTranslatorTest, CheckStringWithSlashes)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "aBcdwXyZ1 \"\\\\\" deFsTUv2\n";
    testFile << "aBcdwXyZ3 \"\\\\\\\\\" deFsTUv4\n";
    testFile << "aBcdwXyZ5 \"\\\\\\\"\\\"\\\\\" deFsTUv6\n";
    testFile.close();

    unsigned lineNumber(1);
    processFile();

    ASSERT_EQ(m_terms.size(), 18);
    auto it = m_terms.begin();
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "aBcdwXyZ1", lineNumber);
    CHECK_TERM_WITH_VALUE_TYPE_THEN_WHITE_SPACE(it, TermType::Constant_String, "\"\\\\\"", "string", lineNumber);
    CHECK_TERM(it, TermType::Identifier, "deFsTUv2", lineNumber);
    CHECK_TERM_IF_NEWLINE(it, lineNumber++);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "aBcdwXyZ3", lineNumber);
    CHECK_TERM_WITH_VALUE_TYPE_THEN_WHITE_SPACE(it, TermType::Constant_String, "\"\\\\\\\\\"", "string", lineNumber);
    CHECK_TERM(it, TermType::Identifier, "deFsTUv4", lineNumber);
    CHECK_TERM_IF_NEWLINE(it, lineNumber++);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Identifier, "aBcdwXyZ5", lineNumber);
    CHECK_TERM_WITH_VALUE_TYPE_THEN_WHITE_SPACE(it, TermType::Constant_String, "\"\\\\\\\"\\\"\\\\\"", "string", lineNumber);
    CHECK_TERM(it, TermType::Identifier, "deFsTUv6", lineNumber);
    CHECK_TERM_IF_NEWLINE(it, lineNumber++);

    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}


TEST_F(TermTranslatorTest, CheckKeyword)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "for while if\n";
    testFile.close();

    unsigned lineNumber(1);
    processFile();

    ASSERT_EQ(m_terms.size(), 6);
    auto it = m_terms.begin();
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Keyword, "for", lineNumber);
    CHECK_TERM_THEN_WHITE_SPACE(it, TermType::Keyword, "while", lineNumber);
    CHECK_TERM(it, TermType::Keyword, "if", lineNumber);
    CHECK_TERM_IF_NEWLINE(it, lineNumber++);

    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}
