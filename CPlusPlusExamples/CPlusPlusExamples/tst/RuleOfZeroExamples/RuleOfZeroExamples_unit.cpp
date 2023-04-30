#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>

using namespace std;

// Taken from Arthur O Dwyer's lecture ("RAII and the Rule of Zero")

namespace alba {

namespace {

struct OperationPrinter {
    OperationPrinter() { cout << "Default constructor\n"; }
    OperationPrinter(int) { cout << "Value constructor\n"; }
    ~OperationPrinter() { cout << "Destructor\n"; }
    OperationPrinter(OperationPrinter const&) { cout << "Copy constructor\n"; }
    OperationPrinter(OperationPrinter&&) noexcept { cout << "Move constructor\n"; }
    OperationPrinter& operator=(OperationPrinter const&) {
        cout << "Copy assignment\n";
        return *this;
    }
    OperationPrinter& operator=(OperationPrinter&&) {
        cout << "Move assignment\n";
        return *this;
    }
    //    OperationPrinter& operator=(OperationPrinter) noexcept {
    //        cout << "Copy by value assignment\n";
    //        // Only need one assignment function
    //        // This works similarly with the copy-and-swap idiom.
    //        return *this;
    //    }
};

// swap NaiveIntVector vectors

class NaiveIntVector {
public:
    NaiveIntVector() : m_ptr(nullptr), m_size(0) {}
    ~NaiveIntVector() { delete[] m_ptr; }
    NaiveIntVector(NaiveIntVector const& rightHandSide) {
        m_size = rightHandSide.m_size;
        m_ptr = new int[m_size];
        copy(rightHandSide.m_ptr, rightHandSide.m_ptr + m_size, m_ptr);
    }
    NaiveIntVector(NaiveIntVector&& rightHandSide) noexcept {
        cout << "Move constructor\n";
        m_ptr = exchange(rightHandSide.m_ptr, nullptr);
        m_size = exchange(rightHandSide.m_size, 0);
    }
    NaiveIntVector& operator=(NaiveIntVector const& rightHandSide) {
        cout << "Copy assignment\n";
        NaiveIntVector copy(rightHandSide);
        swap(copy, *this);  // The copy-and-swap idiom (to be safe for "self assignment").
        return *this;
    }
    NaiveIntVector& operator=(NaiveIntVector&& rightHandSide) {
        cout << "Move assignment\n";
        NaiveIntVector copy(move(rightHandSide));  // calls the move constructor
        // std::move is needed (because rvalue has a name)
        swap(copy, *this);  // The copy-and-swap idiom (to be safe for "self assignment").
        return *this;
    }

    //    NaiveIntVector& operator=(NaiveIntVector copy) noexcept {
    //        cout << "Copy by value assignment\n";
    //        // This can be noexcept because the copying occurs outside of this function.
    //        // Only need one assignment function
    //        // This works similarly with the copy-and-swap idiom.
    //        swap(copy, *this);
    //        return *this;
    //    }

    void push_back(int const newValue) {
        int* newPtr = new int[m_size + 1];  // This is inefficient because it rellocates every time.
        copy(m_ptr, m_ptr + m_size, newPtr);
        delete[] m_ptr;  // delete does not crash even if m_ptr is empty
                         // (see https://en.cppreference.com/w/cpp/language/delete)
        m_ptr = newPtr;
        m_ptr[m_size++] = newValue;
    }

    friend void swap(NaiveIntVector& first, NaiveIntVector& second) noexcept {
        // STL algorithms might call this
        std::swap(first.m_ptr, second.m_ptr);
        std::swap(first.m_size, second.m_size);
    }

private:
    int* m_ptr;
    size_t m_size;
};

}  // namespace

TEST(RuleOfZeroExamplesTest, InitializationIsNotAssignment) {
    OperationPrinter object1;

    // Even though "=" operation is used:
    OperationPrinter object2 = 3;        // Calls the value constructor
    OperationPrinter object3 = object1;  // Calls the copy constructor

    object3 = object2;  // now it calls the copy assignment (operator=);
}

TEST(RuleOfZeroExamplesTest, NaiveIntVectorPushBackWorks) {
    NaiveIntVector vector1;

    vector1.push_back(1);
    vector1.push_back(2);
    vector1.push_back(3);
}

}  // namespace alba

// -> Outline
// ---> Motivating the special members and the Rule ofThree
// ---> Curious pitfall with (indirect) self copy
// ---> RAII and exception safety
// ---> Deleting, defaulting and the Rule of Zero
// ---> Move semantics and the Rule of Five (or Four)
// ---> Recap and examples of RAII types

// -> Classes that manage resources
// ---> A "resource" for our purposes, is anything that requires special (manual) management.
// ---> C++ programs can manage many different kinds of "resources".
// -----> Allocated memory (malloc/free, new delete, new[]/delete[])
// -----> POSIX file handles (open/close)
// -----> C FILE handles (fopen/fclose)
// -----> Mutex locks (pthread_mutex_lock/pthread_mutex_unlock)
// -----> C++ threads (spawn/join)
// -----> Objective-C resource-counted objects (retain/release)

