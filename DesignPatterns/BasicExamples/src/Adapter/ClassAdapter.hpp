#include <iostream>

namespace ClassAdapter
{

// Target
// defines specific interface that Client uses

class Target
{
public:
    virtual ~Target() = default;

    virtual void request() = 0;
    // ...
};


// Adaptee
// all requests get delegated to the Adaptee which defines
// an existing interface that needs adapting

class Adaptee
{
public:
    void specificRequest()
    {
        std::cout << "specific request\n";
    }
    // ...
};


// Adapter
// implements the Target interface and lets the Adaptee respond
// to request on a Target by extending both classes
// ie adapts the interface of Adaptee to the Target interface

class Adapter : public Target, private Adaptee // note the access control
{
public:
    virtual void request() override
    {
        specificRequest();
    }
    // ...
};

}

// Adapter discussion:

// ONE LINE NOTE:
// -> ADAPT a MISMATCHED interface into a matched interface using a class inheritance or object composition

// Intent:
// Convert the interface of a class into another interface the clients expect.// Adapter lets classes work together that couldn't otherwise because of incompatible interfaces,
// ie. allows to use a client with an incompatible interface by an Adapter that does the conversion.
// Adapter has structural purpose and can be applied on classes and also on object.
// A class adapter uses multiple inheritance to adapt one interface to another ("is a" approach).// A object adapter uses object composition to combine classes with different interfaces ("has a" approach).

// When to use (applicability):
// -> you want to use an existing class, and its interface does not match the one you need
// -> you want to create a reusable class that cooperates with classes that don't necessarily have compatible interfaces
// -> (object adapter only) you need to use several existing subclasses, but its impractical to adapt their interface by subclassing every one.

// Consequences:
// -> A class adapter
// ---> adapts Adaptee to target by commiting to a concrete Adapter class.
// ---> lets Adapter override some of Adaptee's behavior, since Adapter is a subclass of Adaptee.
// ---> introduces only one object and no additional pointer indirection is need to get to the adaptee.
// -> A object adapter
// ---> lets a single Adapter work with many Adaptees (and all its subclasses).
// ---> makes it harder to override Adaptee behavior (requires subclassing the Adaptee and making the adapter refer to the subclass).
// -> Issues:
// ---> How much adapting does Adapter do?
// -----> Adapters vary in the amount of work they do to adapt Adaptee to the Target interface.
// -----> There is a spectrum of possible work. Examples:
// -------> simple interface conversion
// -------> changing the names of operations
// -------> supporting an entire different set of operations
// -----> The amount of work Adapter does depends on how similar the Target interface is to Adaptee's.
// ---> Pluggable adapter
// -----> A class is more reusable when you minimize the assumptions other classes mucst make to use it.
// -----> By building interface adaptation into a class, you eliminate the assumption that other classes see the same interface.
// -----> Put another way, interface adaption lets us incorporate our class into existing system that might expect different interface to the class.
// -----> The term "pluggable adapter" to describe classes with built-in interface adaptation.
// ---> Using two-way adapters to provide transparent.
// -----> A potential problem with adapters is that they aren't transparent to all clients.
// -----> An adapted object no longer conforms to the Adaptee interface, to it can't be used as is wherever an Adaptee object can.
// -----> Two-way adapters are useful when two different clients need to view an object differently.

// Implementation:
// -> Implementing class adapters in C++.
// ---> The adapter would inherit publicly from Target and privately from Adaptee.
// ---> Thus, Adapter would be a subtype of Target but not of Adaptee.
// -> Pluggable adapters
// ---> Three ways to implement adapters:
// -----> (1) Using abstract operations
// -------> Define corresponding abstract operations for the narrow Adaptee interface.
// -------> Subclasses must implement the abstract operations and adapt the hierarchically-structured object.
// -----> (2) Using delegate objects
// -------> Statically typed langurages like C++ require an explicit interface definition for the delegate.
// -------> We can specify such an interface by putting the narrow Adaptee interface into an abstract Delegate class.
// -----> (3) Parameterized adapters

// Related Patterns
// -> [Bridge] has a structure similar to an object adapter, but Bridge has different intent.
// ---> [Bridge] is meant to separate an interface from its implementation so that they can be varied easily and independently.
// ---> [Adapter] is meant to change the interface of an existing object.
// -> [Decorator] enchances another object without changing its interface.
// ---> A decoractor is thus more transparent to the application than an adapter is.
// ---> As a consequence, Decorator supports "recursive composition", which isn't possible with pure adapters.
// -> [Proxy] defines a representative or surrogate for another object and does not change its interface.
