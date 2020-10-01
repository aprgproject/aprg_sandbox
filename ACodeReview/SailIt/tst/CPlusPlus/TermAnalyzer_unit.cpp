#include <fstream>
#include "gtest/gtest.h"
#include "../Checkers.hpp"
#include "../MtDirectoryConstants.hpp"
#include "../../src/CPlusPlus/Analyzer/TermAnalyzer.hpp"
#include "../../src/CPlusPlus/Builder/TermBuilder.hpp"
#include "../../src/CPlusPlus/Database/CPlusPlusDatabase.hpp"
#include "../../src/FileDirectoryDatabase/FileDirectoryDatabase.hpp"

using namespace codeReview;
using namespace std;

struct TermAnalyzerTest : public ::testing::Test
{
    TermAnalyzerTest()
        : m_database()
        , m_findings()
        , m_terms()
        , m_termBuilder(m_terms)
        , m_termAnalyzer(m_terms, m_database, m_findings)
    {}

    void processFile()
    {
        m_termAnalyzer.analyze();
        //printTerms(m_terms);
        //m_findings.printFindings(cout);
        //m_database.print(cout);
    }
    CPlusPlusDatabase m_database;
    Findings m_findings;
    DequeOfTerms m_terms;
    TermBuilder m_termBuilder;
    TermAnalyzer m_termAnalyzer;
};

TEST_F(TermAnalyzerTest, CheckCorrectIncludeFiles)
{
    TermBuilder& termBuilder(m_termBuilder);
    termBuilder.addMacro("#include");
    termBuilder.addWhiteSpace();
    termBuilder.addOperator("<");
    termBuilder.addIdentifier("algorithm");
    termBuilder.addOperator(">");
    termBuilder.addNewLine();
    termBuilder.addMacro("#include");
    termBuilder.addWhiteSpace();
    termBuilder.addOperator("<");
    termBuilder.addOperator("<");
    termBuilder.addIdentifier("iostream");
    termBuilder.addOperator(">");
    termBuilder.addIdentifier("withAngleBrackets");
    termBuilder.addOperator(">");
    termBuilder.addNewLine();
    termBuilder.addMacro("#include");
    termBuilder.addWhiteSpace();
    termBuilder.addConstantString("\"stdio.h\"");
    termBuilder.addNewLine();

    processFile();
    ASSERT_EQ(m_terms.size(), 3);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "#include <algorithm>\n", 0);
    CHECK_TERM(it, TermType::ProcessedTerm, "#include <<iostream>withAngleBrackets>\n", 0);
    CHECK_TERM(it, TermType::ProcessedTerm, "#include \"stdio.h\"\n", 0);

    ASSERT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
    ASSERT_EQ(m_database.getIncludeFilesReference().size(), 3);
    auto it2 = m_database.getIncludeFilesReference().begin();
    EXPECT_EQ(*(it2++), "<iostream>withAngleBrackets");
    EXPECT_EQ(*(it2++), "algorithm");
    EXPECT_EQ(*(it2++), "stdio.h");
}

TEST_F(TermAnalyzerTest, CheckCompareSingleLineWithWhiteSpaceAlgorithm)
{
    TermBuilder& termBuilder(m_termBuilder);
    termBuilder.addMacro("#include");
    termBuilder.addOperator("<");
    termBuilder.addIdentifier("algorithm");
    termBuilder.addOperator(">");
    termBuilder.addNewLine();
    termBuilder.addMacro("#include");
    termBuilder.addWhiteSpace();
    termBuilder.addOperator("<");
    termBuilder.addWhiteSpace();
    termBuilder.addIdentifier("algorithm");
    termBuilder.addWhiteSpace();
    termBuilder.addOperator(">");
    termBuilder.addWhiteSpace();
    termBuilder.addNewLine();
    termBuilder.addMacro("#include");
    termBuilder.addWhiteSpace();
    termBuilder.addConstantString("\"stdio.h\"");
    termBuilder.addWhiteSpace();
    termBuilder.addNewLine();
    termBuilder.addNewLine();
    termBuilder.addNewLine();
    termBuilder.addIdentifier("Idon'tKnowWhatIsThePurposeOfThis");

    processFile();
    ASSERT_EQ(m_terms.size(), 6);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "#include<algorithm>\n", 0);
    CHECK_TERM(it, TermType::ProcessedTerm, "#include < algorithm > \n", 0);
    CHECK_TERM(it, TermType::ProcessedTerm, "#include \"stdio.h\" \n", 0);
    CHECK_TERM(it, TermType::NewLine, "\n", 0);
    CHECK_TERM(it, TermType::NewLine, "\n", 0);
    CHECK_TERM(it, TermType::Identifier, "Idon'tKnowWhatIsThePurposeOfThis", 0);

    MultiMapOfFindings& multiMapOfFindings = m_findings.getMultiMapOfFindingsReference();
    ASSERT_EQ(multiMapOfFindings.size(), 6);
    //EXPECT_EQ(multiMapOfFindings.begin()->getDetails(), "Expected white space[4]");

    ASSERT_EQ(m_database.getIncludeFilesReference().size(), 3);
    auto it2 = m_database.getIncludeFilesReference().begin();
    EXPECT_EQ(*(it2++), " algorithm ");
    EXPECT_EQ(*(it2++), "algorithm");
    EXPECT_EQ(*(it2++), "stdio.h");
}

TEST_F(TermAnalyzerTest, CheckCompareMultiLineWithNewLineAlgorithm)
{
    TermBuilder& termBuilder(m_termBuilder);
    m_database.addNamespace("Scope1");
    m_database.addNamespace("Scope2");
    termBuilder.addIdentifier("Scope1");
    termBuilder.addNewLine();
    termBuilder.addOperator("::");
    termBuilder.addNewLine();
    termBuilder.addIdentifier("Scope2");

    processFile();
    ASSERT_EQ(m_terms.size(), 1);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::Namespace, "Scope1\n::\nScope2", 0);
    ASSERT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 3);
}

TEST_F(TermAnalyzerTest, CheckGetEquivalentStringAlgorithm)
{
    TermBuilder& termBuilder(m_termBuilder);
    m_database.addNamespace("Scope1");
    m_database.addNamespace("Scope2");
    termBuilder.addIdentifier("Scope1");
    termBuilder.addWhiteSpace();
    termBuilder.addOperator("::");
    termBuilder.addWhiteSpace();
    termBuilder.addIdentifier("Scope2");

    processFile();
    ASSERT_EQ(m_terms.size(), 1);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::Namespace, "Scope1 :: Scope2", 0);
    ASSERT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 3);
}

TEST_F(TermAnalyzerTest, ExpressionsAreSimplifiedUsingScopeOperator)
{
    TermBuilder& termBuilder(m_termBuilder);
    m_database.addNamespace("Scope1");
    m_database.addNamespace("Scope2");
    m_database.addNamespace("Scope3");
    m_database.addNamespace("Scope4");
    m_database.addNamespace("Scope5");
    termBuilder.addIdentifier("Scope1");
    termBuilder.addOperator("::");
    termBuilder.addIdentifier("Scope2");
    termBuilder.addIdentifier("Scope1");
    termBuilder.addOperator("::");
    termBuilder.addIdentifier("Scope2");
    termBuilder.addOperator("::");
    termBuilder.addIdentifier("Scope3");
    termBuilder.addOperator("::");
    termBuilder.addIdentifier("Scope4");
    termBuilder.addOperator("::");
    termBuilder.addIdentifier("Scope5");
    termBuilder.addIdentifier("Scope1");
    termBuilder.addOperator("::");
    termBuilder.addIdentifier("Scope2");
    termBuilder.addOperator("::");
    termBuilder.addIdentifier("Scope3");

    processFile();
    ASSERT_EQ(m_terms.size(), 3);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::Namespace, "Scope1::Scope2", 0);
    CHECK_TERM(it, TermType::Namespace, "Scope1::Scope2::Scope3::Scope4::Scope5", 0);
    CHECK_TERM(it, TermType::Namespace, "Scope1::Scope2::Scope3", 0);
    ASSERT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 3);
}

