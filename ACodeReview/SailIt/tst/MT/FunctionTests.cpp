#include "../Checkers.hpp"
#include "fixtures/ModuleTest.hpp"
#include "gtest/gtest.h"

#include <fstream>

using namespace codeReview;
using namespace std;

TEST_F(ModuleTest, MultiLineFunctionDefinitionTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "int main(int args, void** argv)\n";
    testFile << "{\n";
    testFile << "int x = 5;\n";
    testFile << "}\n";
    testFile.close();

    processFile();
    CPlusPlusFunction& myFunction(m_database.getFunctionReference("main"));
    auto & signatures = myFunction.getFunctionSignaturesReference();
    ASSERT_EQ(signatures.size(), 1);
    auto & parameters = signatures[0].getFunctionParametersReference();
    ASSERT_EQ(parameters.size(), 2);
    EXPECT_EQ(parameters[0].getType(), CPlusPlusType("int", CPlusPlusTypeType::Primitive));
    EXPECT_EQ(parameters[1].getType(), CPlusPlusType("void", CPlusPlusTypeType::Primitive, 2));

    ASSERT_EQ(m_terms.size(), 1);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "int main(int args, void** argv)\n{\nint x = 5;\n}\n", 1);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, FunctionSignaturesAreCheckedTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "int myFunction(double parameter1, double* parameter2)\n";
    testFile << "{\n";
    testFile << "}\n";
    testFile << "int myInteger;\n";
    testFile << "double myDouble;\n";
    testFile << "double* myDoublePointer;\n";
    testFile << "myFunction(myInteger, myInteger);\n";
    testFile << "myFunction(1, myInteger);\n";
    testFile << "myFunction(myInteger, &myDouble);\n";
    testFile << "myFunction(myDouble, &myDouble);\n";
    testFile << "myFunction(1, &myDouble);\n";
    testFile << "myFunction(*myDoublePointer, &myDouble);\n";
    testFile.close();

    processFile();
    CPlusPlusFunction& myFunction(m_database.getFunctionReference("myFunction"));
    auto & signatures = myFunction.getFunctionSignaturesReference();
    ASSERT_EQ(signatures.size(), 1);
    auto & parameters = signatures[0].getFunctionParametersReference();
    ASSERT_EQ(parameters.size(), 2);
    EXPECT_EQ(parameters[0].getType(), CPlusPlusType("double", CPlusPlusTypeType::Primitive));
    EXPECT_EQ(parameters[1].getType(), CPlusPlusType("double", CPlusPlusTypeType::Primitive, 1));

    ASSERT_EQ(m_terms.size(), 10);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "int myFunction(double parameter1, double* parameter2)\n{\n}\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "int myInteger;\n", 4);
    CHECK_TERM(it, TermType::ProcessedTerm, "double myDouble;\n", 5);
    CHECK_TERM(it, TermType::ProcessedTerm, "double* myDoublePointer;\n", 6);
    CHECK_TERM(it, TermType::ProcessedTerm, "myFunction(myInteger, myInteger);\n", 7);
    CHECK_TERM(it, TermType::ProcessedTerm, "myFunction(1, myInteger);\n", 8);
    CHECK_TERM(it, TermType::ProcessedTerm, "myFunction(myInteger, &myDouble);\n", 9);
    CHECK_TERM(it, TermType::ProcessedTerm, "myFunction(myDouble, &myDouble);\n", 10);
    CHECK_TERM(it, TermType::ProcessedTerm, "myFunction(1, &myDouble);\n", 11);
    CHECK_TERM(it, TermType::ProcessedTerm, "myFunction(*myDoublePointer, &myDouble);\n", 12);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 3);
}

