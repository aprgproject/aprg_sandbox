#include <gtest/gtest.h>

#include <iostream>

using namespace std;

// Taken from Richard Powell's lecture ("The importance of being const")
// Taken from Dan Saks lecture ("Back to Basics- Const as a Promise")

namespace alba {

TEST(ConstExamplesTest, MutationWithConstInPrimitiveTypesDoesNotWork) {
    long a = 0;
    long const b = 1;

    ++a;

    // b++; // Error because "b" is const

    if (b > 4) cout << "b is greater than 4\n";

    if (b == 44) cout << "b is greater than 4\n";

    // if(b>>=a) // Error because "b" is const
    //    cout << "b is greater than 4\n";

    // a = ? ++b : b; // Error because "b" is const

    // Note: You can't modify const data (unless const_cast).
}

TEST(ConstExamplesTest, MutationWithConstInPointersSometimesWorks) {
    int a[] = {1, 2, 3};

    int* b = a;
    b++;
    *b = 20;

    int const* c = a;
    c++;
    //*c = 20; // Error because "c" is const*

    int* const d = a;
    // d++; // Error because "c" is *const
    *d = 20;

    // int const*const e = a;
    // e++; // Error because "e" is const*
    //*e = 20; // Error because "e" is *const

    // Note: Notice the difference of "const*", "*const" and "const*const"
}

TEST(ConstExamplesTest, ConstCanBeAddedOnTopUsingPointers) {
    int data1 = 1;
    int* p1 = &data1;    // p1 points to (mutable) int
    int const* p2 = p1;  // p2 points to "const"ant int, "const" is added on p2
    // int * p3 = p2; // Error because you cannot remove the "const"ness of p2
    int* const p4 = p1;  // p4 is a "const"ant pointer to int, const added to pointer

    int const data2 = 2;
    // int * p5 = p2; // Error because you cannot remove the "const"ness of data2

    cout << "To avoid warnings *p2: [" << *p2 << "] *p4: [" << *p4 << "] data2:[" << data2 << "]\n";

    // Note: You cant remove "const" from data using pointers.
    // "Once you're const, you will be forever ensconced (except when using const_cast)" - Wife of Richard Powell
}

TEST(ConstExamplesTest, ConstCanBeAddedOnTopUsingReferences) {
    int data1 = 1;
    int& r1 = data1;     // r1 refers to (mutable) int
    int const& r2 = r1;  // r2 refers to "const"ant int, "const" is added on r2
    // int & r3 = r2; // Error because you cannot remove the "const"ness of r2
    // int& const r4 = r1; // Error because there is no &const, because address of the reference cannot be moved

    int const data2 = 2;
    // int& r5 = r2; // Error because you cannot remove the "const"ness of data2

    cout << "To avoid warnings r2: [" << r2 << "] data2:[" << data2 << "]\n";

    // Note: You cant remove "const" from data using references.
}

TEST(ConstExamplesTest, MutationWithConstInPrimitiveTypesInStructsDoesNotWork) {
    struct Foo {
        int a = 0;
        int const b = 1;
    };

    Foo f{};
    f.a++;
    // f.b++; // Error because "b" is const

    // Foo const cf{};
    // cf.a++; // Error because "cf" is const
    // cf.b++; // Error because "cf" is const

    Foo* ptr_f = &f;
    ptr_f->a++;
    // ptr_f->b++; // Error because "b" is const
    ptr_f++;  // No error because ptr_f can be moved

    Foo const* c_ptr_f = &f;
    // c_ptr_f->a++; // Error because "c_ptr_f" is const*
    // c_ptr_f->b++; // Error because "c_ptr_f" is const*
    c_ptr_f++;  // No error because c_ptr_f can be moved

    // Note: You can't modify the "const members of structures" and "members of const structures".
}

TEST(ConstExamplesTest, MutationWithConstInPointersInStructsSometimesWorks) {
    static int data;
    struct Foo {
        int* a = &data;
        int const* b = &data;
    };

    Foo f;
    *f.a = 20;
    //*f.b = 20; // Error because "b" is const

    Foo const cf;
    *cf.a = 20;  // No error because "a" address is not changed
    //*cf.b = 20; // Error because "b" is const

    Foo* ptr_f = &f;
    *ptr_f->a = 20;
    //*ptr_f->b = 20; // Error because "b" is const

    Foo const* c_ptr_f = &f;
    *c_ptr_f->a = 20;  // No error because "a" address is not changed
    //*c_ptr_f->b = 20; // Error because "b" is const

    // Note: You can't modify the "const members of structures" and "members of const structures".
    // However, you can modify the data on where its members are pointing at (unless its const*).
}

TEST(ConstExamplesTest, MutationWithConstInReferencesInStructsSometimesWorks) {
    static int data;
    struct Foo {
        int& a = data;
        int const& b = data;
    };

    Foo f;
    f.a = 20;
    // f.b = 20; // Error because "b" is const

    Foo const cf;
    cf.a = 20;  // No error because "a" address is not changed
    // cf.b = 20; // Error because "b" is const

    Foo& ref_f = f;
    ref_f.a = 20;
    // ref_f.b = 20; // Error because "b" is const

    Foo const& c_ref_f = f;
    c_ref_f.a = 20;  // No error because "a" address is not changed
    // c_ref_f.b = 20; // Error because "b" is const

    // Note: You can't modify the "const members of structures" and "members of const structures".
    // However, you can modify the data on where its members are refering at (unless its const&).
}

namespace FunctionMatchingWithWithDifferentParametersWorks {

struct Foo {};
void function1(Foo*) { cout << "function1\n"; }
void function2(Foo const*) { cout << "function2\n"; }
void function3(Foo*) { cout << "function3 with *\n"; }
void function3(Foo const*) { cout << "function3 with const*\n"; }

TEST(ConstExamplesTest, FunctionMatchingWithWithDifferentParametersWorks) {
    Foo f;
    Foo* ptr_f = &f;
    Foo const* c_ptr_f = &f;

    function1(ptr_f);  // goes to "function 1"
    // function1(c_ptr_f); // Error because cannot convert to const*

    function2(ptr_f);    // goes to "function 2"
    function2(c_ptr_f);  // goes to "function 2" as well

    function3(ptr_f);    // goes to "function 3 with *"
    function3(c_ptr_f);  // goes to "function 3 with const*"

    // Note: C++ picks the best function based from its function signature.
    // If the "const"ness is removed, then its a compilation error.
}
}  // namespace FunctionMatchingWithWithDifferentParametersWorks

TEST(ConstExamplesTest, FunctionMatchingWithAndWithoutConstInFunctionSignatureOfAClassWorks) {
    class Foo {
    public:
        void myFunction() { cout << "calling non-const\n"; }
        void myFunction() const { cout << "calling const\n"; }
    };

    Foo a;
    Foo const b(a);

    a.myFunction();  // goes to "non-const"
    b.myFunction();  // goes to "const"

    // Note: C++ picks the best function based from its function signature.
    // The signature includes if the function itself is const.
}

TEST(ConstExamplesTest, FunctionMatchingWithConstInFunctionSignatureOfAClassWorks) {
    class Foo {
    public:
        void myFunction() const { cout << "calling const\n"; }
    };

    Foo a;
    Foo const b(a);

    a.myFunction();  // goes to "const"
    b.myFunction();  // goes to "const"

    // Note: If the member function is const, then you can use it in non const structures to add "const"ness to the
    // operation.
}

TEST(ConstExamplesTest, FunctionMatchingWithoutConstInFunctionSignatureOfAClassWorks) {
    class Foo {
    public:
        void myFunction() { cout << "calling non-const\n"; }
    };

    Foo a;
    // Foo const b(a);

    a.myFunction();  // goes to "non-const"
    // b.myFunction(); // Error because b is const

    // Note: If the member function is non-const, then you cannot use it in const structures.
}

TEST(ConstExamplesTest, MutabilityOfStructInsideAFunctionWorks) {
    static int data = 0;
    struct Foo {
        void myFunction() const {
            // value++; // Error because myFunction is const
            // a++; // Error because myFunction is const
            // b++; // Error because myFunction is const
            *a = 20;  // No error because only deferenced value is changed, not the actual pointer
            //*b=20; // Error because b is const*
            refData = 20;  // No error because only deferenced value is changed, not the actual reference
        }
        int value = 0;
        int* a = &data;
        int const* b = &data;
        int& refData = data;
    };

    // Note: Rules for constness apply to member variables too.
    // -> You can't modify const data (unless const_cast).
    // -> For pointers: You can modify the data on where its members are pointing at (unless its const*).
    // -> For references: You can modify the data on where its members are refering at (unless its const&).

    // Bitwise const vs Logical const
    // -> Bitwise const
    // ---> A member function is Bitwise const if it doesn't modify any of the bits inside the object
    // ---> This is the compiler's view - "a const member function isn't allowed to modify any of the non-static data
    // members of the object on which it is invoked"
    // -> Logical const
    // ---> Logical const means that from the clients point of view, the function has not changed anything
    // ---> There are no detectable changes
    // ---> Observably const
    // -> Comparison
    // ---> From the example above, they are only allowed or not allowed to edit parameter based on "Bitwise const".
    // -----> Const member functions frequently are observer functions
    // -----> You should strive to make your member functions "Observably const".
}

TEST(ConstExamplesTest, MutabilityOfMutableMembersInAClassWorks) {
    // What do you do when you need to do something non-const in a const member function?
    // -> Chaching or logging are prime examples and valid use cases.
    // -> Const functions cannot modify object.
    // -> On these occasions you reach for "mutable", the C+++ wiggle room for const
    // -> "mutable" tells the compiler that the value will change even if the function is const.

    struct DataHolder {
    public:
        int getCheckSum() const {
            ++m_numberOfTimesCalled;  // even though function is const, we can change this because its mutable
            return calculateCheckSum();
        }
        void addMore(int const& data) {
            // modify the data
            m_data += data;
        }
        int getNumberOfTimesCalled() const { return m_numberOfTimesCalled; }

    private:
        int calculateCheckSum() const {
            // do some processing and return data
            return m_data;
        }
        int m_data{0};
        mutable int m_numberOfTimesCalled{0};  // this counter needs to be mutable
    };

    DataHolder dataHolder;
    dataHolder.addMore(10);
    dataHolder.addMore(20);
    dataHolder.addMore(30);
    cout << "data: [" << dataHolder.getCheckSum() << "] number of times called: ["
         << dataHolder.getNumberOfTimesCalled() << "]\n";

    // Ok, now the program compiles. Are we good? Is this safe?
    // -> Warning potentially TOXIC code!
    // -> There is a subtle bug -> Race condition on m_numberOfTimesCalled
    // -> Const means data race free
    // ---> If two or more thread access the same memory location without synchronization, and at least one is a writer,
    // you have undefined behavior.

    // Note: "mutable" member variables are useful, but can be a nuisance because it breaks const (especially in
    // multithreaded applications)
}

namespace OptimzationOfConstParametersDoesNotWork {
void logIt(int) {
    // dont change parameter
}
void modifyIt(int&) {
    // change parameter
}

void foo(int const& a, int& b) {
    // compiler generates two loads (even at -O3)
    // -> gcc.godbolt.org is a website that generates assembly
    // -> Two loads are needed in foo(a, a);
    // ---> Compilers cannot make assumptions about what happens at function calls

    logIt(a);
    modifyIt(b);
    logIt(a);
}

TEST(ConstExamplesTest, OptimzationOfConstParametersDoesNotWork) {
    // -> Does using "const" generate faster code?
    // ---> Generally no.
    // ---> Herb Sutter quote:
    // -----> "when it comes to optimization,
    // -----> const is still principally uses as a tool that lets human class designer better implement handcrafted
    // optimizations
    // -----> and less so as a tag for omniscient compilers to automatically generate better code"

    int a = 10, b = 10;
    foo(a, b);
    foo(a, a);  // Two loads are needed here.

    // Note: "const"ness generally does not optimize for faster code (except of constexpr because its compiled
    // beforehand).
    // -> The argument for "const"ness is not performance but rather correctness and maintainability.
}
}  // namespace OptimzationOfConstParametersDoesNotWork

}  // namespace alba

