#include "../../src/CPlusPlus/Database/CPlusPlusDatabase.hpp"
#include "gtest/gtest.h"

using namespace codeReview;
using namespace std;

TEST(CPlusPlusDatabaseTest, CheckAdders) {
    CPlusPlusDatabase database;

    database.addFunction("function1");
    database.addFunction("function2");
    database.addFunction("function3");
    ASSERT_GE(database.getFunctionsReference().size(), 3);
    EXPECT_TRUE(database.isFunction("function1"));
    EXPECT_TRUE(database.isFunction("function2"));
    EXPECT_TRUE(database.isFunction("function3"));

    database.addIncludeFile("file1");
    database.addIncludeFile("file2");
    database.addIncludeFile("file3");
    database.addIncludeFile("file4");
    IncludeFiles& includeFiles = database.getIncludeFilesReference();
    ASSERT_EQ(includeFiles.size(), 4);
    auto it2 = includeFiles.begin();
    EXPECT_EQ(*(it2++), "file1");
    EXPECT_EQ(*(it2++), "file2");
    EXPECT_EQ(*(it2++), "file3");
    EXPECT_EQ(*(it2++), "file4");

    database.addVariable("variable1", CPlusPlusType());
    database.addVariable("variable2", CPlusPlusType());
    database.addVariable("variable3", CPlusPlusType());
    Variables& variables = database.getVariablesReference();
    ASSERT_EQ(variables.size(), 3);
    auto it3 = variables.begin();
    EXPECT_EQ((*it3++).first, "variable1");
    EXPECT_EQ((*it3++).first, "variable2");
    EXPECT_EQ((*it3++).first, "variable3");
}

TEST(CPlusPlusDatabaseTest, CheckFunctions) {
    CPlusPlusDatabase database;

    EXPECT_FALSE(database.isFunction("function1"));
    EXPECT_FALSE(database.isFunction("function2"));
    EXPECT_FALSE(database.isFunction("function3"));
    database.addFunction("function1");
    database.addFunction("function2");
    database.addFunction("function3");
    EXPECT_TRUE(database.isFunction("function1"));
    EXPECT_TRUE(database.isFunction("function2"));
    EXPECT_TRUE(database.isFunction("function3"));
}

TEST(CPlusPlusDatabaseTest, CheckVariable) {
    CPlusPlusDatabase database;

    EXPECT_FALSE(database.isVariable("variable1"));
    EXPECT_FALSE(database.isVariable("variable2"));
    EXPECT_FALSE(database.isVariable("variable3"));
    database.addVariable("variable1", CPlusPlusType());
    database.addVariable("variable2", CPlusPlusType());
    database.addVariable("variable3", CPlusPlusType());
    EXPECT_TRUE(database.isVariable("variable1"));
    EXPECT_TRUE(database.isVariable("variable2"));
    EXPECT_TRUE(database.isVariable("variable3"));
}

TEST(CPlusPlusDatabaseTest, CheckMacro) {
    CPlusPlusDatabase database;

    EXPECT_FALSE(database.isMacro("MACRO1"));
    EXPECT_FALSE(database.isMacro("MACRO2"));
    EXPECT_FALSE(database.isMacro("MACRO3"));
    database.addMacro("MACRO1");
    database.addMacro("MACRO2");
    database.addMacro("MACRO3");
    EXPECT_TRUE(database.isMacro("MACRO1"));
    EXPECT_TRUE(database.isMacro("MACRO2"));
    EXPECT_TRUE(database.isMacro("MACRO3"));
    database.removeMacro("MACRO1");
    database.removeMacro("MACRO2");
    database.removeMacro("MACRO3");
    EXPECT_FALSE(database.isMacro("MACRO1"));
    EXPECT_FALSE(database.isMacro("MACRO2"));
    EXPECT_FALSE(database.isMacro("MACRO3"));
}

TEST(CPlusPlusDatabaseTest, CheckTypeDef) {
    CPlusPlusDatabase database;

    EXPECT_FALSE(database.isType("typeDef1"));
    EXPECT_FALSE(database.isType("typeDef2"));
    EXPECT_FALSE(database.isType("typeDef3"));
    database.addType("typeDef1", CPlusPlusType("int", CPlusPlusTypeType::Primitive));
    database.addType("typeDef2", CPlusPlusType("double", CPlusPlusTypeType::Primitive));
    database.addType("typeDef3", CPlusPlusType("vector", CPlusPlusTypeType::Class));
    EXPECT_TRUE(database.isType("typeDef1"));
    EXPECT_TRUE(database.isType("typeDef2"));
    EXPECT_TRUE(database.isType("typeDef3"));
}

