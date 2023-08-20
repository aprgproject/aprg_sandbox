#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <optional>
#include <variant>

using namespace std;

// Taken from Ben Deane's talk “Everyday Efficiency- In-Place Construction (Back to Basics-)")

namespace alba {

namespace ClassesWithBasicFunctionWorks {
struct Arg {};

struct S {
    S() { cout << "Default construct\n"; }
    S(Arg) { cout << "Value construct\n"; }
    explicit S(int) { cout << "Explicit value construct (1)\n"; }
    explicit S(int, int) { cout << "Explicit value construct (2)\n"; }
    ~S() { cout << "Destruct\n"; }
    S(S const&) { cout << "Copy construct\n"; }
    S(S&&) { cout << "Move construct\n"; }
    S& operator=(S const&) {
        cout << "Copy assign\n";
        return *this;
    }
    S& operator=(S&&) {
        cout << "Move assign\n";
        return *this;
    }
};

TEST(InPlaceConstructionExamplesTest, ClassesWithBasicFunctionWorks) {
    S s01;              // Default construct
    S s02(Arg{});       // Value construct
    S s03(4);           // Explicit value construct (1)
    S s04(4, 5);        // Explicit value construct (2)
    S s05(s01);         // Copy construct
    S s06(move(s01));   // Move construct
    S s07 = s02;        // Copy construct
    S s08 = move(s02);  // Move construct
    S s09;              // Default construct
    s09 = s03;          // Copy assign
    S s10;              // Default construct
    s10 = s03;          // Copy assign
    // 10 Destructors called
}
}  // namespace ClassesWithBasicFunctionWorks

namespace RvoWorks {
using PhoneBook = map<string, int>;

PhoneBook buildPhoneBook() {
    PhoneBook pb;
    pb.insert(make_pair("Jenny", 8675309));
    return pb;
}

TEST(InPlaceConstructionExamplesTest, RvoWorks) {
    PhoneBook pb = buildPhoneBook();
    // RVO happens in this case
    // RVO is "Return Value Optimization" also known as "Copy Elision".

    // If RVO does not happen, this will be a move.
    // If its Microsoft STL, then its move constructor of map must allocate.
    // -> "Move ctor needs to allocate new sentinel node for the source container,
    // -> because the moved from container must still be a container." Billy O' Neal
}
}  // namespace RvoWorks

namespace NoRvoBecauseNoOpportunity {
string sadFunction(string s) {
    s += "No RVO for you!";
    return s;
}

TEST(InPlaceConstructionExamplesTest, NoRvoBecauseNoOpportunity) {
    string s(sadFunction("Can I please have RVO? "));
    cout << s << "\n";

    // -> You can't RVO a variable if you didn't get the chance to construct it in the first place.
    // -> But the compiler will still move it (Since C++11)
}
}  // namespace NoRvoBecauseNoOpportunity

namespace NoRvoBecauseWrongType {
string sadFunction() {
    string s("No RVO for you!");
    return move(s);
}

TEST(InPlaceConstructionExamplesTest, NoRvoBecauseNoOpportunity) {
    string s(sadFunction());
    cout << s << "\n";

    // -> If its not the correct type, you have to construct the correct type
    // -> An rvalue-ref is not the same type
    // ---> Don't return std::move(...) in most cases - you will get a move when you dont have to
}
}  // namespace NoRvoBecauseWrongType

namespace NoRvoBecauseNotEnoughInfo {
static volatile int happinessValue = 100;
int getHappiness() { return happinessValue; }

string undecidedFunction() {
    string happy("Hooray!");
    string sad("Boo hoo!");
    if (getHappiness() > 50) {
        return happy;
    } else {
        return sad;
    }

    // -> It has to be decidable at construction time.
    // -> Again, the compiler will still move it (Since C++11)
}

TEST(InPlaceConstructionExamplesTest, NoRvoBecauseNotEnoughInfo) {
    string s(undecidedFunction());
    cout << s << "\n";

    // -> If its not the correct type, you have to construct the correct type
    // -> An rvalue-ref is not the same type
    // ---> Don't return std::move(...) in most cases - you will get a move when you dont have to
}
}  // namespace NoRvoBecauseNotEnoughInfo

namespace MultipleExamplesOfRvo {

string directlyReturnTemporary() { return ("I will RVO!"); }

string willThisRvo01() { return ("I will RVO!"); }
string willThisRvo02(bool condition) {
    if (condition) {
        return ("I will RVO!");
    } else {
        return ("I will RVO!");
    }
    // This will RVO because returning a temporary works.
    // This will RVO even in debug builds
}
string willThisRvo03(bool condition, string prohibitingRvo) {
    if (condition) {
        prohibitingRvo = "I won't RVO";
    }
    return prohibitingRvo;

    // This will NOT RVO because there is no opportunity for construction.
}
string willThisRvo04(bool condition) {
    if (condition) {
        return directlyReturnTemporary();
    }
    return "I will RVO as well!";

    // This will RVO (can elide multiple copies).
    // This will RVO in both cases because they are temporaries.
}
string willThisRvo05(bool condition) {
    if (condition) {
        string s("I can RVO!");
        return s;
    }
    return "I can RVO as well!";

    // This depends on your compiler.
    // -> Clang: Yes
    // -> GCC/MSVC: No
}
string willThisRvo06(bool condition) {
    string s("I can't RVO!");
    if (condition) {
        return s;
    }
    return "I can't RVO as well!";

    // This will NOT RVO because compiler can't see it.
    // -> Possibly in the future?
}
string willThisRvo07(bool condition) {
    string s("I won't RVO!");
    return condition ? s : "I won't RVO as well!";

    // This will NOT RVO because we are NOT returning a named variable.
    // This is against the rules (check "RVO rules"): not "the name of a stack variable"
    // We are NOT returning the right type because the TERNARY operator in this case produces an lvalue reference.
    // -> We CAN'T even move here, we have to copy it.
}
string willThisRvo08(bool condition) {
    string s("I will RVO!");
    return condition ? directlyReturnTemporary() : "I will RVO as well!";

    // This will RVO in both cases because they are temporaries.
    // This will RVO because both sides of TERNARY operator are rvalues, so overall type is an rvalue.
    // -> So we are returning temporary.
}
string willThisRvo09() {
    string s("I will RVO!");
    s = "I will RVO! But I changed.";
    return s;

    // This will RVO because we are returning a named variable.
    // This is plain NRVO (Named Return Value Optimization).
}
string willThisRvo10() {
    string s("I can RVO!");
    return (s);

    // The parenthesis makes it an expression.
    // However it should be allowed according to the standard.
    // But making this RVO fails on GCC.
    // This depends on your compiler.
    // -> Clang/MSVC: Yes
    // -> GCC: No
}

struct MoveOnlyConstExprObject {
    constexpr MoveOnlyConstExprObject() : x{0} {}
    constexpr MoveOnlyConstExprObject(MoveOnlyConstExprObject&&) : x{1} {}
    int x;
};

MoveOnlyConstExprObject willThisRvo11() {
    MoveOnlyConstExprObject object;
    return object;

    // It depends.
    // -> The standards says you wont get copy elision on constexpr context.
    // ---> Possibly might be changed int the future.
    // -> It depends on how aggressive the compiler will be on putting it on constexpr context.
    // ---> GCC: Is aggressive on constexpr, and will always get the move here.
    // ---> Clang: Clang is less aggressive.
    // -----> if you make the named variable constexpr -> move will happen
    // -----> if you make the named variable auto -> copy elision will happen
}

TEST(InPlaceConstructionExamplesTest, MultipleExamplesOfRvo) {
    string s01(willThisRvo01());                   // RVO is successful
    string s02(willThisRvo02(true));               // RVO is successful
    string s03(willThisRvo02(false));              // RVO is successful
    string s04(willThisRvo03(true, "Stop RVO"));   // RVO is unsuccessful
    string s05(willThisRvo03(false, "Stop RVO"));  // RVO is unsuccessful
    string s06(willThisRvo04(true));               // RVO is successful
    string s07(willThisRvo04(false));              // RVO is successful
    string s08(willThisRvo05(true));               // can RVO
    string s09(willThisRvo05(false));              // can RVO
    string s10(willThisRvo06(true));               // RVO is unsuccessful
    string s11(willThisRvo06(false));              // RVO is unsuccessful
    string s12(willThisRvo07(true));               // RVO is unsuccessful
    string s13(willThisRvo07(false));              // RVO is unsuccessful
    string s14(willThisRvo09());                   // RVO is successful
    string s15(willThisRvo10());                   // RVO is successful
    MoveOnlyConstExprObject o01(willThisRvo11());  // It depends
}
}  // namespace MultipleExamplesOfRvo

namespace VectorPushBackVsEmplaceBack {
TEST(InPlaceConstructionExamplesTest, VectorPushBackVsEmplaceBack) {
    vector<string> v;
    string s("Content1");

    string sTemp1(s);
    v.push_back(move(sTemp1));
    string sTemp2(s);
    v.emplace_back(move(sTemp2));
    // No difference, except emplace_back returns a reference on the created object by definition

    auto carray = "Content2";
    v.push_back(carray);     // may copy/move from constructed string from carray
    v.emplace_back(carray);  // assured in-place construction based from carray
    // -> Some people: "Just always use emplace_back because its certain more powerful that push back"
    // ---> "I don't like that view, I don't login to my computer as root."
    // ---> "I like to use the least powerful thing that is available to me."
    // ---> "It helps the reader of my code, theres gonna be a copy here and I can't do anything better."

    string& s2 = v.emplace_back();  // first default construct in the vector
    // after emplace_back we can mutate s2
    // emplace_back takes a parameter pack and parameter packs can be empty
    // emplace_back does perfect forwarding. It can call explicit constructors;
    // v.push_back(); // cannot default construct because a parameter needs to be passed
}
}  // namespace VectorPushBackVsEmplaceBack

namespace CopyingToAVectorFromAnArrayOfCustomArguments {
using Arg = ClassesWithBasicFunctionWorks::Arg;
using S = ClassesWithBasicFunctionWorks::S;

TEST(InPlaceConstructionExamplesTest, CopyingToAVectorFromAnArrayOfCustomArguments) {
    array<Arg, 3> a = {Arg{}, Arg{}, Arg{}};

    vector<S> v;
    v.reserve(3);
    copy(a.cbegin(), a.cend(), back_inserter(v));
    // What does back_insert_iterator do here?
    // -> back_inserter is gonna call push_back
    // ---> So each item were gonna get a construct, a move, and a destruct
}
}  // namespace CopyingToAVectorFromAnArrayOfCustomArguments

namespace CopyingToAVectorFromAnArrayUsingCustomArguments {
using Arg = ClassesWithBasicFunctionWorks::Arg;
using S = ClassesWithBasicFunctionWorks::S;

TEST(InPlaceConstructionExamplesTest, CopyingToAVectorFromAnArrayOfInts) {
    array a = {1, 2, 3, 4, 5};

    vector<S> v;
    v.reserve(a.size());
    // copy(a.cbegin(), a.cend(), back_inserter(v));  // compiler failure
    // Compiler is angry at us because push_back does not work on constructors (explicit constructor)

    transform(a.cbegin(), a.cend(), back_inserter(v), [](int i) { return S(i); });
    // -> Does push_back underneath
    // ---> Results to: Construction of temporary, move construction to vector, and destruction of temporary
    // -> This is the best thing we can do right now.
    // -> The library doesn't have back_emplacer.
    // ---> The back_emplacer guarantees that we will have in-place construction.
}
}  // namespace CopyingToAVectorFromAnArrayUsingCustomArguments

namespace AvoidUnecessaryMovesInConstruction {
TEST(InPlaceConstructionExamplesTest, AvoidUnecessaryMovesInConstruction) {
    vector<string_view> tokens;

    string_view newToken;
    tokens.emplace_back(move(newToken));  // move in unnecessary
    // move here prevents in-place construction
}
}  // namespace AvoidUnecessaryMovesInConstruction

namespace AvoidSuperfluousMovesDueToExplicitConstructorCall {
TEST(InPlaceConstructionExamplesTest, AvoidSuperfluousMovesDueToExplicitConstructorCall) {
    vector<string> tokens;

    tokens.emplace_back(string(3, 'A'));  // Explicitly calling the string constructor in unnecessary
    // Move is done and NOT in-place construction

    tokens.emplace_back(3, 'A');  // Construction arguments in emplace_back results to in-place construction
}
}  // namespace AvoidSuperfluousMovesDueToExplicitConstructorCall

namespace CreatingAVectorOfPairs {
struct Value {
    Value(int, string, double) {}
};
TEST(InPlaceConstructionExamplesTest, CreatingAVectorOfPairs) {
    vector<pair<int, Value>> v;

    v.push_back(make_pair(1, Value{42, "hello", 3.14}));  // This is no good

    v.emplace_back(make_pair(1, Value{42, "hello", 3.14}));  // This is no better

    // -> piecewise_construct to the rescue
    // ---> pair has a constructor that will handle your multi argument construtor
    // ---> piecewise_construct_t is a tag type
    // ---> forward tuples to emplace_back to ensure in-place construction

    v.emplace_back(piecewise_construct, forward_as_tuple(1), forward_as_tuple(42, "hello", 3.14));
    // Perfect forwarding and in-place construction
}
}  // namespace CreatingAVectorOfPairs

namespace InitializerListHasConstStorageSoWeCantLocalInitializerLists {
template <int... ints>
auto f() {
    return initializer_list<int>{ints...};  // returns a temporary object
}
void fineFunction() {
    for (int i : {1, 2, 3}) {
        cout << i << ", ";
    }
    cout << "\n";
}
void fineUntilItExplodesFunction() {
    for (int i : f<1, 2, 3>()) {
        cout << i << ", ";
    }
    cout << "\n";
}
TEST(InPlaceConstructionExamplesTest, InitializerListHasConstStorageSoWeCantLocalInitializerLists) {
    fineFunction();  // Prints 1, 2, 3,

    fineUntilItExplodesFunction();  // Prints garbage values
    // It has garbage values because f returns using a temporary object.
}
}  // namespace InitializerListHasConstStorageSoWeCantLocalInitializerLists

namespace InitializerListHasConstStorageSoWeCantUseMoveOnlyObjects {
TEST(InPlaceConstructionExamplesTest, InitializerListHasConstStorageSoWeCantUseMoveOnlyObjects) {
    //  vector<unique_ptr<int>> v = {make_unique<int>(1), make_unique<int>(2)};  // cannot compile, needs copy
}
}  // namespace InitializerListHasConstStorageSoWeCantUseMoveOnlyObjects

namespace InitializerListWithMap {
using Arg = ClassesWithBasicFunctionWorks::Arg;
using S = ClassesWithBasicFunctionWorks::S;

TEST(InPlaceConstructionExamplesTest, InitializerListWithMap) {
    using M = map<int, S>;

    M m{{0, Arg{}}};  // 1 value construction, 1 copy construction, 2 destruction
}
}  // namespace InitializerListWithMap

namespace PuttingThingsWithMapUsingBracketOperator {
using Arg = ClassesWithBasicFunctionWorks::Arg;
using S = ClassesWithBasicFunctionWorks::S;

TEST(InPlaceConstructionExamplesTest, PuttingThingsWithMapUsingBracketOperator) {
    using M = map<int, S>;
    M m;

    m[0] = Arg{};  // 1 value construction, 1 default construction, 1 move assignment, 2 destruction
}
}  // namespace PuttingThingsWithMapUsingBracketOperator

namespace PuttingThingsWithMapUsingInsert {
using Arg = ClassesWithBasicFunctionWorks::Arg;
using S = ClassesWithBasicFunctionWorks::S;

TEST(InPlaceConstructionExamplesTest, PuttingThingsWithMapUsingInsert) {
    using M = map<int, S>;
    M m;

    m.insert(make_pair(0, Arg{}));  // 1 value construction, 1 destruction
}
}  // namespace PuttingThingsWithMapUsingInsert

namespace PuttingThingsWithMapUsingEmplace {
using Arg = ClassesWithBasicFunctionWorks::Arg;
using S = ClassesWithBasicFunctionWorks::S;

TEST(InPlaceConstructionExamplesTest, PuttingThingsWithMapUsingEmplace) {
    using M = map<int, S>;
    M m;

    m.emplace(0, Arg{});  // 1 value construction, 1 destruction
}
}  // namespace PuttingThingsWithMapUsingEmplace

namespace PuttingThingsWithMapWithDefaultConstruction {
using Arg = ClassesWithBasicFunctionWorks::Arg;
using S = ClassesWithBasicFunctionWorks::S;

TEST(InPlaceConstructionExamplesTest, PuttingThingsWithMapWithDefaultConstruction) {
    using M = map<int, S>;
    M m;

    m[0];               // 1 default construction, 1 destruction, dont do this please
    m.emplace(1, S{});  // 1 default construction, 1 move construction, 2 destructions, still not good
    m.emplace(piecewise_construct, forward_as_tuple(2), forward_as_tuple());
    // 1 default construction, 1 destruction
}
}  // namespace PuttingThingsWithMapWithDefaultConstruction

namespace PuttingThingsWithMapWithReturnOfAFunctionCall {
using Arg = ClassesWithBasicFunctionWorks::Arg;
using S = ClassesWithBasicFunctionWorks::S;

S getS() { return S{1}; }

TEST(InPlaceConstructionExamplesTest, PuttingThingsWithMapWithReturnOfAFunctionCall) {
    using M = map<int, S>;
    M m;

    m.emplace(0, getS());  // 1 value construction, 1 move construction, 2 destructions, still not good
    m.emplace(piecewise_construct, forward_as_tuple(1), forward_as_tuple(getS()));
    // 1 value construction, 1 move construction, 2 destructions, still not good

    // Check Superconstructing super elider, Arthur O' Dwyer
}
}  // namespace PuttingThingsWithMapWithReturnOfAFunctionCall

namespace OptionalConstruction {
using Arg = ClassesWithBasicFunctionWorks::Arg;
using S = ClassesWithBasicFunctionWorks::S;

TEST(InPlaceConstructionExamplesTest, OptionalConstruction) {
    using OptionalS = optional<S>;

    OptionalS opt1 = Arg{};            // 1 value construction, 1 destruction, good
    OptionalS opt2 = S{1};             // 1 value construction, 1 move construction, 2 destructions, not good
    OptionalS opt3(in_place, 1);       // 1 value construction, 1 destruction, good
    OptionalS opt4(make_optional(1));  // 1 value construction, 1 destruction, good
}
}  // namespace OptionalConstruction

namespace OptionalAssignment {
using Arg = ClassesWithBasicFunctionWorks::Arg;
using S = ClassesWithBasicFunctionWorks::S;

TEST(InPlaceConstructionExamplesTest, OptionalAssignment) {
    using VariantS = optional<S>;
    VariantS opt1, opt2, opt3;

    opt1 = Arg{};     // 1 value construction, 1 destruction, good
    opt2 = S{1};      // 1 value construction, 1 move construction, 2 destructions, not good
    opt3.emplace(1);  // 1 value construction, 1 destruction, good
}
}  // namespace OptionalAssignment

namespace VariantConstruction {
using Arg = ClassesWithBasicFunctionWorks::Arg;
using S = ClassesWithBasicFunctionWorks::S;

TEST(InPlaceConstructionExamplesTest, VariantConstruction) {
    using VariantS = variant<int, S>;

    VariantS opt1 = Arg{};                // 1 value construction, 1 destruction, good
    VariantS opt2 = S{1};                 // 1 value construction, 1 move construction, 2 destructions, not good
    VariantS opt3(in_place_type<S>, 1);   // 1 value construction, 1 destruction, good
    VariantS opt4(in_place_index<1>, 1);  // 1 value construction, 1 destruction, good
}
}  // namespace VariantConstruction

namespace VariantAssignment {
using Arg = ClassesWithBasicFunctionWorks::Arg;
using S = ClassesWithBasicFunctionWorks::S;

TEST(InPlaceConstructionExamplesTest, VariantAssignment) {
    using VariantS = variant<int, S>;
    VariantS opt1, opt2, opt3;

    opt1 = Arg{};        // 1 value construction, 1 destruction, good
    opt2 = S{1};         // 1 value construction, 1 move construction, 2 destructions, not good
    opt3.emplace<S>(1);  // 1 value construction, 1 destruction, good
    opt3.emplace<1>(1);  // 1 value construction, 1 destruction, good
}
}  // namespace VariantAssignment

}  // namespace alba