TEST_F(TermAnalyzerTest, ExpressionsAreSimplifiedUsingIncrementDecrementOperators)
{
    TermBuilder& termBuilder(m_termBuilder);
    termBuilder.addTerm(T(TermType::Value_LValue, "LValue"));
    termBuilder.getLastTermReference().setValueType(CPlusPlusType("unsigned int", CPlusPlusTypeType::Primitive));
    termBuilder.addOperator("++");
    termBuilder.addSemiColon();
    termBuilder.addNewLine();
    termBuilder.addTerm(T(TermType::Variable, "Variable"));
    termBuilder.getLastTermReference().setValueType(CPlusPlusType("float", CPlusPlusTypeType::Primitive));
    termBuilder.addOperator("--");
    termBuilder.addSemiColon();
    termBuilder.addNewLine();
    termBuilder.addOperator("++");
    termBuilder.addTerm(T(TermType::Value_LValue, "LValue"));
    termBuilder.getLastTermReference().setValueType(CPlusPlusType("unsigned int", CPlusPlusTypeType::Primitive));
    termBuilder.addSemiColon();
    termBuilder.addNewLine();
    termBuilder.addOperator("--");
    termBuilder.addTerm(T(TermType::Value_RValue, "Variable"));
    termBuilder.getLastTermReference().setValueType(CPlusPlusType("float", CPlusPlusTypeType::Primitive));
    termBuilder.addSemiColon();

    processFile();
    ASSERT_EQ(m_terms.size(), 5);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "LValue++;\n", 0);
    CHECK_TERM(it, TermType::ProcessedTerm, "Variable--;\n", 0);
    CHECK_TERM(it, TermType::ProcessedTerm, "++LValue;\n", 0);
    CHECK_TERM(it, TermType::Value_RValue, "--Variable", 0);
    CHECK_TERM(it, TermType::Operator, ";", 0);
    ASSERT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 2);
}

TEST_F(TermAnalyzerTest, ExpressionsAreSimplifiedUsingFunctionCall)
{
    CPlusPlusType intPrimitiveType("int", CPlusPlusTypeType::Primitive);

    m_database.addFunction("myFunction0");
    CPlusPlusFunction& myFunction0(m_database.getFunctionReference("myFunction0"));
    myFunction0.addFunctionSignature(CPlusPlusFunctionSignature());
    m_database.addFunction("myFunction1");
    CPlusPlusFunction& myFunction1(m_database.getFunctionReference("myFunction1"));
    CPlusPlusFunctionSignature myFunctionSignature1;
    myFunctionSignature1.addParameter(intPrimitiveType, "parameter1");
    myFunction1.addFunctionSignature(myFunctionSignature1);

    TermBuilder& termBuilder(m_termBuilder);
    m_database.addFunction("myFunction0");
    m_database.addFunction("myFunction1");
    termBuilder.addIdentifier("myFunction0");
    termBuilder.addOperator("(");
    termBuilder.addOperator(")");
    termBuilder.addIdentifier("myFunction1");
    termBuilder.addOperator("(");
    termBuilder.addTerm(T(TermType::Value_RValue, "Value1"));
    termBuilder.getLastTermReference().setValueType(intPrimitiveType);
    termBuilder.addOperator(")");

    processFile();
    ASSERT_EQ(m_terms.size(), 2);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::Value_RValue_CanBeALine, "myFunction0()", 0);
    CHECK_TERM(it, TermType::Value_RValue_CanBeALine, "myFunction1(Value1)", 0);

    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 2);
}

TEST_F(TermAnalyzerTest, ExpressionsAreSimplifiedUsingPeriodOperator)
{
    TermBuilder& termBuilder(m_termBuilder);
    termBuilder.addTerm(T(TermType::Value_RValue, "RValue"));
    termBuilder.getLastTermReference().setValueType(CPlusPlusType("unsigned int", CPlusPlusTypeType::Primitive));
    termBuilder.addOperator(".");
    termBuilder.addTerm(T(TermType::Identifier, "Identifier"));
    termBuilder.addTerm(T(TermType::Value_LValue, "LValue"));
    termBuilder.getLastTermReference().setValueType(CPlusPlusType("float", CPlusPlusTypeType::Primitive));
    termBuilder.addOperator(".");
    termBuilder.addTerm(T(TermType::Identifier, "Identifier"));
    termBuilder.addSemiColon();

    processFile();
    ASSERT_EQ(m_terms.size(), 3);
    auto it = m_terms.begin();
    CHECK_TERM_WITH_VALUE_TYPE(it, TermType::Value_RValue, "RValue.Identifier", "unsigned int", 0);
    CHECK_TERM_WITH_VALUE_TYPE(it, TermType::Value_RValue, "LValue.Identifier", "float", 0);
    CHECK_TERM(it, TermType::Operator, ";", 0);
    ASSERT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 3);
}

