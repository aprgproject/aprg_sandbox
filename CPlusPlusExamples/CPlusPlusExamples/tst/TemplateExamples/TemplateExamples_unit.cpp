#include <Common/Macros/AlbaMacros.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>

#include <gtest/gtest.h>

#include <array>
#include <iostream>
#include <vector>

using namespace alba::typeHelper;
using namespace std;

// Taken from Arthur O'Dwyer's lecture ("Template Normal Programming")

namespace alba {

namespace FunctionTemplatesWork {

template <typename T>
T abs(T x) {
    return (x >= 0) ? x : -x;
}

TEST(TemplateExamplesTest, FunctionTemplatesWork) {
    double (*foo)(double) = abs<double>;  // create a function pointer
    cout << foo(-42.3) << "\n";
    cout << abs<int>(-42) << "\n";
}

// -> Function templates are not functions
// ---> They are templates for making functions
// -> "Dont pay for what you don't use" philosophy
// ---> If nobody calls abs<int>, it won't be instantiated by the compiler at all.
// -> The template abs will not be instantiated with any particular type Foo until you,
// ---> the programmer, explicitly mention abs<Foo> in your program.
// -> As soon as you mentioned abs<Foo>, the compiler will have to go instantiate it,
// ---> in order to fiture out its return and so on.
// -> Sometimes the compiler can deduce abs<Foo> when all you wrote was abs;
// ---> but well talk about that deduction process in the next tests.

}  // namespace FunctionTemplatesWork

namespace ClassTemplatesWork {

template <typename T>
struct mylist {
    T data;
    mylist<T>* next;
};

TEST(TemplateExamplesTest, ClassTemplatesWork) {
    mylist<int> intList{5, nullptr};
    mylist<double> doubleList{4.5, nullptr};
    cout << "intList: " << intList.data << "\n";
    cout << "doubleList: " << doubleList.data << "\n";
}

// -> Class templates are not classes
// ---> They are templates for making classes
// -> "Dont pay for what you don't use" philosophy
// ---> If nobody calls mylist<int>, it won't be instantiated by the compiler at all.
// -> The resulting "template classes" follow all the same rules as normal classes.
// ---> In particular, each static data member must be defined somewhere if you want to use it.
// ---> Templates are similar to inline

}  // namespace ClassTemplatesWork

namespace TemplateIsSimilarToInline {

template <typename T>
struct ST {
    static int intData;
    static T tData;
};

template <typename T>
int ST<T>::intData = 42;  // still fine in header

template <typename T>
T ST<T>::tData = {};  // still fine in header

TEST(TemplateExamplesTest, TemplateIsSimilarToInline) {
    cout << "intData: " << ST<int>::intData << "\n";
    cout << "tData: " << ST<int>::tData << "\n";
}

// -> Templates are similar to inline
// ---> How come I can define ST<T>::intData in a header file and #include it all over the place,
// -----> whereas I get a multiple-definition linker error if I try the same thing with S::intData?
// -> The same C++ Standard wording that governs inline functions and variables
// ---> also governs the definitions of templates and their members. (N4606 3.2 [basic.def.odr])

}  // namespace TemplateIsSimilarToInline

namespace VariableTemplatesWork {

template <typename T>
struct isVoidStruct {
    static constexpr bool value = isVoidType<T>();
};

template <typename T>
constexpr bool isVoidVariable = isVoidType<T>();  // variable template

TEST(TemplateExamplesTest, VariableTemplatesWork) {
    cout << "isVoidStruct with int: " << isVoidStruct<int>::value << "\n";
    cout << "isVoidStruct with void: " << isVoidStruct<void>::value << "\n";
    cout << "isVoidVariable with int: " << isVoidVariable<int> << "\n";
    cout << "isVoidVariable with void: " << isVoidVariable<void> << "\n";
}

// -> In C++14, variable templates was introduced.
// -> Variable templates are syntactic sugar
// ---> A variable template is exactly 100% equivalent to a static data member of class template.
// ---> In the STL, "_v" variations are available as variable templates.

}  // namespace VariableTemplatesWork

namespace AliasTemplatesWork {

template <typename T>
using myvec = vector<T>;  // alias template

TEST(TemplateExamplesTest, AliasTemplatesWork) {
    cout << "is alias same with int: " << areSameTypes<myvec<int>, vector<int>> << "\n";
    cout << "is alias same with double: " << areSameTypes<myvec<double>, vector<double>> << "\n";
}

// -> In C++11, alias templates was introduced.
// -> Alias templates are literally the same type from its source.

}  // namespace AliasTemplatesWork

namespace TemplateTypeDeductionWorksUsingPrettyFunction {

template <typename T>
void foo(T) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}

TEST(TemplateExamplesTest, TemplateTypeDeductionWorksUsingPrettyFunction) {
    foo(4);
    foo(4.2);
    foo("hello");
}

// -> In C++11, alias templates was introduced.
// -> Alias templates are literally the same type from its source.

}  // namespace TemplateTypeDeductionWorksUsingPrettyFunction