// -> Classes that manage resources
// ---> Some of these resources are intinsically "unique" (mutex locks)
// -----> and some are "duplicable" (heap allocations, POSIX file handles).
// -----> For our purposes so far, this doesn't really matter.
// ---> What matters is that there is some explicit action that needs to be taken
// -----> by the program in order to free the resource
// ---> We'll stick with the callsing boring example of heap allocation.

// -> The Rule of Three
// ---> This is needed if your class directly manages some kind of resource (such as new'ed pointer),
// -----> then you almost certainly need to hand-write three special member functions:
// -------> A "destructor" to free the resource
// -------> A copy constructor to opy the resource
// -------> A "copy assignment operator" to free the left hand resource and copy the right hand one.
// ---> Use the copy-and-swap idiom to implement assignment.
// ---> Guideline: You need to write this if the destructor needs some sort of cleanup.

// -> Why copy-and-swap?
// ---> Alternative is not safe for "safe assignment":
// -----> NaiveIntVector& operator=(NaiveIntVector const& rightHandSide) {
// ----->     delete[] ptr_;
// ----->     ptr_ = new int[rightHandSide.m_size];
// ----->     size_ = rightHandSide.m_size;
// ----->     copy(rightHandSide.m_ptr, rightHandSide.m_ptr+size, m_ptr); // crashes on self assignment
// ----->     return *this;
// -----> }
// ---> Also, how about if you have complicated structure (where nodes can refer to itself)
// -----> Follow the copy-and-swap idiom to be safe.

// -> Copy-and-swap to the rescue
// ---> See the code above
// ---> We make a complete copy of rhse before the first modification to *this.
// ---> So any aliasing relationship between rhs and *this cannot trip us up.

// -> RAII meaning
// ---> "Resource Acquisition Is Initialization"
// ---> The slogan is about initialization but its meaning is really about cleanup.
// ---> The should have been "Resource freeing is deletion/destruction".

// -> RAII and exception safefy
// ---> Destructors help us write code that is robust against exceptions
// ---> C++ supports try/catch and throw.
// ---> When an exception is thrown, the runtime looks "up the call stack"
// -----> until it finds a suitable catch handler for the type of the exception being thrown.
// ---> Assuming a catch is found, the runtime peforms "stack unwinding".
// -----> For every local scope between the throw and the catch handler,
// -----> the runtime invokes the destructors of all local variables in that scope.
// ---> To avoid leaks, place all your cleanup code in destructors.

// -> Deleted special member functions
// ---> We can improve RAII objects by making it non-copyable.
// ---> When a function definition has the body=delete; instead of a curly-braced compound statement,
// -----> the compiler will reject calls to that function at compile time.
// ---> This facility is completely unrelated to new/delete; its just a cutesy use of an existing keyword.
// ---> New keywords are expensive, because C++ values backward compatibility.

// -> Defaulted special member functions
// ---> When a special member function has the body =default; instead of a curly-braced compound statement,
// -----> the compiler will create a default version of that function, just as if it were implicity generated.
// ---> Explicitly defaulting your special members can help your code to be "self-documenting".

// -> The Rule of Zero
// ---> If your class does not directly manage any resource,
// -----> but merely uses library components such as vector and string,
// -----> then should strive to write no special member functions.
// ---> Default them all:
// -----> Let the compiler implicitly generate a default destructor.
// -----> Let the compiler generate the copy constructor.
// -----> Let the compiler generate the copy assignment operator.
// -----> But your own swap might improve performance.
// -------> NOTE: A non-member friend swap function can be recognized by the STL and will call them appropriately.
// -------> Similar to comparison operators (==, !=, etc)
// ---> This is known as the "Rule of Zero".

// -> There are two kinds of well-designed value-semantic C++ classes:
// ---> Business-logic classes that do not manually manage any resources and follow the Rule of Zero:
// -----> They delegate the job of resource management to data member of types such as string.
// ---> Resource-management classes (small, single-purpose) that follow the Rule of Three:
// -----> Acquire the resource in each constructor.
// -----> Free the resource in your destructor.
// -----> Copy-and-swap in you assignment operator.

// -> Introducing rvalue references
// ---> C++11 introduces rvalue-reference types.
// ---> The reference we've seen so far are lvalue references.
// ---> The terms "lvalue" and "rvalue" come from the syntax of assignment expressions.
// -----> An lvalue "can" appear on the lef-hand side of an assignment.
// -----> An revalue "must" appear on the right-hand side.

// -> Introducing rvalue references
// ---> int& is an lvalue reference to an int.
// ---> int&& (two ampersands) is an rvalue reference to an int.
// ---> As a general rule, lvalue references parameters do not bind to rvalues,
// -----> and rvalue reference parameters do not bind to lvalues.
// ---> NOTE: Special case for backward compability:
// -----> A const lvalue reference will happily bind to an rvalue.