// Notes:

// -> const helps you find bugs at compile time
// -> const makes it easier to reason about your code
// -> It helps preserve your class invariants
// -> Attempt to use const following type style to help readability
// ---> "T const t"
// -> const member runctions should be observably const and thread-safe
// -> const doesn't necessarily make faster code, but it makes more correct code

// -> Uses for const
// ---> To define symbolic constants:
// -----> Yes but constexpr is better
// ---> To define immutable (never changing) data:
// -----> Yes but constexpr is better
// ---> To prevent modifying a potentially modifiable operand?
// -----> Yes!
// -----> We see this mostly when passing arguments and returning values by pointer or reference.
// -----> This is the primary use for const in Modern C++.

// -> Using const is Good Hygiene
// ---> Using const turn potential runtime bugs into compile time errors
// -----> As compile-time errors, the bugs are impossible to ignore
// ---> Consequently using const properly helps make interfaces
// -----> easier to use correctly
// -----> harder to use inforrectly
// ---> Using constexpr helps turn runtime computations into compile computations

// -> Be Proactive
// ---> Unfortunately, too many programmers use const reactively
// -----> only in response to compiler complaints
// ---> Conscientious programmer use const proactively
// -----> as they design and code.
// ---> Be conscientious
// ---> Use const proactively

// -> What const sorta means?
// ---> You can use const to define objects of built-in or user-defined types:
// -----> int const number = 8675309; // const int
// -----> char const msg[] = "Hello"; // array of const char
// ---> A const object is non modifiable... sorta.
// -----> That is you can read from it but not write to it

