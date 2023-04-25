#include "../Checkers.hpp"
#include "fixtures/ModuleTest.hpp"
#include "gtest/gtest.h"

#include <fstream>

using namespace codeReview;
using namespace std;

TEST_F(ModuleTest, MultiLineIfStatementTest) {
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "if(1 == 1)\n";
    testFile << "{\n";
    testFile << "int x = 5;\n";
    testFile << "}\n";
    testFile << "if(2 == 2);\n";
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 2);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::MultiLine_IfElseIfStartChain_Ignorable, "if(1 == 1)\n{\nint x = 5;\n}\n", 1);
    CHECK_TERM(it, TermType::MultiLine_IfElseIfStartChain_Ignorable, "if(2 == 2);\n", 5);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, MultiLineIfStatementWithConstantBoolTest) {
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "if(true)\n";
    testFile << "{\n";
    testFile << "int x = 5;\n";
    testFile << "}\n";
    testFile << "if(false);\n";
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 2);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::MultiLine_IfElseIfStartChain_Ignorable, "if(true)\n{\nint x = 5;\n}\n", 1);
    CHECK_TERM(it, TermType::MultiLine_IfElseIfStartChain_Ignorable, "if(false);\n", 5);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, MultiLineIfStatementIncorrectFormatTest) {
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "int x;\n";
    testFile << "if(hello){int y=5;}\n";
    testFile << "if(x | 5){int z=5;}\n";
    testFile << "if(2 ==2) \n; \n";
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 4);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "int x;\n", 1);
    CHECK_TERM(it, TermType::MultiLine_IfElseIfStartChain_Ignorable, "if(hello){int y=5;}\n", 2);
    CHECK_TERM(it, TermType::MultiLine_IfElseIfStartChain_Ignorable, "if(x | 5){int z=5;}\n", 3);
    CHECK_TERM(it, TermType::MultiLine_IfElseIfStartChain_Ignorable, "if(2 ==2) \n; \n", 4);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 14);
}

TEST_F(ModuleTest, MultiLineElseIfStatementTest) {
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "else   if(2 == 2)\n";
    testFile << "{\n";
    testFile << "int x = 5;\n";
    testFile << "}\n";
    testFile << "else if(3 == 3);\n";
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 2);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::MultiLine_ElseIfClause, "else if(2 == 2)\n{\nint x = 5;\n}\n", 1);
    CHECK_TERM(it, TermType::MultiLine_ElseIfClause, "else if(3 == 3);\n", 5);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 3);
}

TEST_F(ModuleTest, MultiLineElseStatementTest) {
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "else\n";
    testFile << "{\n";
    testFile << "int x = 5;\n";
    testFile << "}\n";
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 1);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::MultiLine_ElseClause, "else\n{\nint x = 5;\n}\n", 1);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 1);
}

TEST_F(ModuleTest, MultiLineIfElseIfElseStatementTest) {
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "int a = 5;\n";
    testFile << "if(1 == 1)\n";
    testFile << "{\n";
    testFile << "int x = 5;\n";
    testFile << "}\n";
    testFile << "else if(2 == 2);\n";
    testFile << "else if(3 == 3)\n";
    testFile << "{\n";
    testFile << "int x = 5;\n";
    testFile << "}\n";
    testFile << "else\n";
    testFile << "{\n";
    testFile << "int x = 5;\n";
    testFile << "}\n";
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 2);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "int a = 5;\n", 1);
    CHECK_TERM(
        it, TermType::ProcessedTerm,
        "if(1 == 1)\n{\nint x = 5;\n}\nelse if(2 == 2);\nelse if(3 == 3)\n{\nint x = 5;\n}\nelse\n{\nint x = 5;\n}\n",
        2);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, MultiLineCascadingIfClauses) {
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "int a = 1;\n";
    testFile << "if(1 == 1)\n";
    testFile << "{\n";
    testFile << "int a = 2;\n";
    testFile << "if(2 == 2)\n";
    testFile << "{\n";
    testFile << "int a = 3;\n";
    testFile << "if(3 == 3)\n";
    testFile << "{\n";
    testFile << "int a = 4;\n";
    testFile << "}\n";
    testFile << "}\n";
    testFile << "}\n";
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 2);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "int a = 1;\n", 1);
    CHECK_TERM(
        it, TermType::MultiLine_IfElseIfStartChain_Ignorable,
        "if(1 == 1)\n{\nint a = 2;\nif(2 == 2)\n{\nint a = 3;\nif(3 == 3)\n{\nint a = 4;\n}\n}\n}\n", 2);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, MultiLineIncorrectIfElseIfElseStatementTest) {
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "if(1 == 1)\n";
    testFile << "   \n";
    testFile << "{\n";
    testFile << "   \n";
    testFile << "int x = 5;\n";
    testFile << "   \n";
    testFile << "}\n";
    testFile << "   \n";
    testFile << "else if(2 == 2)\n";
    testFile << "   \n";
    testFile << "{\n";
    testFile << "   \n";
    testFile << "int x = 5;\n";
    testFile << "   \n";
    testFile << "}\n";
    testFile << "   \n";
    testFile << "else\n";
    testFile << "   \n";
    testFile << "{\n";
    testFile << "   \n";
    testFile << "int x = 5;\n";
    testFile << "   \n";
    testFile << "}\n";
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 1);
    auto it = m_terms.begin();
    CHECK_TERM(
        it, TermType::ProcessedTerm,
        "if(1 == 1)\n\n{\n\nint x = 5;\n\n}\n\nelse if(2 == 2)\n\n{\n\nint x = 5;\n\n}\n\nelse\n\n{\n\nint x = "
        "5;\n\n}\n",
        1);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 11);
}

TEST_F(ModuleTest, MultiLineWhileLoopTest) {
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "while(1 == 1)\n";
    testFile << "{\n";
    testFile << "int x = 5;\n";
    testFile << "}\n";
    testFile << "while(2 == 2);\n";
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 2);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "while(1 == 1)\n{\nint x = 5;\n}\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "while(2 == 2);\n", 5);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}
