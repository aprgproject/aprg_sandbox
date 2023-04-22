#include <iostream>
#include <memory>

namespace State
{

// State
// defines an interface for encapsulating the behavior associated
// with a particular state of the Context

class State
{
public:
    virtual ~State() = default;

    virtual void handle() = 0;
    // ...
};


// Concrete States
// each subclass implements a behavior associated with a state
// of the Context

class ConcreteStateA : public State
{
public:
    void handle() override
    {
        std::cout << "State A handled.\n";
    }
    // ...
};

class ConcreteStateB : public State
{
public:
    void handle() override
    {
        std::cout << "State B handled.\n";
    }
    // ...
};


// Context
// defines the interface of interest to clients

class Context
{
public:
    Context()
        : m_statePointer() // default state
    {
        //...
    }

    void setState(std::unique_ptr<State> statePointer)
    {
        m_statePointer = move(statePointer);
    }

    void request()
    {
        m_statePointer->handle();
    }
    // ...

private:
    std::unique_ptr<State> m_statePointer;
    // ...
};

}

// State discussion:

// ONE LINE NOTE:
// -> Implement a common ABSTRACT STATE INTERFACE and implement different STATE SPECIFIC BEHAVIORS by having STATE SUBCLASSES

// Intent:
// The pattern allows an object to alter its behavior when its internal state changes.
// The object will appear to change its class.
// It has behavioral purpose and applies to the objects.

// When to use (applicability):
// -> when an object's behavior depends on its state, and it must change its behavior at run-time depending on that state
// -> operations have large, multipart conditional statements that depend on the object's state

// Consequences:
// -> It localizes state-specific behavior and partitions behavior for different states.
// ---> The State pattern puts all behavior associated with a particular state into one object/class.
// -----> Because all state-specific code lives in a State subclass, new states and transitions can be added easily by defining new subclasses.
// ---> An alternative is to use data values to define internal states and have Context operations check the data explicitly.
// -----> But then we'd look-alike conditional or case statements scattered throughout Context's implementation.
// -----> Adding a new state could require changing several operations, which complicates maintenance (violates the open/close priniciple).
// -------> The state pattern avoids this problem but might introduce another, it distributes behavior of different states across several State subclasses.
// ---------> This increases the number of classes and is less compact than a single class.
// -> It makes state transition explicit.
// ---> When an object defines its current state solely in terms of internal data values,
// -----> its state transitions have no explicit representation and they only show up as assignments to some variables.
// ---> Introducing separate objects for different states makes the transitions more explicit.
// ---> State object can protect the Context from inconsistent internal states because state transistion are atomic from Context perspective.
// -> State objects can be shared.
// ---> If state objects have no instance variables(they represented entirely in their type), then the contexts can share a State object.
// -----> When states are shared in this way, they are essentially flyweights with no intrinsic state only behavior.

// Implementation:
// -> Who defines the state transitions?
// ---> The state pattern does not specify which participant defines the criteria for state transitions.
// -----> If the criteria are fixed, then they can implemented entirely in the Context.
// -----> However, it is generally more flexible, to let the State subclasses themselves specify their successor state and when to make the transistion.
// -------> This requires adding an interface to the Context that lets State objects set the Context current state explicitly.
// ---> Decentralizing the transition logic in this way makes it easy to modify or extend the logic by defining new state subclasses.
// -----> A disadvantage of decentralization is that one State subclass will have knowledge of at least one other, which introduces implementation dependencies.
// -> A table-based alternative (or matrix alternative)
// ---> Tables can be used to map inputs to state transitions.
// -----> For each state, a table maps every possible input to a succeeding state.
// -----> In effect, this approach converts conditional code (states as variable) or virtual dispatch (state pattern) into a table look-up.
// ---> Advantage: You can change the transition criteria by modifying data instead of changing program code.
// ---> Disadvantages:
// -----> A table look-up is often less efficient that a virtual function call (Note: Can't claim really without testing).
// -----> Putting transition logic into a uniform, tabular format makes the transition criteria less explicit and therefore harder to understand.
// -----> Its usually difficult to add actions to accompany the state transitions.
// -------> The table-driven approach captures the states and their transitions, but it must be augmented to perform arbitiary computation on each transition.
// -> Creating and destroying state objects
// ---> A common implmentation trade-off worth considering is whether:
// -----> (1) to create State objects only when they are needed and destroy them thereafter
// -------> This is preferable if the states that will be entered aren't known at runtime and contexts change state infrequently.
// -------> This approach avoids creating objects that wont be used, which is important if the State objects store a lot of information.
// -----> (2) to create State objects ahead of time and never destroying them
// -------> This is better when the states changes occur rapidly, in which case you want to avoid destroying state to avoid delays.
// -------> Instantiation cost are paid once up-front and destruction costs only occurs when program is terminated.
// -------> This approach might be inconvenient, though, because the Context must keep references to all states that might be entered.
// -> Using dynamic inheritance
// ---> Changing the behavior for a particular request could be accomplished by changing object class at runtime but its not possible in most OOP languages.
// -----> This is not possible in C++.

// Related Patterns
// -> The [Flyweight] pattern explains when and how State objects can be shared.
// -> State objects are often [Singletons].