TEST_F(ModuleTest, ReturnValuesAreUsed)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "int myFunction()\n";
    testFile << "{\n";
    testFile << "}\n";
    testFile << "int x = myFunction();\n";
    testFile.close();

    processFile();
    CPlusPlusFunction& myFunction(m_database.getFunctionReference("myFunction"));
    auto & signatures = myFunction.getFunctionSignaturesReference();
    ASSERT_EQ(signatures.size(), 1);
    auto & parameters = signatures[0].getFunctionParametersReference();
    ASSERT_EQ(parameters.size(), 0);

    ASSERT_EQ(m_terms.size(), 2);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "int myFunction()\n{\n}\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "int x = myFunction();\n", 4);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, ComplicatedFunctionTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "int myFunction(int parameter1, int& parameter2, int* parameter3, int** parameter4)\n";
    testFile << "{\n";
    testFile << "}\n";
    testFile << "int myInteger;\n";
    testFile << "int x = myFunction(myInteger, myInteger, &myInteger, &(&myInteger));\n";
    testFile.close();

    processFile();
    CPlusPlusFunction& myFunction(m_database.getFunctionReference("myFunction"));
    auto & signatures = myFunction.getFunctionSignaturesReference();
    ASSERT_EQ(signatures.size(), 1);
    auto & parameters = signatures[0].getFunctionParametersReference();
    ASSERT_EQ(parameters.size(), 4);
    EXPECT_EQ(parameters[0].getType(), CPlusPlusType("int", CPlusPlusTypeType::Primitive));
    CPlusPlusType integerReference("int", CPlusPlusTypeType::Primitive);
    integerReference.setAsReference();
    EXPECT_EQ(parameters[1].getType(), integerReference);
    EXPECT_EQ(parameters[2].getType(), CPlusPlusType("int", CPlusPlusTypeType::Primitive, 1));
    EXPECT_EQ(parameters[3].getType(), CPlusPlusType("int", CPlusPlusTypeType::Primitive, 2));

    ASSERT_EQ(m_terms.size(), 3);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "int myFunction(int parameter1, int& parameter2, int* parameter3, int** parameter4)\n{\n}\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "int myInteger;\n", 4);
    CHECK_TERM(it, TermType::ProcessedTerm, "int x = myFunction(myInteger, myInteger, &myInteger, &(&myInteger));\n", 5);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, FunctionsCanBeOverloadedTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "int myFunction(int parameter1)\n";
    testFile << "{\n";
    testFile << "}\n";
    testFile << "int myFunction(int parameter1, int parameter2)\n";
    testFile << "{\n";
    testFile << "}\n";
    testFile << "int x = myFunction(5);\n";
    testFile.close();

    processFile();
    CPlusPlusFunction& myFunction(m_database.getFunctionReference("myFunction"));
    auto & signatures = myFunction.getFunctionSignaturesReference();
    ASSERT_EQ(signatures.size(), 2);
    EXPECT_EQ(signatures[0].getFunctionParametersReference().size(), 1);
    EXPECT_EQ(signatures[1].getFunctionParametersReference().size(), 2);

    ASSERT_EQ(m_terms.size(), 3);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "int myFunction(int parameter1)\n{\n}\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "int myFunction(int parameter1, int parameter2)\n{\n}\n", 4);
    CHECK_TERM(it, TermType::ProcessedTerm, "int x = myFunction(5);\n", 7);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, NamesCheckedForFunctionDeclarationAndDefinitionTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "int myFunction1(int thisIsADifferentName);\n";
    testFile << "int myFunction1(int parameter1)\n";
    testFile << "{\n";
    testFile << "}\n";
    testFile << "int myFunction2(int);\n";
    testFile << "int myFunction2(int parameter1)\n";
    testFile << "{\n";
    testFile << "}\n";
    testFile << "int myFunction3(int thisIsADifferentName);\n";
    testFile << "int myFunction3(int)\n";
    testFile << "{\n";
    testFile << "}\n";
    testFile << "int x = myFunction1(5);\n";
    testFile << "int y = myFunction2(5);\n";
    testFile << "int z = myFunction3(5);\n";
    testFile.close();

    processFile();
    CPlusPlusFunction& myFunction1(m_database.getFunctionReference("myFunction1"));
    ASSERT_EQ(myFunction1.getFunctionSignaturesReference().size(), 1);
    CPlusPlusFunction& myFunction2(m_database.getFunctionReference("myFunction2"));
    ASSERT_EQ(myFunction2.getFunctionSignaturesReference().size(), 1);
    CPlusPlusFunction& myFunction3(m_database.getFunctionReference("myFunction3"));
    ASSERT_EQ(myFunction3.getFunctionSignaturesReference().size(), 1);

    ASSERT_EQ(m_terms.size(), 9);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "int myFunction1(int thisIsADifferentName);\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "int myFunction1(int parameter1)\n{\n}\n", 2);
    CHECK_TERM(it, TermType::ProcessedTerm, "int myFunction2(int);\n", 5);
    CHECK_TERM(it, TermType::ProcessedTerm, "int myFunction2(int parameter1)\n{\n}\n", 6);
    CHECK_TERM(it, TermType::ProcessedTerm, "int myFunction3(int thisIsADifferentName);\n", 9);
    CHECK_TERM(it, TermType::ProcessedTerm, "int myFunction3(int)\n{\n}\n", 10);
    CHECK_TERM(it, TermType::ProcessedTerm, "int x = myFunction1(5);\n", 13);
    CHECK_TERM(it, TermType::ProcessedTerm, "int y = myFunction2(5);\n", 14);
    CHECK_TERM(it, TermType::ProcessedTerm, "int z = myFunction3(5);\n", 15);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 3);
}
