cmake_minimum_required(VERSION 3.16)
project(SailIt C CXX)

set(TEST_MODE "ON")
#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
#Assign Flags
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)

#Assign Definitions
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Include gtest, this needs APRG Directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

#Include AprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

set(CODE_SOURCES
    src/SailIt.cpp
    src/SailIt.hpp
    src/CPlusPlus/Analyzer/Analyzers/Classes.cpp
    src/CPlusPlus/Analyzer/Analyzers/ControlStructures.cpp
    src/CPlusPlus/Analyzer/Analyzers/Expressions.cpp
    src/CPlusPlus/Analyzer/Analyzers/Functions.cpp
    src/CPlusPlus/Analyzer/Analyzers/Macros.cpp
    src/CPlusPlus/Analyzer/Analyzers/Namespaces.cpp
    src/CPlusPlus/Analyzer/Analyzers/SharedSimplifiers.cpp
    src/CPlusPlus/Analyzer/Analyzers/Statements.cpp
    src/CPlusPlus/Analyzer/Findings/FindingHelpers.cpp
    src/CPlusPlus/Analyzer/Findings/FindingsBuffer.cpp
    src/CPlusPlus/Analyzer/Findings/FindingsBuffer.hpp
    src/CPlusPlus/Analyzer/Findings/FindingsToAdd.hpp
    src/CPlusPlus/Analyzer/Findings/FindingsToAddHelper.cpp
    src/CPlusPlus/Analyzer/Findings/FindingsToAddHelper.hpp
    src/CPlusPlus/Analyzer/Findings/TemporaryFindings.cpp
    src/CPlusPlus/Analyzer/Findings/TemporaryFindings.hpp
    src/CPlusPlus/Analyzer/Loopers/Looper.cpp
    src/CPlusPlus/Analyzer/Loopers/Looper.hpp
    src/CPlusPlus/Analyzer/Modifiers/Modifiers.cpp
    src/CPlusPlus/Analyzer/TermAnalyzer.cpp
    src/CPlusPlus/Analyzer/TermAnalyzer.hpp
    src/CPlusPlus/Analyzer/TermAnalyzerTemplateFunctions.hpp
    src/CPlusPlus/Builder/TermBuilder.cpp
    src/CPlusPlus/Builder/TermBuilder.hpp
    src/CPlusPlus/Database/CPlusPlusClass/CPlusPlusClass.cpp
    src/CPlusPlus/Database/CPlusPlusClass/CPlusPlusClass.hpp
    src/CPlusPlus/Database/CPlusPlusFunction/CPlusPlusFunction.cpp
    src/CPlusPlus/Database/CPlusPlusFunction/CPlusPlusFunction.hpp
    src/CPlusPlus/Database/CPlusPlusFunction/CPlusPlusFunctionParameter.cpp
    src/CPlusPlus/Database/CPlusPlusFunction/CPlusPlusFunctionParameter.hpp
    src/CPlusPlus/Database/CPlusPlusFunction/CPlusPlusFunctionSignature.cpp
    src/CPlusPlus/Database/CPlusPlusFunction/CPlusPlusFunctionSignature.hpp
    src/CPlusPlus/Database/CPlusPlusDatabase.cpp
    src/CPlusPlus/Database/CPlusPlusDatabase.hpp
    src/CPlusPlus/Database/CPlusPlusMacro.cpp
    src/CPlusPlus/Database/CPlusPlusMacro.hpp
    src/CPlusPlus/Database/CPlusPlusNamespace.cpp
    src/CPlusPlus/Database/CPlusPlusNamespace.hpp
    src/CPlusPlus/Database/CPlusPlusScope.cpp
    src/CPlusPlus/Database/CPlusPlusScope.hpp
    src/CPlusPlus/Database/CPlusPlusType.cpp
    src/CPlusPlus/Database/CPlusPlusType.hpp
    src/CPlusPlus/Database/CPlusPlusVariable.cpp
    src/CPlusPlus/Database/CPlusPlusVariable.hpp
    src/CPlusPlus/Findings/Finding.hpp
    src/CPlusPlus/Findings/Findings.cpp
    src/CPlusPlus/Findings/Findings.hpp
    src/CPlusPlus/Term/CheckerHelpers.cpp
    src/CPlusPlus/Term/CheckerHelpers.hpp
    src/CPlusPlus/Term/MultipleTerms.cpp
    src/CPlusPlus/Term/MultipleTerms.hpp
    src/CPlusPlus/Term/Term.cpp
    src/CPlusPlus/Term/Term.hpp
    src/CPlusPlus/Term/TermChecker.cpp
    src/CPlusPlus/Term/TermChecker.hpp
    src/CPlusPlus/Translator/TermListConstants.hpp
    src/CPlusPlus/Translator/TermTranslator.cpp
    src/CPlusPlus/Translator/TermTranslator.hpp
    src/CPlusPlus/Reminders.cpp
    src/CPlusPlus/Utilities.cpp
    src/CPlusPlus/Utilities.hpp
    src/FileDirectoryDatabase/CMake/CMakeDatabase.cpp
    src/FileDirectoryDatabase/CMake/CMakeDatabase.hpp
    src/FileDirectoryDatabase/CMake/CMakeReader.cpp
    src/FileDirectoryDatabase/CMake/CMakeReader.hpp
    src/FileDirectoryDatabase/DatabaseTypes.hpp
    src/FileDirectoryDatabase/FileDirectoryDatabase.cpp
    src/FileDirectoryDatabase/FileDirectoryDatabase.hpp
)

set(TEST_SOURCES
    tst/Checkers.hpp
    tst/CPlusPlus/CPlusPlusDatabase_unit.cpp
    tst/CPlusPlus/TermAnalyzer_unit.cpp
    tst/CPlusPlus/TermTranslator_unit.cpp
    tst/FileDirectoryDatabase/CMake/CMakeDatabase_unit.cpp
    tst/FileDirectoryDatabase/CMake/CMakeReader_unit.cpp
    tst/FileDirectoryDatabase/FileDirectoryDatabase_unit.cpp
    tst/MtDirectoryConstants.hpp
    tst/MT/fixtures/ModuleTest.cpp
    tst/MT/fixtures/ModuleTest.hpp
    tst/MT/ClassTests.cpp
    tst/MT/ControlStructuresTests.cpp
    tst/MT/CPPStyleModuleTests.cpp
    tst/MT/CStyleModuleTests.cpp
    tst/MT/FunctionTests.cpp
    tst/MT/MacroTests.cpp
    tst/MT/NamespaceTests.cpp
    tst/MT/TypeTests.cpp
    tst/SCT/SCT.cpp
)

set(MAIN_SOURCES
    main.cpp
)

set(PROJECT_NAME_SCT ${PROJECT_NAME}_TEST)

if (TEST_MODE)
    add_executable(${PROJECT_NAME_SCT} ${CODE_SOURCES} ${TEST_SOURCES})
    include_directories(src ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME_SCT} gtest APRG_COMMON ${CMAKE_THREAD_LIBS_INIT})
    add_test(${PROJECT_NAME_SCT} ${PROJECT_NAME_SCT})
else()
    add_executable(${PROJECT_NAME} ${CODE_SOURCES} ${MAIN_SOURCES})
    target_link_libraries(${PROJECT_NAME} APRG_COMMON)
endif()