namespace TemplateTypeDeductionWorks {

template <typename T, typename U>
void f(T, U) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}

template <typename T>
void g(T, T) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}

template <typename T, typename U>
void foo(array<T, sizeof(U)>, array<U, sizeof(T)>, int) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}

template <typename R, typename A>
void fooFunction(R (*)(A)) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}

TEST(TemplateExamplesTest, TemplateTypeDeductionWorks) {
    f(1, 2);  // [with T = int; U = int]
    g(1, 2);  // [with T = int]
    // g(1, 2U); // Error: no matching function for call to 'g' ('int' vs. 'unsigned int')

    foo(array<int, 8>{}, array<double, 4>{}, 0.0);
    // foo(array<int, 9>{}, array<double, 4>{}, 0.0); // Compilation error
    // Error: no matching function for call to 'foo'
    // Note: candidate template ignored: deduced type 'array<[...], sizeof(double) aka 8>' of 1st parameter
    // does not match adjusted type 'array<[...], 9>' of argument [with T = int, U = double]

    // fooFunction([](double x) { return int(x); }); // Compilation error
    fooFunction(+[](double x) { return int(x); });
    // Captureless lambda types are always implicitly convertible to function pointer type.
    // But being implicitly convertible to a thing doesn't mean actually being that thing!
    // Protip: If you absolute need the function-pointer conversion to happen add a unary+.
}

// -> Type deduction in a nutshell (N4606 14.8.2.1 [temp.deduct.call]):
// ---> Each function parameter may contribute (or not) to the deduction of each template parameter (or not).
// ---> All deductions are carried out "in parallel"; they don't cross talk with each other.
// ---> Finally, the compiler checks to make sure that each template parameter
// -----> has been deduced at least once
// -------> Otherwise: "Couldn't infer template argument T" error
// -----> and that all deductions agree with each other
// -------> Otherwise: "Deduced conflicting types for parameter T" error
// ---> Furthermore, any function parameter that does contribute to deduction
// -----> must match its function argument type exactly.
// -----> No implicit conversions allowed!

}  // namespace TemplateTypeDeductionWorks

namespace CallingTemplateInstanceWithTemplateParametersWorks {

template <typename T, typename U>
void add(T, U) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}

TEST(TemplateExamplesTest, CallingTemplateInstanceWithTemplateParametersWorks) {
    add<int, int>('x', 3.0);  // [with T = int; U = int]
    add<int>('x', 3.0);       // [with T = int; U = double]
    add<>('x', 3.0);          // [with T = char; U = double]
    add('x', 3.0);            // [with T = char; U = double]
}

// -> Type deduction in a nutshell (added this line):
// ---> Any template parameters that were explicitly specified by the caller
// -----> are fixed as whatever the caller said they were
// -----> and they dont participate any further in deduction

}  // namespace CallingTemplateInstanceWithTemplateParametersWorks

namespace TemplateParameterThatCannotBeDeducedFailsWorks {

template <typename T>
void add() {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}

TEST(TemplateExamplesTest, TemplateParameterThatCannotBeDeducedFailsWorks) {
    add<int>();  // compiles
    // add<>(); // Compilation error: couldn't infer template argument 'T'
    // add<>(); // Compilation error: couldn't infer template argument 'T'
}

// -> Type deduction in a nutshell (added this line):
// ---> If any template parameter (that wasn't specified by the caller) couldn't be deduced,
// -----> but has a default value, then it is fixed as its default value.

}  // namespace TemplateParameterThatCannotBeDeducedFailsWorks

namespace TemplateTypeDeductionWithAmpersandsWorks {

template <typename T>
void f(T) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}

