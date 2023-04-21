#include <iostream>
#include <functional>
#include <vector>

namespace Mediator
{

class Mediator;

// Colleague classes
// each colleague communicates with its mediator whenever
// it would have otherwise communicated with another colleague

class Colleague
{
public:
    Colleague(
            Mediator & mediator,
            const unsigned int id)
        : m_mediator(mediator)
        , m_id(id)
    {}

    virtual ~Colleague() = default;

    unsigned int getID() const
    {
        return m_id;
    }

    virtual void send(std::string const&) = 0;
    virtual void receive(std::string const&) = 0;

protected:
    Mediator & m_mediator;
    unsigned int m_id;
};

class ConcreteColleague : public Colleague
{
public:
    ConcreteColleague(
            Mediator & mediator,
            unsigned int const id)
        : Colleague(mediator, id)
    {}

    void send(std::string const& message) override;
    void receive(std::string const& message) override;
};


// Mediator
// defines an interface for communicating with Colleague objects

class Mediator
{
public:
    virtual ~Mediator() = default;

    virtual void add(Colleague & colleague) = 0;
    virtual void distribute(Colleague const& sender, std::string const& message) = 0;

protected:
    Mediator() = default;
};


// Concrete Mediator
// implements cooperative behavior by coordinating Colleague objects
// and knows its colleagues

class ConcreteMediator : public Mediator
{
public:
    void add(Colleague & colleague) override
    {
        m_colleagueReferences.emplace_back(colleague);
    }

    void distribute(Colleague const& sender, std::string const& message) override
    {
        for (auto & colleagueReference : m_colleagueReferences)
        {
            if(colleagueReference.get().getID() != sender.getID())
            {
                colleagueReference.get().receive(message);
            }
        }
    }

private:
    std::vector<std::reference_wrapper<Colleague>> m_colleagueReferences;
};

void ConcreteColleague::send(std::string const& message)
{
    std::cout << "Message '"<< message << "' sent by Colleague " << m_id << "\n";
    m_mediator.distribute(*this, message);
}

void ConcreteColleague::receive(std::string const& message)
{
    std::cout << "Message '" << message << "' received by Colleague " << m_id << "\n";
}

}

// Mediator discussion:

// ONE LINE NOTE:
// -> MEDIATE communications between different colleagues to decouple, simplify, abstract, centralize the way of communication.

// Intent:
// Mediator pattern has behavioral purpose and applies on objects.
// The pattern defines an object that encapsulates how a set of objects interact.
// It promotes loose coupling by keeping objects from referring to each
// other explicitly, and it lets you vary their interaction independently.

// When to use (applicability):
// -> a set of objects communicate in well-defined but complex ways
// -> reusing an object is difficult because it refers to and communicates with many other objects
// -> a behavior that's distributed between several classes should be customizable without a lot of subclassing

// Consequences:
// -> It limits subclassing.
// ---> A mediator localizes behavior that otherwise would be distributed among several objects.
// ---> Changing this behavior requires subclassing Mediator only; Colleague classes can be reused as is.
// -> It decouples colleagues.
// ---> A mediator promotes loose coupling between colleagues.
// ---> You can vary and reuse Colleague and Mediator classes independently.
// -> It simplifies object protocols.
// ---> A mediator replaces many-to-many interactions with one-to-many interactions between the mediator and its colleagues.
// ---> One-to-many relationships are easier to understand, maintain, and extend.
// -> It abstracts how objects cooperate.
// ---> Making mediation an independent concept and encapsulating in an object lets you focus on how objects interact apart from their individual behavior.
// -----> This can help clarify how objects interact in a system.
// -> It centralizes control.
// ---> The Mediator pattern trade complexity of interaction for complexity in the mediator.
// ---> Because a mediator encapsulates protocols it can become more complex than any individual colleague.
// ---> This can make the mediator itself a monolith that's hard to maintain.

// Implementation:
// -> Omitting the abstract Mediator class
// ---> There's no need to define an abstract Mediator class when colleagues work with only one mediator.
// ---> The abstract coupling the Meditator class provide lets colleagues work with different Mediator subclasses and vice versa.
// -> Colleague-Mediator communication
// ---> Colleagues have to communicate with their mediator when an event of interest occurs.
// -----> One approach is to implment the Mediator as an Observer using the [Observer] pattern
// -------> Colleague classes act as Subjects, sending notifications to the mediator whenever they change state.
// -------> The mediator responds by propagating the effect of the change to other colleagues.
// ---> Another approach defines a specialized notification interface in Mediator that lets colleagues be more direct in their communication.
// -----> Smalltalk/V for Windows uses a form of delegation in the communication.

// Related Patterns
// -> [Facade] differs from Mediator in that it abstracts a subsystem of objects to provide a more convenient interface.
// ---> Its protocol is unidirectional: Facade objects make request of the subsystem classes but not vice versa.
// ---> In concrast, Mediator enables cooperative behavior that colleague objects don't or can't provide, and the protocol is multidirectional.
// -> Colleagues can communicate with the mediator using the [Observer] pattern.
