#include <iostream>
#include <memory>
#include <vector>

namespace Iterator
{

class Iterator;
class ConcreteAggregate;


// Aggregate
// defines an interface for aggregates and it decouples your
// client from the implementation of your collection of objects

class Aggregate
{
public:
    virtual ~Aggregate() = default;

    virtual std::unique_ptr<Iterator> createIterator() = 0;
    // ...
};


// Concrete Aggregate
// has a collection of objects and implements the method
// that returns an Iterator for its collection

class ConcreteAggregate : public Aggregate
{
public:
    ConcreteAggregate(unsigned int const size)
    {
        m_listPointer = std::make_unique<int[]>(size);
        m_count = size;
    }

    std::unique_ptr<Iterator> createIterator() override; // defined after Iterator is declared

    unsigned int size() const
    {
        return m_count;
    }

    int getValueAt(unsigned int const index)
    {
        return m_listPointer[index];
    }
    // ...

private:
    std::unique_ptr<int[]> m_listPointer;
    unsigned int m_count;
    // ...
};


// Iterator
// provides the interface that all iterators must implement and
// a set of methods for traversing over elements

class Iterator
{
public:
    virtual ~Iterator() = default;

    virtual void gotoFirst() = 0;
    virtual void gotoNext() = 0;
    virtual bool isDone() const = 0;
    virtual int getCurrentItem() const = 0;
    // ...
};


// Concrete Iterator
// implements the interface and is responsible for managing
// the current position of the iterator

class ConcreteIterator : public Iterator
{
public:
    ConcreteIterator(ConcreteAggregate & aggregate)
        : m_aggregate(aggregate)
        , index(0)
    {}

    void gotoFirst() override
    {
        index = 0;
    }

    void gotoNext() override
    {
        index++;
    }

    bool isDone() const override
    {
        return (index >= m_aggregate.size());
    }

    int getCurrentItem() const override
    {
        return isDone() ? -1 : m_aggregate.getValueAt(index);
    }
    // ...

private:
    ConcreteAggregate & m_aggregate;
    unsigned int index;
    // ...
};

std::unique_ptr<Iterator> ConcreteAggregate::createIterator()
{
    return std::make_unique<ConcreteIterator>(*this);
}

}

// Iterator discussion:

// ONE LINE NOTE:
// -> Provide a "iterator object" that can ITERATE and ACCESS elements on an AGGREGATE without EXPOSING its underlying representation.

// Intent:
// Iterator pattern has behavioral purpose and applies to objects.
// The pattern provides a way to access the elements of an aggregate object sequentially without exposing its underlying representation.

// When to use (applicability):
// -> to access an aggregate object's contents without exposing its internal representation
// -> to support multiple traversals of aggregate objects
// -> to provide a uniform interface for traversing different aggregate structures (to support polymorphic iteration)

// Consequences:
// -> It supports variation in the traversal of an aggregate.
// ---> Complex aggregates may be traversed in many ways (for example in trees, it can be preorder, inorder or postorder).
// ---> Iterators subclasses can be created to support new traversals.
// ---> Iterators make it easy to change the traversal algorithm (just change the iterator instance with a different one).
// -> Iterators simplify the Aggregate interface.
// ---> Iterator's traversal interface obviates the need for a similar interface in Aggregate (simplifying the aggregate's interface)
// -> More than one traversal can be pending on an aggregate
// ---> An iterator keeps track of its own traversal state.
// -----> Therefore you can have more than one traversal in progress at once.