// Notes:

// -> Are moves cheap or not?
// ---> Observation
// -----> Moving from a string usually isn't any faster than copying from it.
// -----> If you doubt this, ask yourself why the small string optimization exists in the first place.
// -------> Most strings are small and they go on the "small strings buffer"
// -------> Moves only matter for objects on the heap.
// -------> This results on copy and zeroing out (make the length 0) the "moved-from" string.
// -----> http://quick-bench.com/eb54Wv8Bmvr08frpgtgFOIxQqa4
// -----> https://quick-bench.com/q/NhgKqpmyRprciBpLnqAOocx7nII

// -> Why is RVO so important?
// ---> Because move aren't necessarily cheap

// -> What is Copy Elision aka RVO?
// ---> Perhaps the most important optimization the compiler does.

// -> RVO in Pictures
// ---> When a caller calls into a callee,
// -----> there this hidden parameter on the stack which is the address of the return value.
// ---> If the callee can return/construct directly in the caller stack frame
// -----> there is no need to construct and then copy to the point of return

// -> When can RVO not apply?
// ---> How can we make RVO? And how can we accidentally inhibit RVO?
// ---> Two things to consider:
// -----> What the standard says
// -----> Whats possible
// ---> RVO rules: what is returned has to be either?
// -----> a temporary (prvalue) - guaranteed in C++17 (standards mentions this)
// -----> the name of a stack variable (standards mentions this)
// ---> RVO ability: Sometimes, the callee can't construct the object in place.
// -----> If there is no opportunity to (see example above)
// -------> You can't RVO a variable if you didn't get the chance to construct it in the first place.
// -------> But the compiler will still move it (Since C++11)
// -----> If its not the right type (see example above)
// -------> If its not the correct type, you have to construct the correct type
// -------> An rvalue-ref is not the same type
// ---------> Don't return std::move(...) in most cases - you will get a move when you dont have to
// -----> If the callee doesn't know enough (see example above)
// ---------> It has to be decidable at construction time.
// ---------> Again, the compiler will still move it (Since C++11)