template <typename T>
void fWithRef(T&) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}

template <typename T>
void fWithDoubleRef(T&&) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}

TEST(TemplateExamplesTest, TemplateTypeDeductionWithAmpersandsWorks) {
    int i = 3;
    const int ci = 4;

    f(i);                // [with T = int]
    fWithRef(i);         // [with T = int]
    fWithDoubleRef(42);  // [with T = int]
    fWithDoubleRef(i);   // [with T = int&]

    f(ci);               // [with T = int]
    fWithRef(ci);        // [with T = const int]
    fWithDoubleRef(ci);  // [with T = const int&]

    fWithRef(static_cast<int&>(i));  // [with T = int]
    // fWithRef(static_cast<int&&>(i));     // [with T = int] Error: expects an lvalue for 1st argument
    fWithRef(static_cast<const int&>(i));   // [with T = const int]
    fWithRef(static_cast<const int&&>(i));  // [with T = const int&]
}

// -> T&& is a forwarding reference or ("universal reference" by Scott Meyers)
// -> Reference collapsing:
// ---> The rule to remember when dealing with references is that combining two reference types
// -----> mins the number of ampersands between them.
// -------> & + & = &
// -------> & + && = &
// -------> && + & = &
// -------> && + && = &&
// -> Rvalues are kinda like const lvalues
// ---> You can bind a parameter of "non-volative const lvalue reference" type to an argument of "rvalue" type
// -----> However, this rule doesn;t interact with the type deduction rules!
// -----> The compiler won't insert const qulaifiers into its deduced T just to make the binding come out right.
// -------> This is why f(static_cast<int&&>(i)) doesn't deduce to T=int.
// -> (N4606 13.3.3.1.4 [over.ics.ref]/3)

}  // namespace TemplateTypeDeductionWithAmpersandsWorks

namespace TemplateTypeDeductionWithDoubleRefRefDeduction {

template <typename T>
void f(void (*)(T)) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}
void g(int&&) {}

TEST(TemplateExamplesTest, TemplateTypeDeductionWithDoubleRefRefDeduction) {
    f(g);  // [with T = int&&]
}

// -> Although we prefer to deduce T=int rather T=int&& in the forwarding-reference case,
// ---> there do exists other cases where T=int&& is the only possible deduction.

}  // namespace TemplateTypeDeductionWithDoubleRefRefDeduction

namespace TemplateSpecializationWorks {

template <typename T>
struct isVoidStruct {
    static constexpr bool value = false;
};

template <typename T>
int mySizeOf() {
    return sizeof(T);
}

// template specializations
template <>
struct isVoidStruct<void> {
    static constexpr bool value = true;
};

template <>
int mySizeOf<void>() {  // has to use <void> to be deduced
    return 1;
}

TEST(TemplateExamplesTest, TemplateSpecializationWorks) {
    cout << "isVoidStruct with int: " << isVoidStruct<int>::value << "\n";
    cout << "isVoidStruct with void: " << isVoidStruct<void>::value << "\n";

    cout << "mySizeOf with int: " << mySizeOf<int>() << "\n";
    cout << "mySizeOf with void: " << mySizeOf<void>() << "\n";
}

// -> Defining a specialization in a nutshell
// ---> Prefix the definition with template<>, and then write the function definition
// -----> as if you were USING the specialization that you want to write.
// ---> For function templates, because of their type deduction rules,
// -----> this usually means you don't need to write any more angle brackets at all.
// -----> But when a type can't be deduced or defaulted, you have to write the brackets.
// -> (N4606 14.7.3 [temp.expl.spec]/1)

}  // namespace TemplateSpecializationWorks

namespace AliasTemplatesCannotBeSpecialized {

template <typename T>
using myvec = vector<T>;  // alias template

template <typename T>
void foo(myvec<T>&) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}

TEST(TemplateExamplesTest, AliasTemplatesCannotBeSpecialized) {
    vector<int> v;
    foo(v);  // Compiles: [with T = int, myvec<T> = std::vector<int>]
}

// -> We can "propagate T through" the definition of myvec to find that foo<T> takes std::vector<T>
// ---> Because myvec is always a std::vector (specialization is not allowed), the compiler can just substitute it.

}  // namespace AliasTemplatesCannotBeSpecialized

