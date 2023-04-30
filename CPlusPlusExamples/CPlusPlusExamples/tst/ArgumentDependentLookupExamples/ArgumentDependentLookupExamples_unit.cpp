#include <gtest/gtest.h>

#include <iostream>

using namespace std;

// Taken from Arthur O Dwyer's lecture (ADT Puzzler")

namespace alba {

namespace FunctionNotOnTheCurrentNamespaceStillWorks {
namespace A {
struct DL {
    double x;
};
void f1(DL) {}
template <int I>
void f2(DL) {}
template <int I>
void f3(DL) {}
}  // namespace A

template <int I>
void f3();  // just let the compiler know f3 is a template, even if the function signatures does not match.

TEST(ArgumentDependentLookupExamplesTest, FunctionNotOnTheCurrentNamespaceStillWorks) {
    f1(A::DL{3.14});  // compiles because "f1" is considered because argument is in A.

    // f2(A::DL{3.14}); // does not compile because "f2" because template argument can't be determined
    // f2<0>(A::DL{3.14}); // warns because "f2" is not declared in the scope
    // ---> N4696 14.2/2: For a template-name fo be explicitly qualified by the template arguments, the name must be
    // known to refer to a template.

    f3<0>(A::DL{3.14});  // compiles even though f3 is in a different namespace and does not match (just let the
                         // compiler know f3 is a template).
}
}  // namespace FunctionNotOnTheCurrentNamespaceStillWorks

}  // namespace alba

// Notes:
