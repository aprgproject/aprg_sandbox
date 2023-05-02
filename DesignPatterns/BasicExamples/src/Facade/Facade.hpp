#include <iostream>

namespace Facade {

// Subsystems
// implement more complex subsystem functionality
// and have no knowledge of the facade

class SubsystemA {
public:
    void suboperation() {
        std::cout << "Subsystem A method\n";
        // ...
    }
    // ...
};

class SubsystemB {
public:
    void suboperation() {
        std::cout << "Subsystem B method\n";
        // ...
    }
    // ...
};

class SubsystemC {
public:
    void suboperation() {
        std::cout << "Subsystem C method\n";
        // ...
    }
    // ...
};

// Facade
// delegates client requests to appropriate subsystem object
// and unified interface that is easier to use

class Facade {
public:
    Facade() : m_subsystemA(), m_subsystemB(), m_subsystemC() {}

    void operation1() {
        m_subsystemA.suboperation();
        m_subsystemB.suboperation();
        // ...
    }

    void operation2() {
        m_subsystemC.suboperation();
        // ...
    }
    // ...

private:
    SubsystemA m_subsystemA;
    SubsystemB m_subsystemB;
    SubsystemC m_subsystemC;
    // ...
};

}  // namespace Facade

// Façade discussion:

// ONE LINE NOTE:
// -> Provide a FACADE (or unified interface) for MULTIPLE components in a SUBSYSTEM

// Intent:
// Provide a unified interface to a set of interfaces in a subsystem.
// Facade defines a higher-level interface that makes the subsystem easier to use.
// The pattern has structural purpose and applies to objects.

// When to use (applicability):
// -> you want to provide a simple interface to a complex subsystem
// -> there are many dependencies between clients and the implementation classes of an abstraction
// -> you want to layer your subsystems, use a facade to define an entry point to each subsystem level

// Consequences:
// -> It shields clients from subsystem components, making it easier to use several subsystem components.
// -> It promotes weak coupling between the subsystem and its clients.
// ---> Often the components in a subsystem are strongly coupled.
// ---> Weak coupling lets you vary the components of the subsystem without affecting its clients.
// -> Facades help layer a system and the dependencies between objects.
// ---> They can eliminate complex or cricular dependencies.
// ---> This can be an important consequence when the client and the subsystem are implemented independently.
// -> Reducing compilation dependencies is vital in large software systems.
// ---> You want to save time by minimizing recompilation when subsystem classes change.
// ---> This pattern can also limit the recompilation needed for a small change in an important subsystem.
// ---> This pattern can also simplify porting systems to other platforms.
// -> It doesnt prevent applications from using subsystem classes if they need to.
// ---> Thus you can choose between ease of use and generality.

// Implementation:
// -> Reducing client-subsystem coupling.
// ---> The coupling can be reduced more by making Facade an abstract class and have concrete classes with different
// implementations.
// ---> Then, the clients can communicate with the subsystem through the interface of the abstract Facade class.
// ---> This abstract coupling keeps clients from knowing which implementation of a subsystem is used.
// -> Public versus private subsystem classes.
// ---> A class encapsulate state and and operations and a subsystem encapsulate classes.
// ---> Since we can have public and private interface of a class, we can also do it for subsystems.
// -----> The public interface consists of classes that all clients can access.
// -----> The private interface is just for subsystem extenders.

// Related Patterns
// -> [AbstractFactory] can be used with Facade to provide an interface for creating subsystem objects in a subsystem
// independent way.
// -> [AbstractFactory] can also be used as an alternative to Facade to hide platform specific classes.
// -> [Mediator] is similar to Facade in that it abstract functionality of existing classes.
// ---> However, Mediator purpose is abstract arbitiary communication between colleague objects,
// ---> often centralizing functionality that doesn't belong in any one of them.
// ---> A Mediator colleages are aware of and communicate with the meditator instead of communicating with each other
// directly.
// ---> In contrast a [Facade] merely abstracts the interface to subsystem objects to make them easier to use.
// ---> [Facade] doesnt define new functionality and subsystem classes dont know about it.
// -> Facade objects are often [Singleton] because usually only one [Facade] object is required.
