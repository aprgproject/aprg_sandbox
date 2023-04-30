/*#include <Common/Debug/AlbaTypeDisplayerInCompilation.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {

namespace {

// Its a bad idea to initialize dependent variable like this in an anonymous namespace.
// But this is just for debug test for compilation failure (not a regression test) so lets give it a pass.

int lValue = 0xA1BA;
int const lValueConst = 0xA1BA;
int& lValueReference = lValue;
int const& lValueConstReference = lValueConst;
#define R_VALUE 0xA1BA  // This will does not work: [int&& rValue=0xA1BA;].
// A named variable will never be considered to be an rvalue even if it is declared as such.

int* intPointer = &lValue;
int const* intConstPointer = &lValue;
int* const intPointerConst = &lValue;
int const* const intConstPointerConst = &lValue;
}  // namespace

// This test cases are commentted out because it causes compilation failure

TEST(AlbaTypeDisplayerInCompilationTest, DisplayTypeInTemplateByValueWorks) {
    displayTypeInTemplateByValue(lValue);                // TypeInTemplate is [int] and ParameterType is [int]
    displayTypeInTemplateByValue(lValueConst);           // TypeInTemplate is [int] and ParameterType is [int]
    displayTypeInTemplateByValue(lValueReference);       // TypeInTemplate is [int] and ParameterType is [int]
    displayTypeInTemplateByValue(lValueConstReference);  // TypeInTemplate is [int] and ParameterType is [int]
    displayTypeInTemplateByValue(R_VALUE);               // TypeInTemplate is [int] and ParameterType is [int]
    displayTypeInTemplateByValue(intPointer);            // TypeInTemplate is [int*] and ParameterType is [int*]
    displayTypeInTemplateByValue(intConstPointer);  // TypeInTemplate is [const int*] and ParameterType is [const int*]
    displayTypeInTemplateByValue(intPointerConst);  // TypeInTemplate is [int*] and ParameterType is [int*]
    displayTypeInTemplateByValue(
        intConstPointerConst);  // TypeInTemplate is [const int*] and ParameterType is [const int*]
}

TEST(AlbaTypeDisplayerInCompilationTest, DisplayTypeInTemplateByReferenceWorks) {
    displayTypeInTemplateByReference(lValue);       // TypeInTemplate is [int] and ParameterType is [int &]
    displayTypeInTemplateByReference(lValueConst);  // TypeInTemplate is [const int] and ParameterType is [const int&]
    displayTypeInTemplateByReference(lValueReference);  // TypeInTemplate is [int] and ParameterType is [int &]
    displayTypeInTemplateByReference(
        lValueConstReference);  // TypeInTemplate is [const int] and ParameterType is [const int & ]
    // displayTypeInTemplateByReference(R_VALUE);  // compilation failure
}

TEST(AlbaTypeDisplayerInCompilationTest, DisplayTypeInTemplateByConstReferenceWorks) {
    displayTypeInTemplateByConstReference(lValue);       // TypeInTemplate is [int] and ParameterType is [const int&]
    displayTypeInTemplateByConstReference(lValueConst);  // TypeInTemplate is [int] and ParameterType is [const int&]
    displayTypeInTemplateByConstReference(
        lValueReference);  // TypeInTemplate is [int] and ParameterType is [const int&]
    displayTypeInTemplateByConstReference(
        lValueConstReference);                       // TypeInTemplate is [int] and ParameterType is [const int &]
    displayTypeInTemplateByConstReference(R_VALUE);  // TypeInTemplate is [int] and ParameterType is [const int&]
}

TEST(AlbaTypeDisplayerInCompilationTest, DisplayTypeInTemplateByUniversalReferenceWorks) {
    displayTypeInTemplateByUniversalReference(lValue);  // TypeInTemplate is [int &] and ParameterType is [int &]
    displayTypeInTemplateByUniversalReference(
        lValueConst);  // TypeInTemplate is [const int&] and ParameterType is[const int & ]
    displayTypeInTemplateByUniversalReference(
        lValueReference);  // TypeInTemplate is [int &] and ParameterType is [int &]
    displayTypeInTemplateByUniversalReference(
        lValueConstReference);  // TypeInTemplate is [const int&] and ParameterType is[const int &]
    displayTypeInTemplateByUniversalReference(R_VALUE);  // TypeInTemplate is [int] and ParameterType is [int&&]
}

TEST(AlbaTypeDisplayerInCompilationTest, DisplayTypeInTemplateByPointerWorks) {
    displayTypeInTemplateByPointer(intPointer);       // TypeInTemplate is [int] and ParameterType is [int*]
    displayTypeInTemplateByPointer(intConstPointer);  // TypeInTemplate is [const int] and ParameterType is [const int*]
    displayTypeInTemplateByPointer(intPointerConst);  // TypeInTemplate is [int] and ParameterType is [int*]
    displayTypeInTemplateByPointer(
        intConstPointerConst);  // TypeInTemplate is [const int] and ParameterType is [const int*]
}

TEST(AlbaTypeDisplayerInCompilationTest, DisplayThisTypeWorksUsingAutoByValue) {
    auto autoWithLValue = lValue;
    auto autoWithLValueConst = lValueConst;
    auto autoWithLValueReference = lValueReference;    auto autoWithLValueConstReference = lValueConstReference;
    auto autoWithRValue = R_VALUE;
    auto autoWithIntPointer = intPointer;
    auto autoWithIntConstPointer = intConstPointer;
    auto autoWithIntPointerConst = intPointerConst;
    auto autoWithIntConstPointerConst = intConstPointerConst;

    DisplayThisType<decltype(autoWithLValue)> autoWithLValueToCheck;                    // ParameterType is [int]
    DisplayThisType<decltype(autoWithLValueConst)> autoWithLValueConstToCheck;          // ParameterType is [int]
    DisplayThisType<decltype(autoWithLValueReference)> autoWithLValueReferenceToCheck;  // ParameterType is [int]
    DisplayThisType<decltype(autoWithLValueConstReference)>
        autoWithLValueConstReferenceToCheck;                                            // ParameterType is [int]
    DisplayThisType<decltype(autoWithRValue)> autoWithRValueToCheck;                    // ParameterType is [int]
    DisplayThisType<decltype(autoWithIntPointer)> autoWithIntPointerToCheck;            // ParameterType is [int*]
    DisplayThisType<decltype(autoWithIntConstPointer)> autoWithIntConstPointerToCheck;  // ParameterType is [const int*]
    DisplayThisType<decltype(autoWithIntPointerConst)> autoWithIntPointerConstToCheck;  // ParameterType is [int*]
    DisplayThisType<decltype(autoWithIntConstPointerConst)>
        autoWithIntConstPointerConstToCheck;  // ParameterType is [const int *]
}

TEST(AlbaTypeDisplayerInCompilationTest, DisplayThisTypeWorksUsingAutoByReference) {
    auto& autoWithLValue = lValue;
    auto& autoWithLValueConst = lValueConst;
    auto& autoWithLValueReference = lValueReference;
    auto& autoWithLValueConstReference = lValueConstReference;
    auto& autoWithRValue = R_VALUE;

    DisplayThisType<decltype(autoWithLValue)> autoWithLValueToCheck;                    // ParameterType is [int&]
    DisplayThisType<decltype(autoWithLValueConst)> autoWithLValueConstToCheck;          // ParameterType is [const int&]
    DisplayThisType<decltype(autoWithLValueReference)> autoWithLValueReferenceToCheck;  // ParameterType is [int&]
    DisplayThisType<decltype(autoWithLValueConstReference)>
        autoWithLValueConstReferenceToCheck;                          // ParameterType is [const int & ]
    DisplayThisType<decltype(autoWithRValue)> autoWithRValueToCheck;  // ParameterType is [int&]
}

TEST(AlbaTypeDisplayerInCompilationTest, DisplayThisTypeWorksUsingAutoByConstReference) {
    auto const& autoWithLValue = lValue;
    auto const& autoWithLValueConst = lValueConst;
    auto const& autoWithLValueReference = lValueReference;
    auto const& autoWithLValueConstReference = lValueConstReference;
    auto const& autoWithRValue = R_VALUE;

    DisplayThisType<decltype(autoWithLValue)> autoWithLValueToCheck;                    // ParameterType is [const int&]
    DisplayThisType<decltype(autoWithLValueConst)> autoWithLValueConstToCheck;          // ParameterType is [const int&]
    DisplayThisType<decltype(autoWithLValueReference)> autoWithLValueReferenceToCheck;  // ParameterType is [const int&]
    DisplayThisType<decltype(autoWithLValueConstReference)>
        autoWithLValueConstReferenceToCheck;                          // ParameterType is [const int & ]
    DisplayThisType<decltype(autoWithRValue)> autoWithRValueToCheck;  // ParameterType is [const int&]
}

TEST(AlbaTypeDisplayerInCompilationTest, DisplayThisTypeWorksUsingAutoByUniversalReference) {
    auto&& autoWithLValue = lValue;
    auto&& autoWithLValueConst = lValueConst;
    auto&& autoWithLValueReference = lValueReference;
    auto&& autoWithLValueConstReference = lValueConstReference;
    auto&& autoWithRValue = R_VALUE;

    DisplayThisType<decltype(autoWithLValue)> autoWithLValueToCheck;                    // ParameterType is [int&]
    DisplayThisType<decltype(autoWithLValueConst)> autoWithLValueConstToCheck;          // ParameterType is [const int&]
    DisplayThisType<decltype(autoWithLValueReference)> autoWithLValueReferenceToCheck;  // ParameterType is [int&]
    DisplayThisType<decltype(autoWithLValueConstReference)>
        autoWithLValueConstReferenceToCheck;                          // ParameterType is [const int & ]
    DisplayThisType<decltype(autoWithRValue)> autoWithRValueToCheck;  // ParameterType is [int&&]
}

TEST(AlbaTypeDisplayerInCompilationTest, DisplayThisTypeWorksUsingAutoByPointer) {
    auto* autoWithIntPointer = intPointer;
    auto* autoWithIntConstPointer = intConstPointer;
    auto* autoWithIntPointerConst = intPointerConst;
    auto* autoWithIntConstPointerConst = intConstPointerConst;

    DisplayThisType<decltype(autoWithIntPointer)> autoWithIntPointerToCheck;            // ParameterType is [int*]
    DisplayThisType<decltype(autoWithIntConstPointer)> autoWithIntConstPointerToCheck;  // ParameterType is [const int*]
    DisplayThisType<decltype(autoWithIntPointerConst)> autoWithIntPointerConstToCheck;  // ParameterType is [int*]
    DisplayThisType<decltype(autoWithIntConstPointerConst)>
        autoWithIntConstPointerConstToCheck;  // ParameterType is [const int *]
}

TEST(AlbaTypeDisplayerInCompilationTest, DisplayThisTypeWorksUsingAutoByValueWithBraceInitializer) {
    auto autoWithOneInitialized{1};
    auto autoWithMultipleInitialized{1, 2, 3, 4};
    auto autoWithOneAssigned = {1};
    auto autoWithMultipleAssigned = {1, 2, 3, 4};

    DisplayThisType<decltype(autoWithOneInitialized)> autoWithOneInitializedToCheck;  // ParameterType is [int]
    DisplayThisType<decltype(autoWithMultipleInitialized)>
        autoWithMultipleInitializedToCheck;  // ParameterType is [std::initializer<int>]
    DisplayThisType<decltype(autoWithOneAssigned)>
        autoWithOneAssignedToCheck;  // ParameterType is [std::initializer<int>]
    DisplayThisType<decltype(autoWithMultipleAssigned)>
        autoWithMultipleAssignedToCheck;  // ParameterType is[std::initializer<int>]
}

TEST(AlbaTypeDisplayerInCompilationTest, DisplayThisTypeWorksUsingDecltypeByName) {
    DisplayThisType<decltype(lValue)> decltypeWithLValueToCheck;                    // ParameterType is [int]
    DisplayThisType<decltype(lValueConst)> decltypeWithLValueConstToCheck;          // ParameterType is [const int]
    DisplayThisType<decltype(lValueReference)> decltypeWithLValueReferenceToCheck;  // ParameterType is [int&]
    DisplayThisType<decltype(lValueConstReference)>
        decltypeWithLValueConstReferenceToCheck;                                    // ParameterType is [const int&]
    DisplayThisType<decltype(R_VALUE)> decltypeWithRValueToCheck;                   // ParameterType is [int]
    DisplayThisType<decltype(intPointer)> decltypeWithIntPointerToCheck;            // ParameterType is [int*]
    DisplayThisType<decltype(intConstPointer)> decltypeWithIntConstPointerToCheck;  // ParameterType is [const int*]
    DisplayThisType<decltype(intPointerConst)> decltypeWithIntPointerConstToCheck;  // ParameterType is [int* const]
    DisplayThisType<decltype(intConstPointerConst)>
        decltypeWithIntConstPointerConstToCheck;  // ParameterType is [const int* const]
}

TEST(AlbaTypeDisplayerInCompilationTest, DisplayThisTypeWorksUsingDecltypeByExpression) {
    DisplayThisType<decltype((lValue))> decltypeWithLValueToCheck;                    // ParameterType is [int&]
    DisplayThisType<decltype((lValueConst))> decltypeWithLValueConstToCheck;          // ParameterType is [const int&]
    DisplayThisType<decltype((lValueReference))> decltypeWithLValueReferenceToCheck;  // ParameterType is [int&]
    DisplayThisType<decltype((lValueConstReference))>
        decltypeWithLValueConstReferenceToCheck;                                      // ParameterType is[const int & ]
    DisplayThisType<decltype((R_VALUE))> decltypeWithRValueToCheck;                   // ParameterType is [int&]
    DisplayThisType<decltype((intPointer))> decltypeWithIntPointerToCheck;            // ParameterType is [int*&]
    DisplayThisType<decltype((intConstPointer))> decltypeWithIntConstPointerToCheck;  // ParameterType is [const int*&]
    DisplayThisType<decltype((intPointerConst))> decltypeWithIntPointerConstToCheck;  // ParameterType is [int* const&]
    DisplayThisType<decltype((intConstPointerConst))>
        decltypeWithIntConstPointerConstToCheck;  // ParameterType is [const int* const & ]
}

TEST(AlbaTypeDisplayerInCompilationTest, DisplayThisTypeWorksUsingDecltypeAuto) {
    decltype(auto) autoWithLValue = lValue;
    decltype(auto) autoWithLValueConst = lValueConst;
    decltype(auto) autoWithLValueReference = lValueReference;    decltype(auto) autoWithLValueConstReference = lValueConstReference;
    decltype(auto) autoWithRValue = R_VALUE;
    decltype(auto) autoWithIntPointer = intPointer;
    decltype(auto) autoWithIntConstPointer = intConstPointer;
    decltype(auto) autoWithIntPointerConst = intPointerConst;
    decltype(auto) autoWithIntConstPointerConst = intConstPointerConst;

    DisplayThisType<decltype(autoWithLValue)> autoWithLValueToCheck;                    // ParameterType is [int]
    DisplayThisType<decltype(autoWithLValueConst)> autoWithLValueConstToCheck;          // ParameterType is [const int]
    DisplayThisType<decltype(autoWithLValueReference)> autoWithLValueReferenceToCheck;  // ParameterType is [int&]
    DisplayThisType<decltype(autoWithLValueConstReference)>
        autoWithLValueConstReferenceToCheck;                                  // ParameterType is [const int &]
    DisplayThisType<decltype(autoWithRValue)> autoWithRValueToCheck;          // ParameterType is [int]
    DisplayThisType<decltype(autoWithIntPointer)> autoWithIntPointerToCheck;  // ParameterType is [int*]
    DisplayThisType<decltype(autoWithIntConstPointer)> autoWithIntConstPointerToCheck;  // ParameterType is [const int*]
    DisplayThisType<decltype(autoWithIntPointerConst)> autoWithIntPointerConstToCheck;  // ParameterType is [int* const]
    DisplayThisType<decltype(autoWithIntConstPointerConst)>
        autoWithIntConstPointerConstToCheck;  // ParameterType is [const int* const]
}

TEST(AlbaTypeDisplayerInCompilationTest, DisplayThisTypeWorksUsingLambdaCaptureByValue) {
    auto lambda = [=]() {
        DisplayThisType<decltype(lValue)> lValueToCheck;                              // ParameterType is [int]
        DisplayThisType<decltype(lValueConst)> lValueConstToCheck;                    // ParameterType is [const int]
        DisplayThisType<decltype(lValueReference)> lValueReferenceToCheck;            // ParameterType is [int&]
        DisplayThisType<decltype(lValueConstReference)> lValueConstReferenceToCheck;  // ParameterType is [const int&]
        DisplayThisType<decltype(R_VALUE)> rValueToCheck;                             // ParameterType is [int]
        DisplayThisType<decltype(intPointer)> intPointerToCheck;                      // ParameterType is [int*]
        DisplayThisType<decltype(intConstPointer)> intConstPointerToCheck;            // ParameterType is [const int*]
        DisplayThisType<decltype(intPointerConst)> intPointerConstToCheck;            // ParameterType is [int* const]
        DisplayThisType<decltype(intConstPointerConst)>
            intConstPointerConstToCheck;  // ParameterType is [const int* const]
    };
}

TEST(AlbaTypeDisplayerInCompilationTest, DisplayThisTypeWorksUsingLambdaCaptureByReference) {
    auto lambda = [&]() {
        DisplayThisType<decltype(lValue)> lValueToCheck;                              // ParameterType is [int]
        DisplayThisType<decltype(lValueConst)> lValueConstToCheck;                    // ParameterType is [const int]
        DisplayThisType<decltype(lValueReference)> lValueReferenceToCheck;            // ParameterType is [int&]
        DisplayThisType<decltype(lValueConstReference)> lValueConstReferenceToCheck;  // ParameterType is [const int&]
        DisplayThisType<decltype(R_VALUE)> rValueToCheck;                             // ParameterType is [int]
        DisplayThisType<decltype(intPointer)> intPointerToCheck;                      // ParameterType is [int*]
        DisplayThisType<decltype(intConstPointer)> intConstPointerToCheck;            // ParameterType is [const int*]
        DisplayThisType<decltype(intPointerConst)> intPointerConstToCheck;            // ParameterType is [int* const]
        DisplayThisType<decltype(intConstPointerConst)>
            intConstPointerConstToCheck;  // ParameterType is [const int* const]
    };
}

TEST(AlbaTypeDisplayerInCompilationTest, DisplayThisTypeWorksUsingLambdaInitCapture) {
    auto lambda = [initializedWithLValue = lValue, initializedWithLValueConst = lValueConst,
                   initializedWithLValueReference = lValueReference,
                   initializedWithLValueConstReference = lValueConstReference, initializedWithRValue = R_VALUE,
                   initializedWithIntPointer = intPointer, initializedWithIntConstPointer = intConstPointer,
                   initializedWithIntPointerConst = intPointerConst,
                   initializedWithIntConstPointerConst = intConstPointerConst]() {
        DisplayThisType<decltype(initializedWithLValue)> lValueToCheck;            // ParameterType is [const int]
        DisplayThisType<decltype(initializedWithLValueConst)> lValueConstToCheck;  // ParameterType is [const int]
        DisplayThisType<decltype(initializedWithLValueReference)>
            lValueReferenceToCheck;  // ParameterType is [const int]
        DisplayThisType<decltype(initializedWithLValueConstReference)>
            lValueConstReferenceToCheck;                                         // ParameterType is [const int]
        DisplayThisType<decltype(initializedWithRValue)> rValueToCheck;          // ParameterType is [const int]
        DisplayThisType<decltype(initializedWithIntPointer)> intPointerToCheck;  // ParameterType is [int* const]
        DisplayThisType<decltype(initializedWithIntConstPointer)>
            intConstPointerToCheck;  // ParameterType is [const int* const]
        DisplayThisType<decltype(initializedWithIntPointerConst)>
            intPointerConstToCheck;  // ParameterType is [int* const]
        DisplayThisType<decltype(initializedWithIntConstPointerConst)>
            intConstPointerConstToCheck;  // ParameterType is [const int* const]
    };
}

#undef R_VALUE

}  // namespace alba
*/