#include <Common/Macros/AlbaMacros.hpp>

#include <gtest/gtest.h>

#include <iostream>
using namespace std;

// Taken from Ben Saks's lecture ("Back to Basics- Understanding Value Categories")
namespace alba {

namespace RValueAssignmentCannotWork {

TEST(ValueCategoriesExamplesTest, RValueAssignmentCannotWork) {
    int n = 5;
    // 1 = n; // Error: lvalue required as left operand of assignment
}
}  // namespace RValueAssignmentCannotWork

namespace LValuesAndRValuesBindToDifferentFunctions {
void foo(string const &) {
    // takes lvalues
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}
void foo(string &&) {
    // takes rvalues
    // Here we can steal the guts of the parameter because its a temporary.
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
}
TEST(ValueCategoriesExamplesTest, LValuesAndRValuesBindToDifferentFunctions) {
    string s = "hello";
    foo(s);             // calls foo (with lvalue)
    foo(s + " world");  // calls foo (with rvalue)
    foo("hi");          // calls foo (with rvalue)
    foo(move(s));       // calls foo (with rvalue)
}
}  // namespace LValuesAndRValuesBindToDifferentFunctions

}  // namespace alba

// Notes:
// -> Value Categories
// ---> Value categories aren't really language features.
// ---> Rather, they're semantic properties of expression.// ---> Understanding them provides valuable insights into:
// -----> helps understand how the compiler thinks
// -----> built-in and user defined operators
// -----> reference types
// -----> otherwise-cryptic compiler error messages

// -> LValues and RValues have evolved
// ---> In early C, there were two value categories: lvalues and rvalues
// -----> The associated concepts were fairly simple.
// ---> Early C++ added classes, const, and references
// -----> Those concepts need to evolve to handle these new language features
// -----> The concepts got more complicated.
// ---> Modern C++ added rvalue references
// -----> C++ needed more value categories to specify the associated behaviors.
// -----> This talk explains value vategories from this historical perspective.

// -> LValues and RValues
// ---> The term comes up in assignment expressions.
// ---> In "The C Programming Language", Kernighan and Ritchie wrote
// -----> The name "lvalue" comes from the assignment expression.
// -------> E1=E2
// -------> in which the left operand E1 must be an lvalue expression.
// ---> An lvalue is an expression referring to an object.
// ---> An object is a region of storage.
// ---> For example:
// -----> Code:
// -------> int n;  // a deinition from an integer object named n
// -------> n = 1;  // an assignment expression
// -----> n is a sub-expression referring to an int object
// -------> Its an lvalue.
// -----> 1 is a sub-expression not referring to an object
// -------> Its an rvalue.
// ---> An rvalue is simply an expression thats not an lvalue.
// ---> Another example:
// -----> Code:
// -------> x[i+1] = abs(p->value);
// -----> x[i+1] is an expression
// -----> abs(p->value) is an expression
// -----> For the assignment to be valid:
// -------> The left operand must be an lvalue.
// ---------> It must refer to an object.
// -------> The right operand can be either an lvalue or rvalue
// ---------> It can be any expression

// -> A look under the hood
// ---> Why make this distinction between lvalues and rvalues?
// ---> Why do language designers made this distinction?
// ---> Answers:
// -----> So that compilers can assume that rvalues don't neccessarily occupy storage.
// -----> This offers considerable freedom in code generation.
// -----> Lets the compiler generate code more efficiently compared to when rvalues are required to have storage

// -> Data storage for rvalues
// ---> For example:
// -----> Code:
// -------> int n;  // a deinition from an integer object named n
// -------> n = 1;  // an assignment expression
// -----> Its possible the compiler might place "1" as named data storage
// -------> As if 1 were an lvalue
// -----> Some machines provide instructions with an immediate operand:
// -------> A source operand value can be part of and instruction
// -------> It doesn't have to be a separate data value.
// -----> In this case:
// -------> The rvalue 1 never appears as an object in the data space.
// -------> Rather, its part of an instruction in the code space.

// -> Must be an lvalue == Can't be an rvalue
// ---> Now, suppose you write:
// -----> Code:
// -------> 1 = n ;  // obviously silly
// -----> This tries to change the value of the integer literal, 1.
// -----> Of course, C++ rejects it as an error.
// -----> But why, exactly?
// -------> Its not because of type (both have type int)
// -------> An assignment assigns a value to an object
// -------> Its left operand must be an lvalue.
// -------> But 1 is not an lvalue its an rvalue.

// -> Recap
// ---> Every expression in C++ is either an lvalue or an rvalue
// ---> In general:
// -----> An lvalue is an expression that refers to an object.
// -----> An rvalue is imply any expression that isn't an lvalue.
// ---> Caveat:
// -----> This is true for non-class types.
// -----> Its not true for class types.

