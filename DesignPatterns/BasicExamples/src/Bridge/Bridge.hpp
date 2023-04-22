#include <iostream>
#include <memory>

namespace Bridge
{

// Implementor
// defines the interface for implementation classes

class Implementor
{
public:
    virtual ~Implementor() = default;

    virtual void action() = 0;
    // ...
};


// Concrete Implementors
// implement the Implementor interface and define concrete implementations

class ConcreteImplementorA : public Implementor
{
public:
    void action() override
    {
        std::cout << "Concrete Implementor A\n";
    }
    // ...
};

class ConcreteImplementorB : public Implementor
{
public:
    void action() override
    {
        std::cout << "Concrete Implementor B\n";
    }
    // ...
};


// Abstraction
// defines the abstraction's interface

class Abstraction
{
public:
    virtual ~Abstraction() = default;

    virtual void operation() = 0;
    // ...
};


// RefinedAbstraction
// extends the interface defined by Abstraction

class RefinedAbstraction : public Abstraction
{
public:
    RefinedAbstraction(std::unique_ptr<Implementor> implementor)
        : m_implementor(std::move(implementor))
    {}

    void operation() override
    {
        m_implementor->action();
    }
    // ...

private:
    std::unique_ptr<Implementor> m_implementor;
};

}

// Bridge discussion:

// ONE LINE NOTE:
// -> BRIDGE several IMPLEMENTATIONS (or responsibilities) into one class

// Intent:
// Decouple an abstraction from its implementation so that the two can vary independently.
// Bridge pattern has structural purpose and applies to objects, so it deals with the composition of objects.
// NOTE: This is related to "Dependency Inversion Principle".

// When to use (applicability):
// -> you want to avoid a permanent binding between an abstraction and its implementation
// -> both the abstractions and their implementations should be extensible by subclassing
// -> changes in the implementation of an abstraction should have no impact on clients
// -> you want to hide the implementation of an abstraction completely from clients
// -> you have a proliferation of classes (class explosion), and responsibilities needs to extracted
// -> you want to share an implementation among multiple objects (and it needs to be hidden from the client)

// Consequences:
// -> Decoupling interface and implementation.
// ---> An implementation is not bound permanently to an interface.
// -----> The implementation for an abstraction can be configured or changed at runtime.
// ---> This also elimintate compile time dependencies on the implementation (minimize recompiling when implementation is changed).
// -----> This protery is essential when you must ensure binary compatibility between different version of a class library.
// ---> This encourages layering that can lead to a better structured system.
// -> Improved extensibility
// ---> You can extend the Abstraction and Implementor hierarchies independently
// -> Hiding implementation details from clients
// ---> You can shield clients from implementation details, like the sharing of implementor objects and accompanying reference count mechanism.

// Implementation:
// -> Only one implementor
// ---> If there is one implementation, using an abstract Implementor class isn't necessary.
// -----> This is a degenerate case. But is still useful to prevent recompilation (but it still needs to be relinked).
// -> Creating the right implementor object
// ---> How, when and where do you decide which Implementor class to instantiate when these's more than one.
// -----> In the construction, just pass one implementator class and just have a "set"/"change" function to change it.
// -----> In the construction, put all the implementator classes and just change in runtime depending on the situation.
// -> Sharing implementors (use a reference count, in case it needs to be deleted).
// -> Using multiple inhertiance.
// ---> You can use multiple inheritance in C++ to combine an interface with its implementation.
// -----> For example, a class can inherit publicly from Abstraction and privately from a ConcreteImplementor.
// -----> But because this approach relies on static inhertiance, it binds an implementation permanently to its interface.
// -----> Hence, you can't implement a true Bridge with multiple inheritance (at least not in C++).

// Related Patterns
// -> An [AbstractFactory] can create and configure a particular Bridge.
// -> The [Adapter] pattern is geared toward making unrelated classes work together.
// ---> It is usually applied to system after they're designed.
// ---> Bridge, on the hand, is used up-front in a design to let abstractions and implementations vary independently.
