#include "../Checkers.hpp"
#include "fixtures/ModuleTest.hpp"
#include "gtest/gtest.h"

#include <fstream>
#include <string>

using namespace codeReview;
using namespace std;

TEST_F(ModuleTest, ExternTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "extern int x = 5;" << endl;
    testFile << "extern  \tint y = 5;" << endl;
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 4);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "extern ", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "int x = 5;\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "extern ", 2);
    CHECK_TERM(it, TermType::ProcessedTerm, "int y = 5;\n", 2);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 1);
}

TEST_F(ModuleTest, CommentAreIgnored)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "#define /*My comment1*/MACRO/*My comment2*/ int//My comment3" << endl;
    testFile << "#include /*My comment1*/<iostream>//My comment2" << endl;
    testFile << "MACRO /*My comment1*/variable /*My comment2*/= 5;//My comment3" << endl;
    testFile << "if/*My comment1*/(/*My comment2*/1/*My comment3*/ == /*My comment4*/1/*My comment5*/)//My comment5" << endl;
    testFile << "/*My comment1*/{//My comment2" << endl;
    testFile << "int x = 5;" << endl;
    testFile << "/*My comment1*/}//My comment2" << endl;
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 4);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "#define /*My comment1*/MACRO/*My comment2*/ int//My comment3\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "#include /*My comment1*/<iostream>//My comment2\n", 2);
    CHECK_TERM(it, TermType::ProcessedTerm, "int /*My comment1*/variable /*My comment2*/= 5;//My comment3\n", 3);
    CHECK_TERM(it, TermType::MultiLine_IfElseIfStartChain_Ignorable, "if/*My comment1*/(/*My comment2*/1/*My comment3*/ == /*My comment4*/1/*My comment5*/)//My comment5\n/*My comment1*/{//My comment2\nint x = 5;\n/*My comment1*/}//My comment2\n", 4);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 1);
}

TEST_F(ModuleTest, SingleLineCommentWithExtraNewLineTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "//Single line comment" << endl;
    testFile << "//Single line comment with spaces in the end" << endl;
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 2);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::Comment, "//Single line comment\n", 1);\
    CHECK_TERM(it, TermType::Comment, "//Single line comment with spaces in the end\n", 2);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, MultiLineCommentWithExtraNewLineTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "/*" << endl;
    testFile << "Multi line comments" << endl;
    testFile << "*/" << endl;
    testFile << endl;
    testFile << "/*" << endl;
    testFile << "Multi line comment with spaces in the end" << endl;
    testFile << "*/   " << endl;
    testFile << endl;
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 4);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::Comment, "/*\nMulti line comments\n*/\n", 3);
    CHECK_TERM_IF_NEWLINE(it, 4);
    CHECK_TERM(it, TermType::Comment, "/*\nMulti line comment with spaces in the end\n*/ \n", 7);
    CHECK_TERM_IF_NEWLINE(it, 8);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 4);
}

TEST_F(ModuleTest, CheckUnnecessaryLinesIndentionAreNotChecked)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "    " << endl;
    testFile << "           " << endl;
    testFile << "             " << endl;
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 3);
    auto it = m_terms.begin();
    CHECK_TERM_IF_NEWLINE(it, 1);
    CHECK_TERM_IF_NEWLINE(it, 2);
    CHECK_TERM_IF_NEWLINE(it, 3);
}

TEST_F(ModuleTest, ExtraParenthesisTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "int x = (100 + 200) + 5;" << endl;
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 1);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "int x = (100 + 200) + 5;\n", 1);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, ContinuousSimplificationTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "int a = (100 + 200) + 5;" << endl << endl;
    testFile << "int b = (100 + 200) + 5;" << endl << endl;
    testFile << "int c = (100 + 200) + 5;" << endl << endl;
    testFile << "int d = (100 + 200) + 5;" << endl << endl;
    testFile << "int e = (100 + 200) + 5;" << endl << endl;
    testFile << "int f = (100 + 200) + 5;" << endl << endl;
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 12);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "int a = (100 + 200) + 5;\n", 1);
    CHECK_TERM(it, TermType::NewLine, "\n", 2);
    CHECK_TERM(it, TermType::ProcessedTerm, "int b = (100 + 200) + 5;\n", 3);
    CHECK_TERM(it, TermType::NewLine, "\n", 4);
    CHECK_TERM(it, TermType::ProcessedTerm, "int c = (100 + 200) + 5;\n", 5);
    CHECK_TERM(it, TermType::NewLine, "\n", 6);
    CHECK_TERM(it, TermType::ProcessedTerm, "int d = (100 + 200) + 5;\n", 7);
    CHECK_TERM(it, TermType::NewLine, "\n", 8);
    CHECK_TERM(it, TermType::ProcessedTerm, "int e = (100 + 200) + 5;\n", 9);
    CHECK_TERM(it, TermType::NewLine, "\n", 10);
    CHECK_TERM(it, TermType::ProcessedTerm, "int f = (100 + 200) + 5;\n", 11);
    CHECK_TERM(it, TermType::NewLine, "\n", 12);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 6);
}

TEST_F(ModuleTest, MultipleVariableDeclarationTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "int a, b = 1, c, d = 5;" << endl;
    testFile.close();

    processFile();
    EXPECT_TRUE(m_database.isVariable("a"));
    EXPECT_TRUE(m_database.isVariable("b"));
    EXPECT_TRUE(m_database.isVariable("c"));
    EXPECT_TRUE(m_database.isVariable("d"));

    ASSERT_EQ(m_terms.size(), 1);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "int a, b = 1, c, d = 5;\n", 1);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, CStyleArrayTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "int integerArray[5];" << endl;
    testFile << "int x = integerArray[4];" << endl;
    testFile.close();

    processFile();

    ASSERT_EQ(m_terms.size(), 2);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "int integerArray[5];\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "int x = integerArray[4];\n", 2);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, CStyleStructTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "struct" << endl;
    testFile << "{" << endl;
    testFile << "char* locale;" << endl;
    testFile << "wchar_t* wlocale;" << endl;
    testFile << "int* refcount;" << endl;
    testFile << "int* wrefcount;" << endl;
    testFile << "}" << endl;
    testFile << "lc_category;" << endl;
    testFile.close();

    processFile();

    ASSERT_EQ(m_terms.size(), 1);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "struct\n{\nchar* locale;\nwchar_t* wlocale;\nint* refcount;\nint* wrefcount;\n}\nlc_category;\n", 1);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, CStyleStructArrayTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "struct" << endl;
    testFile << "{" << endl;
    testFile << "char* locale;" << endl;
    testFile << "wchar_t* wlocale;" << endl;
    testFile << "int* refcount;" << endl;
    testFile << "int* wrefcount;" << endl;
    testFile << "}" << endl;
    testFile << "lc_category[6];" << endl;
    testFile.close();

    processFile();

    ASSERT_EQ(m_terms.size(), 1);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "struct\n{\nchar* locale;\nwchar_t* wlocale;\nint* refcount;\nint* wrefcount;\n}\nlc_category[6];\n", 1);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, CStyleStructPointerTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "struct lconv* lconv;" << endl;
    testFile.close();

    processFile();

    ASSERT_EQ(m_terms.size(), 1);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "struct lconv* lconv;\n", 1);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}