TEST_F(TermAnalyzerTest, ExpressionsAreSimplifiedUsingArrowOperator)
{
    TermBuilder& termBuilder(m_termBuilder);
    termBuilder.addTerm(T(TermType::Value_RValue, "RValue"));
    termBuilder.getLastTermReference().setValueType(CPlusPlusType("unsigned int", CPlusPlusTypeType::Primitive));
    termBuilder.addOperator("->");
    termBuilder.addTerm(T(TermType::Identifier, "Identifier"));
    termBuilder.addSemiColon();
    termBuilder.addTerm(T(TermType::Value_LValue, "LValue"));
    termBuilder.getLastTermReference().setValueType(CPlusPlusType("float", CPlusPlusTypeType::Primitive));
    termBuilder.addOperator("->");
    termBuilder.addTerm(T(TermType::Identifier, "Identifier"));
    termBuilder.addSemiColon();

    processFile();
    ASSERT_EQ(m_terms.size(), 4);
    auto it = m_terms.begin();
    CHECK_TERM_WITH_VALUE_TYPE(it, TermType::Value_RValue, "RValue->Identifier", "unsigned int", 0);
    CHECK_TERM(it, TermType::Operator, ";", 0);
    CHECK_TERM_WITH_VALUE_TYPE(it, TermType::Value_RValue, "LValue->Identifier", "float", 0);
    CHECK_TERM(it, TermType::Operator, ";", 0);
    ASSERT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 4);
}

TEST_F(TermAnalyzerTest, ExpressionsAreSimplifiedUsingPrefixOperator)
{
    TermBuilder& termBuilder(m_termBuilder);
    termBuilder.addOperator("+");
    termBuilder.addTerm(T(TermType::Value_RValue, "RValue"));
    termBuilder.getLastTermReference().setValueType(CPlusPlusType("unsigned int", CPlusPlusTypeType::Primitive));
    termBuilder.addSemiColon();
    termBuilder.addOperator("&");
    termBuilder.addTerm(T(TermType::Value_LValue, "LValue"));
    termBuilder.getLastTermReference().setValueType(CPlusPlusType("float", CPlusPlusTypeType::Primitive));
    termBuilder.addSemiColon();

    processFile();
    ASSERT_EQ(m_terms.size(), 4);
    auto it = m_terms.begin();
    CHECK_TERM_WITH_VALUE_TYPE(it, TermType::Value_RValue, "+RValue", "unsigned int", 0);
    CHECK_TERM(it, TermType::Operator, ";", 0);
    CHECK_TERM_WITH_VALUE_TYPE(it, TermType::Value_RValue, "&LValue", "float", 0);
    CHECK_TERM(it, TermType::Operator, ";", 0);
    ASSERT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 4);
}

TEST_F(TermAnalyzerTest, ExpressionsAreSimplifiedUsingBiDirectoryOperator)
{
    TermBuilder& termBuilder(m_termBuilder);
    termBuilder.addTerm(T(TermType::Value_LValue, "LValue"));
    termBuilder.getLastTermReference().setValueType(CPlusPlusType("unsigned int", CPlusPlusTypeType::Primitive));
    termBuilder.addWhiteSpace();
    termBuilder.addOperator("+");
    termBuilder.addWhiteSpace();
    termBuilder.addTerm(T(TermType::Value_RValue, "RValue"));
    termBuilder.getLastTermReference().setValueType(CPlusPlusType("float", CPlusPlusTypeType::Primitive));
    termBuilder.addSemiColon();
    termBuilder.addTerm(T(TermType::Value_LValue, "RValue"));
    termBuilder.getLastTermReference().setValueType(CPlusPlusType("unsigned int", CPlusPlusTypeType::Primitive));
    termBuilder.addWhiteSpace();
    termBuilder.addOperator("/");
    termBuilder.addWhiteSpace();
    termBuilder.addTerm(T(TermType::Value_LValue, "LValue"));
    termBuilder.getLastTermReference().setValueType(CPlusPlusType("float", CPlusPlusTypeType::Primitive));
    termBuilder.addSemiColon();

    processFile();
    ASSERT_EQ(m_terms.size(), 4);
    auto it = m_terms.begin();
    CHECK_TERM_WITH_VALUE_TYPE(it, TermType::Value_RValue, "LValue + RValue", "unsigned int", 0);
    CHECK_TERM(it, TermType::Operator, ";", 0);
    CHECK_TERM_WITH_VALUE_TYPE(it, TermType::Value_RValue, "RValue / LValue", "unsigned int", 0);
    CHECK_TERM(it, TermType::Operator, ";", 0);
    ASSERT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 4);
}