// -> Literals
// ---> Most literals are rvalues, including:
// -----> numeric literals, suach as 3 and 3.141559
// -----> character literals cusch as 'a'
// ---> They dont necessarily occupy data storage.
// ---> However character string literals such as "xyzzy", are levalues
// -----> The occupy data storage.

// -> lvalues Used as rvalues
// ---> An lvalue can appear on either side of an assignment as in:
// -----> int m, n;
// -----> m = n; // OK: m and n are both lvalues
// ---> Obviously you can assign the value in n to the object designated by m.
// ---> This assignment uses the lvalue expression n as an rvalue
// ---> Officially, C++ performs an lvalue to rvalue conversion.

// -> Operands of other operators
// ---> The concepts of lvalue and rvalue apply in all expressions.
// -----> Not just assignment.
// ---> For example, both operands of the binary + operator must be expressions
// -----> Obviously, those expressions must have suitable types
// ---> But eash operand can be either an lvalue or rvalue.
// -----> int x;
// -----> x+2 // OK lvalue + rvalue
// -----> 2+x // OK rvalue + lvalue

// -> What about the result?
// ---> For built-in binary (non-assignment) operators such +:
// -----> The operands may be lvalues or rvalues
// -----> But what about the result
// ---> An expression such as m+n places its result
// -----> not in m
// -----> not in n
// -----> but rather in a compiler-generated temprary object, often a CPU register.
// ---> Such temprary objects are rvalues
// ---> For example:
// -----> Code:
// -------> m + 1 = n;  // error... but why?
// -----> Its an error because m+1 yields an rvalue

// -> Unary * operator
// ---> Unary * yields an lvalue
// ---> A pointer p can point to an object, so "*p" is an lvalue
// ---> Code:
// -----> int a[N];
// -----> int *p = a;
// -----> char *s = nullptr;
// -----> ...
// -----> *p = 3; // OK
// -----> *s = '\0'; // undefined behavior
// ---> Note: lvalue-ness is a compile-time property (evaluated at compile time)
// -----> *s is an lvalue even if s is null
// -----> If s is null, evaluating *s causes undefined behavior.

// -> Data storage for expressions
// ---> Conceptually, rvalues (of non-class type) don't occupy data storage in the object program
// -----> In truth, some might.
// -----> Large temporary objects might not fit on instructions might occupy data storage
// ---> C and C++ insist that you program as if non-class rvalues don't occupy storage.
// ---> Conceptually, lvalues (of any type) occupy data storage
// -----> In truth, the optimizer might eliminate some of them.
// -----> But only when you won't notice.
// ---> C and C++ let you assume that lvalues always do occupy storage.

// -> Rvalues of class type
// ---> Conceptually rvalues of class type do occupy data storage
// ---> Why the difference?
// ---> Consider the following code:
// -----> struct S{ nt x, y;};
// -----> S s1 = {1,4};
// ---> How does the compiler generate code for a line like this?
// -----> int i = s1.y; // read y from lvalue of type S
// -----> The compiler uses a base+offset calculation to access s1.y
// ---> Now consider this code:
// -----> S foo(); // function that return rvalue of type S
// -----> int j = foo().y; // access y member of rvalue
// ---> Again uses a base+offset calculation to access foo().y
// ---> Therefore, the return value of foo() must have a base address.
// -----> Conceptually, any object with an address occupies data storage
// -----> This is why rvalues of class types must be treated differently.

// -> Non-modifiable lvalues
// ---> In fact, not all lvalues can appear on the left of an assignment.
// ---> An lvalue is non-modifiable if it has a const qualified type.
// ---> For example,
// -----> char const name[] = "dan";
// -----> ...
// -----> name[0] = 'D'; // error: name[0] is const
// ---> name[0] is an lvalue, but its non-modifiable
// -----> Each element of a const array is itself const.

// -> Non-modifiable lvalues
// ---> This is actually mentioned in the standard.
// ---> lvalues and rvalues provide a vocabulary for desribing subtle behavioral differences.
// -----> such as between enumeration constant and const objects.
// ---> For example, this max is a constant of an unnamed enumeration type:
// -----> Code:
// -------> enum {MAX=100};
// -----> Unscoped enumeration values implicity convert to integer.
// -----> When MAX appears in an expression, it yields an integer rvalue.
// -----> Thus, you can't assign to it.
// -------> MAX += 3; // error: MAX is an rvalue
// -----> You can't take its address either
// -------> int*p = &MAX; // error: again, MAX is an rvalue
// ---> On the other hand, this MAX is a const-qualified object:
// -----> Code:
// -------> int const MAX = 100;
// -----> When it appears in an expression, its  a non-modifiable lvalue.
// -----> Thus, you can't still assign to it.
// -------> MAX += 3; // error: MAX is an rvalue
// -----> You can't take its address either
// -------> int const*p = &MAX; // OK: MAX is an lvalue