// -> Beware of superfluous "std::move"s
// ---> In some cases it removes NRVO.

// -> Putting stuff into a vector
// ---> Should you use push_back or should you use emplace_back? How should you use them?

// -> Definitions
// ---> push_back
// -----> void push_back(T const& x);
// -----> void push_back(T && x);
// ---> emplace_back
// -----> template <class... Args> void emplace_back(Args&&... args);
// ---> push_back is overloaded with lvalue and rvalue references
// ---> emplace_back uses forwarding references

// -> Some people: "Just always use emplace_back because its certain more powerful that push back"
// ---> "I don't like that view, I don't login to my computer as root."
// ---> "I like to use the least powerful thing that is available to me."
// ---> "It helps the reader of my code, theres gonna be a copy here and I can't do anything better."

// -> back_inserter
// ---> Does push_back underneath
// -----> Results to: Construction of temporary, move construction to vector, and destruction of temporary
// ---> This is the best thing we can do right now.
// ---> The library doesn't have back_emplacer.
// -----> The back_emplacer guarantees that we will have in-place construction.

// -> Creating a vector of pairs
// ---> Sometimes, we use a sorted vector of pair as replacement for map.
// ---> What do you do if part of your pair has a multi-argument constructor?
// -----> piecewise_construct to the rescue
// -------> pair has a constructor that will handle your multi argument construtor
// -------> piecewise_construct_t is a tag type
// -------> forward tuples to emplace_back to ensure in-place construction