TEST_F(TermAnalyzerTest, TypesAreSimplifiedUsingMultiplePrimtiveTypes)
{
    TermBuilder& termBuilder(m_termBuilder);
    termBuilder.addPrimitiveType("signed");
    termBuilder.addWhiteSpace();
    termBuilder.addPrimitiveType("int");
    termBuilder.addSemiColon();
    termBuilder.addPrimitiveType("unsigned");
    termBuilder.addWhiteSpace();
    termBuilder.addPrimitiveType("long");
    termBuilder.addWhiteSpace();
    termBuilder.addPrimitiveType("long");
    termBuilder.addSemiColon();

    processFile();
    ASSERT_EQ(m_terms.size(), 4);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::Type, "signed int", 0);
    CHECK_TERM(it, TermType::Operator, ";", 0);
    CHECK_TERM(it, TermType::Type, "unsigned long long", 0);
    CHECK_TERM(it, TermType::Operator, ";", 0);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 4);
}

TEST_F(TermAnalyzerTest, TypesAreSimplifiedUsingPointersAndReference)
{
    TermBuilder& termBuilder(m_termBuilder);
    termBuilder.addPrimitiveType("void");
    termBuilder.addOperator("*");
    termBuilder.addPrimitiveType("int");
    termBuilder.addOperator("&");
    termBuilder.addPrimitiveType("unsigned");
    termBuilder.addWhiteSpace();
    termBuilder.addPrimitiveType("long");
    termBuilder.addWhiteSpace();
    termBuilder.addPrimitiveType("long");
    termBuilder.addOperator("*");
    termBuilder.addOperator("*");

    processFile();
    ASSERT_EQ(m_terms.size(), 3);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::Type, "void*", 0);
    CHECK_TERM(it, TermType::Type, "int&", 0);
    CHECK_TERM(it, TermType::Type, "unsigned long long**", 0);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 3);
}

TEST_F(TermAnalyzerTest, StatementsAreSimplifiedUsingAssignment)
{
    TermBuilder& termBuilder(m_termBuilder);
    termBuilder.addPrimitiveType("int");
    termBuilder.addWhiteSpace();
    termBuilder.addIdentifier("testname1");
    termBuilder.addSemiColon();
    termBuilder.addNewLine();
    termBuilder.addPrimitiveType("int");
    termBuilder.addWhiteSpace();
    termBuilder.addIdentifier("testname2");
    termBuilder.addWhiteSpace();
    termBuilder.addOperator("=");
    termBuilder.addWhiteSpace();
    termBuilder.addConstantNumber("5");
    termBuilder.addSemiColon();
    termBuilder.addNewLine();
    termBuilder.addIdentifier("testname2");
    termBuilder.addWhiteSpace();
    termBuilder.addOperator("=");
    termBuilder.addWhiteSpace();
    termBuilder.addConstantNumber("10");
    termBuilder.addSemiColon();
    termBuilder.addNewLine();

    processFile();
    ASSERT_EQ(m_terms.size(), 3);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "int testname1;\n", 0);
    CHECK_TERM(it, TermType::ProcessedTerm, "int testname2 = 5;\n", 0);
    CHECK_TERM(it, TermType::ProcessedTerm, "testname2 = 10;\n", 0);

    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);

    ASSERT_EQ(m_database.getVariablesReference().size(), 2);
    EXPECT_TRUE(m_database.isVariable("testname1"));
    EXPECT_TRUE(m_database.isVariable("testname2"));
}

TEST_F(TermAnalyzerTest, StatementsAreSimplifiedUsingFunctionDeclaration)
{
    TermBuilder& termBuilder(m_termBuilder);
    termBuilder.addPrimitiveType("void");
    termBuilder.addWhiteSpace();
    termBuilder.addIdentifier("function1");
    termBuilder.addOperator("(");
    termBuilder.addOperator(")");
    termBuilder.addSemiColon();
    termBuilder.addNewLine();
    termBuilder.addPrimitiveType("void");
    termBuilder.addWhiteSpace();
    termBuilder.addIdentifier("function2");
    termBuilder.addOperator("(");
    termBuilder.addPrimitiveType("int");
    termBuilder.addWhiteSpace();
    termBuilder.addIdentifier("parameter1");
    termBuilder.addOperator(",");
    termBuilder.addWhiteSpace();
    termBuilder.addPrimitiveType("int");
    termBuilder.addOperator("*");
    termBuilder.addOperator("*");
    termBuilder.addWhiteSpace();
    termBuilder.addIdentifier("parameter2");
    termBuilder.addOperator(")");
    termBuilder.addSemiColon();
    termBuilder.addNewLine();

    processFile();
    ASSERT_EQ(m_terms.size(), 2);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "void function1();\n", 0);
    CHECK_TERM(it, TermType::ProcessedTerm, "void function2(int parameter1, int** parameter2);\n", 0);

    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);

    ASSERT_GE(m_database.getFunctionsReference().size(), 2);
    EXPECT_TRUE(m_database.isFunction("function1"));
    EXPECT_TRUE(m_database.isFunction("function2"));
}

