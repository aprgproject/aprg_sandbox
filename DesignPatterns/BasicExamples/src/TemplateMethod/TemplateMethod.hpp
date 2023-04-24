#include <iostream>

namespace TemplateMethod
{

// AbstractClass
// implements a template method defining the skeleton of an algorithm

class AbstractClass
{
public:
    virtual ~AbstractClass() = default;

    void templateMethod() // should be NOT "virtual" or should be marked as "final"
    {
        // ...
        primitiveOperation1();
        // ...
        primitiveOperation2();
        // ...
        hookOperation();
        // ...
    }

protected: // This ensures how primitive operations are used only by the templateMethod.

    virtual void primitiveOperation1() = 0; // abstract operations MUST be overridden
    virtual void primitiveOperation2() = 0;
    virtual void hookOperation(){} // hooks MAY be overriden (can be empty an implementation)
    // ...
};


// Concrete Class
// implements the primitive operations to carry out specific steps  of the algorithm,
// there may be many Concrete classes, each implementing the full set of the required operation

class ConcreteClass : public AbstractClass
{
    void primitiveOperation1() override
    {
        std::cout << "Primitive operation 1\n";
        // ...
    }

    void primitiveOperation2() override
    {
        std::cout << "Primitive operation 2\n";
        // ...
    }

    void hookOperation() override
    {
        std::cout << "Overriden hook operation\n";
        // ...
    }
    // ...
};

}

// Template Method discussion:

// ONE LINE NOTE:
// -> Provide a "template method" with KNOWN STEPS and allow polymorphism and subclassing to support DIFFERENT VERSION of the STEPS.

// Intent:
// Template method defines the skeleton of an algorithm in an operation, deferring some steps to subclasses.
// It lets subclasses redefine certain steps of an algorithm  without changing the algorithm's structure.
// The pattern has behavioral purpose and applies to the classes.

// When to use (applicability):
// -> to implement the invariant parts of an algorithm once and leave it up to subclasses to implement the behavior that can vary
// -> when common behavior among subclasses should be factored and localized in a common class to avoid code duplication
// -> to control subclasses extensions

// Consequences:
// -> Template methods are a fundamental technique for code reuse.
// ---> These are important in class libraries because they are means of factoring out common behavior in class libraries.
// -> Template methods lead to an inverted control structure.
// ---> Also known as the "Holywood principle" or "Don't call us, we'll call you".
// ---> This refers how a parent class calls the operations of a subclass and not the other way around.
// -> Template methods calls the following kinds ot operations:
// ---> concrete operations (either on the ConcreteClass or on client classes)
// ---> concrete AbstractClass operations (operations that are generally useful to subclasses)
// ---> primitive operations (abstract operations)
// ---> factory method operations
// ---> hook operations (which provide default behavior that subclasses can extend if necessary)
// -----> A hook operation often does nothing by default.
// -> Its important to specify which operations are hooks (may be overriden) and which are abstract operations (must be overridden)
// ---> To reuse an abstract class effective, subclass writers must understand which operations are designed for overriding.
// ---> A subclass can extend a parent class operation's behavior by overriding the operation and calling the parent operation explicitly.
// -> This helps with open-close principle (because only parts are changed by overriding an operation).

// Implementation:
// -> Using C++ access control
// ---> In C++, the primitive operations that a template method calls can be declared protected members.
// -----> This ensures that are only called by the template method.
// ---> Primitive operations that must be overriden are declared pure virtual.
// ---> The template itself should not be overriden; therefore you can make the template method a nonvirtual member function.
// -> Minimizing primitive operations
// ---> Minimizing the number of primitive operations that a subclass must override is needed to flesh out the algorithm.
// -----> The more operations that needs overriding, the more tedious things get for clients.
// -> Naming conventions
// ---> You can identify the operations that should be overriding by adding a prefix to their names.
// -----> For example, "Do" prefix can be used.

// Related Patterns
// -> [FactoryMethods] are often called by template methods.
// -> [Strategies] uses delegation to vary the entire algorithm.
// ---> In contrast, [TemplateMethods] uses inheritance to vary part of an algorithm.