// -> Mandated initialization
// ---> You can't write to an existing const object.
// ---> Your only chance to give it a value is when you create it.
// ---> Thus, C++ insists that you must initializa every const object.
// -----> "extern" still works because its only a declaration not a definition

// -> Constant expressions
// ---> In C++, the dimension in an array object definition must be an integer constant expression.
// ---> Field width in a struct must be constant
// ---> A constant expression
// -----> can have operators and multiple operands
// -----> but must be evaluated at compile time.
// ---> In C++ an integer constant object initialize with a constant expression is an integer constant expression.
// ---> Suprisingly, a const object isn't always a constant expression.
// ---> C++ lets you initialize a const object with a non-constant expression.
// -----> The program might initialize at runtime.
// ---> You can use constexpr to guarantee compile-time evaluation.
// ---> A constexpr object must be initialize with a constant expression.
// -----> "constepxr is conster that const" - Steve Dewhurst
// ---> Prefer constexpr to const for defining symbolic constants.

// -> CV-Qualifiers
// ---> Anywhere you can use const, you can use either:
// -----> const
// -----> volatile
// -----> both (in either order )
// ---> Collectively const and volatile are cv-qualifiers
// -----> Type conversions involving volative are very similar to those involving const
// ---> constexpr is not a cv-qualifier
// -----> you can't use constexpr everywhere that you can use const
// -----> and vice versa