namespace ClassTemplatesCanBeSpecialized {

template <typename T>
struct myvec {
    using type = vector<T>;
};

template <typename T>
void foo(typename myvec<T>::type&) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}

TEST(TemplateExamplesTest, ClassTemplatesCanBeSpecialized) {
    vector<int> v1;
    // foo(v1);  // Error : couldn't infer template argument 'T'
}

// -> We don't know what myvec<T>::type is until we know what T is (because it can be specialized).

}  // namespace ClassTemplatesCanBeSpecialized

namespace PartialSpecializationWorks {

// This is the primary template:
template <typename T>
constexpr bool isAnArray = false;

// These are the partial specializations:
template <typename Tp>
constexpr bool isAnArray<Tp[]> = true;

template <typename Tp, size_t N>
constexpr bool isAnArray<Tp[N]> = true;

// This is a full specialization
template <>
constexpr bool isAnArray<void> = true;

TEST(TemplateExamplesTest, PartialSpecializationWorks) {
    cout << "isAnArray with int: " << isAnArray<int> << "\n";
    cout << "isAnArray with int[]: " << isAnArray<int[]> << "\n";
    cout << "isAnArray with int[5]: " << isAnArray<int[5]> << "\n";
    cout << "isAnArray with void: " << isAnArray<void> << "\n";
}

// -> A partial specialization is any specialization that is, itself a template
// ---> It still requires further "customization" by the user before it can be used.
// -> The user can explicitly specify values for the original template's template parameters,
// ---> but not for the partial specialization's template parameters.
// -----> So the latter must be deducible, or the partial specialization will never be used.
// -> The number of template paramters on the partial specialization is completely unrelated
// ---> to the number of template parameters on the original template.
// -> (N4606 14.5.5 [temp.class.spec])

}  // namespace PartialSpecializationWorks

namespace SelectingTheSpecializationWorks {

// This is the primary template:
template <typename T>
struct myVectorStruct {
    using type = std::vector<T>;
    explicit myVectorStruct() { cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n"; }
};

// This is a full specialization
template <>
struct myVectorStruct<void> {
    using type = void;
    explicit myVectorStruct() { cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n"; }
};

// These are the partial specializations:
template <typename Tp>
struct myVectorStruct<Tp*> {
    using type = Tp;
    explicit myVectorStruct() { cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n"; }
};

template <typename Tp>
struct myVectorStruct<Tp**> {
    using type = Tp;
    explicit myVectorStruct() { cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n"; }
};

TEST(TemplateExamplesTest, SelectingTheSpecializationWorks) {
    myVectorStruct<int> a;     // myVectorStruct<T>::myVectorStruct() [with T = int]
    myVectorStruct<void> b;    // myVectorStruct<void>::myVectorStruct()
    myVectorStruct<int*> c;    // myVectorStruct<Tp*>::myVectorStruct() [with Tp = int]
    myVectorStruct<int***> d;  // myVectorStruct<Tp**>::myVectorStruct() [with Tp = int*]
}

// -> Selecting the specialization
// ---> First, deduce all the template type parameters
// -----> Then, if they exactly match some full specialization, of course well use that full specialization
// -----> Otherwise, look for the best-matching partial specialization.
// -------> If the "best match" is hard to identify (ambiguous), give an error instead.

}  // namespace SelectingTheSpecializationWorks

namespace FunctionTemplatesCannotBePartiallySpecialized {

// This is the primary template:
template <typename T>
bool isPointer(T) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
    return false;
}

// This is a full specialization
template <>
bool isPointer(void*) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
    return true;
}

// This is a NOT a partial specialization, this is another template
template <typename Tp>
bool isPointer(Tp*) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
    return true;
}

TEST(TemplateExamplesTest, FunctionTemplatesCannotBePartiallySpecialized) {
    void* pv = nullptr;
    bool result = isPointer(pv);  // isPointer(Tp*) [with Tp = void]
    // [T=void*] specialization is not called, because the other template is a better match.

    cout << "isPointer with void*: " << result << "\n";
}

// -> This creates a pair of function templates in the same overload set.
// ---> It may seem to work in this case, but don't get used to it.
// -----> http://www.gotw.ca/publications/mill17.htm
// ---> Remember that the syntax for a full specialization always starts with template<>
// -----> and the syntax for a partial specialization always contains angle brackets after the template-name
// ------->(isPointer in this example).

}  // namespace FunctionTemplatesCannotBePartiallySpecialized

namespace FunctionTemplatesPartiallySpecializationUsingClasses {

// This is the primary class template:
template <typename T>
struct isPointerImpl {
    static bool isPointer() {
        cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
        return false;
    }
};

// This is the class partial specialization:
template <typename Tp>
struct isPointerImpl<Tp*> {
    static bool isPointer() {
        cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
        return true;
    }
};

// This is the function template
template <typename T>
bool isPointer(T) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
    return isPointerImpl<T>::isPointer();
}

TEST(TemplateExamplesTest, FunctionTemplatesPartiallySpecializationUsingClasses) {
    void* pv = nullptr;
    bool result = isPointer(pv);  // isPointerImpl<Tp*>::isPointer() [with Tp = void]

    cout << "isPointer with void*: " << result << "\n";
}

// -> If you need partial specialization, then you should delegate all the work to a class template,
// ---> which can be partially specialized
// ---> Use the right tool for the job!

}  // namespace FunctionTemplatesPartiallySpecializationUsingClasses

