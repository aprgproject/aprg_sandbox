#include "../Checkers.hpp"
#include "fixtures/ModuleTest.hpp"
#include "gtest/gtest.h"

#include <fstream>

using namespace codeReview;
using namespace std;

TEST_F(ModuleTest, ReturnTypeTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "const char *__mingw_get_crt_info(void);\n";
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 1);
    EXPECT_TRUE(m_database.isFunction("__mingw_get_crt_info"));
    CPlusPlusFunction& myFunction(m_database.getFunctionReference("__mingw_get_crt_info"));
    auto & signatures = myFunction.getFunctionSignaturesReference();
    ASSERT_EQ(signatures.size(), 1);
    CPlusPlusType constCharPointer("char", CPlusPlusTypeType::Primitive);
    constCharPointer.setAsConst();
    constCharPointer.incrementPointerCount();
    EXPECT_EQ(signatures[0].getReturnTypeReference(), constCharPointer);

    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "const char *__mingw_get_crt_info(void);\n", 1);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 3);
}

TEST_F(ModuleTest, TypeDefTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "#define MACROINT int\n";
    testFile << "typedef unsigned int MyInteger;\n";
    testFile << "MyInteger myInteger1 = 5;\n";
    testFile << "typedef MACROINT MyInteger2;\n";
    testFile << "MyInteger2 myInteger2 = 5;\n";
    testFile.close();

    processFile();
    CHECK_TYPE_IN_DATABASE(m_database, "MyInteger", CPlusPlusType("unsigned int", CPlusPlusTypeType::Primitive));
    CHECK_TYPE_IN_DATABASE(m_database, "MyInteger2", CPlusPlusType("int", CPlusPlusTypeType::Primitive));

    ASSERT_EQ(m_terms.size(), 5);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "#define MACROINT int\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef unsigned int MyInteger;\n", 2);
    CHECK_TERM(it, TermType::ProcessedTerm, "MyInteger myInteger1 = 5;\n", 3);
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef int MyInteger2;\n", 4);
    CHECK_TERM(it, TermType::ProcessedTerm, "MyInteger2 myInteger2 = 5;\n", 5);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, TypeDefWithParenthesisTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "typedef int __int128 __attribute__ ((__mode__ (TI)));\n";
    testFile.close();

    processFile();
    CHECK_TYPE_IN_DATABASE(m_database, "__int128", CPlusPlusType("int", CPlusPlusTypeType::Primitive));
    CHECK_TYPE_IN_DATABASE(m_database, "__attribute__", CPlusPlusType("int", CPlusPlusTypeType::Primitive));

    ASSERT_EQ(m_terms.size(), 1);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef int __int128 __attribute__ ((__mode__ (TI)));\n", 1);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}