// -> Recap
// ---> This table summaries the behavior of lvalues and rvalues (of non-class type)
// -------------------------------------------------------------------
// |                       | can take the address of | can assign to |
// -------------------------------------------------------------------
// | lvalue                | yes                     | yes           |
// | non-modifiable lvalue | yes                     | no            |
// | (non class) rvalue    | no                      | no            |
// -------------------------------------------------------------------

// -> Reference Types
// ---> The concepts of lvalues and rvalues help explain C++ reference types
// ---> Reference provide an alternative to pointers as a way fo associating names with objects
// ---> C++ libraries often use references instead of pointers as function parameters and return types
// ---> Consider the following code:
// -----> // int i; // define i as an integer object
// -----> // int &ri = i;  // define ri as "reference to int"
// ---> The last line above
// -----> defines ri with type "reference to int" and
// -----> initializes ri to refer to i
// ---> Hence, reference ri is an alias for i.

// -> Reference Types
// ---> Reference and pointers are DIFFERENT things but you can think of them similarly.
// ---> A reference is essentially a pointer that's automatically dereference each time its used.
// ---> You can rewrite most, if not all, code that uses a reference as code that uses a const pointer as in:
// ----------------------------------------------------
// | reference notation | equivalent pointer notation |
// ----------------------------------------------------
// | int &ri = i;       | int * const cpi = &i;       |
// | ri = 4             | *cpi = 4;                   |
// | int j = ri + 2     | int j = *cpi + 2            |
// ----------------------------------------------------
// ---> A reference yields an lvalue.

// -> References and overloaded operators
// ---> What good are references?
// ---> Why not just use pointers?
// ---> Reference can provide friendler function interfaces
// ---> More specifically, C++ has references so that overloaded operators can look just like built-in operators...
// -----> One of the design philosophies in C++:
// -------> Built in types and class types should behave pretty much the same

// -> "Reference to Const" Parameters
// ---> A "reference to const" parameter will accpet an argument that either const or non-const
// -----> R f(T const &t);
// ---> In constrast, a reference (to non-const) parameter will accept only a non-const argument.
// ---> Whe it appears in an expression, a "reference to const" yields a non-modifiable lvalue.
// ---> For the most part, a function declared as:
// -----> R f(T const &t); // by "reference to const"
// -----> has the same outward behavior as a function declared as:
// -----> R f(T t); // by value
// ---> That is, the calls look and act very much the same...
// ---> Either way you declare f, you write the argument expression the same way:
// -----> T x;
// -----> f(x); // by value, or by "reference to const"?
// ---> Either way, calling f can't alter the actual argument, x:
// -----> By value: f has access only to a copy of x, not x itself.
// -----> By "reference to const": f's parameter is declared to be non-modifiable.

// -> Why use "Reference to Const"?
// ---> Why pass by "reference to const" instead by value?
// ---> Passing by "reference to const" might be much more efficient than passing by value.
// ---> It depends on the cost to make a copy.

// -> References and temporaries
// ---> A "pointer to T" can point only to an lvalue of type T
// ---> Similarly, a "reference to T" binds only to an lvalue of type T
// ---> For example these are both compilation errors:
// -----> int *pi = &3;
// -----> int &ri = 3;
// ---> These are also errors:
// -----> int i;
// -----> double *pd = &i; // can't convert pointers
// -----> double &rd = i; // can't bind this, either
// ---> There's an expction to the rule that a reference must bind to an lvalue of the referenced type:
// -----> A "refernce to const T" can bind to an expression x that's not an lvalue of type T ...
// -----> ... if there's a conversion from x's type to T.
// ---> In this case, the compiler creates a temporary object to hold a copy of x converted to T.
// -----> This is so the reference has something to bind to.

// -> References and temporaries
// ---> Given:
// -----> double const &rd = 3;
// ---> When program execution reaches this declaration, the program:
// -----> (1) converts the value of 3 from int to double
// -----> (2) creates a temporary double to hold the coverted result and
// -----> (3) binds rd to the temporary
// ---> When execution leaves the scope containing rd, the program
// -----> (4) destroys the temporary
// ---> This special behavior enables passing by "reference to const" to
// -----> consistently have the same outward behavior as passing by value
// ---> For example:
// -----> long double x;
// -----> void f(long double ld); // by value
// -----> void g(long double const& ld); // by reference to const
// -----> ...
// -----> f(x) // passes a copy of x
// -----> f(1) // passes a copy of 1 converted to long double
// -----> g(x) // passes a reference of x
// -----> g(1) // passes a reference to a temporary containing 1 converted to long double

