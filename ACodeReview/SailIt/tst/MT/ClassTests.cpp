#include "fixtures/ModuleTest.hpp"

#include "gtest/gtest.h"
#include <fstream>
#include "../Checkers.hpp"

using namespace codeReview;
using namespace std;

TEST_F(ModuleTest, MultiLineClassTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "class myClass" << endl;
    testFile << "{" << endl;
    testFile << "int classFunction();" << endl;
    testFile << "int classVariable;" << endl;
    testFile << "};" << endl;
    testFile.close();

    processFile();
    EXPECT_TRUE(m_database.isClass("myClass"));
    EXPECT_FALSE(m_database.isNamespace("myClass"));
    EXPECT_TRUE(m_database.isFunction("myClass::classFunction"));
    EXPECT_TRUE(m_database.isVariable("myClass::classVariable"));
    ASSERT_EQ(m_database.getClassesReference().size(), 1);
    CPlusPlusClass& cPlusPlusClass = m_database.getClassReference("myClass");
    VectorOfStrings& functionNames = cPlusPlusClass.getFunctionNamesReference();
    VectorOfStrings& variableNames = cPlusPlusClass.getVariableNamesReference();
    ASSERT_EQ(functionNames.size(), 1);
    ASSERT_EQ(variableNames.size(), 1);
    EXPECT_TRUE(cPlusPlusClass.isFunction("classFunction"));
    EXPECT_TRUE(cPlusPlusClass.isVariable("classVariable"));

    ASSERT_EQ(m_terms.size(), 1);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "class myClass\n{\nint classFunction();\nint classVariable;\n};\n", 1);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, MultiLineStructTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "struct myStruct" << endl;
    testFile << "{" << endl;
    testFile << "int structFunction();" << endl;
    testFile << "int structVariable;" << endl;
    testFile << "};" << endl;
    testFile.close();

    processFile();
    EXPECT_TRUE(m_database.isClass("myStruct"));
    EXPECT_FALSE(m_database.isNamespace("myStruct"));
    EXPECT_TRUE(m_database.isFunction("myStruct::structFunction"));
    EXPECT_TRUE(m_database.isVariable("myStruct::structVariable"));
    ASSERT_EQ(m_database.getClassesReference().size(), 1);
    CPlusPlusClass& cPlusPlusClass = m_database.getClassReference("myStruct");
    VectorOfStrings& functionNames = cPlusPlusClass.getFunctionNamesReference();
    VectorOfStrings& variableNames = cPlusPlusClass.getVariableNamesReference();
    ASSERT_EQ(functionNames.size(), 1);
    ASSERT_EQ(variableNames.size(), 1);
    EXPECT_TRUE(cPlusPlusClass.isFunction("structFunction"));
    EXPECT_TRUE(cPlusPlusClass.isVariable("structVariable"));

    ASSERT_EQ(m_terms.size(), 1);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "struct myStruct\n{\nint structFunction();\nint structVariable;\n};\n", 1);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, ForwardDeclarationTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "class myClass;" << endl;
    testFile << "struct myStruct;" << endl;
    testFile.close();

    processFile();
    EXPECT_TRUE(m_database.isClass("myClass"));
    EXPECT_TRUE(m_database.isClass("myStruct"));

    ASSERT_EQ(m_terms.size(), 2);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "class myClass;\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "struct myStruct;\n", 2);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

