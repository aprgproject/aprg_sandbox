#include <iostream>
#include <memory>
#include <vector>

namespace Composite {

// Component
// defines an interface for all objects in the composition
// both the composite and the leaf nodes

class Component {
public:
    virtual ~Component() = default;

    virtual Component const* getChildPointerAt(
        int const) const  // Make sure that this doesn't break interface segregation principle. (Make sure the
                                   // method/function makes sense.)
    {
        return nullptr;    }

    virtual void add(std::unique_ptr<Component>)  // Make sure that this doesn't break interface segregation principle.
                                                  // (Make sure the method/function makes sense.)    {
        //...
    }

    virtual void removeAtIndex(int const)  // Make sure that this doesn't break interface segregation
                                                    // principle. (Make sure the method/function makes sense.)
    {
        //...    }

    virtual void operation() = 0;
};
// Composite
// defines behavior of the components having children
// and store child components

class Composite : public Component {
public:
    Component const* getChildPointerAt(int const index) const override { return m_children.at(index).get(); }

    void add(std::unique_ptr<Component> component) override { m_children.emplace_back(move(component)); }

    void removeAtIndex(int const index) override { m_children.erase(m_children.begin() + index); }

    void operation() override {
        for (auto& child : m_children) {            child->operation();
        }
    }
private:
    std::vector<std::unique_ptr<Component>> m_children;
};

// Leaf
// defines the behavior for the elements in the composition,
// it has no children

class Leaf : public Component {
public:
    Leaf(int const id) : m_id(id) {}

    void operation() override { std::cout << "Leaf " << m_id << " operation\n"; }

private:
    int m_id;
};

}  // namespace Composite
// Composite discussion:

// ONE LINE NOTE:// -> Provide an object that CAN be an "individual object" or a "composite object", and they are treated UNIFORMLY

// Intent:
// Compose objects into tree structures to represent part-whole hierarchies.
// Composite lets clients treat individual objects and compositions of objects uniformly.
// The pattern has structural purpose and applies to objects.
// NOTE: Please make sure that pattern actually fits the concepts that Leaves and Compositions
// -> are treated uniformly to avoid violating the interface segregation principle.

// When to use (applicability):
// -> you want to represent part-whole hierarchies of objects
// -> you want clients to be able to ignore the difference between compositions of objects and individual objects

// Consequences:
// -> The Composite pattern defines class hierarchies consisting of primitive objects and composite objects.
// ---> Primitive objects can be composed into more complex objects, which in turn can be composed, and so on
// recursively.
// ---> Whenever client code expects a primitive object, it can also take a composite object.
// -> The Composite pattern makes the client simple.
// ---> Clients can treat composite structures and individual objects uniformly.
// ---> Clients don't know (and shouldn't care) whether they're dealing with a leaf or a composite component.
// ---> This simplifies client code because it avoid having to write tag-and-case-statement-style functions that define
// the composition.
// -> The Composite pattern makes it easier to add new kinds of components.
// ---> Newly defined Composite or Leaf subclasses work automatically with existing structures and client code.
// ---> Clients dont have to be changed for new Component classes.
// -> The Composite pattern can make you design overly general.
// ---> The disadvantage of making it easy to add new component is that it makes it harder to restrict the components of
// a composite.
// ---> Sometimes, you want a composite to have only certain components.
// -----> You can't rely on the type system to enforce those constraints for you. Youll have to use run-time checks
// instead.