TEST_F(ModuleTest, TypeDefWithMultipleTypedefNamesTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "typedef unsigned __int64 size_t;\n";
    testFile << "typedef __int64 ssize_t;\n";
    testFile << "typedef __int64 intptr_t;\n";
    testFile << "typedef unsigned __int64 uintptr_t;\n";
    testFile << "typedef __int64 ptrdiff_t;\n";
    testFile << "typedef unsigned short wint_t;\n";
    testFile << "typedef unsigned short wctype_t;\n";
    testFile << "typedef int errno_t;\n";
    testFile << "typedef long __time32_t;\n";
    testFile << "typedef __int64 __time64_t;\n";
    testFile << "typedef __time32_t time_t;\n";
    testFile.close();

    processFile();
    CHECK_TYPE_IN_DATABASE(m_database, "__int64", CPlusPlusType("unsigned", CPlusPlusTypeType::Primitive));
    CHECK_TYPE_IN_DATABASE(m_database, "size_t", CPlusPlusType("unsigned", CPlusPlusTypeType::Primitive));
    CHECK_TYPE_IN_DATABASE(m_database, "ssize_t", CPlusPlusType("unsigned", CPlusPlusTypeType::Primitive));
    CHECK_TYPE_IN_DATABASE(m_database, "intptr_t", CPlusPlusType("unsigned", CPlusPlusTypeType::Primitive));
    CHECK_TYPE_IN_DATABASE(m_database, "uintptr_t", CPlusPlusType("unsigned", CPlusPlusTypeType::Primitive));
    CHECK_TYPE_IN_DATABASE(m_database, "ptrdiff_t", CPlusPlusType("unsigned", CPlusPlusTypeType::Primitive));
    CHECK_TYPE_IN_DATABASE(m_database, "wint_t", CPlusPlusType("unsigned short", CPlusPlusTypeType::Primitive));
    CHECK_TYPE_IN_DATABASE(m_database, "wctype_t", CPlusPlusType("unsigned short", CPlusPlusTypeType::Primitive));
    CHECK_TYPE_IN_DATABASE(m_database, "errno_t", CPlusPlusType("int", CPlusPlusTypeType::Primitive));
    CHECK_TYPE_IN_DATABASE(m_database, "__time32_t", CPlusPlusType("long", CPlusPlusTypeType::Primitive));
    CHECK_TYPE_IN_DATABASE(m_database, "__time64_t", CPlusPlusType("unsigned", CPlusPlusTypeType::Primitive));
    CHECK_TYPE_IN_DATABASE(m_database, "time_t", CPlusPlusType("long", CPlusPlusTypeType::Primitive));

    ASSERT_EQ(m_terms.size(), 11);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef unsigned __int64 size_t;\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef __int64 ssize_t;\n", 2);
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef __int64 intptr_t;\n", 3);
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef unsigned __int64 uintptr_t;\n", 4);
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef __int64 ptrdiff_t;\n", 5);
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef unsigned short wint_t;\n", 6);
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef unsigned short wctype_t;\n", 7);
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef int errno_t;\n", 8);
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef long __time32_t;\n", 9);
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef __int64 __time64_t;\n", 10);
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef __time32_t time_t;\n", 11);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, TypeDefWithMultipleTypesTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "class size_t;\n";
    testFile << "typedef long _off_t;\n";
    testFile << "typedef long off32_t;\n";
    testFile << "typedef long long _off64_t;\n";
    testFile << "typedef long long off64_t;\n";
    testFile << "typedef off64_t off_t;\n";
    testFile << "typedef unsigned long long size_t;\n";
    testFile.close();

    processFile();
    CHECK_TYPE_IN_DATABASE(m_database, "_off_t", CPlusPlusType("long", CPlusPlusTypeType::Primitive));
    CHECK_TYPE_IN_DATABASE(m_database, "off32_t", CPlusPlusType("long", CPlusPlusTypeType::Primitive));
    CHECK_TYPE_IN_DATABASE(m_database, "_off64_t", CPlusPlusType("long long", CPlusPlusTypeType::Primitive));
    CHECK_TYPE_IN_DATABASE(m_database, "off64_t", CPlusPlusType("long long", CPlusPlusTypeType::Primitive));
    CHECK_TYPE_IN_DATABASE(m_database, "off_t", CPlusPlusType("long long", CPlusPlusTypeType::Primitive));
    CHECK_TYPE_IN_DATABASE(m_database, "size_t", CPlusPlusType("unsigned long long", CPlusPlusTypeType::Primitive));

    ASSERT_EQ(m_terms.size(), 7);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "class size_t;\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef long _off_t;\n", 2);
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef long off32_t;\n", 3);
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef long long _off64_t;\n", 4);
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef long long off64_t;\n", 5);
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef off64_t off_t;\n", 6);
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef unsigned long long size_t;\n", 7);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, TypeDefTypePointersAreUsed)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "typedef int MyIntType;\n";
    testFile << "MyIntType* myInt;\n";
    testFile.close();

    processFile();
    CHECK_TYPE_IN_DATABASE(m_database, "MyIntType", CPlusPlusType("int", CPlusPlusTypeType::Primitive));

    ASSERT_TRUE(m_database.isType("MyIntType"));
    ASSERT_EQ(m_terms.size(), 2);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef int MyIntType;\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "MyIntType* myInt;\n", 2);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, ClassTypePointerIsUsed)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "class myType;\n";
    testFile << "myType* classPointer;\n";
    testFile.close();

    processFile();
    EXPECT_TRUE(m_database.isClass("myType"));

    ASSERT_EQ(m_terms.size(), 2);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "class myType;\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "myType* classPointer;\n", 2);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}


TEST_F(ModuleTest, ConstPointerIsUsedForNewType)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "const int* intPointer1;\n";
    testFile << "int const* intPointer2;\n";
    testFile << "int* const intPointer3;\n";
    testFile.close();

    processFile();

    ASSERT_EQ(m_terms.size(), 3);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "const int* intPointer1;\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "int const* intPointer2;\n", 2);
    CHECK_TERM(it, TermType::ProcessedTerm, "int* const intPointer3;\n", 3);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 2);
}