// -> Two kinds of rvalues
// ---> Conceptually, rvalues of built-in types don't occupy data storage.
// ---> However, the temporary object created in this way does.
// -----> Even if it has a built-in type like long double.
// ---> The temporary is still an rvalue, but it occupies data storage.
// -----> Just like rvalues of class types do.
// ---> In modern C++, there are two kinds of rvalues:
// -----> "Pure rvalues" or "prvalues", which don't occupy data storage.
// -----> "Expiring values" or "xvalues" which do occupy data storage.
// ---> The temporary object is created through a temporary materialization conversion.
// -----> It converts a prvalue into an xvalue.

// -> Mimicking built-in operators
// ---> Recall the beahvior of the built-in + operator
// -----> The operands may be lvalues or rvalues.
// -----> The result is always an rvalue.
// ---> How do you declare an overloaded operator with the same behavior?
// ---> Consider a rudimentary (character) string class with + as a concatenation operator...

// -> References
// ---> C++11 introduced another kind of reference.
// ---> What C++03 calls "references", C++11 calls "lvalue references".
// ---> This distinguishes them from C++11's new "rvalue references".
// ---> Except of the name change, lvalue references in C++1 behave just like references in C++03

// -> Rvalue references
// ---> Whereas an lvalue reference declaration uses the & operator, an rvalue reference uses the && operator
// ---> For example, this declares fi to be an "rvalue reference to int""
// -----> int &&ri = 10;
// ---> You can use "rvalue references" as function parameters and return types, as in"
// -----> double &&f(int &&ri);
// ---> You can also have an "rvalue reference to const" as in:
// -----> in const &&rci = 20;
// ---> rvalue references bind only to rvalues
// ---> This is true even for "rvalue reference to const".
// ---> For example:
// -----> int n=10;
// -----> int &&ri = n; // error: n is an lvalue
// -----> int const&&rj = n; // error: n is an lvalue
// ---> Binding an "rvalue reference" to an rvalue triggers a temporary materialization conversion
// -----> Just like binding an "lvalue reference to const" to an rvalue.

// -> Move operations
// ---> Modern C++ uses rvalue references to implement move operations that can avoid unnecessary copying:
// ---> Copy operations:
// -----> string (string const&) noexcept; // constructor
// -----> string & operator=(string const&) noexcept; //assignment
// ---> Move operations:
// -----> string (string &&) noexcept; // constructor
// -----> string & operator=(string &&) noexcept; //assignment

// -> Move operations
// ---> Given the following objects:
// -----> string s1, s2, s3;
// ---> Assigning from an lvalue results in copy assignment
// ---> The value isn't expiring, so it must be preserved.
// -----> s1=s2; // string::operator=(string const&)
// ---> Assigning from an rvalue results in move assignment.
// ---> The value expires at the end of the statement so it can be safely moved.
// -----> s1=s2+s3 // string::operator=(string &&)

// -> Rvalue references as lvalues
// ---> Binding an "rvalue reference" to an rvalue creates an xvalue.
// ---> However, look inside the function
// ---> Within the function, the variable exists for the durection of the function
// -----> In this context, its an lvalue!
// ---> In general: "if it has a name, its an lvalue"

// -> lvalues as xvalues
// ---> Sometimes it makes sense to move from a lvalue.
// -----> The most common example is swap(...)
// ---> The compiler copy constructs temp because a is not expiring.
// ---> But we know that the next line overwrites a.
// -----> There's no need to preserve the value of a.

// -> lvalues as xvalues
// ---> Its safe to move an lvalue only if its expiring.
// -----> The compiler can't always recognize an expiring lvalue.
// -----> How can you inform the compiler?
// ---> To move from an lvalue, you need to convert it to xvalue.
// -----> In other words convert it to an unamed rvalue reference.
// -----> Thats what std::move does.
// -------> Return values dont have names.
// ---> As programmers, we dont think about xvalues.
// -----> However, this needed by compiler implementors to distinguish this slightly inbetween state the objects can be.

// -> Value Categories
// ---> Modern C++ introduces a more complex categorization of expressions:
// -------------------------
//       expression
//        |      |
//    glvalue  rvalue
//     |    |  |   |
//  lvalue xvalue prvalue
// -------------------------
// ---> The newer categories are:
// -----> glvalue: a "generalized" lvalue
// -----> prvalue: a "pure" rvalue
// -----> xvalue: an "expiring" lvalue

// -> When do lvalues implicitly convert to xvalues?
// ---> In return statements.
// -> Are string literals lvalues?
// ---> Yes. But you can't assign to it because its type is constant characters of arrays.
