#include "../Checkers.hpp"
#include "fixtures/ModuleTest.hpp"
#include "gtest/gtest.h"

#include <fstream>

using namespace codeReview;
using namespace std;

TEST_F(ModuleTest, CheckScopeOperatorForCPlusPlus)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "namespace myNamespace\n";
    testFile << "{\n";
    testFile << "}\n";
    testFile << "class myClass;\n";
    testFile << "struct myStruct;\n";
    testFile << "int myNamespace::variable1;\n";
    testFile << "int myClass::variable1;\n";
    testFile << "int myStruct::variable1;\n";
    testFile.close();

    processFile();    ASSERT_EQ(m_terms.size(), 6);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "namespace myNamespace\n{\n}\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "class myClass;\n", 4);    CHECK_TERM(it, TermType::ProcessedTerm, "struct myStruct;\n", 5);
    CHECK_TERM(it, TermType::ProcessedTerm, "int myNamespace::variable1;\n", 6);
    CHECK_TERM(it, TermType::ProcessedTerm, "int myClass::variable1;\n", 7);
    CHECK_TERM(it, TermType::ProcessedTerm, "int myStruct::variable1;\n", 8);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}
