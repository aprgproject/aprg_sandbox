#include <iostream>
#include <memory>

namespace Builder
{

// Product
// the final object that will be created using Builder

class Product
{
public:
    void makeA(std::string const& part)
    {
        m_partA = part;
    }
    void makeB(std::string const& part)
    {
        m_partB = part;
    }
    void makeC(std::string const& part)
    {
        m_partC = part;
    }
    std::string getProduct()
    {
        return (m_partA + " " + m_partB + " " + m_partC);
    }
    // ...

private:
    std::string m_partA;
    std::string m_partB;
    std::string m_partC;
    // ...
};


// Builder
// abstract interface for creating products

class Builder
{
public:
    virtual ~Builder() = default;

    Product getProduct()
    {
        return m_product;
    }

    virtual void buildPartA() = 0;
    virtual void buildPartB() = 0;
    virtual void buildPartC() = 0;
    // ...

protected:
    Product m_product;
};


// Concrete Builder X and Y
// create real products and stores them in the composite structure

class ConcreteBuilderX : public Builder
{
public:
    void buildPartA() override
    {
        m_product.makeA("A-X");
    }
    void buildPartB() override
    {
        m_product.makeB("B-X");
    }
    void buildPartC() override
    {
        m_product.makeC("C-X");
    }
    // ...
};

class ConcreteBuilderY : public Builder
{
public:
    void buildPartA() override
    {
        m_product.makeA("A-Y");
    }
    void buildPartB() override
    {
        m_product.makeB("B-Y");
    }
    void buildPartC() override
    {
        m_product.makeC("C-Y");
    }
    // ...
};


// Director
// responsible for managing the correct sequence of object creation

class Director {
public:
    Director(std::unique_ptr<Builder> builder)
        : m_builder(move(builder))
    {}

    void setBuilder(std::unique_ptr<Builder> builder)
    {
        m_builder = move(builder);
    }

    Product getProduct()
    {
        return m_builder->getProduct();
    }

    void construct()
    {
        m_builder->buildPartA();
        m_builder->buildPartB();
        m_builder->buildPartC();
        // ...
    }
    // ...

private:
    std::unique_ptr<Builder> m_builder;
};

}

// Bridge discussion:

// ONE LINE NOTE:
// -> Create objects using an ABSTRACT/CHANGING BUILDER, building it STEP BY STEP, and DIRECTING it with CONSISTENT build steps

// Intent:
// Builder pattern has creational purpose and separates the construction of a complex object
// from its representation so that the same construction process can create different representations.
// It is object pattern, ie. relationships can be changed at run-time and are more dynamic.
// Often is used for building composite structures but constructing objects requires more domain knowledge of the client than using a Factory.

// When to use (applicability):
// -> the algorithm for creating a object should be independent of the parts and how they're assembled
// -> the construction process must allow different representations for the object that's constructed

// Consequences:
// -> It lets you vary a product's internal representation.
// ---> The builder object provides the director with an abstract interface for constructing the product.
// ---> The interface lets the builder hide the representation and internal structure of the product.
// -----> It also hides how the product gets assemebled
// -----> Because its an abstract interface, all you have to do to change the product internal structure is to define a new kind of builder
// -> It isolates code for construction and representation.
// ---> The Builder pattern improves modularity by encapsulating the way a complex object is constructed and represented.
// ---> Clients doesn't need to know about the classes that define the product internal structure (such classes are not exposed on the builder)
// ---> Each ConcreteBuilder contains all the code to create and assemble a particular kind of product.
// -----> The code is written once and different Directors can reuse it to build Product variants from the same set of parts.
// -> It gives you finer control over the construction process.
// ---> Unlike creational pattern that construct product in one shot, the Builder pattern construct the product step by step under the director's control.
// ---> Only when the product is finished does the director retrieve it from the builder.
// ---> Hence, the Builder interface reflects the process of constructing the product more than other creational patterns.
// ---> This gives you finer control over the construction process and consequently the internal structure of the resulting product.

// Implementation:
// -> Assembly and construction interface
// ---> Builders construct their products in step-by-step fashion.
// ---> The Builder class interface must be general enough to allow the construction of product for all kinds of concrete builders.
// ---> A key design issue concerns the model for the construction and assembly process.
// -----> A model where the results of construction request are simply appended to the product is usually sufficient.
// -> Why no abstract class for products
// ---> In the common case, the products from concrete builders differ so greatly that there is little to gain from having a common product parent class.
// ---> Because the client configures the director with a concrete builder, the client knows handle the products properly.
// -> Empty methods as default in Builder
// ---> In C++, the build methods are commonly not declared as pure virtual functions.
// -----> They are defined as empty methods instead, letting the clients override only the operation they're interested in.

// Related Patterns
// -> [Abstract factory] is similar to [Builder] in that it too may construct complex objects.
// ---> The primary difference is that the [Builder[ pattern focuses on constructing a complex object step by step.
// ---> The [AbstractFactory]'s emphasis is on families of product object (either simple or complex).
// ---> Also in [Builder] returns the product as a final step, but [AbstractFactory] the product gets returned immediately.
// -> A [Composite] is what the builder often builds.