// -> Key insights
// ---> Const objects of arithmetic type are pretty straight forward
// ---> "const" is more useful when you combine it with pointers or references
// -----> It also gets more complicated.
// ---> As with much of C+, understanding const is difficult if you can't get past the syntax
// ---> Here are key insights to help you understand the syntax...

// -> The Structure of Declarations
// ---> Insight: Every object and function declaration has two main parts:
// -----> a sequence of one or more declaration specifiers
// -----> a declarator (or a sequence there of, separated by commas)
// ---> For example:
// -----> static unsigned long int *x[N];
// -----> "static unsigned long int" -> [declaration specifiers]
// -----> "*x[N]" -> [declarator]
// ---> The name declared in declarator is the declarator-id.

// -> Declaration specifiers and declarators
// ---> A declaration specifier can be:
// -----> A type specifier:
// -------> a keyword such as inst, unsigned, long, or double
// -------> a user-defined type, such a string or vector<int>
// -----> A non type specifier:
// -------> a keyword such as extern, static, inline or typedef.

// -> Declarator operators
// ---> A declarator is a declarator-id, possibly surrounded by operators
// -----> Insight: In a declarator, the operators group according
// -----> to the same precedence as when they appear in an expression
// ---------------------------------------------
// | Precedence | Operator | Meaning           |
// ---------------------------------------------
// | Highest    | ()       | grouping          |
// |            | []       | array             |
// |            | ()       | function          |
// ---------------------------------------------
// | Lowest     | unary *  | pointer           |
// |            | unary &  | lvalue reference  |
// |            | unary && | rvalue reference  |
// ---------------------------------------------
// ---> How about *x[N]?
// -----> How do you know whether
// -------> x is "a pointer to an array"
// -------> x is "array of pointers"
// -----> [] has higher precedence that unary *
// -------> x is "array of pointers"
// -------> More precisely, x is an "array with N elements of type pointer"

// -> Parentheses in Declarators
// ---> Parentheses serve two roles in declarators:
// ---> As the function call operator:
// -----> These ()s "follow" the declarator-id
// -----> They have the same precedence as [].
// ---> As grouping:
// -----> These ()s "enclose" the declarator-id
// -----> They have the highest precedence of all.

// -> Type vs Non-type specifiers
// ---> Insight: Type specifiers modify other type specifiers
// ---> Insight: Non-type specifiers apply directly to the declarator-id.
// ---> static unsigned long int *x[N]
// ---> Here unsigned long, and int are type specifiers
// -----> They form the type to which the pointers in array x point
// ---> static is a non-type specifiers that applies directly to x.

// -> const is a type-specifier
// ---> The order of declaration specifiers doesn;t matter to the compiler.
// ---> These two declaration mean the same thing:
// -----> unsigned long ul;
// -----> long unsigned ul;
// ---> So do these three:
// -----> const unsigned long cul;
// -----> long unsigned const cul;
// -----> unsigned const long cul;
// ---> const is atype specifier much like long or unsigned
// ---> const modfies the other type specifiers in the same declaration