TEST_F(TermAnalyzerTest, StatementsAreSimplifiedUsingRValueStatement)
{
    CPlusPlusType intPrimitiveType("int", CPlusPlusTypeType::Primitive);

    m_database.addFunction("myFunction0");
    CPlusPlusFunction& myFunction0(m_database.getFunctionReference("myFunction0"));
    myFunction0.addFunctionSignature(CPlusPlusFunctionSignature());
    m_database.addFunction("myFunction1");
    CPlusPlusFunction& myFunction1(m_database.getFunctionReference("myFunction1"));
    CPlusPlusFunctionSignature myFunctionSignature1;
    myFunctionSignature1.addParameter(intPrimitiveType, "parameter1");
    myFunction1.addFunctionSignature(myFunctionSignature1);
    m_database.addFunction("myFunction2");
    CPlusPlusFunction& myFunction2(m_database.getFunctionReference("myFunction2"));
    CPlusPlusFunctionSignature myFunctionSignature2;
    myFunctionSignature2.addParameter(intPrimitiveType, "parameter1");
    myFunctionSignature2.addParameter(intPrimitiveType, "parameter2");
    myFunction2.addFunctionSignature(myFunctionSignature2);
    m_database.addFunction("myFunction3");
    CPlusPlusFunction& myFunction3(m_database.getFunctionReference("myFunction3"));
    CPlusPlusFunctionSignature myFunctionSignature3;
    myFunctionSignature3.addParameter(intPrimitiveType, "parameter1");
    myFunctionSignature3.addParameter(intPrimitiveType, "parameter2");
    myFunctionSignature3.addParameter(intPrimitiveType, "parameter3");
    myFunction3.addFunctionSignature(myFunctionSignature3);

    TermBuilder& termBuilder(m_termBuilder);
    termBuilder.addIdentifier("myFunction0");
    termBuilder.addOperator("(");
    termBuilder.addOperator(")");
    termBuilder.addSemiColon();
    termBuilder.addNewLine();
    termBuilder.addIdentifier("myFunction1");
    termBuilder.addOperator("(");
    termBuilder.addTerm(T(TermType::Value_RValue, "Value1"));
    termBuilder.getLastTermReference().setValueType(intPrimitiveType);
    termBuilder.addOperator(")");
    termBuilder.addSemiColon();
    termBuilder.addNewLine();
    termBuilder.addIdentifier("myFunction2");
    termBuilder.addOperator("(");
    termBuilder.addTerm(T(TermType::Value_RValue, "Value1"));
    termBuilder.getLastTermReference().setValueType(intPrimitiveType);
    termBuilder.addOperator(",");
    termBuilder.addWhiteSpace();
    termBuilder.addTerm(T(TermType::Value_RValue, "Value2"));
    termBuilder.getLastTermReference().setValueType(intPrimitiveType);
    termBuilder.addOperator(")");
    termBuilder.addSemiColon();
    termBuilder.addNewLine();
    termBuilder.addIdentifier("myFunction3");
    termBuilder.addOperator("(");
    termBuilder.addTerm(T(TermType::Value_RValue, "Value1"));
    termBuilder.getLastTermReference().setValueType(intPrimitiveType);
    termBuilder.addOperator(",");
    termBuilder.addWhiteSpace();
    termBuilder.addTerm(T(TermType::Value_RValue, "Value2"));
    termBuilder.getLastTermReference().setValueType(intPrimitiveType);
    termBuilder.addOperator(",");
    termBuilder.addWhiteSpace();
    termBuilder.addTerm(T(TermType::Value_RValue, "Value3"));
    termBuilder.getLastTermReference().setValueType(intPrimitiveType);
    termBuilder.addOperator(")");
    termBuilder.addSemiColon();
    termBuilder.addNewLine();

    processFile();
    ASSERT_EQ(m_terms.size(), 4);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "myFunction0();\n", 0);
    CHECK_TERM(it, TermType::ProcessedTerm, "myFunction1(Value1);\n", 0);
    CHECK_TERM(it, TermType::ProcessedTerm, "myFunction2(Value1, Value2);\n", 0);
    CHECK_TERM(it, TermType::ProcessedTerm, "myFunction3(Value1, Value2, Value3);\n", 0);

    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}