TEST(CPlusPlusDatabaseTest, CheckEnterExitScope) {
    CPlusPlusDatabase database;

    database.performInNewScope([&]() {
        database.addFunction("function1");
        database.addVariable("variable1", CPlusPlusType());
        database.performInNewScope([&]() {
            database.addFunction("function2");
            database.addVariable("variable2", CPlusPlusType());
            database.performInNewScope([&]() {
                database.addFunction("function3");
                database.addVariable("variable3", CPlusPlusType());
                EXPECT_TRUE(database.isFunction("function1"));
                EXPECT_TRUE(database.isFunction("function2"));
                EXPECT_TRUE(database.isFunction("function3"));
                EXPECT_TRUE(database.isVariable("variable1"));
                EXPECT_TRUE(database.isVariable("variable2"));
                EXPECT_TRUE(database.isVariable("variable3"));
            });
            EXPECT_TRUE(database.isFunction("function1"));
            EXPECT_TRUE(database.isFunction("function2"));
            EXPECT_FALSE(database.isFunction("function3"));
            EXPECT_TRUE(database.isVariable("variable1"));
            EXPECT_TRUE(database.isVariable("variable2"));
            EXPECT_FALSE(database.isVariable("variable3"));
        });
        EXPECT_TRUE(database.isFunction("function1"));
        EXPECT_FALSE(database.isFunction("function2"));
        EXPECT_FALSE(database.isFunction("function3"));
        EXPECT_TRUE(database.isVariable("variable1"));
        EXPECT_FALSE(database.isVariable("variable2"));
        EXPECT_FALSE(database.isVariable("variable3"));
    });

    EXPECT_FALSE(database.isFunction("function1"));
    EXPECT_FALSE(database.isFunction("function2"));
    EXPECT_FALSE(database.isFunction("function3"));
    EXPECT_FALSE(database.isVariable("variable1"));
    EXPECT_FALSE(database.isVariable("variable2"));
    EXPECT_FALSE(database.isVariable("variable3"));
}

TEST(CPlusPlusDatabaseTest, CheckEnterExitClass) {
    CPlusPlusDatabase database;

    database.performInClass("Class1", [&]() {
        database.addFunction("function1");
        database.addVariable("variable1", CPlusPlusType());
        database.performInClass("Class2", [&]() {
            database.addFunction("function2");
            database.addVariable("variable2", CPlusPlusType());
            database.performInClass("Class3", [&]() {
                database.addFunction("function3");
                database.addVariable("variable3", CPlusPlusType());
                EXPECT_TRUE(database.isFunction("Class1::function1"));
                EXPECT_TRUE(database.isFunction("Class1::Class2::function2"));
                EXPECT_TRUE(database.isFunction("Class1::Class2::Class3::function3"));
                EXPECT_TRUE(database.isVariable("Class1::variable1"));
                EXPECT_TRUE(database.isVariable("Class1::Class2::variable2"));
                EXPECT_TRUE(database.isVariable("Class1::Class2::Class3::variable3"));
                EXPECT_TRUE(database.isClass("Class1"));
                EXPECT_TRUE(database.isClass("Class1::Class2"));
                EXPECT_TRUE(database.isClass("Class1::Class2::Class3"));
            });
            EXPECT_TRUE(database.isFunction("Class1::function1"));
            EXPECT_TRUE(database.isFunction("Class1::Class2::function2"));
            EXPECT_TRUE(database.isFunction("Class1::Class2::Class3::function3"));
            EXPECT_TRUE(database.isVariable("Class1::variable1"));
            EXPECT_TRUE(database.isVariable("Class1::Class2::variable2"));
            EXPECT_TRUE(database.isVariable("Class1::Class2::Class3::variable3"));
            EXPECT_TRUE(database.isClass("Class1"));
            EXPECT_TRUE(database.isClass("Class1::Class2"));
            EXPECT_TRUE(database.isClass("Class1::Class2::Class3"));
        });
        EXPECT_TRUE(database.isFunction("Class1::function1"));
        EXPECT_TRUE(database.isFunction("Class1::Class2::function2"));
        EXPECT_TRUE(database.isFunction("Class1::Class2::Class3::function3"));
        EXPECT_TRUE(database.isVariable("Class1::variable1"));
        EXPECT_TRUE(database.isVariable("Class1::Class2::variable2"));
        EXPECT_TRUE(database.isVariable("Class1::Class2::Class3::variable3"));
        EXPECT_TRUE(database.isClass("Class1"));
        EXPECT_TRUE(database.isClass("Class1::Class2"));
        EXPECT_TRUE(database.isClass("Class1::Class2::Class3"));
    });
    EXPECT_TRUE(database.isFunction("Class1::function1"));
    EXPECT_TRUE(database.isFunction("Class1::Class2::function2"));
    EXPECT_TRUE(database.isFunction("Class1::Class2::Class3::function3"));
    EXPECT_TRUE(database.isVariable("Class1::variable1"));
    EXPECT_TRUE(database.isVariable("Class1::Class2::variable2"));
    EXPECT_TRUE(database.isVariable("Class1::Class2::Class3::variable3"));
    EXPECT_TRUE(database.isClass("Class1"));
    EXPECT_TRUE(database.isClass("Class1::Class2"));
    EXPECT_TRUE(database.isClass("Class1::Class2::Class3"));
}