// -> const in Declarators
// ---> Insight: const and volatile are the only symbols (in C++)
// -----> that can appear either as declaration specifiers or in declarators.
// ---> In both of these, const is a type specifier
// -----> const int  |  *v[N];
// -----> int const  |  *v[N];
// ---> Here, const appears in the declarator:
// -----> int  |  *const v[N];
// ---> When the const appears to the immediate right of a * in a declarator turns
// -----> the "pointer" into a "const pointer"
// ---> The spacing around the * doesnt matter to the compiler.
// -----> * and const are separate tokens.
// ---> However, * followed by const is effectively a single operator
// -----> the "const pointer" operator
// ---> "*const" has the same operator precedence as just *.

// -> Declarations that mean what you intend
// ---> There's a simple way to ensure that you're placing const (or volatile) where you want it in a declaration
// -----> First, write the declaration as it would be without const (or volativle)
// -----> Then...
// -----> Place const(or volatile) to the immediate right of the type specifier or operator that you want it modify
// -------> For example, suppose we want x to be:
// ---------> "array of N const pointers to volatile uint32_t"
// -------> Start by writing the declaration for:
// ---------> "array of N pointers to uint32_t"
// --------->  uint32_t * x[N]
// -------> Next, add const to the immediate right of the *:
// --------->  uint32_t * const x[N]
// -------> Finally, add volatile to the immediate right of the uint32_t:
// --------->  uint32_t volatile * const x[N]
// -------> Were done!

// -> So what about constexpr
// ---> Syntactically, constexpr is not a type-specifier
// ---> It behaves more like a non-type specifier.
// -----> constexpr unsigned long int *x[N];
// ---> Here, constexpr modifies x, not the other type specifiers.
// ---> x's type is as if it were declared as
// -----> unsigned long int * const x[N];
// ---> But the initializer must be constant expression.

// -> Address-of
// ---> The address-of operator (&) preserves constness.
// -----> int i;
// -----> int const ci = 42;
// -----> &i  // yields "pointer to [non-const] int"
// -----> &ci // yields "pointer to const int"

// -> Array-to Pointer Conversions
// ---> In various contexts, arrays implicitly convert to pointers.
// ---> The array-to-pointer conversion preserves constness:
// -----> "array of [non-const] T" converts to "pointer to [non-const] T"
// -----> "array of const T" converts to "pointer to const T"
// ---> String literals such as "xyzzy", have type "array of const char"
// -----> They convert to "pointer to const char"

// -> const as a promise
// ---> Think of const as a promise
// ---> You can apply ethical reasoning to the sematics of const.
// ---> Imagine a conversation between:
// -----> K: The current keeper of X and
// -----> B: The borrower of X
// -----> K: "If I give you access to X canI trust that you won't change it?"
// -----> B: "Yes, I promise I won't change X."
// -----> K: "You understand that I might still be able to change X, and give other permission."
// -----> B: "Yes, my promise not to change X doesn't necessarily mean no one else can change X."
// -----> K: "You also understand that you can't weasel out by asking others to break the promise for you"
// -----> B: "Yes, I do. I won't ask others to break my promise."

// -> Qualification conversion
// ---> A qualification conversion adds cv-qualifiers to the type to which the converted pointer points
// ---> More precisely, a qualification conversion converts.
// -----> an object of type "pointer to CV1T"
// -----> into type "pointer to CV2T"
// ---> where
// -----> CV1 is either empty, const, volatile or const volatile and
// -----> CV2 is more cv-qualified that CV1
// -------> That is, CV2 has every qualfiier in CV1, plus at least one more.

// -> Reference initialization
// ---> Reference initialization behaves similarly to qualification conversions for pointers
// ---> A reference initialization can increase the constness of the reference object
// ---> A reference initialization can't decrease the constness of the reference object

// -> Using const in parameter declarations
// ---> function(T const* t) // makes sense
// -----> This is meaningful constraint on foo's behavior.
// ---> function(T *const t) // does not makes sense
// -----> "In 40 years of experience, I never seen this."
// -----> Note: You can copy "t" and save it on another variable and change it.
// -----> This const is pretty useless, if not deceptive:
// -------> Its reasonable to expect that const in a parameter list affects the function's outward behavior.
// ---> function(T const*const t) // overkill

// -> Top-Level CV qualifiers
// ---> Types in C++ can have one or more levels of composition
// ---> For example, type "pointer to char" has two levels:
// -----> "pointer to"
// -----> "char"
// ---> Type "array of pointer to int" has three levels:
// -----> "array of"
// -----> "pointer to"
// -----> "int"
// ---> Type "string" has just one level:
// -----> "string"
// ---> A cv-qualifier on the first leve of a type is called a top-level cv qualifier.
