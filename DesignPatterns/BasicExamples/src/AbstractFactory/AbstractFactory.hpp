#include <iostream>
#include <memory>

namespace AbstractFactory
{

// Product A
// products implement the same interface so that the classes can refer
// to the interface not the concrete product

class ProductA
{
public:
    virtual ~ProductA() = default;

    virtual std::string getName() const = 0;
    // ...
};


// ConcreteProductAX and ConcreteProductAY
// define objects to be created by concrete factory

class ConcreteProductAX : public ProductA
{
public:
    std::string getName() const override
    {
        return "ConcreteProductAX";
    }
    // ...
};

class ConcreteProductAY : public ProductA
{
public:
    std::string getName() const override
    {
        return "ConcreteProductAY";
    }
    // ...
};


// Product B
// same as Product A, Product B declares interface for concrete products
// where each can produce an entire set of products

class ProductB
{
public:
    virtual ~ProductB() = default;

    virtual std::string getName() const = 0;
    // ...
};


// ConcreteProductBX and ConcreteProductBY
// same as previous concrete product classes

class ConcreteProductBX : public ProductB
{
public:
    std::string getName() const override
    {
        return "ConcreteProductBX";
    }
    // ...
};

class ConcreteProductBY : public ProductB
{
public:
    std::string getName() const override
    {
        return "ConcreteProductBY";
    }
    // ...
};


// Abstract Factory
// provides an abstract interface for creating a family of products

class AbstractFactory
{
public:
    virtual ~AbstractFactory() = default;

    virtual std::unique_ptr<ProductA> createProductA() const = 0;
    virtual std::unique_ptr<ProductB> createProductB() const = 0;
};


// Concrete Factory X and Y
// each concrete factory create a family of products and client uses
// one of these factories so it never has to instantiate a product object

class ConcreteFactoryX : public AbstractFactory
{
public:
    std::unique_ptr<ProductA> createProductA() const override
    {
        return std::make_unique<ConcreteProductAX>();
    }
    std::unique_ptr<ProductB> createProductB() const override
    {
        return std::make_unique<ConcreteProductBX>();
    }
    // ...
};

class ConcreteFactoryY : public AbstractFactory
{
public:
    std::unique_ptr<ProductA> createProductA() const override
    {
        return std::make_unique<ConcreteProductAY>();
    }
    std::unique_ptr<ProductB> createProductB() const override
    {
        return std::make_unique<ConcreteProductBY>();
    }
    // ...
};

}

// AbstractFactory discussion:

// ONE LINE NOTE:
// -> Create FAMILIES of objects using an ABSTRACT/CHANGING factory

// Intent:
// Abstract factory pattern has creational purpose.
// It provides an interface for creating families of related or dependent objects without specifying their concrete classes.
// Pattern applies to object and deal with object relationships (families), which are more dynamic.
// In contrast to Factory Method, Abstract Factory pattern produces family of types that are related,
// ie. it has more than one method of types it produces.
// NOTE: This is related to "Open Close Principle".

// When to use (applicability):
// -> a system should be independent of how its products are created, composed, and represented
// -> a system should be configured with one of multiple families of products
// -> a family of related product objects is designed to be used together
// -> you want to provide a class library of products, and you want to reveal just their interfaces, not their implementations

// Consequences:
// -> It isolates concrete classes
// ---> Because the factory encapsulates the responsibility and process of creating product objects, it isolates clients from the implementation.
// -> It makes exchanging product families easy.
// ---> Its easy to change the concrete factory the application is using.
// ---> Because an abstract factory creates a complete family of products, the whole product family changes at once.
// -> It promotes consistency among products.
// ---> When prdocut objects familty are designed to work together, its important to stick with one family (AbstractFactory makes it easy to enforce).
// -> Supporting new kinds of products is difficult.
// ---> Abstract Facotry interfaces fixes the set of product that can be created.
// ---> Supporting new kinds of product requires extending the factory interface, which involves changing all of its subclasses.

// Implementation:
// -> Factories as singletons
// ---> Typically needs only one instance of a ConcreteFactory per product family, so its usually best implemented as a Singleton.
// -> Creating the products
// ---> AbstractFactory is only an interface, its up to to the concreate classes to actually create them.
// ---> FactoryMethod is a common way to do the creation of each product.
// -----> A ConcreteFactory will specify its products by overriding the factory method for each.
// -----> This might require a new concrete facoty subclass for each product family, even if the product families differ only slightly.
// ---> Prototype is another way to do the creation of each product.
// -----> A ConcreteFactory is initialized with prototypes of each product, and its creates a new product by cloning its prototype.
// -----> This prototype apporach eliminates the neeed for a new concrete factory class for each new product family.
// -> Defining extensible factories
// ---> A more flexible but less safe design is to add a parameter to operations that create objects.
// -----> This parameter specifies the kind of object to be created.
// -----> AbstractFactory only needs a single "create"/"make" operation with a parameter indicating the kind of Product to create.

// Related Patterns
// -> [FactoryMethod] or [Prototype]: are often used to implement AbstractFactory.
// -> [Singleton]: A concrete factory is often a singleton.