TEST(CPlusPlusDatabaseTest, CheckEnterExitNamespace) {
    CPlusPlusDatabase database;

    database.performInNamespace("Namespace1", [&]() {
        database.addFunction("function1");
        database.addVariable("variable1", CPlusPlusType());
        database.performInNamespace("Namespace2", [&]() {
            database.addFunction("function2");
            database.addVariable("variable2", CPlusPlusType());
            database.performInNamespace("Namespace3", [&]() {
                database.addFunction("function3");
                database.addVariable("variable3", CPlusPlusType());
                EXPECT_TRUE(database.isFunction("Namespace1::function1"));
                EXPECT_TRUE(database.isFunction("Namespace1::Namespace2::function2"));
                EXPECT_TRUE(database.isFunction("Namespace1::Namespace2::Namespace3::function3"));
                EXPECT_TRUE(database.isVariable("Namespace1::variable1"));
                EXPECT_TRUE(database.isVariable("Namespace1::Namespace2::variable2"));
                EXPECT_TRUE(database.isVariable("Namespace1::Namespace2::Namespace3::variable3"));
                EXPECT_TRUE(database.isNamespace("Namespace1"));
                EXPECT_TRUE(database.isNamespace("Namespace1::Namespace2"));
                EXPECT_TRUE(database.isNamespace("Namespace1::Namespace2::Namespace3"));
            });
            EXPECT_TRUE(database.isFunction("Namespace1::function1"));
            EXPECT_TRUE(database.isFunction("Namespace1::Namespace2::function2"));
            EXPECT_TRUE(database.isFunction("Namespace1::Namespace2::Namespace3::function3"));
            EXPECT_TRUE(database.isVariable("Namespace1::variable1"));
            EXPECT_TRUE(database.isVariable("Namespace1::Namespace2::variable2"));
            EXPECT_TRUE(database.isVariable("Namespace1::Namespace2::Namespace3::variable3"));
            EXPECT_TRUE(database.isNamespace("Namespace1"));
            EXPECT_TRUE(database.isNamespace("Namespace1::Namespace2"));
            EXPECT_TRUE(database.isNamespace("Namespace1::Namespace2::Namespace3"));
        });
        EXPECT_TRUE(database.isFunction("Namespace1::function1"));
        EXPECT_TRUE(database.isFunction("Namespace1::Namespace2::function2"));
        EXPECT_TRUE(database.isFunction("Namespace1::Namespace2::Namespace3::function3"));
        EXPECT_TRUE(database.isVariable("Namespace1::variable1"));
        EXPECT_TRUE(database.isVariable("Namespace1::Namespace2::variable2"));
        EXPECT_TRUE(database.isVariable("Namespace1::Namespace2::Namespace3::variable3"));
        EXPECT_TRUE(database.isNamespace("Namespace1"));
        EXPECT_TRUE(database.isNamespace("Namespace1::Namespace2"));
        EXPECT_TRUE(database.isNamespace("Namespace1::Namespace2::Namespace3"));
    });
    EXPECT_TRUE(database.isFunction("Namespace1::function1"));
    EXPECT_TRUE(database.isFunction("Namespace1::Namespace2::function2"));
    EXPECT_TRUE(database.isFunction("Namespace1::Namespace2::Namespace3::function3"));
    EXPECT_TRUE(database.isVariable("Namespace1::variable1"));
    EXPECT_TRUE(database.isVariable("Namespace1::Namespace2::variable2"));
    EXPECT_TRUE(database.isVariable("Namespace1::Namespace2::Namespace3::variable3"));
    EXPECT_TRUE(database.isNamespace("Namespace1"));
    EXPECT_TRUE(database.isNamespace("Namespace1::Namespace2"));
    EXPECT_TRUE(database.isNamespace("Namespace1::Namespace2::Namespace3"));
}

