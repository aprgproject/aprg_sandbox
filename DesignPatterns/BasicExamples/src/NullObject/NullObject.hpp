#include <array>
#include <iostream>
#include <memory>

namespace NullObject {

// NullObject
// implements default behavior for the interface common to all classes

class AbstractObject {
public:
    virtual ~AbstractObject() = default;

    virtual void doSomething() = 0;
    // ...
};

// RealObject
// defines a concrete subclass of AbstractObject whose instances provide useful behavior that Client expects.

class RealObject : public AbstractObject {
public:
    void doSomething() override {
        // Do something for a valid object.
        std::cout << "RealObject did something.\n";
    }
    // ...
};

// NullObject
// provides an interface identical to AbstractObject's so that a null object can be substituted for a real object

class NullObject : public AbstractObject {
public:
    void doSomething() override {
        // Do something for a null object.
        std::cout << "NullObject did nothing.\n";
    }

    // ...
};

}  // namespace NullObject

// NullObject discussion:

// ONE LINE NOTE:
// -> Create a NULL OBJECT to HANDLE special NULL or EMPTY cases with polymorphism.

// Intent:
// The Null object pattern is a design pattern that handles null references.
// Null objects can arise in a program and it is usually handled as a special case which is unnecessarily adds a test
// case. A better way to handle this is to add native support for null objects in the class design.

// It focuses on simplifying the use of dependencies.
// The given operation is achieved by using instances of a concrete class that further implements a known interface,
// instead of null references.

// When to use (applicability):
// -> an object requires a collaborator.
// ---> The Null Object pattern does not introduce this collaboration.
// ---> It makes use of a collaboration that already exists
// -> some collaborator instances should do nothing
// -> you want to abstract the handling of null away from the client

// Consequences:
// ---> The Null Object pattern defines class hierarchies consisting of real objects and null objects.
// -----> Null objects can be used in place of real objects when the object is expected to do nothing.
// -----> Whenever client code expects a real object, it can also take a null object.
// ---> The Null Object pattern makes client code simple.
// -----> Clients can treat real collaborators and null collaborators uniformly.
// -----> Clients normally don't know (and shouldn't care) whether they're dealing with a real or a null collaborator.
// -----> This simplifies client code, because it avoids having to write testing code which handles the null
// collaborator specially.
// ---> The Null Object pattern encapsulates the do nothing code into the null object.
// -----> The do nothing code is easy to find.
// -----> Its variation with the AbstractObject and RealObject classes is readily apparent.
// -----> It can be efficiently coded to do nothing.
// -----> It does not require variables that contain null values because those values can be hard-coded as constants
// -------> or the do nothing code can avoid using those values altogether.
// ---> The Null Object pattern makes the do nothing code in the null object easy to reuse.
// -----> Multiple clients which all need their collaborators to do nothing will all do nothing the same way.
// -----> If the do nothing behavior needs to be modified, the code can be changed in one place.
// -----> Thereafter, all clients will continue to use the same do nothing behavior, which is now the modified do
// nothing behavior.
// ---> The Null Object pattern makes the do nothing behavior difficult to distribute or mix into the real behavior of
// several collaborating objects.
// -----> The same do nothing behavior cannot easily be added to several classes
// -------> unless those classes all delegate the behavior to a class which can be a null object class.
// ---> The Null Object pattern can necessitate creating a new NullObject class for every new AbstractObject class.
// ---> The Null Object pattern can be difficult to implement if various clients do not agree
// -----> on how the null object should do nothing as when your AbstractObject interface is not well defined.
// ---> The Null Object pattern always acts as a do nothing object.
// -----> The Null Object does not transform into a Real Object.

// Implementation:
// -> There are several issues to consider when implementing the Null Object pattern:
// ---> Null Object as Singleton.
// -----> The Null Object class is often implemented as a Singleton [GHJV95, page 127].
// -----> Since a null object usually does not have any state, its state can't change, so multiple instances are
// identical.
// -----> Rather than use multiple identical instances, the system can just use a single instance repeatedly.
// ---> Clients don't agree on null behavior.
// -----> If some clients expect the null object to do nothing one way and some another, multiple NullObject classes
// will be required.
// -----> If the do nothing behavior must be customized at run time,
// -------> the NullObject class will require pluggable variables so that the client can specify how the null object
// should do nothing.
// -----> This may generally be a symptom of the AbstractObject not having a well defined (semantic) interface.
// ---> Transformation to Real Object.
// -----> A Null Object does not transform to become a Real Object.
// -----> If the object may decide to stop providing do nothing behavior and start providing real behavior, it is not a
// null object.
// -----> It may be a real object with a do nothing mode, such as a controller which can switch in and out of read-only
// mode.
// -----> If it is a single object which must mutate from a do nothing object to a real one,
// -------> it should be implemented with the State pattern [GHJV95, page 305] or perhaps the Proxy pattern [GHJV95,
// page 207].
// -----> In this case a Null State may be used or the proxy may hold a Null Object.
// ---> Null Object is not Proxy.
// -----> The use of a null object can be similar to that of a Proxy [GHJV95, page 207], but the two patterns have
// different purposes.
// -----> A proxy provides a level of indirection when accessing a real subject, thus controlling access to the subject.
// -----> A null collaborator does not hide a real object and control access to it, it replaces the real object.
// -----> A proxy may eventually mutate to start acting like a real subject.
// -----> A null object will not mutate to start providing real behavior, it will always provide do nothing behavior.
// ---> Null Object as special Strategy.
// -----> A Null Object can be a special case of the Strategy pattern [GHJV95, page 315].
// -----> Strategy specifies several ConcreteStrategy classes as different approaches for accomplishing a task.
// -----> If one of those approaches is to consistently do nothing, that ConcreteStrategy is a NullObject.
// -----> For example, a Controller is a View's Strategy for handling input, and NoController is the Strategy that
// ignores all input.
// ---> Null Object as special State.
// -----> A Null Object can be a special case of the State pattern [GHJV95, page 305].
// -----> Normally, each ConcreteState has some do nothing methods because they're not appropriate for that state.
// -----> In fact, a given method is often implemented to do something useful in most states but to do nothing in at
// least one state.
// -----> If a particular ConcreteState implements most of its methods to do nothing or at least give null results,
// -------> it becomes a do nothing state and as such is a null state. [Woolf96]
// ---> Null Object as Visitor host.
// -----> A Null Object can be used to allow a Visitor [GHJV95, page 331] to safely visit a hierarchy and handle the
// null situation.
// ---> The Null Object class is not a mixin.
// -----> Null Object is a concrete collaborator class that acts as the collaborator for a client which needs one.
// -----> The null behavior is not designed to be mixed into an object that needs some do nothing behavior.
// -----> It is designed for a class which delegates to a collaborator all of the behavior that may or may not be do
// nothing behavior. [Woolf96]

// Related Patterns
// -> It can be regarded as a special case of the [State] pattern and the [Strategy] pattern.