namespace TemplateIsOnlyInstantiatedWhenNeeded {

template <typename T>
struct NoInstantiationClass {
    // static_assert(false, "This will happen because its ill formed"); // Compiler error because ill formed
    static_assert(sizeof(T) == -1, "This will not happen because we are not instantiated");
};

template <typename T>
struct InstantiationClass {
    static void noInstantiationStaticFunction() {
        static_assert(sizeof(T) == -1, "This will not happen because we are not instantiated");
    }

    void noInstantiationFunction() {
        static_assert(sizeof(T) == -1, "This will not happen because we are not instantiated");
    }
};

TEST(TemplateExamplesTest, TemplateIsOnlyInstantiatedWhenNeeded) {
    // NoInstantiationClass<int> variable1;  // Compiler error (static_assert failure)
    NoInstantiationClass<int>* variable2;  // No compiler error.

    InstantiationClass<int> variable3;  // No compiler error.
    // InstantiationClass<int>::noInstantiationStaticFunction(); // Compiler error (static_assert failure)
    // variable3.noInstantiationFunction();  // Compiler error (static_assert failure)
}

// -> When is instantiation needed?
// ---> A decent rule of thumb is: Never instantiate anything you don't absolutely 100% have to.
// -----> N4604 14.7.1 [temp.inst]/1
// ---> Template class declarations does not instantiate member function definitions
// ---> An explicit/full specialization works basically like a plain old function,
// -----> because you've taken away all the template parameters.
// -----> There's no templatey stuff left to instantiate in this case.
// ---> Variable templates work similarly, but watch out that clang and GCC currently disagree
// -----> as to what constitutes a "definition" of a variable template
// -----> N4606 14.7.1 temp.inst/5:
// -------> Unless a variable template specialization has been explicitly instantiated or explicitly specialized,
// ---------> the variable template specialization is implicitly instantiated when the specialization is used.

// -> static_assert
// ---> static_assert(false) makes the program ill-formed
// ---> static_assert(some-falsely-expression-dependent-on-T) make the program ill-form
// -----> only if the template is actually instantiated
// -----> In theory, as of this writing a sufficiently smart compiler might refuse to compile this as well.
// ---> N4604 dcl.dcl /6, 14.6 temp.res /8.3

}  // namespace TemplateIsOnlyInstantiatedWhenNeeded

namespace VariadicTemplateParameterDeductionWorks {

template <typename T, typename... Us>
void foo1(Us...) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}

template <typename T, typename... Us, typename V>
void foo2() {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}

template <typename... Ts, typename U>
void foo3(U) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}

template <typename... Ts>
void foo4(Ts...) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}

template <typename... Ts, typename U>
void foo5(U, Ts...) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}

template <typename T, typename... Us>
void foo6(Us..., T) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}

template <typename... Ts, typename... Us>
void foo7(Ts..., Us...) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}