// Implementation:
// -> Who controls the iteration?
// ---> A fundamental issue is deciding which party controls the iterations, the iterator or the client that uses the iterator.
// -----> Its an "external iterator" if the client controls the iteration.
// -------> Clients that use an external iterator must advance the traversal and request the next element explicitly from the iterator.
// -----> Its an "internal iterator" if the iteration controls the iterator.
// -------> The clients hands an internal iterator an operation to perform, and the iterator applies that operation to every element in the aggregate.
// -------> Internal iterators are especially weak in a language like C++ that does not provide anonymous functions, closures or continuations.
// -------> Internal iterators are easier to use, because they define the iteration logic for you.
// -> Who defines the traversal algorithm?
// ---> The iterator is not the only place where the traversal algorithm can be defined.
// -----> The when the aggregate might define the traversal algorithm and use the iterator to store just the state of iteration.
// -----> This is called a "cursor iterator", since it merely points to the current position in the aggregate.
// -----> A client will invoke the next operation on the aggregate with the cursor as an argument, and the Next operation will change the state of the "cursor".
// ---> If the iterator is responsible for the traversal algorithm, then its easy to use different iteration algorithm on the same aggregate.
// -----> Its can also be easier to reuse the same algorithm on different aggregates.
// -----> On the other hand, the traversal algorithm might need to access the private variables of the aggregate.
// -------> If so, putting the traversal algorithm in the iterator violates the encapsulation of the aggregate.
// -> How robust is the iterator?
// ---> It can be dangerous to modify an aggregate while traversing it.
// -----> If elements are added or deleted from the aggregate, you might end up accessing an element twice or missing it completely.
// -----> A simple solution is to copy the aggregate and traverse the copy, but thats too expensive to do in general.
// ---> A robust iterator ensures that insertions and removals wont interfere with traversal and it does it without copying the aggregate.
// -----> There are many ways to implement robust iterators.
// -----> Most rely on registering the iterator with the aggregate.
// -----> On insertion or removal, the aggregate either adjust the internal state of iterator or it maintains ingformation internally to ensure proper traversal.
// -> Additional iterator operations
// ---> The minimal interface to Iterator consists of the operations "First", "Next", "IsDone" and "CurrentItem".
// ---> Some other operations might prove useful. For example:
// -----> The ordered aggregates can have a "Previous" operation that positions the iterator to the previous element.
// -----> A "SkipTo" operation is useful for sorted of indexed collections, it positions the iterator to an object matching a specific criteria.
// -> Using polymorphic iterators in C++
// ---> Polymorphic iterators have their cost.
// -----> They require the iterator object to be allocated dynamically by a factory method.
// -----> Hence they should only be used when there's a need for polymorphism, otherwise use concrete iterators which can be allocated on the stack.
// ---> Polymorphic iterators have another drawback; the client is responsible on deleting them (non smart pointer iterators).
// ---> The [Proxy] pattern provides a solution.
// -----> We can use a stack allocated proxy as stand-in for the real iterator.
// -----> The [Proxy] deletes the iterator in its destructor.
// -------> When the proxy goes out of scope the real iterator will get deallocated along with it.
// -> Iterators may have privileged access
// ---> An iterator can be viewed as an extension of the aggregate that created it.
// -----> The iterator and aggregate are tightly coupled.
// -----> We can express this close relationship in C++ by making the iterator a friend of its aggregate.
// -------> Then you don't need to define aggregate operations whose sole purpose is to let iterators implement traversal efficiently.
// -> Iterators for composites
// ---> External iterators can be difficult to implment over recusive aggregate structures like those in the [Composite] pattern.
// -----> This is because the a position in the structure may span many levels of nested aggregates.
// -----> Therefore an external iterator has to store a path through the Composite to keep track of the current object.
// -----> Sometimes its easier to use an internal iterator.
// -------> It can record the current position simply by calling itself recursively thereby storing the path implicit in the call stack.
// ---> If the nodes in a Composite have an interface for moving a node to its sibling, parent and children then a cursor-based iterator is a better alternative.
// -----> The cursor only needs to keeptrack of the current node and it can rely on the node interface to traverse the Composite.
// -> Null iterators
// ---> A NullIterator is a degenerate iterator that helpful for handling boundary conditions.
// -----> By definition, a NullIterator is always done with traversal (its IsDone oepration always evaluates to true)
// ---> NullIterator can make traversing tree-structured aggregates easier.
// -----> At each point in the traversal, we ask the current element for an iterator for its children.
// -----> Aggregate elements return a concrete iterator as usual.
// -----> But Leaf elements return an instance of NullIterator.
// -------> That lets us implement traversal over the entire structure in a uniform way.

// Related Patterns
// -> [Composite]: Iterators are often applied to recursive structures such as [Composites].
// -> [FactoryMethod]: Polymorphic iterators rely on factory methods to instantiate.
// -> [Memento] is often used in conjunction with the iterator pattern.
// ---> An iterator can use a memento to capture the state of an iteration.
// ---> The iterator stores the memento to internally.