// -> Recommendations (on push_back vs emplace_back)
// ---> push_back is perfectly fine for rvalues
// ---> use emplace_back only when you need its powers
// -----> in-place construction (including nullary construction)
// -----> a reference to what's added (C++17)
// ---> never pass an explicit temporary to emplace_back
// ---> use piecewise_construct/forward_as_tuple to forward args through pair.

// -> What is an initializer_list
// ---> When you write:
// -----> std::vector<int> v{1, 2, 3};
// ---> Its as if you wrote (pseudo code):
// -----> const in a[] = {1, 2, 3};
// -----> std::vector<int> v = std::initializer_list<int>(a, a+3);
// -------> Note this is copying (not moving)

// -> Initializer list are so convenient!
// ---> But typically results to multiple constructs, copies (not moves), destructs
// ---> Compared to in-place construction which are only constructs
// ---> Initializer lists are broken!
// -----> "Initializer lists are boken, lets fix them" - Jason Turner, C++ Now 2018

// -> Caveat construction
// ---> std::string is an interesting case here. We intuit/are taught:
// -----> "Delay construction, allocation, etc, as late as possible"
// -------> But that might hurt us with std::string.
// -------> As soon as string/string_view get converted to const char*
// ---------> somewhere down the line it will have to call strlen.

// -> Recommendations (on initializer_list)
// ---> use initializer_list only for literal types
// ---> consider using array and manually moving?
// ---> probably don't use initializer_list for anything that'll get run more than once
// ---> wait for in_place_t constructor on vector
// ---> wait for more work on std::initializer_list
// ---> watch Jason Turner's talk