TEST(CPlusPlusDatabaseTest, CheckClassContents) {
    CPlusPlusDatabase database;

    database.performInClass("Class1", [&]() {
        database.addFunction("function1");
        database.addVariable("variable1", CPlusPlusType());
        database.addClass("innerClass1");
        database.addNamespace("namespace1");
    });
    EXPECT_TRUE(database.isFunction("Class1::function1"));
    EXPECT_TRUE(database.isVariable("Class1::variable1"));
    EXPECT_TRUE(database.isClass("Class1::innerClass1"));
    EXPECT_TRUE(database.isNamespace("Class1::namespace1"));
    ASSERT_EQ(database.getClassesReference().size(), 2);
    CPlusPlusClass& cPlusPlusClass = database.getClassReference("Class1");
    VectorOfStrings& variableNames = cPlusPlusClass.getVariableNamesReference();
    VectorOfStrings& functionNames = cPlusPlusClass.getFunctionNamesReference();
    VectorOfStrings& classNames = cPlusPlusClass.getClassNamesReference();
    VectorOfStrings& namespaceNames = cPlusPlusClass.getNamespaceNamesReference();
    ASSERT_EQ(variableNames.size(), 1);
    ASSERT_EQ(functionNames.size(), 1);
    ASSERT_EQ(classNames.size(), 1);
    ASSERT_EQ(namespaceNames.size(), 1);
    EXPECT_TRUE(cPlusPlusClass.isVariable("variable1"));
    EXPECT_TRUE(cPlusPlusClass.isFunction("function1"));
    EXPECT_TRUE(cPlusPlusClass.isClass("innerClass1"));
    EXPECT_TRUE(cPlusPlusClass.isNamespace("namespace1"));
}

TEST(CPlusPlusDatabaseTest, CheckNamespaceContents) {
    CPlusPlusDatabase database;

    database.performInNamespace("Namespace1", [&]() {
        database.addFunction("function1");
        database.addVariable("variable1", CPlusPlusType());
        database.addClass("class1");
        database.addNamespace("innerNamespace1");
    });
    EXPECT_TRUE(database.isFunction("Namespace1::function1"));
    EXPECT_TRUE(database.isVariable("Namespace1::variable1"));
    EXPECT_TRUE(database.isClass("Namespace1::class1"));
    EXPECT_TRUE(database.isNamespace("Namespace1::innerNamespace1"));
    ASSERT_EQ(database.getNamespacesReference().size(), 2);
    CPlusPlusNamespace& cPlusPlusNamespace = database.getNamespaceReference("Namespace1");
    VectorOfStrings& variableNames = cPlusPlusNamespace.getVariableNamesReference();
    VectorOfStrings& functionNames = cPlusPlusNamespace.getFunctionNamesReference();
    VectorOfStrings& classNames = cPlusPlusNamespace.getClassNamesReference();
    VectorOfStrings& namespaceNames = cPlusPlusNamespace.getNamespaceNamesReference();
    ASSERT_EQ(variableNames.size(), 1);
    ASSERT_EQ(functionNames.size(), 1);
    ASSERT_EQ(classNames.size(), 1);
    ASSERT_EQ(namespaceNames.size(), 1);
    EXPECT_TRUE(cPlusPlusNamespace.isVariable("variable1"));
    EXPECT_TRUE(cPlusPlusNamespace.isFunction("function1"));
    EXPECT_TRUE(cPlusPlusNamespace.isClass("class1"));
    EXPECT_TRUE(cPlusPlusNamespace.isNamespace("innerNamespace1"));
}

