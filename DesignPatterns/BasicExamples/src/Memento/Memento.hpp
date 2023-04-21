#include <iostream>
#include <memory>
#include <vector>

namespace Memento
{

// Memento
// stores internal state of the Originator object
// and protects against access by objects other than the originator

class Memento
{
private:
    friend class Originator; // accessible only to Originator

    Memento(int const state)
        : m_state(state)
    {}

    int getState() const
    {
        return m_state;
    }

    void setState(int const state)
    {
        m_state = state;
    }
    // ...

private:
    int m_state;
    // ...
};


// Originator
// creates a memento containing a snapshot of its current internal state
// and uses the memento to restore its internal state

class Originator
{
public:
    static constexpr int INVALID_STATE=0;

    Originator()
        : m_state(INVALID_STATE)
    {}

    Originator(int const state)
        : m_state(state)
    {}

    std::unique_ptr<Memento> createMemento() const
    {
        std::cout << "In Originator, createMemento() with " << m_state << ".\n";
        return std::unique_ptr<Memento>(new Memento(m_state));
    }

    void restoreFromMemento(Memento const& memento)
    {
        m_state = memento.getState();
        std::cout << "In Originator, restoreMemento() to " << m_state << ".\n";
    }

private:
    int m_state;
    // ...
};


// CareTaker
// is responsible for the memento's safe keeping

class CareTaker
{
public:
    void save(Originator const& originator)
    {
        std::cout << "In CareTaker, save state.\n";
        m_history.emplace_back(originator.createMemento());
    }

    Originator undoAndGetLastOriginator()
    {
        Originator result;
        if(!m_history.empty())
        {
            std::cout << "In CareTaker, undo state.\n";
            result.restoreFromMemento(*(m_history.back()));
            m_history.pop_back();
        }
        else
        {
            std::cout << "In CareTaker, Unable to undo state.\n";
        }
        return result;
    }
    // ...

private:
    std::vector<std::unique_ptr<Memento>> m_history;
    // ...
};

}

// Memento discussion:

// ONE LINE NOTE:
// -> Provide a "memento object" that SAVES the STATE of an "originator object" so that it can be RESTORED later.

// Intent:
// Memento without violating encapsulation, captures snd externalizes an object's internal state
// so that the object can be restored to this state later.
// The pattern has behavioral purpose and applies to the objects.

// When to use (applicability):
// -> a snapshot of an object's state must be saved so that it can be restored to that state later
// -> a direct interface to obtaining the state would expose implementation details and break the object's encapsulation

// Consequences:
// -> Preserving encapsulation boundaries.
// ---> Memento avoids exposing information that only an originator should manage but that must be store nevertheless outside the originator.
// ---> The pattern shields other from potentially complex Originator internals, thereby preserving encapsulation boundaries.
// -> It simplifies Originator.
// ---> In other encapsulation-preserving designs, Originator keeps the version of internal state that clients have requested.
// ---> That puts all the storage managment burden on Originator.
// ---> Having clients manage the state they ask for simplifies Originator and keeps clients from hacing to notify orgiginator when they're done.
// -> Using mementos might be expensive.
// ---> Mementos might incur considerable overhead if Originator must copy large amounts of information to store in the memento
// -----> or if clients create and return mementos to originator often enough.
// ---> Unless encapsulating and restoring Originator state is cheap, the pattern might not be appropriate (see incremental part in Implementation).
// -> Defining narrow and wide interfaces.
// ---> It may difficult in some languages to ensure that only the originator can access the memento's state.
// -> Hidden costs in caring for mementos.
// ---> A caretaker is responsible for deleting the mementos it cares for.
// -----> However, the caretaker has no idea how much state is in the memento.
// -----> Hence, an otherwise lightweight caretaker might incur large storage costs when it store mementos.

// Implementation:
// -> Language support
// ---> Mementos have two interface: a wide one for originators and a narrow one for other objects.
// ---> Ideally the implementation langurage will support two levels of static protection.
// -----> C++ lets you do this by making the Originator a friend of Memento and making Memento's wide interface private.
// -> Storing incremental changes.
// ---> When mementos get created and passed back to their originator in a predictable sequence,
// -----> then Memento can save just the incremental change to the originator's internal state.
// ---> For example, undoable commands in a history list can use mementos to ensure that commands are restored to their state when they undone.
// -----> The history list defines a specific order in which commands can be undone and redone.
// -----> That means mementos can store just the incremental change that a command makes rather than the full state of every object they affect.

// Related Patterns
// -> [Command]: [Commands] can use mementos maintain state for undoable operations.
// -> [Iterator]: Mementos can be used for iteration.