// -> Rvalues won't be missed
// ---> When pass and rvalue as a parameter, we can steal the guts of the parameter because its a temporary.
// ---> The most common application of rvalue references is the move constructor.
// ---> Allocating and copying is slow, the move constructor doesn't need to do either of those slow things!
// ---> Each STL container type has a move constructor in addition to its copy constructor.

// -> The Rule of Five
// ---> If your class directly manages some kind of resource (such as a new'ed pointer),
// -----> then you may need to hand-write five special member functions for correctness and performance.
// -------> A destructor to free the resource
// -------> A copy constructor to copy the resource
// -------> A move constructor to transfer ownership of the resource
// -------> A copy assignment operator to free the left-hand resource and copy the right-hand one.
// -------> A move assignment operator to free the left-hand resource and transfer ownership of the right-hand one.

// -> Copy and swap leads to duplication
// ---> We have similar code on our "copy assignment" and "move assignment".
// ---> By value assignment operator (Copy by value assignment)
// -----> What if we just wrote assignment operator and left the copy up to our caller?
// -----> I'm not aware of any problems with this idiom.
// -----> Writing copy assignment and move assignment separately is more frequently seen.
// -------> In particular, the STL always writes them separately.

// -> The Rule of Four (and a half)
// ---> If your class directly manages some kind of resource (such as a new'ed pointer),
// -----> then you may need to hand-write five special member functions for correctness and performance.
// -------> A destructor to free the resource
// -------> A copy constructor to copy the resource
// -------> A move constructor to transfer ownership of the resource
// -------> A by-value assignment operator to free the left-hand resource and transfer ownership of the right-hand one.
// -------> (1/2) A nonmember swap function, and ideally a member version too.

// -> Closer to rule of zero vector
// ---> Just use "unique_ptr" to lessen the work
// -----> Move constructor can be set a default
// -----> Destructor can be set a default
// -----> Still might need to create copy constructor
// -----> Assignment can be needed too
// -----> swap function might be needed as well

// -> Examples of resource management
// ---> "unique_ptr: manages a raw pointer to a uniquely owned heap allocation:
// -----> Destructor frees the resource
// -------> Calls delete on the raw pointer
// -----> Copy consturctor copies the resource
// -------> Copying doesn't make sense. We =delete this member function.
// -----> Move constructor transfers ownership of the resource.
// -------> Transfers the raw pointer, nulls out the right hand side.
// -----> Copy assignment operator frees the left hand side and copies the right hand side
// -------> Copying doesn't make sense. We =delete this member function.
// -----> Move assignment operator frees the left hand side and transfer ownership of the right hand side
// -------> Calls delete on the left-hand ptr, transfers, then nulls out the right hand side.
// ---> "shared_ptr: manages a raw pointer to a uniquely owned heap allocation:
// -----> Destructor frees the resource
// -------> Decrements the refcount (and maybe cleans up if the refcount is now zero)
// -----> Copy consturctor copies the resource
// -------> Increments the refcount
// -----> Move constructor transfers ownership of the resource.
// -------> Leaves the refcount the same, then disengages the right-hand side.
// -----> Copy assignment operator frees the left hand side and copies the right hand side
// -------> Decrements the old refcount, increments the new refcount.
// -----> Move assignment operator frees the left hand side and transfer ownership of the right hand side
// -------> Decrements the old refcount, then disengages the right-hand side.
// ---> "ifstream: manages a POSIX file handle and an associated buffer.
// -----> Destructor frees the resource
// -------> Calls "close" on the handle.
// -----> Copy consturctor copies the resource
// -------> We =delete this member function.
// -----> Move constructor transfers ownership of the resource.
// -------> Transfers the handle and the contents of the buffer.
// -----> Copy assignment operator frees the left hand side and copies the right hand side
// -------> We =delete this member function.
// -----> Move assignment operator frees the left hand side and transfer ownership of the right hand side
// -------> Calls "close", then transfers the handle and contents of the buffer.

// -> Pilfering implies an empty state
// ---> Each of the preceding examples had a move operation which involved:
// -----> disengageing the right-hand side
// -----> nulling out the right-hand side.
// ---> If you forget to do this, then you may have double-free bugs.
// ---> After your move operation pilfers the guts of the right-hand object without destroying it,
// -----> the right-hand object must be left in a state "emptied of guts".
// ---> You can do RAII with only copy and destroy operations, no move.
// -----> In that case you have no empty state.
// -----> But if making a copy is slow or impossible, then you won't be able to go this route.
// ---> You can even do RAII with only destroy; just delete your copy and move operations.
// -----> std::lock_guard is an example.
// -------> This object just lives on the stack.
// --->
// --->
// --->
// --->
// --->
// --->
