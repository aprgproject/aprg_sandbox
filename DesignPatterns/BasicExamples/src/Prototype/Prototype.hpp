#include <array>
#include <iostream>
#include <memory>

namespace Prototype
{

// Prototype
// declares an interface for cloning itself

class Prototype
{
public:
    virtual ~Prototype() = default;

    virtual std::unique_ptr<Prototype> clone() = 0;
    virtual std::string getType() const = 0;
    // ...
};


// Concrete Prototype A and B
// implement an operation for cloning itself

class ConcretePrototypeA : public Prototype
{
public:
    std::unique_ptr<Prototype> clone() override
    {
        return std::make_unique<ConcretePrototypeA>();
    }

    std::string getType() const override
    {
        return "type A";
    }
    // ...
};

class ConcretePrototypeB : public Prototype
{
public:
    std::unique_ptr<Prototype> clone() override
    {
        return std::make_unique<ConcretePrototypeB>();
    }

    std::string getType() const override
    {
        return "type B";
    }
    // ...
};


// Client
// creates a new object by asking a prototype to clone itself

class Client // This actually works like a "prototype manager"
{
public:
    static constexpr int NUMBER_OF_TYPES=2;

    void setPrototypeAt(int const index, std::unique_ptr<Prototype> prototype)
    {
        if(index < NUMBER_OF_TYPES)
        {
            m_types[index] = move(prototype);
        }
    }

    std::unique_ptr<Prototype> createBasedFrom(int const index)
    {
        std::unique_ptr<Prototype> result;
        if(index < NUMBER_OF_TYPES)
        {
            result = m_types.at(index)->clone();
        }
        return result;
    }
    // ...

private:
    std::array<std::unique_ptr<Prototype>, NUMBER_OF_TYPES> m_types;
};

}

// Prototype discussion:

// ONE LINE NOTE:
// -> Create objects by CLONING or copying PROTOTYPE objects that can be set in runtime.

// Intent:
// Specify the kinds of objects to create using a prototypical instance, and create new objects by copying this prototype.
// Pattern has creational purpose and deals with object relationships, which are more dynamic.
// The pattern hides the complexities of making new instances from the client.

// When to use (applicability):
// -> when the classes to instantiate are specified at run-time
// -> to avoid building a class hierarchy of factories that parallels the class hierarchy of products
// -> when instances of a class can have one of only a few different combinations of state

// Consequences:
// -> Prototype has many of the same consequences that [AbstractFactory] and [Builder] have:
// ---> It hides the concrete product classes from the client, thereby reducing the number of names clients know about.
// ---> Moreover, these patterns let a client work with application-specific classes without modification.
// -> Adding and removing products at runtime
// ---> Prototypes let you incorporate a new concrete product class into a system simply by registering a prototypical instact with the client.
// ---> That's a bit more flexible thatn other creational pattern, because a client can install and moreve prototypes at runtime.
// -> Specifying new objects by varying values.
// ---> Highly dynamic systems let you define new behavior through object composition (by specifying values for an object's variable)
// -----> You effectively define new kinds of objects by instantiating existing classes and registering the instance as prototypes of client objects.
// -----> A client can exhibit new behavior by delegating responsibility to the prototype.
// ---> This kind of design lets users define new "classes" without programming.
// -----> In fact, cloning a prototype is similar to instantiating a class.
// -----> The prototype pattern can greatly reduct the number of classes a system needs.
// -----> In our music editor, one GraphicTool class can create a limitless variety of music objects.
// -> Speciying new objects by varying structure.
// ---> Many applications build objects from parts and subparts.
// ---> For example, editors for circuit design, build circuits out of subcircuits.
// ---> For convenience, such applications often let you instantiate complex, user-defined structures, say, to use an specific subcircuit again and again.
// -----> We simply add this subcircuit as a prototype to the palette of available circuit elements.
// -----> As long as the composite circuit object implements Clone as a deep copy, circuits with different structure can be prototypes.
// -> Reduced subclassing
// ---> [FactoryMethod] often produces a hierarchy of Creator classes that parallels the product class hierarchy.
// ---> The Prototype pattern lets you clone a prototype instead of asking a factory method to make a new object.
// -----> Hence you don't need a Creator class hierarchy at all.
// -----> This benefits applies primarily to language like C++ that don't treat classes as first-class objects.
// ---> Class objects already act like prototypes in these languages.
// -> Configuring an application with classes dynamically
// ---> Some runtime environments let you load classes into an application dynamically.
// -----> The Prototype pattern is the key to exploiting such facilities in a language like C++.
// ---> An application that wants to create instances of a dynamically loaded class won't be able to reference its constructor statically.
// -----> Instead, an instance of each class is created when its loaded and it registers the instance with a prototype manager.
// -----> Then the application can ask the prototype manager for instances of newly loaded classes, classes that weren't linked with the problem originally.

