#include <iostream>
#include <memory>

namespace FactoryMethod
{

// Product
// products implement the same interface so that the classes can refer
// to the interface not the concrete product

class Product
{
public:
    virtual ~Product() = default;
    virtual std::string getName() const = 0;
    // ...
};


// Concrete Product
// define product to be created

class ConcreteProductA : public Product
{
public:
    std::string getName() const override
    {
        return "type A";
    }
    // ...
};


// Concrete Product
// define product to be created

class ConcreteProductB : public Product
{
public:
    std::string getName() const override
    {
        return "type B";
    }
    // ...
};


// Creator
// contains the implementation for all of the methods
// to manipulate products except for the factory method

class Creator
{
public:
    virtual ~Creator() = default;

    virtual std::unique_ptr<Product> createProductA() const = 0;
    virtual std::unique_ptr<Product> createProductB() const = 0;
    // ...
};


// Concrete Creator
// implements factory method that is responsible for creating
// one or more concrete products ie. it is class that has
// the knowledge of how to create the products

class ConcreteCreator : public Creator
{
public:
    std::unique_ptr<Product> createProductA() const override
    {
        return std::make_unique<ConcreteProductA>();
    }

    std::unique_ptr<Product> createProductB() const override
    {
        return std::make_unique<ConcreteProductB>();
    }
    // ...
};

}

// FactoryMethod discussion:

// ONE LINE NOTE:
// -> Provide a "factory method" for creating objects and let polymophism and subclassing support DIFFERENT VERSIONS of the "factory method".

// Intent:
// Define an interface for creating an object, but let subclasses decide which class to instantiate.
// Factory Method lets a class defer instantiation to subclasses.
// The pattern has creational purpose and applies to classes where it deals with relationships through inheritance
// (ie. they are static-fixed at compile time).
// In contrast to Abstract Factory, the Factory Method contains a method to produce only one type of product.

// When to use (applicability):
// -> a class can't anticipate the class of objects it must create
// -> a class wants its subclasses to specify the objects it creates
// -> classes delegate responsibility to one of several helper subclasses,
// and you want to localize the knowledge of which helper subclass is the delegate

// Consequences:
// -> A potential disadvantage of factory methods is that clients might have to subclass
// the Creator class just to create a particular ConcreteProduct object.
// -> Provides hooks for subclasses
// ---> Creating objects inside a class with a factory method is more flexible than creating an object directly.
// ---> FactoryMethod gives subclasses a hook for providing an extended version of an object.
// -> Connects parallel class hierarchies.

// Implementation:
// -> Two major varieties:
// ---> (1) Creator class is an abstract class and does not provide an implementation for the factory method (only declaration)
// -----> This requires subclasses to define an implementation (because there is no default).
// -----> It gets around the dilemma of having to instantiate unforeseeable classes.
// ---> (2) Creator class is an concrete class and provides a default implementation for the factory method.
// -----> Creator uses the FactoryMethod primarily for flexibility.
// -----> Its a following a rule that says "Create objects in a separate operation so that subclasses can override the way they're created."
// -----> This rule ensures that designers of subclasses can change the class of objects their parent class instantiates if necessary.
// -> Parameterized factory methods
// ---> Another variation is create multiple kinds of products.
// -----> This means it takes a parameter to identify the kind of object to create, but it still share the same Product interface.
// -----> This has negative impact of having multiple paths in the creation method because we are creating multiple products.
// -> Language specific variants and issues
// ---> Factory methods in C++ are always virtual functions and are often pure virtual.
// ---> Just be careful not to call factory methods in the Creator's constructor (the factory method in the ConcreteCreator won't be available yet)
// -> Using templates to avoid subclassing
// ---> Another potential problem with factory method is that they might force you to subclass just to create the appropriate Product objects.
// ---> Another approach is provide a template subclass of Creator that's parameterized by the concrete Product class.
// -> Naming conventions
// ---> Its good practice to use naming conventions that make it clear you're using factory methods ("create", "make" etc).

// Related Patterns
// -> [AbstractFactory] is often implemented with factory methods.
// The motivation example in the AbstractFactory pattern illustrates FactoryMethod as well.
// -> [Template Methods] are usually called in FactoryMethods.
// -> [Prototypes] don't requires subclassing Creator.
// However, they often require an Initialize operation on the Product class.
// Creator uses Initialize to initialize the object.
// Factory Method doesn't require such an operation.
