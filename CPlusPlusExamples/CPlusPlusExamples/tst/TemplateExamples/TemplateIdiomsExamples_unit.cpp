#include <Common/Macros/AlbaMacros.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace alba::typeHelper;
using namespace std;

// Taken from Arthur O'Dwyer's lecture ("Template Normal Programming")

namespace alba {

namespace TemplateParametersCanBeOmittedOnClassTemplates {

template <typename Element>
struct TreeIterator {
    // Element can be omitted
    TreeIterator& operator++() {
        cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
        return *this;
    }
};

TEST(TemplateIdiomsExamplesTest, TemplateParametersCanBeOmittedOnClassTemplates) {
    TreeIterator<int> iterator;
    ++iterator;  // still works
}

// -> Template parameters can be omitted on class templates:
// ---> Inside the definition of a class template, the base template-name can be used a type-name,
// -----> in which case its basically as if you <all the template-parameters> after it
// ---> So this is fine, and helps cut down on repetition. I recommend it.

}  // namespace TemplateParametersCanBeOmittedOnClassTemplates

namespace DependentNamesShouldBeCalledWithTemplates {

struct S1 {
    static constexpr int A = 0;
};
struct S2 {
    template <int N>
    static void A(int) {
        cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
    }
};
struct S3 {
    template <int N>
    struct A {
        A(int) {}
    };
};

template <typename T>
void foo() {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
    // T::A<0>(5);  // for S1
    // T::template A<0>(5);  // for S2
    // typename T::template A<0>(5);  // for S3
}

TEST(TemplateIdiomsExamplesTest, DependentNamesShouldBeCalledWithTemplates) {
    // foo<S1>();
    // foo<S2>();
    // foo<S3>();
}

// -> Dependent names
// ---> Why typename or ".template" or "::template"?
// -----> C++'s grammar is not context-free.
// -----> Normally, in order to parse a function definition,
// -------> you need to know something of the context in which that function is being defined.
// -----> So "typename" is there to notify that we are accessing a type in the template.
// -----> By default, C++ will assume that any name whose lookup is dependent on a template parameter refers to
// -------> a non-type, non-template, plain old variable/function/object-style entity.

}  // namespace DependentNamesShouldBeCalledWithTemplates

namespace TagDispatchIdiomWorks {

template <typename Element>
struct TreeIterator {
    using SupportsPlusType = std::false_type;
};

template <typename Element>
struct VectorIterator {
    using SupportsPlusType = std::true_type;
};

template <typename Iterator>
Iterator advanceImpl(Iterator begin, int, std::false_type) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
    // for (int i = 0; i < n; ++i) ++begin; // sample implementation
    return begin;
}

template <typename Iterator>
Iterator advanceImpl(Iterator begin, int, std::true_type) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
    // begin += n;  // sample implementation
    return begin;
}

template <typename Iterator>
auto advance(Iterator begin, int n) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
    return advanceImpl(begin, n, typename Iterator::SupportsPlusType{});  // why typename? (see Notes)
}

TEST(TemplateIdiomsExamplesTest, TagDispatchIdiomWorks) {
    TreeIterator<int> treeIterator;
    VectorIterator<int> vectorIterator;

    advance(treeIterator, 5);    // Correctly maps to tree iterator and false_type
    advance(vectorIterator, 5);  // Correctly maps to tree iterator and true_type
}

// Note: This works because we can overload on SupportsPlusType.

}  // namespace TagDispatchIdiomWorks

namespace TagDispatchIdiomWithIteratorTraitsWorks {

template <typename Element>
struct TreeIterator {};

template <typename Element>
struct VectorIterator {};

template <typename Iterator>
struct IteratorTraits {
    using SupportsPlusType = std::false_type;  // false by default
};

template <typename Element>
struct IteratorTraits<VectorIterator<Element>> {
    using SupportsPlusType = std::true_type;
};

template <typename Iterator>
Iterator advanceImpl(Iterator begin, int, std::false_type) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
    // for (int i = 0; i < n; ++i) ++begin; // sample implementation
    return begin;
}

template <typename Iterator>
Iterator advanceImpl(Iterator begin, int, std::true_type) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
    // begin += n;  // sample implementation
    return begin;
}

template <typename Iterator>
auto advance(Iterator begin, int n) {
    cout << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
    return advanceImpl(begin, n, typename IteratorTraits<Iterator>::SupportsPlusType{});  // why typename? (see Notes)
}

TEST(TemplateIdiomsExamplesTest, TagDispatchIdiomWithIteratorTraitsWorks) {
    TreeIterator<int> treeIterator;
    VectorIterator<int> vectorIterator;

    advance(treeIterator, 5);    // Correctly maps to tree iterator and false_type
    advance(vectorIterator, 5);  // Correctly maps to tree iterator and true_type
}

// Note: This works because we can overload on SupportsPlusType.
// Best practice is to follow STL, have "_t" on the template name for the type.

}  // namespace TagDispatchIdiomWithIteratorTraitsWorks

namespace CrtpWorks {

template <typename CatOrDog>
struct DoubleSpeaker {
    void speakTwice() {
        CatOrDog* catOrDog = static_cast<CatOrDog*>(this);
        catOrDog->speak();
        catOrDog->speak();
    }
};

struct Cat : public DoubleSpeaker<Cat> {
    void speak() { cout << "Meow!\n"; }
};

struct Dog : public DoubleSpeaker<Dog> {
    void speak() { cout << "Woof!\n"; }
};

TEST(TemplateIdiomsExamplesTest, CrtpWorks) {
    Cat cat;
    Dog dog;

    cat.speakTwice();
    dog.speakTwice();
}

// -> This implementation falls a fould of "DRY": Don't Repeat Yourself
// ---> We really want to factor out the repeated speaktwice() code into a common base class
// ---> Lets call that common base class DoubleSpeaker

// -> Using polymorphism will cause virtual method calls which can be costly.
// ---> We want to just do the right thing, statically.
// ---> Plus, polymorphism is viral.
// ---> CRTP is another way to do this without the virtual dispatch.

}  // namespace CrtpWorks

}  // namespace alba

// Collect all notes here:
// General Notes:

// -> Template parameters can be omitted on class templates:
// ---> Inside the definition of a class template, the base template-name can be used a type-name,
// -----> in which case its basically as if you <all the template-parameters> after it
// ---> So this is fine, and helps cut down on repetition. I recommend it.

// -> Dependent names
// ---> Why typename or ".template" or "::template"?
// -----> C++'s grammar is not context-free.
// -----> Normally, in order to parse a function definition,
// -------> you need to know something of the context in which that function is being defined.
// -----> So "typename" is there to notify that we are accessing a type in the template.
// -----> By default, C++ will assume that any name whose lookup is dependent on a template parameter refers to
// -------> a non-type, non-template, plain old variable/function/object-style entity.
