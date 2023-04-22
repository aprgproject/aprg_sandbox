#include <iostream>
#include <memory>

namespace Strategy
{

// Strategy
// declares an interface common to all supported algorithms

class Strategy
{
public:
    virtual ~Strategy() = default; // polymorphic destruction

    virtual void algorithmInterface() = 0;
    // ...
};


// Concrete Strategies
// implement the algorithm using the Strategy interface

class ConcreteStrategyA : public Strategy
{
public:
    void algorithmInterface() override
    {
        std::cout << "Concrete Strategy A\n";
    }
    // ...
};

class ConcreteStrategyB : public Strategy
{
public:
    void algorithmInterface() override
    {
        std::cout << "Concrete Strategy B\n";
    }
    // ...
};

class ConcreteStrategyC : public Strategy
{
public:
    void algorithmInterface() override
    {
        std::cout << "Concrete Strategy C\n";
    }
    // ...
};


// Context
// maintains a reference to a Strategy object

class Context
{
public:
    Context(std::unique_ptr<Strategy> strategy)
        : m_strategy(std::move(strategy))
    {}

    void contextInterface()
    {
        m_strategy->algorithmInterface();
    }
    // ...

private:
    std::unique_ptr<Strategy> m_strategy;
    // ...
};

}

// Strategy discussion:

// ONE LINE NOTE:
// -> Implement a common ABSTRACT STRATEGY INTERFACE and implement different strategies or FAMILIES OF ALGORITHMS by subclassing so that it can be changed in runtime.

// Intent:
// Strategy defines a family of algorithms, encapsulates each one, and makes them interchangeable.// It lets the algorithm vary independently from clients that use it.
// The pattern has behavioral purpose and applies to the objects.
// NOTE: This is related to "Dependency Inversion Principle".
// When to use (applicability):
// -> many related classes differ only in their behavior
// -> you need different variants of an algorithm
// -> an algorithm uses data that clients shouldn't know about
// -> a class defines many behaviors, and these appear as multiple conditional statements in its operations
// ---> Instead of many conditionals, move related conditional branches into their own Strategy class.

// Consequences:
// -> Families of related algorithms
// ---> Hierarchies fo Strategy classes define a family of algorihtms and behaviors for context to reuse.
// ---> Inheritance can help factor out common functionality of the algorithms.
// -> An alternative to subclassing
// ---> Inhertiance offers another way to support a variety of algorithms or behaviors.
// -> Strategies eliminate conditional statements
// ---> The Strategy pattern offers an alternative to conditional statements for selecting desired behavior.
// ---> When different behaviors are lumped into one class, its hard to avoid using conditional statements to select the right behavior.
// -> A choice of implementations
// ---> Strategies can provide different implementations.
// -> Clients must be aware different Strategies
// ---> Clients must understand how Strategies different before it can select a appropriate one.
// ---> Clients might be exposed to implementation issues.
// -> Communication overhead between Strategy and Context
// ---> Since the Strategy interface is shared by all ConcreteStrategies,
// ---> so its likely that all information passed to the interface might not be needed.
// -> Increased number of objects
// ---> Creating multiple strategies can increase the number of objects (especially if Strategies have state)
// ---> This can be reduced by implementing strategies as stateless objects and the context can share

// Implementation:
// -> Defining the Strategy and Context interfaces
// ---> The Strategy and Context interfaces must give a ConcreteStrategy
// efficient access to any data it needs from a context and vice versa
// -> Strategies as template parameters.
// ---> This can be done if:
// ---> (1) The Strategy can be selected at compile-time
// ---> (2) It does not have to be changed at runtime.
// -> Making Strategy objects optional
// ---> When Strategy pointer can be null, it needs to be check when its null.

// Related Patterns
// -> [Flyweight]: Strategy objects often make good flyweights.