// Implementation:
// -> Explicit parent references
// ---> Maintaining parent reference from child components can simplify the traversal and management of a composite
// structure.
// ---> The parent reference simplifies moving up the structure and deleting a component.
// ---> Parent references also help support [Chain of Responsibility] pattern.
// ---> The usual place to define the parent reference is in the component class.
// -----> Leaf and component classes can inherit the reference and the operations that manage it.
// -> Sharing components
// ---> It's often useful to share components, for example, to reduce storage requirements.
// ---> But then a component can have no more than one parent, sharing components becomes difficult (shared_ptr maybe?)
// ---> A possible solution is for children to store multiple parents.
// -----> But that can lead to ambiguities as a request propagates up the structure.
// ---> The [Flyweight] patterns shows how to rework a design to avoid strong parent altogether.
// -> Maximizing the Component interface
// ---> The Component class should define as many common operations for Leaf and Composite classes as possible
// (factoring out commonality).
// ---> The Component class usually provide default implementations for these operations and Leaf and Composite sub
// classes will override them.
// ---> This can possibly conflict with the ISP (Interface Segregation Principle).
// -----> The principle of class hierarchy design that says a class should only define operations that are meaningful to
// its subclasses.
// -----> Litte Creativity: An operation that would make sense only for Composites can be put for all Components by
// moving it to the Component class.
// -------> For example, a Leaf is a component that never has children.
// -------> Therefore we can define a default operation for child access in the Component class that never returns
// children.
// -------> Leaf classes can use the default implementation, but composite classes will reimplement it to return their
// children.
// -> Declaring the child management operations
// ---> Which classes declare these child management operations ("add" and "remove") in the Composite class hierarchy?
// -----> Should we add this on Component and make this visible on the Leaf? or only Composite?
// -------> This a decision involves a trade-off between "safety" and "transparency".
// -----> Defining the child management interface at the root of the class hierarchy gives "transparency" but it costs
// "safety".
// -------> It gives "transparency" because we can treat all components uniformly.
// -------> It costs "safety" because the client may try to do meaningless things like "add" and "remove" objects from
// leaves.
// -----> Defining the child management in the Composite class gives "safety" but loses "transparency".
// -------> It gives "safety" because any attempt to add or remove objects from leaves will be caught at compile time.
// -------> It loses "transparency" because Leaves and Composites have different interfaces.
// ---> If we opt for "safety", then at times we lose type information, how can we use composites without the
// type-unsafe cast?
// -----> Create a method getComposite at Component that returns Composite* if its valid (for leaves it returns null).
// -----> Similar tests for a Composite can be donte using the C++ dynamic_cast construct.
// ---> The only way to provide transparency is to define default "add" and "remove" in Component.
// -----> This creates a new problem, it introduces the possibility of the functions failing ("add" can fail).
// -------> You could make it do nothing, but that ignores an important consideration (introducing surprise to the
// reader).
// -> Should Component implement a list of Components?
// ---> Defining the set of children and using a child pointer in the Component class introduces space penalty for every
// leaf.
// -> Child ordering
// ---> Many designs specify an ordering on the children of Composite.
// ---> When child ordering is an issue, you desing child access and management interface carefully to manage the
// sequence of children.
// -> Caching to improve performance
// ---> If you need to traverse/search frequently, the composite class can cache traversal or search information about
// its children.
// -----> The composite can cache actual information and jump the traversal to quickly finish.
// -----> Changes to a component will require invalidating the caches of its parents.
// -------> Thus if you are using caching, you need to define an interface for telling composites that their caches are
// invalid.
// -> Who should delete components?
// ---> In languages without garbage collection, its usually best to make a composite responsible for deleting its
// children when its destroyed.
// -----> An exception to this rule is when Leaf objects are immutable and thus can be shared.
// -> Whats the best data for storing Components?
// ---> Coponsite may use a variety fo data structues to store their children.
// -----> This includes the linked list, tree, array and hash tables.
// -----> The choice of data structure depends on efficiency of needed operations.
// -----> In fact, it isn't even necessary to use a general purpose data structure at all.
// -----> Sometimes composites have variable for each child
// -------> Although this requires each subclass of Composite to implement its own management interface (see
// [Interpreter] pattern).

// Related Patterns
// -> The component parent link is used for a [Chain of responsibility]
// -> [Decorator] is often used with Composite.
// ---> When decorator and composites are used together, they usually have a common parent class.
// ---> So decorators will have to support the Component interface with operations like Add, Remove, and GetChild.
// -> [Flyweight] lets you share components but they can no longer refer to their parents.
// -> [Iterator] can be used to traverse composites.
// -> [Visitor] localizes operations and behavior that would otherwise be distributed across Composite and Leaf classes.
