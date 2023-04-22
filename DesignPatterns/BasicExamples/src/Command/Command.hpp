#include <iostream>

namespace Command
{

// Receiver
// knows how to perform the operations associated
// with carrying out a request

class Receiver
{
public:
    void action()
    {
        std::cout << "Receiver: perform action\n";
    }

    void reverseAction()
    {
        std::cout << "Receiver: perform reverse action\n";
    }
    // ...
};


// Command
// declares an interface for all commands

class Command
{
public:
    virtual ~Command() = default;

    virtual void execute() = 0;
    virtual void undo() = 0;
    // ...

protected:
    Command() = default;
};


// Concrete Command
// implements execute by invoking the corresponding
// operation(s) on Receiver

class ConcreteCommand : public Command
{
public:
    ConcreteCommand(Receiver & receiver)
        : m_receiver(receiver)
    {}

    void execute() override
    {
        m_receiver.action();
    }

    void undo() override
    {
        m_receiver.reverseAction();
    }
    // ...

private:
    Receiver & m_receiver;
    // ...
};


// Invoker
// asks the command to carry out the request

class Invoker
{
public:
    Invoker()
        : m_command(nullptr)
    {}

    void setCommand(Command * command)
    {
        m_command = command;
    }

    void invoke()
    {
        if(m_command != nullptr)
        {
            m_command->execute();
        }
    }

    void invokeUndo()
    {
        if(m_command != nullptr)
        {
            m_command->undo();
        }
    }
    // ...

private:
    Command * m_command; // can be reference if you can but it will need the command on constructor
    // ...
};

}

// Command discussion:

// ONE LINE NOTE:
// -> Encapsulate a REQUEST into a "command object" that can INVOKE different operations (such as execute/undo)

// Intent:
// Command pattern encapsulates a request as an object,// thereby letting you parameterize clients with different requests, queue or log requests, and supports undoable operations.
// The pattern has a behavioral purpose and deals with relationships between objects.

// When to use (applicability):// -> want to parameterize objects by an action to perform
// -> want to specify, queue, and execute requests at different times
// -> support undo
// -> support logging changes so that they can be reapplied in case of a system crash
// -> structure a system around high-level operations built on primitives operations

// Consequences:
// -> The command decouples the object that invokes the operation from the one that knows how to perform it.
// -> The commands are first-class objects. They can be manipulated and extended like any other object.
// -> You can assemble command into a composite command (using [Composite] pattern).
// -> Its easy to add new Commands, because you don't have to change existing classes.

// Implementation:
// -> How intelligent should a command be?
// ---> At one extreme it merely defines a binding between a receiver and the actions that carry out the request.
// ---> At the other extreme it implements everything itself without delegating to a receiver at all.
// -----> This is applicable when commands are independent, when no suitable receiver exists or when command knows its receiver implicitly.
// -> Supporting undo and redo
// ---> Commands can support undo and redo capabilities if they can provide a way to reverse their execution.
// ---> A concrete command class might need to store additional state to do so. The state can include:
// -----> The receiver object, which actually carries out operations in response to the request.
// -----> The arguments to the operation performed on the receiver.
// -----> Any original values in the receiver that can change as a result of handling the request.
// ---> For multiple level of undo and redo, the application needs a history list of commands that have been executed.
// -----> Some commands might need to save additional information.
// -------> For example the DeleteCommand might need to copy original information to restore that information.
// -> Avoiding error accumulation in the undo process
// ---> Hysteresis can be a problem in enxureing a reliable, semantics-preserving undo/redo mechanism.
// ---> It may be necessary therefore to store more information in the command to ensure that objects are restored to their original state.
// -----> The [Memento] pattern can be applied to give the command access to this information without exposing the internals of objects.
// -> Using C++ templates
// ---> For commands that arent undoable and dont require arguments, we can use C++ templates to avoid creating additional subclasses.

// Related Patterns
// -> A [Composite] can be used to implement MacroCommands (commands that contain multiple commands).
// -> A [Memento] can keep the state the command requires to undo its effect.
// -> A command that must be copied before being place on the history list acts as a [Prototype].


