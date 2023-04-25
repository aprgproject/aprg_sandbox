#include <iostream>
#include <vector>

namespace Observer {

class Subject;

// Observer
// defines an updating interface for objects that should be notified
// of changes in a subject

class Observer {
public:
    virtual ~Observer() = default;

    virtual int getState() const = 0;
    virtual void update(Subject const* const subject) = 0;
    // ...
};

// Concrete Observer
// stores state of interest to ConcreteObserver objects and
// sends a notification to its observers when its state changes

class ConcreteObserver : public Observer {
public:
    ConcreteObserver(const int state) : m_observer_state(state) {}

    int getState() const override { return m_observer_state; }

    void update(Subject const* const subject) override;
    // ...

private:
    int m_observer_state;
    // ...
};

// Subject
// knows its observers and provides an interface for attaching
// and detaching observers

class Subject {
public:
    virtual ~Subject() = default;

    void attach(Observer* observer) { m_observerPointers.emplace_back(observer); }

    void detach(const int index) { m_observerPointers.erase(m_observerPointers.begin() + index); }

    void notify() {
        for (Observer* observerPointer : m_observerPointers) {
            observerPointer->update(this);
        }
    }

    virtual int getState() const = 0;
    virtual void setState(const int s) = 0;
    // ...

private:
    std::vector<Observer*> m_observerPointers;
    // ...
};

// Concrete Subject
// stores state that should stay consistent with the subject's

class ConcreteSubject : public Subject {
public:
    int getState() const override { return m_subjectState; }

    void setState(int const state) override { m_subjectState = state; }
    // ...

private:
    int m_subjectState;
    // ...
};

void ConcreteObserver::update(
    Subject const* const subject)  // Implementation is here because subject needs to be defined first
{
    m_observer_state = subject->getState();
    std::cout << "Observer state updated.\n";
}

}  // namespace Observer

// Observer discussion:

// ONE LINE NOTE:
// -> Have Observers OBSERVE a Subject/Observable so that when something is changed, the Observers are NOTIFIED and
// UPDATED AUTOMATICALLY

// Intent:
// Observer defines a one-to-many dependency between objects so that when one object changes state,
// all its dependents are notified and updated automatically.
// The pattern has behavioral purpose and applies to the objects.

// When to use (applicability):
// -> when an abstraction has two aspects, one dependent on the other
// -> when a change to one object requires changing others, and you don't know how many objects need to be changed
// -> when an object should be able to notify other objects without making assumptions about who these objects are

// Consequences:
// -> Abstract coupling between Subject and Observer
// ---> Subject does not know the concrete class of any observer, thus coupling needs to be abstract and minimal
// ---> Since Subject and Observer are loosely coupled, they can belong to different layes of abstraction in a system.
// -> Support for broadcast communication
// ---> Unlike an ordinary request, the notification that a subject sends needn't specify its reciever
// -> Unexpected updates
// ---> Because observers have no knowledge of each other's presence, they can be blind to the ultimate cost of changing
// the subject.
// -----> A seemingly innocuous operation on the subject may cause a cascade of updates to observers and their dependent
// objects.
// -----> Moreover, dependency criteria that aren't well-defined or maintained usually lead to spurious updates (which
// can be hard to track down).
// ---> It can be a problem since there no details on what changed in the subject.

// Implementation:
// -> Mapping subject to thair observers.
// ---> The simplest way for a subject to keep track of the observers it should notify is to store references to them
// explicitly in the subject.
// -----> One solution is to trade space for time by using associative look-up (hash table) to maintain the subject to
// observer mapping.
// -> Observing more than one subject.
// ---> It might make sense in some situations for an observer to depend on more than one subject.
// ---> It might be necessary to extend the update interface to let the observer which subject is sending the
// notification.
// -> Who triggers the update?
// ---> The subject and its observers rely on the notification mechanism to stay consistent.
// ---> But what object actually calls notify to trigger the update? Here are two options:
// -----> (1) Have state-setting operations on Subject call Notify after they change the subject's state.
// -----> (2) Make clients responsible for calling Notify at the right time.
// -------> The advantage here is that the client can wait to trigger the update
// -------> until after series of state changes has been made, thus avoiding needless intermediate updates.
// -> Dangling reference to deleted Subjects (when no RAII is used)
// -> Making sure Subject state is self consistent before notification
// ---> This is important because observers query the subject for its current state in the course of updating their own
// state.
// -> Avoiding observer specific protocols (the push and pull models)
// ---> The push model: The subject sends observers detailed information about the change (whether its needed or not).
// -----> This assumes that subjects know something about their observers needs.
// -----> This might make observers less reusable.
// ---> The pull model: The subject sends nothing but the most minimal notification, and observers ask for details
// explicitly there after.
// -----> This assumes that subjects dont care about their needs.
// -----> This might be less efficient because Observer does not know what was changed in the subject.
// -> Specifying modifications of interest explicitly.
// ---> You can improve update efficiency by extending the subject's registration interface
// -----> to allow registering objects only for specific events of interest
// -----> When a particular event occurs, only Observers registered for that will be updated.
// -> Encapsulating complex update semantics.
// ---> An ChangeManager might be needed when the dependency relationship between Subjects and Observers is complex.
// -----> A ChangeManager has three responsibilities
// -----> 1) It maps a subject to its observers and provide an interface to maintain this mapping.
// -----> 2) It defines a particular update strategy.
// -----> 3) It updates all dependent observers at the request of a subject.

// Related Patterns
// -> [Mediator]: By encapsulating complex update semantics, the ChangeManager acts a mediator between subjects and
// observers.
// -> [Singleton]: The ChangeManager may use the Singleton pattern to make it unique and globally accessible