TEST(TemplateExamplesTest, TemplateTypeDeductionWorksUsingPrettyFunction) {
    foo1<char>(0, 1, 2);        // [with T = char; Us = {int, int, int}]
    foo1<char, char>(0, 1, 2);  // [with T = char; Us = {char, int, int}]
    // foo1<int, char, int>(); // Compiler error: requires 2 arguments, but 0 were provided

    // foo2<int, char, int>();  // Compiler error: couldn't infer template argument 'V'

    foo3<int, char>(3.1);  // [with Ts = {int, char}; U = double]

    foo4<int, char>(0, 0, 3.1);  // [with Ts = {int, char, double}]

    foo5('x', 1, 2);  // [with Ts = {int, int}; U = char]

    // foo6('x', 1, 2);  // Compiler error: requires 1 argument, but 3 were provided
    // Us... is NOT at the end of function parameter list.
    // Us... doesnt contribute to deduction, so this fails

    foo6<int, int, int>('x', 1, 2);  // [with T = int; Us = {int, int}]
    // Us.. doesnt contribute to deduction, but we explicit mention T = int; Us = {int, int} so it works

    foo7<int, int>(1, 2, 3);  // [with Ts = {int, int}; Us = {int}]
    // -> What does it mean to contribute to deduction?
    // ---> Clang: claims Ts can't be deduced; compiler error
    // ---> MSVC/GCC: assumes Ts wont be lengthened Ts=<int, int> Us=<int>
}

// -> Type deduction in a nutshell (with variadic templates)
// ---> For variadic templates:
// -----> As far as explicitly specified template parameters are concerned,
// -------> the first pack-expansion (Ts... ts) encountered in the template parameter list
// -------> "soaks up" all the remaining explicitly specified template parameters.
// -----> The type deduction step might wind up lenghtening ts, but will never shorten it.
// -----> As far as deduction is concern a parameter-pack (Ts... ts) contributes to deduction
// -------> only if it comes at the VERY END of the function parameter list.
// -----> Otherwise, it does not contribute to deduction.

}  // namespace VariadicTemplateParameterDeductionWorks

namespace TemplateAutoWorks {

template <typename Ty, Ty Value>
struct IntegralConstantWithoutAuto {
    static constexpr auto value = Value;
};

template <auto Value>
struct IntegralConstantWithAuto {
    static constexpr auto value = Value;
};

TEST(TemplateExamplesTest, TemplateAutoWorks) {
    using FortyTwoWithoutAuto = IntegralConstantWithoutAuto<int, 42>;
    using TrueTypeWithoutAuto = IntegralConstantWithoutAuto<bool, true>;

    using FortyTwoWithAuto = IntegralConstantWithAuto<42>;
    using TrueTypeWithAuto = IntegralConstantWithAuto<true>;

    // These (IntegralConstantWithoutAuto, IntegralConstantWithAuto) are basically the same.
}

}  // namespace TemplateAutoWorks

