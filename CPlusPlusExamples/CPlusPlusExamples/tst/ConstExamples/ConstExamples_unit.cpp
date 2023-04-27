#include <gtest/gtest.h>

#include <iostream>

using namespace std;

// Taken from Richard Powell's lecture ("The importance of being const")

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

    int* b = a;    b++;
    *b = 20;

    int const* c = a;    c++;
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
    int const* p2 = p1;  // p2 points to "const"ant int, "const" is added on p2    // int * p3 = p2; // Error because you cannot remove the "const"ness of p2
    int* const p4 = p1;  // p4 is a "const"ant pointer to int, const added to pointer

    int const data2 = 2;    // int * p5 = p2; // Error because you cannot remove the "const"ness of data2

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

    int const data2 = 2;    // int& r5 = r2; // Error because you cannot remove the "const"ness of data2

    cout << "To avoid warnings r2: [" << r2 << "] data2:[" << data2 << "]\n";

    // Note: You cant remove "const" from data using references.
}

TEST(ConstExamplesTest, MutationWithConstInPrimitiveTypesInStructsDoesNotWork) {
    struct Foo {
        int a = 0;
        int const b = 1;    };

    Foo f{};
    f.a++;    // f.b++; // Error because "b" is const

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
        int* a = &data;        int const* b = &data;
    };

    Foo f;    *f.a = 20;
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
        int& a = data;        int const& b = data;
    };

    Foo f;    f.a = 20;
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
void function1(Foo*) { cout << "function1\n"; }void function2(Foo const*) { cout << "function2\n"; }
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
        void myFunction() { cout << "calling non-const\n"; }        void myFunction() const { cout << "calling const\n"; }
    };

    Foo a;    Foo const b(a);

    a.myFunction();  // goes to "non-const"
    b.myFunction();  // goes to "const"

    // Note: C++ picks the best function based from its function signature.
    // The signature includes if the function itself is const.
}

TEST(ConstExamplesTest, FunctionMatchingWithConstInFunctionSignatureOfAClassWorks) {
    class Foo {
    public:
        void myFunction() const { cout << "calling const\n"; }    };

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
        void myFunction() { cout << "calling non-const\n"; }    };

    Foo a;
    // Foo const b(a);
    a.myFunction();  // goes to "non-const"
    // b.myFunction(); // Error because b is const

    // Note: If the member function is non-const, then you cannot use it in const structures.
}

TEST(ConstExamplesTest, MutabilityOfStructInsideAFunctionWorks) {
    static int data = 0;
    struct Foo {
        void myFunction() const {            // value++; // Error because myFunction is const
            // a++; // Error because myFunction is const
            // b++; // Error because myFunction is const
            *a = 20;  // No error because only deferenced value is changed, not the actual pointer            //*b=20; // Error because b is const*
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
    // -> Const functions cannot modify object.    // -> On these occasions you reach for "mutable", the C+++ wiggle room for const
    // -> "mutable" tells the compiler that the value will change even if the function is const.

    struct DataHolder {    public:
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
}void modifyIt(int&) {
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
    // ---> Herb Sutter quote:    // -----> "when it comes to optimization,
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
// -> const makes it easier to reason about your code// -> It helps preserve your class invariants
// -> Attempt to use const following type style to help readability
// ---> "T const t"
// -> const member runctions should be observably const and thread-safe
// -> const doesn't necessarily make faster code, but it makes more correct code