// -> Putting stuff into a map (or other associative container)
// ---> It's a bit complicated.

// -> initializer_list with map
// ---> Its perfectly possible to initialize a map with an initializer_list
// -----> Use aggregate initialization with pair. Is this good?

// -> Enough initializing, how about putting things into a map?
// ---> The easy way: operator[]
// ---> Use piecewise_construct with forward_as_tuple
// -----> Tuples are allowed to be empty!
// -----> Yes, we can also use this for more-than-one-arg constructors.

// -> C++17: insert or assign
// ---> Of course, insert/emplace and operatorp[ actually do different things.
// ---> What do you do if you want to insert or assign if the element is already there

// -> In case you're not keeping cout
// ---> We now have at least (3-4-5) N (>5) different interface styles for putting things in a map...
// ----->  insert takes a value_type (aka pair)
// -------> or an iterator pair
// -------> or an initializer_lilst
// -------> or a node
// -----> emplace takes a parameter pack
// -----> try_emplace takes a key and parameter pack
// -----> insert_or_assign takes a key and [something convertible to] a value
// -------> so does operator[] (without forwarding)
// -----> marge takes another map...
// ---> See also: "A Clean and Minimal Map API" - Chancler Carruth, C++ Now 2019

// -> emplace & emplace_back epilogue
// ---> What to do if mapped_type is an aggregate? You want the rule of zero
// -----> C++20 P0960: Aggregate initialization with parentheses
// -----> This means forward_as_tuple(...) will now work with aggregates.

