#include <iostream>

namespace Visitor
{

class Element;
class ConcreteElementA;
class ConcreteElementB;


// Visitor
// declares a Visit operation for each class of ConcreteElement
// in the object structure

class Visitor
{
public:
    virtual ~Visitor() = default;

    virtual void visitElementA(ConcreteElementA* const) = 0;
    virtual void visitElementB(ConcreteElementB* const) = 0;
    // ...
};


// Concrete Visitors
// implement each operation declared by Visitor, which implement
// a fragment of the algorithm defined for the corresponding class
// of object in the structure

class ConcreteVisitor1 : public Visitor
{
public:
    void visitElementA(ConcreteElementA* const) override
    {
        std::cout << "Concrete Visitor 1: Element A visited.\n";
    }

    void visitElementB(ConcreteElementB* const) override
    {
        std::cout << "Concrete Visitor 1: Element B visited.\n";
    }
    // ...
};

class ConcreteVisitor2 : public Visitor
{
public:
    void visitElementA(ConcreteElementA* const) override
    {
        std::cout << "Concrete Visitor 2: Element A visited.\n";
    }

    void visitElementB(ConcreteElementB* const) override
    {
        std::cout << "Concrete Visitor 2: Element B visited.\n";
    }
    // ...
};


// Element
// defines an accept operation that takes a visitor as an argument

class Element
{
public:
    virtual ~Element() = default;

    virtual void accept(Visitor & visitor) = 0;
    // ...
};


// Concrete Elements
// implement an accept operation that takes a visitor as an argument

class ConcreteElementA : public Element
{
public:
    void accept(Visitor & visitor) override
    {
        visitor.visitElementA(this);
    }
    // ...
};

class ConcreteElementB : public Element
{
public:
    void accept(Visitor & visitor) override
    {
        visitor.visitElementB(this);
    }
    // ...
};

}

// Visitor discussion:

// ONE LINE NOTE:
// -> Provide an ABSTRACT VISITOR that can be PASSED to an ABSTRACT ELEMENT so that it can perform "visit operations" without relying on concretions.

// Intent:
// Visitor represents an operation to be performed on the elements of an object structure.// It lets you define a new operation without changing the classes of the elements on which it operates.
// The pattern has behavioral purpose and applies to the objects.

// When to use (applicability):// -> an object structure contains many classes of objects with differing interfaces,
// ---> and you want to perform operations on these objects that depend on their concrete classes
// -> many distinct and unrelated operations need to be performed on objects in an object structure,
// ---> and you want to avoid "polluting" their classes with these operations
// -> the classes defining the object structure rarely change, but you often want to define new operations over the structure

// Consequences:
// -> Visitor makes adding new operation easy.
// ---> Visitors make it easy to add operations that depend on the components of complex objects.
// ---> You can define a new operation over an object sturcut simply by adding a new visitor.
// ---> In contrast, if you spread functionality over many classes, then you must change each class to define a new operation.
// -> A visitor gather related operation and separate unrelated ones
// ---> Related behavior isn't spread over the classes defining the object structure; it's localized in a visitor.
// ---> Unrelated sets of behavior are partitioned in their own visitor subclasses.
// ---> That simplifies both the classes defining the elements and the algorithms defined in the visitors.
// ---> An algorithm-specific data structures can be hidden in the visitor.
// -> Adding new ConcreteElement classes is hard
// ---> The visitor pattern makes it hard to add new subclasses of Element.
// -----> Each new ConcreteElement gives rise to a new abstract operation on Visitor and a corresponding implementation in every ConcreteVisitor class.
// -----> Sometimes a default implementation can be provided in Visitor that can be inherited by most of the ConcreteVisitors,
// -------> but this is the exception rather than the rule.
// ---> So the key consideration in applying the Visitor pattern is whether:
// -----> you are mostly likely to change the algorithm applied over an object structure
// -----> or the classes of objects that make up the structure
// ---> The Visitor class hierarchy can be difficult to maintain when new ConcreteElement classes are added frequently.
// -----> In such cases, its probably easier just to define operation on the classes that make up the structure.
// -----> If the Element class hierarchy is stable, but you are continually adding operations or changing algorithms,
// -------> then the Visitor pattern will help you manage the changes.
// -> Visiting across class hierarchies
// ---> An [iterator] can visit the objects in a structure as it traverses them by calling their operations.
// -----> But an iterator can't work across object structures with different types of elements.
// -> Accumulating state
// ---> Visitor can accumulate state as they visit each element in th object structure.
// -----> Without a visitor, this state would be passed as extra arguments to the operations that perform the traversal, or they might appear as global variables.
// -> Breaking encapsulation
// ---> Visitor approach assumes that the ConcreteElement interface is powerful enough to let visitor do their job.
// ---> As a result, pattern often forces you to provide public operations that access an element's internal state, which may compromise its encapsulation.

// Implementation:
// -> Each object structure will have an associated Visitor class.
// ---> This abstract visitor class declares a VisitConcreteElement operation for each class of ConcreteElement defining the object structure.
// ---> Each Visit operation on the Visitor declares its argument to be a particular ConcreteElement,
// -----> allowing the Visitor to access the interface of the ConcreteElement directly.
// ---> ConcreteVisitor classes override each Visit operation to implement visitor-specific behavior for the corresponding ConcreteElement class.
// ---> Each class of ConcreteElement implements an Accept operation that calls the matching Visit... operation on the visitor for the ConcreteElement.
// -----> Thus the operation that ends up getting called depends on both the class of the element and the class of the visitor.
// -> Double dispatch
// ---> Effectively, the Visitor pattern lets you add operations to classes without changing them.
// -----> Visitor achieves this by using a technique called "double dispatch" (It's a well-known technique).
// -------> In fact, some programming langurages support this directly.
// -------> Languages like C++ and Smalltalk support single-dispatch.
// ---> "Double dispatch" simplify means the operation that gets executed depends on the kind of request and the types of two receivers.
// -----> Accept is a double-dispath operation.
// -------> Its meaning depends on two type: the Visitor's and the Element's.
// -------> Double-dispatching lets visitors request different operations on each class of element.
// ---> This is the key of the Visitor pattern:
// -----> The operation that gets executed depends on both the type of Visitor and the type Element it visits.
// -----> Instead of binding operations statically into the Element interface,
// -------> you can consolidate the operations in a Visitor and use Accept to do the binding at runtime.
// -----> Extending the Element interface amounts to defining one new Visitor subclass rather than many new Element subclasses.
// -> Who is responsible for traversing the object structure?
// ---> A visitor must visit each element of the object structure. The question is, how does it get there?
// ---> We can put responsibility for traversal in any of three places:
// -----> (1) in the object structure
// -----> (2) in the visitor
// -----> (3) or in a separate iterator object.
// ---> Often the object structure is responsible for iteration.
// -----> A collection will simply iterate over its elements, calling the Accept oepration on each.
// -----> A composite will commonly traverse itself by having each Accept operation traverse the element's children and call Accpet on each of them recursively.
// ---> Another solution is to use an iterator to visit the elements.
// -----> In C++, you could use either an internal or external iterator, depending on what is available and what is most efficient.
// ---> You could even put the traversal algorithm in the visitor,
// -----> although youll end up duplicating the traversal code in each ConcreteVisitor for each aggregate ConcreteElement.
// ---> The main reason to put the traversal strategy in the visitor is to implement a particularly complex traversal,
// -----> one that depends on the results of the operations on the object structure.

// Related Patterns
// -> [Composite]: Visitors can be used to apply an operation over an object structure defined by the [Composite] pattern.
// -> [Interpreter]: Visitors may be applied to do interpretation.