// Implementation:
// -> Prototype is particularly useful with static langurage like C++, where classes are not objects and little or no type information is available at runtime.
// -> Using a "prototype manager"
// ---> When the number of prototypes in a system isn't fixed (that is, they can be created and destroyed dynamically), keep a registry of available prototypes.
// -----> Clients won't manage prototypes themselves but will store and retrieve them from the registry.
// -----> A client will ask the registry for a prototype before cloning it.
// ---> A prototype manager is an associative store that returns the prototype matching a given key.
// -----> It has operations for registering a prototype under a key and for unregistering it.
// -----> Clients can change or even browse through the registry at runtime.
// -------> This lets clients extend and take inventory on the system without writing code.
// -> Implementing the Clone operation
// ---> The hardest part of the Prototype pattern is implementing the Clone operation correctly.
// ---> Its particularly tricky when object structures contain circular references.
// ---> Most languages provide some support for cloning objects.
// -----> For example, Smalltalk provides an implementation of copy that's inherited by all subclasses of Object.
// -----> C++ provides a copy constructor, but these facilities don't solve the "shallow copy versus deep copy" problem.
// -----> That is, does cloning an object in turn clone its instance variables or do the clone and orginal just share the variables.
// ---> A shallow copy is simple and often sufficient and that's what Smalltalk provides by default.
// -----> The default copy constructor in C++ does a member-wise copy, which means pointers will be shared between the copy and the original.
// -----> But cloning prototypes with complex structures usually requires a deep copy, because the clone and the original must be independent.
// -----> Therefore you must ensure that the clone's components are clones of the prototype's components.
// -----> Cloning forces you to decide what if anything will be shared.
// ---> If objects in the system provide Save and Load operations,
// -----> then you can use them to provide a default implementation of Clone simply by saing the object and loading it back immediately
// -----> The save operation saves the object into a memory buffer.
// -----> The load operation creates a duplicate by reconstructing the object from the buffer.
// -> Initializing clones
// ---> While some clients are perfectly happy with the clone as is, other will want to initialize some or all its instanal state to values of their choosing.
// -----> You generally can't pass these values in the Clone operation, because their number will vary between classes of prototypes.
// -----> Some prototypes might need multiple initialization parameters, other won't need any.
// -----> Passing parameters in the Clone operation precludes a uniform cloning interface.
// ---> It might be the case that your prototype classes already define operations for (re)setting key pieces of state.
// -----> If so, clients may use these operations immediately after cloning.
// -----> If not, an "Initialize" operation is needed to take initialization parameters as arguments and sets the clones internal state accordingly
// -----> Beware of deep-copying Clone operations, the copies may have to be deleted (either explicitly or within "Initialize") before you reinitialize them.

// Related Patterns
// -> [Prototype] and [AbstractFactory] are competing patterns in some ways, as we discuss at the end of this chapter.
// ---> However, they can also be used together, an [AbstractFactory] might store a set of prototypes from which to clone and return products objects.
// -> Designs that make heavy use of the [Composite] and [Decorator] pattern often can benefit from [Prototype] as well.