TEST_F(ModuleTest, ConstReferenceIsUsedForNewType)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "const int& intReference1;\n";
    testFile << "int const& intReference2;\n";
    testFile << "int& const intReference3;\n";
    testFile.close();

    processFile();

    ASSERT_EQ(m_terms.size(), 3);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "const int& intReference1;\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "int const& intReference2;\n", 2);
    CHECK_TERM(it, TermType::ProcessedTerm, "int& const intReference3;\n", 3);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 2);
}

TEST_F(ModuleTest, CStyleStructTypedefs)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "struct threadlocaleinfostruct;\n";
    testFile << "struct threadmbcinfostruct;\n";
    testFile << "typedef struct threadlocaleinfostruct *pthreadlocinfo;\n";
    testFile << "typedef struct threadmbcinfostruct *pthreadmbcinfo;\n";
    testFile << "typedef struct threadlocaleinfostruct\n";
    testFile << "{\n";
    testFile << "}\n";
    testFile << "threadlocinfo;\n";
    testFile.close();

    processFile();
    EXPECT_TRUE(m_database.isClass("struct threadlocaleinfostruct"));
    EXPECT_TRUE(m_database.isClass("struct threadmbcinfostruct"));
    CPlusPlusType type1("struct threadlocaleinfostruct", CPlusPlusTypeType::Class);
    type1.incrementPointerCount();
    CPlusPlusType type2("struct threadmbcinfostruct", CPlusPlusTypeType::Class);
    type2.incrementPointerCount();
    CPlusPlusType type3("struct threadlocaleinfostruct", CPlusPlusTypeType::Class);
    CHECK_TYPE_IN_DATABASE(m_database, "pthreadlocinfo", type1);
    CHECK_TYPE_IN_DATABASE(m_database, "pthreadmbcinfo", type2);
    CHECK_TYPE_IN_DATABASE(m_database, "threadlocinfo", type3);

    ASSERT_EQ(m_terms.size(), 5);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "struct threadlocaleinfostruct;\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "struct threadmbcinfostruct;\n", 2);
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef struct threadlocaleinfostruct *pthreadlocinfo;\n", 3);
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef struct threadmbcinfostruct *pthreadmbcinfo;\n", 4);
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef struct threadlocaleinfostruct\n{\n}\nthreadlocinfo;\n", 5);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, CStyleStructWithBracesTypedefs)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "typedef struct tagLC_ID\n";
    testFile << "{\n";
    testFile << "unsigned short wLanguage;\n";
    testFile << "unsigned short wCountry;\n";
    testFile << "unsigned short wCodePage;\n";
    testFile << "}\n";
    testFile << "LC_ID,*LPLC_ID;\n";
    testFile.close();

    processFile();
    EXPECT_TRUE(m_database.isClass("struct tagLC_ID"));
    EXPECT_TRUE(m_database.isVariable("struct tagLC_ID::wLanguage"));
    EXPECT_TRUE(m_database.isVariable("struct tagLC_ID::wCountry"));
    EXPECT_TRUE(m_database.isVariable("struct tagLC_ID::wCodePage"));
    CPlusPlusType type1("struct tagLC_ID", CPlusPlusTypeType::Class);
    CPlusPlusType type2("struct tagLC_ID", CPlusPlusTypeType::Class);
    type2.incrementPointerCount();
    CHECK_TYPE_IN_DATABASE(m_database, "LC_ID", type1);
    CHECK_TYPE_IN_DATABASE(m_database, "LPLC_ID", type2);

    ASSERT_EQ(m_terms.size(), 1);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef struct tagLC_ID\n{\nunsigned short wLanguage;\nunsigned short wCountry;\nunsigned short wCodePage;\n}\nLC_ID,*LPLC_ID;\n", 1);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, TypesAreRecognizedAfterMacro)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "typedef unsigned int size_t;\n";
    testFile << "#endif\n";
    testFile << "#endif\n";
    testFile << "size_t _fread_nolock_s(void* _DstBuf, size_t _DstSize, size_t _ElementSize, size_t _Count);\n";
    testFile.close();

    processFile();
    CHECK_TYPE_IN_DATABASE(m_database, "size_t", CPlusPlusType("unsigned int", CPlusPlusTypeType::Primitive));

    ASSERT_EQ(m_terms.size(), 4);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "typedef unsigned int size_t;\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "#endif\n", 2);
    CHECK_TERM(it, TermType::ProcessedTerm, "#endif\n", 3);
    CHECK_TERM(it, TermType::ProcessedTerm, "size_t _fread_nolock_s(void* _DstBuf, size_t _DstSize, size_t _ElementSize, size_t _Count);\n", 4);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

//check database for type
//edit type database how?