namespace TemplateTypeDeductionWorksForClassesInCpp17 {

template <typename T>
struct myvec {
    explicit myvec(T) { cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n"; }
    explicit myvec(T*) { cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n"; }
};

TEST(TemplateExamplesTest, TemplateTypeDeductionWorksForClassesInCpp17) {
    int integer = 5;
    myvec v1(integer);   // myvec(T) [with T = int]
    myvec v2(&integer);  // myvec(T*) [with T = int]
}

// -> Class templates can do deduction on CPP17
// ---> Forward works: If T is int, we know that myvec<T>'s constructor takes an int parameter.
// ---> But what about backward: If myvec<U>'s constructor takes an int parameter determine the value of U.
// -----> It works as demonstrated above.

// -> How it works?
// ---> Construct a fictitious set of function overloads
// -----> matching all the constructor of the myvec class template.
// -----> This doesn't involve instantiating anything!
// -----> In our case, there's only two:
// -------> template<class T> auto make_myvec(T t);
// -------> template<class T> auto make_myvec(T * t);
// -----> Now use overload resolution to resolve make_myvec(1)
// -------> Deduce T=int. Tada! Result: myvec(T) [with T = int]
// -> N4606 13.3.1.8 over.match.class.deduct

}  // namespace TemplateTypeDeductionWorksForClassesInCpp17

namespace TemplateDeductionGuidesWorksForCpp17 {

template <typename T>
struct myvec {
    explicit myvec(int) { cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n"; }
    explicit myvec(double) { cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n"; }
};
myvec(int)->myvec<double>;  // deduction guide
myvec(double)->myvec<int>;  // deduction guide

TEST(TemplateExamplesTest, TemplateDeductionGuidesWorksForCpp17) {
    myvec v1(5);    // myvec(int) [with T = double]
    myvec v2(5.1);  // myvec(double) [with T = int]
}

}  // namespace TemplateDeductionGuidesWorksForCpp17

namespace FunctionSelectionWorksAsExpected {

void commonFunctionName(int) { cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n"; }

template <typename Type>
std::enable_if_t<!areSameTypes<Type, unsigned int>()> commonFunctionName(Type) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}

template <>
void commonFunctionName(float) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}

TEST(TemplateExamplesTest, FunctionSelectionWorksAsExpected) {
    // perfect match is first
    commonFunctionName(5);  // commonFunctionName(int)

    // template specialization is second
    commonFunctionName(5.f);  // commonFunctionName(Type) [with Type = float]

    // template instantiation is third
    commonFunctionName(5.0);  // commonFunctionName(Type) [with Type = double]

    // implicit conversions is last
    commonFunctionName(5U);  // commonFunctionName(int)
}

}  // namespace FunctionSelectionWorksAsExpected

}  // namespace alba

// Collect all notes here:
// General Notes:

// Template kinds (introduction year):
// ------------------------------------
// | Template kind | Introduction year
// ------------------------------------
// | Function      | < 1998
// | Class         | < 1998
// | Alias         | 2011
// | Variable      | 2014
// ------------------------------------

// Template kinds:
// -----------------------------------------------------------------------------------------------------
// | Template kind | Does type deduction occur?    | Is full specialization | Is partial specialization
// |               |                               | allowed?               | allowed?
// -----------------------------------------------------------------------------------------------------
// | Function      | Yes                           | Yes                    | No
// | Class         | No* (except deduction guides) | Yes                    | Yes
// | Alias         | No                            | No                     | No
// | Variable      | No                            | Yes                    | Yes
// -----------------------------------------------------------------------------------------------------
// -> Type deduction only happens on function templates
// -> The standard calls full specialization as "explicit specialization".
// -> Partial specialization is not allowed for function templates.
// ---> If you need partial specialization, then you should delegate all the work to a class template.

// -> Type deduction in a nutshell (N4606 14.8.2.1 [temp.deduct.call]):
// ---> Any template parameters that were explicitly specified by the caller
// -----> are fixed as whatever the caller said they were
// -----> and they dont participate any further in deduction
// ---> Each function parameter may contribute (or not) to the deduction of each template parameter (or not).
// ---> All deductions are carried out "in parallel"; they don't cross talk with each other.
// ---> If any template parameter (that wasn't specified by the caller) couldn't be deduced,
// -----> but has a default value, then it is fixed as its default value.
// ---> For variadic templates:
// -----> As far as explicitly specified template parameters are concerned,
// -------> the first pack-expansion (Ts... ts) encountered in the template parameter list
// -------> "soaks up" all the remaining explicitly specified template parameters.
// -----> The type deduction step might wind up lenghtening ts, but will never shorten it.
// -----> As far as deduction is concern a parameter-pack (Ts... ts) contributes to deduction
// -------> only if it comes at the VERY END of the function parameter list.
// -----> Otherwise, it does not contribute to deduction.
// ---> Finally, the compiler checks to make sure that each template parameter
// -----> has been deduced at least once
// -------> Otherwise: "Couldn't infer temp late argument T" error
// -----> and that all deductions agree with each other
// -------> Otherwise: "Deduced conflicting types for parameter T" error
// ---> Furthermore, any function parameter that does contribute to deduction
// -----> must match its function argument type exactly.
// -----> No implicit conversions allowed!

// -> Reference collapsing:
// ---> The rule to remember when dealing with references is that combining two reference types
// -----> mins the number of ampersands between them.
// -------> & + & = &
// -------> & + && = &
// -------> && + & = &
// -------> && + && = &&

// -> Defining a specialization in a nutshell
// ---> Prefix the definition with template<>, and then write the function definition
// -----> as if you were USING the specialization that you want to write.
// ---> For function templates, because of their type deduction rules,
// -----> this usually means you don't need to write any more angle brackets at all.
// -----> But when a type can't be deduced or defaulted, you have to write the brackets.
// -> (N4606 14.7.3 [temp.expl.spec]/1)

// -> A partial specialization is any specialization that is, itself a template
// ---> It still requires further "customization" by the user before it can be used.
// -> The user can explicitly specify values for the original template's template parameters,
// ---> but not for the partial specialization's template parameters.
// -----> So the latter must be deducible, or the partial specialization will never be used.
// -> The number of template paramters on the partial specialization is completely unrelated
// ---> to the number of template parameters on the original template.
// -> (N4606 14.5.5 [temp.class.spec])

// -> Selecting the specialization
// ---> First, deduce all the template type parameters
// -----> Then, if they exactly match some full specialization, of course well use that full specialization
// -----> Otherwise, look for the best-matching partial specialization.
// -------> If the "best match" is hard to identify (ambiguous), give an error instead.

// -> Define a specialization in another translation unit
// ---> Declarations and definitions work just the way you'd expect them to.
// ---> In our .h file, we might have this:
// -----> template <typename CS> int mblen(const char*, int);
// -----> template <> int mblen<ascii>(const char*, int);
// -----> template <> int mblen<utf8>(const char*, int);
// ---> And then in our .cpp file, we might have this:
// -----> template <> int mblen<ascii>(const char*, int) { impl }
// -----> template <> int mblen<utf8>(const char*, int) { impl }
// -> Note: This violates "Dont pay for what you don't use" philosophy so be careful.

// -> Explicit instantiation definition
// ---> This special syntax means:
// -----> "Please instantiate this template, with the given template parameters, as if it were being used right here."
// ---> Semantically, its not giving the compiler any new information.
// ---> Its just asking the compiler to instantiate a definition of the template entity right here.
// ---> It looks just like a full specialization, but without the <>.
// -----> template int abs(int); // or: abs<>(int), or: abs<int>(int)
// ---> To tell the compilar that you dont this in a different translation unit,
// -----> and therefore the compiler does not need to instantiate this template again in this .o file, just add extern.
// -------> extern template int abs(int);
// -> Note: This violates "Dont pay for what you don't use" philosophy so be careful.
// -> N4606 14.7.2 [temp.explicit] /2

// -> Explicit instantiation of a class template (what are we going to do with members)
// ---> When you explicitly instantiate a template class,
// -----> that single definition counts as an explicit instantiation of all member of that template class too,
// -----> both the static members and the non-static members.
// -> N4606 14.7.2 [temp.explicit] /8

// -> Dont mix and match template specialization and instantiation
// ---> Because  we can instantiate and we can explicitly specialize,
// -----> we can have got two competing definitions.
// -----> Which one wins depends on your optimization level.
// -> N4606 14.7.3 [temp.expl.spec]/6; 14.7.2 [temp.explicit] /11

// -> Template entities on header and translation unit
// ---> N4606 "A function template, member function of a class template, or static data member of a class template
// -----> shall be defined in every translation unit in which it is implicitly instantiated
// -----> unless the corresponding specialization is explicitly instantiated in some translation unit."
// -----> N4606 14 [temp]/7

// -> There are at least four ways template stuff can go wrong.
// ---> The compiler can't figure out the template parameters. Result: Compiler error.
// ---> Problems in instantiating a declaration. Result: Compiler error.
// ---> Problems in instantiating a definition. Result: Compiler error.
// ---> Instantiating only a declaration (or nothing at all),
// -----> when you though you were getting a definition. Result: Linker error.

// -> When is instantiation needed?
// ---> A decent rule of thumb is: Never instantiate anything you don't absolutely 100% have to.
// -----> N4604 14.7.1 [temp.inst]/1
// ---> Template class declarations does not instantiate member function definitions
// ---> An explicit/full specialization works basically like a plain old function,
// -----> because you've taken away all the template parameters.
// -----> There's no templatey stuff left to instantiate in this case.
// ---> Variable templates work similarly, but watch out that clang and GCC currently disagree
// -----> as to what constitutes a "definition" of a variable template
// -----> N4606 14.7.1 temp.inst/5:
// -------> Unless a variable template specialization has been explicitly instantiated or explicitly specialized,
// ---------> the variable template specialization is implicitly instantiated when the specialization is used.

// -> static_assert
// ---> static_assert(false) makes the program ill-formed
// ---> static_assert(some-falsely-expression-dependent-on-T) make the program ill-form
// -----> only if the template is actually instantiated
// -----> In theory, as of this writing a sufficiently smart compiler might refuse to compile this as well.
// ---> N4604 dcl.dcl /6, 14.6 temp.res /8.3
