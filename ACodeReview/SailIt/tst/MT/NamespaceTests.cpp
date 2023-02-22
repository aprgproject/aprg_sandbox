#include "../Checkers.hpp"
#include "fixtures/ModuleTest.hpp"
#include "gtest/gtest.h"

#include <fstream>

using namespace codeReview;
using namespace std;

TEST_F(ModuleTest, MultiLineNamespaceTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "namespace myNamespace\n";
    testFile << "{\n";
    testFile << "int namespaceFunction();\n";
    testFile << "int namespaceVariable;\n";
    testFile << "}\n";
    testFile.close();

    processFile();
    EXPECT_TRUE(m_database.isNamespace("myNamespace"));
    EXPECT_FALSE(m_database.isClass("myNamespace"));
    EXPECT_TRUE(m_database.isFunction("myNamespace::namespaceFunction"));
    EXPECT_TRUE(m_database.isVariable("myNamespace::namespaceVariable"));
    ASSERT_EQ(m_database.getNamespacesReference().size(), 1);
    CPlusPlusNamespace& cPlusPlusNamespace = m_database.getNamespaceReference("myNamespace");
    VectorOfStrings& functionNames = cPlusPlusNamespace.getFunctionNamesReference();
    VectorOfStrings& variableNames = cPlusPlusNamespace.getVariableNamesReference();
    ASSERT_EQ(functionNames.size(), 1);
    ASSERT_EQ(variableNames.size(), 1);
    EXPECT_TRUE(cPlusPlusNamespace.isFunction("namespaceFunction"));
    EXPECT_TRUE(cPlusPlusNamespace.isVariable("namespaceVariable"));

    ASSERT_EQ(m_terms.size(), 1);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "namespace myNamespace\n{\nint namespaceFunction();\nint namespaceVariable;\n}\n", 1);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, UsingNamespaceKeywordTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "namespace myNamespace\n";
    testFile << "{\n";
    testFile << "int namespaceVariable;\n";
    testFile << "}\n";
    testFile << "using namespace myNamespace;\n";
    testFile << " int x = namespaceVariable;\n";
    testFile.close();

    processFile();
    EXPECT_TRUE(m_database.isNamespace("myNamespace"));
    EXPECT_TRUE(m_database.isVariable("x"));
    EXPECT_TRUE(m_database.isVariable("myNamespace::namespaceVariable"));

    ASSERT_EQ(m_terms.size(), 3);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "namespace myNamespace\n{\nint namespaceVariable;\n}\n", 1);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, ExternBlockTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "extern \"C\"\n";
    testFile << "{\n";
    testFile << "}\n";
    testFile << "extern \"C++\"\n";
    testFile << "{\n";
    testFile << "}\n";
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 2);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "extern \"C\"\n{\n}\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "extern \"C++\"\n{\n}\n", 4);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, ExternBlockInvalidSpacesTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "extern \"C\" {\n";
    testFile << "}\n";
    testFile << "extern \"C++\" {\n";
    testFile << "}\n";
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 2);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "extern \"C\" {\n}\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "extern \"C++\" {\n}\n", 3);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 4);
}