TEST(CPlusPlusDatabaseTest, CheckNamespaceAliasIsFound) {
    CPlusPlusDatabase database;

    database.performInNamespace("Namespace1", [&]() {
        database.addFunction("function1");
        database.addVariable("variable1", CPlusPlusType());
        database.addClass("class1");
        database.addNamespace("innerNamespace1");
    });

    database.performInNamespace("Namespace1", [&]() {
        EXPECT_TRUE(database.isFunctionWithAlias("function1"));
        EXPECT_TRUE(database.isVariableWithAlias("variable1"));
        EXPECT_TRUE(database.isClassWithAlias("class1"));
        EXPECT_TRUE(database.isNamespaceWithAlias("innerNamespace1"));
    });
}

TEST(CPlusPlusDatabaseTest, CheckClassAliasIsFound) {
    CPlusPlusDatabase database;

    database.performInClass("Class1", [&]() {
        database.addFunction("function1");
        database.addVariable("variable1", CPlusPlusType());
        database.addClass("innerClass1");
        database.addNamespace("namespace1");
    });

    database.performInClass("Class1", [&]() {
        EXPECT_TRUE(database.isFunctionWithAlias("function1"));
        EXPECT_TRUE(database.isVariableWithAlias("variable1"));
        EXPECT_TRUE(database.isClassWithAlias("innerClass1"));
        EXPECT_TRUE(database.isNamespaceWithAlias("namespace1"));
    });
}

TEST(CPlusPlusDatabaseTest, CheckUsingNamespaceAliasIsFound) {
    CPlusPlusDatabase database;

    database.performInNamespace("Namespace1", [&]() {
        database.addFunction("function1");
        database.addVariable("variable1", CPlusPlusType());
        database.addClass("class1");
        database.addNamespace("innerNamespace1");
    });
    database.addUsingNamespace("Namespace1");

    EXPECT_TRUE(database.isFunctionWithAlias("function1"));
    EXPECT_TRUE(database.isVariableWithAlias("variable1"));
    EXPECT_TRUE(database.isClassWithAlias("class1"));
    EXPECT_TRUE(database.isNamespaceWithAlias("innerNamespace1"));
}

TEST(CPlusPlusDatabaseTest, CheckNewScopeInNamespace_AliasesAreFound) {
    CPlusPlusDatabase database;

    database.performInNamespace("Namespace1", [&]() {
        database.addFunction("function1");
        database.addVariable("variable1", CPlusPlusType());
        database.addClass("class1");
        database.addNamespace("innerNamespace1");
        database.performInNewScope([&]() {
            EXPECT_TRUE(database.isFunctionWithAlias("function1"));
            EXPECT_TRUE(database.isVariableWithAlias("variable1"));
            EXPECT_TRUE(database.isClassWithAlias("class1"));
            EXPECT_TRUE(database.isNamespaceWithAlias("innerNamespace1"));
        });
    });
}

TEST(CPlusPlusDatabaseTest, CheckNewScopeInClass_AliasesAreFound) {
    CPlusPlusDatabase database;

    database.performInClass("Class1", [&]() {
        database.addFunction("function1");
        database.addVariable("variable1", CPlusPlusType());
        database.addClass("innerClass1");
        database.addNamespace("namespace1");
        database.performInNewScope([&]() {
            EXPECT_TRUE(database.isFunctionWithAlias("function1"));
            EXPECT_TRUE(database.isVariableWithAlias("variable1"));
            EXPECT_TRUE(database.isClassWithAlias("innerClass1"));
            EXPECT_TRUE(database.isNamespaceWithAlias("namespace1"));
        });
    });
}

void checkThatDatabaseIsEmpty(CPlusPlusDatabase& database) {
    EXPECT_EQ(database.getClassesReference().size(), 0);
    EXPECT_EQ(database.getFunctionsReference().size(), 0);
    EXPECT_EQ(database.getIncludeFilesReference().size(), 0);
    EXPECT_EQ(database.getMacrosReference().size(), 0);
    EXPECT_EQ(database.getNamespacesReference().size(), 0);
    EXPECT_EQ(database.getTypesReference().size(), 0);
    EXPECT_EQ(database.getUsingNamespacesReference().size(), 0);
    EXPECT_EQ(database.getVariablesReference().size(), 0);
}
