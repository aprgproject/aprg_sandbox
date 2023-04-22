#include <memory>
#include <iostream>

namespace Singleton
{

// Singleton
// has private static variable to hold one instance of the class
// and method which gives us a way to instantiate the class

class Singleton
{
public:
    friend std::unique_ptr<Singleton> std::make_unique<Singleton>();

    static Singleton& getInstance()
    {
        // "static variable approach" can be done here
        if(!m_instancePointer)
        {
            m_instancePointer = std::make_unique<Singleton>();
        }
        return *m_instancePointer;
    }

    static void restartInstance() // "static variable approach" has no restart
    {
        if(m_instancePointer)
        {
            m_instancePointer.reset();
        }
    }

    void tellSomething()
    {
        std::cout << "This is Singleton.\n";
        // ...
    }
    // ...

private:
    Singleton() = default;
    static std::unique_ptr<Singleton> m_instancePointer;
    // ...
};

std::unique_ptr<Singleton> Singleton::m_instancePointer; // this still have problem of static variables (whether they are initialized when called)

}

// Singleton discussion:

// ONE LINE NOTE:
// -> Ensure a class only has SINGLE instance, and provide a global point of access to it.

// Intent:
// Ensure a class only has one instance, and provide a global point of access to it.
// Pattern has creational purpose and deals with object relationships, which are more dynamic.
// The Singleton is often used as a part another design patterns (see [Façade] and [Flyweight]).

// When to use (applicability):
// -> there must be exactly one instance of a class, and it must be accessible to clients from a well-known access point
// -> when the sole instance should be extensible by subclassing, and clients should be able to use an extended instance without modifying their code

// Consequences:
// -> Controlled access to sole instance
// ---> It can have strict control over how and when clients access it.
// -> Reduced name space
// ---> The Singleton pattern is an improvement over global variables.
// ---> It avoids polluting the namespace space with global variables that store sole instances.
// -> Permits refinement of operations and representation
// ---> Its easy to configure an application with an instance of this extended class.
// ---> The application can be configured the with an instance of the class you need at runtime.
// -> Permits a variable number of instances
// ---> The pattern makes it easy to change our mind and allow more than once instance of the Singleton class.
// ---> Only the operation that grants access to the Singleton instance needs to change.
// -> More flexible than class operations
// ---> A way to package a singleton's functionality is to use class operations (static member functions in C++).
// ---> The static member functions in C++ are never virtual, so subclasses can't override them polymorphically.

// Implementation:
// -> Ensuring a unique instance
// ---> Static member function and private constructor in C++
// -> Subclassing the Singleton class

// Related Patterns
// -> [Mediator]: By encapsulating complex update semantics, the ChangeManager acts a mediator between subjects and observers.
// -> [Singleton]: The ChangeManager may use the Singleton pattern to make it unique and globally accessible

