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
    testFile << "int main(int args, void** argv)" << endl;
    testFile << "{" << endl;
    testFile << "int x = 5;" << endl;
    testFile << "}" << endl;
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
    testFile << "int myFunction(double parameter1, double* parameter2)" << endl;
    testFile << "{" << endl;
    testFile << "}" << endl;
    testFile << "int myInteger;" << endl;
    testFile << "double myDouble;" << endl;
    testFile << "double* myDoublePointer;" << endl;
    testFile << "myFunction(myInteger, myInteger);" << endl;
    testFile << "myFunction(1, myInteger);" << endl;
    testFile << "myFunction(myInteger, &myDouble);" << endl;
    testFile << "myFunction(myDouble, &myDouble);" << endl;
    testFile << "myFunction(1, &myDouble);" << endl;
    testFile << "myFunction(*myDoublePointer, &myDouble);" << endl;
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
    testFile << "int myFunction()" << endl;
    testFile << "{" << endl;
    testFile << "}" << endl;
    testFile << "int x = myFunction();" << endl;
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
    testFile << "int myFunction(int parameter1, int& parameter2, int* parameter3, int** parameter4)" << endl;
    testFile << "{" << endl;
    testFile << "}" << endl;
    testFile << "int myInteger;" << endl;
    testFile << "int x = myFunction(myInteger, myInteger, &myInteger, &(&myInteger));" << endl;
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
    testFile << "int myFunction(int parameter1)" << endl;
    testFile << "{" << endl;
    testFile << "}" << endl;
    testFile << "int myFunction(int parameter1, int parameter2)" << endl;
    testFile << "{" << endl;
    testFile << "}" << endl;
    testFile << "int x = myFunction(5);" << endl;
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
    testFile << "int myFunction1(int thisIsADifferentName);" << endl;
    testFile << "int myFunction1(int parameter1)" << endl;
    testFile << "{" << endl;
    testFile << "}" << endl;
    testFile << "int myFunction2(int);" << endl;
    testFile << "int myFunction2(int parameter1)" << endl;
    testFile << "{" << endl;
    testFile << "}" << endl;
    testFile << "int myFunction3(int thisIsADifferentName);" << endl;
    testFile << "int myFunction3(int)" << endl;
    testFile << "{" << endl;
    testFile << "}" << endl;
    testFile << "int x = myFunction1(5);" << endl;
    testFile << "int y = myFunction2(5);" << endl;
    testFile << "int z = myFunction3(5);" << endl;
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



