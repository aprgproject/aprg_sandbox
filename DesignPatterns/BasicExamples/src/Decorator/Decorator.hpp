#include <iostream>
#include <memory>

namespace Decorator
{

// Component
// defines an interface for objects that can have responsibilities
// added to them dynamically

class Component
{
public:
    virtual ~Component() = default;

    virtual void operation() = 0;
    // ...
};


// Concrete Component
// defines an object to which additional responsibilities
// can be attached

class ConcreteComponent : public Component
{
public:
    void operation() override
    {
        std::cout << "Concrete Component operation\n";
    }
    // ...
};


// Decorator
// maintains a reference to a Component object and defines an interface
// that conforms to Component's interface

class Decorator : public Component
{
public:
    Decorator(std::unique_ptr<Component> componentPointer)
        : m_componentPointer(std::move(componentPointer))
    {}

    virtual void operation() override
    {
        m_componentPointer->operation();
    }
    // ...

private:
    std::unique_ptr<Component> m_componentPointer;
};


// Concrete Decorators
// add responsibilities to the component (can extend the state
// of the component)

class ConcreteDecoratorA : public Decorator
{
public:
    ConcreteDecoratorA(std::unique_ptr<Component> componentPointer)
        : Decorator(std::move(componentPointer))
    {}

    void operation() override
    {
        Decorator::operation();
        std::cout << "Decorator A\n";
    }
    // ...
};

class ConcreteDecoratorB : public Decorator
{
public:
    ConcreteDecoratorB(std::unique_ptr<Component> componentPointer)
        : Decorator(std::move(componentPointer))
    {}

    void operation() override
    {
        Decorator::operation();
        std::cout << "Decorator B\n";
    }
    // ...
};

}

// Decorator discussion:

// ONE LINE NOTE:
// -> DECORATE (or attach) additional RESPONSIBILITIES into an object in runtime.

// Intent:
// Attach additional responsibilities to an object dynamically.
// Decorators provide a flexible alternative to subclassing for extending functionality.
// The pattern has structural purpose and applies to objects.
// Note: It both uses the "has a" and "is a" approach.

// When to use (applicability):
// -> to add responsibilities to individual objects dynamically and transparently, that is, without affecting other objects
// -> for responsibilities that can be withdrawn
// -> when extension by subclassing is impractical

// Consequences:
// -> More flexibility than static inheritance.
// ---> With decorators, responsibilities can be added and removed at runtime simply by attaching and detaching them.
// ---> Providing different Decorator classes for a specific Component class lets you mix and match responsibilities.
// ---> Decorators also make it easy to add a property twice.// -> Avoids feature-laden classes high up in the hierarchy.
// ---> Decorator offers a pay-as-you-go approach to adding responsibilities.
// ---> Instead of trying to support all foreseeable features in a complex customizable class,
// ---> you can define a simple class and add functionality incrementally with Decorator objects.// ---> Its easy to defined new kinds of decorators independently from classes of objects they extend, even for unforeseen extensions.
// -> A decorator and its component aren't identical
// ---> A decorator is a transparent enclosure.
// ---> But from an object identity point of view, a decorated component is not identical to the component itself (dont rely on object identity)
// -> Lots of little objects
// ---> A design that uses Decorator often results in system of lot of little objects that all look alike.
// ---> Although these systems are easy to customizable by those who understand them, they can be hard to learn and debug.

// Implementation:
// -> Interface conformance
// ---> A decorator objects interface must conform to interface of the component it decorates.
// -> Omitting the abstract Decorator class
// ---> There's no need to define an abstract decorator class when only to add one responsibility.
// -> Keeping the Component classes lightweight
// ---> Component classes should only define interface and dont store data because decorators might become heavyweight to use in quantity.
// -> Changing the skin of an object versus changing its guts.
// ---> We can think of a decorator as a skin over an object that changes its behavior.
// ---> Since the Decorator pattern only changes a component from the outside, the component deoesnt have to know anything about its decorators.
// ---> It contrast, the Strategy pattern is a good example of a pattern for changing the guts.

// Related Patterns
// -> [Adapter]: A decorator is different from an adapter in that a decorator only changes an object responsibilities and not its interface.
// And an adapter will give an object a completely new interface.
// -> [Composite]: A decorator can be viewed as a degenerate composite with only the component.
// However, a decorator adds additional responsibilities (it isnt intended for object aggregation)
// -> [Strategy]: A decorator lets change the skin of an object; a strategy lets you change the guts.
// These are two alternative ways of changing an object.