// -> Recommendations (for using a map)
// ---> Initialization: consider for_each_n_args
// ---> You can use insert with make_pair and implicit consturction
// -----> But don't use call-site explicit consturction
// ---> Use emplace but beware of explicit construction
// -----> try_emplace takes a key and parameter pack
// ---> Use piecewise_construct for other that single-arg consturction
// ---> Use operator[] only when you know the key exists
// ---> Adpot insert_or_assign when you can
// ---> Consider with_result_of
// ---> Aggregates will suck until C++20
// -----> Or, use a non-standard map with a better API.

// -> Putting stuff into other things (optional, variant, any)
// ---> They have a tag type which takes can piecewise construct.
// -----> They can have in-place construction

// -> Recommendations (about variant)
// ---> always be explicit about types
// ---> use in_place_type or in_place_index construictor
// ---> us emplace<T> or emplace <I>
// ---> avoid operator= (except on actual variant-to-variant)

// -> Recommendations (overall)
// ---> Think about copies and moves
// ---> Moves aren't free and may not be cheap.
// ---> Usually, in-place construction is prefereable. And it is (nearly?) always possible.
// ---> Know how RVO works and check that the compiler is doing it when you think it is
// ---> Study the interfaces of the containers you're using
// ---> Don't be afraid to use push_back
// ---> Beware of initializer_list

// Quotes:

// -> What happens when we move something?
// ---> "Mov'd! In good time! Let him that mov'd you hither remove you hence."
// ----->  William Shakespeare, The Taming of the Shrew

// -> Copy Elision aka RVO
// ---> "If you will, lead these graces to the grave and leave the world no copy."
// -----> William Shakespeare, Twelfth Night or What You Will

// -> Putting stuff into a vector
// ---> "Didst thou not say, when I did push thee back --
// ---> Which was when I perceived thee -- that thou camest
// ---> From good descending?"
// -----> William Shakespeare, Pericles

// -> initializer_list
// ---> "I fear these stubborn lines lack power to move"
// -----> William Shakespeare, Love's Labours Lost

// -> Putting stuff into a map (or other associative container)
// ---> "A plague upon it! I have forgot the map."
// -----> William Shakespeare, Henry IV Part I

// -> Putting stuff into other things (optional, variant, any)
// ---> "There's more depends on this than on the value."
// -----> William Shakespeare, The Merchant of Venice.

// -> Final guidelines and recommendations
// ---> "Share the advice betwixt you; if both gain all,
// ---> The gift doth stretch itself as 'tis receiv'd
// ---> And is enough for both."
// -----> William Shakespeare, All's Well That Ends Well
