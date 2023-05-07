#include <iostream>
#include <map>
#include <memory>

namespace Flyweight {

// Flyweight
// declares an interface through which flyweights can receive
// and act on extrinsic state

class Flyweight {
public:
    virtual ~Flyweight() = default;
    virtual void operation(int const extrinsicState) = 0;
    // ...
};

// SharedConcreteFlyweight
// implements the Flyweight interface and adds storage for intrinsic state

class SharedConcreteFlyweight : public Flyweight {
public:
    SharedConcreteFlyweight(int& intrinsicState) : m_sharedIntrinsicState(intrinsicState) {}

    void operation(int const extrinsicState) override {
        std::cout << "Concrete Flyweight with extrinsicState " << extrinsicState
                  << " and sharedIntrinsicState:" << m_sharedIntrinsicState << "\n";
    }
    // ...

private:
    int& m_sharedIntrinsicState;  // This might be different on the example of the book (we store it as reference).
    // ...
};

// UnsharedConcreteFlyweight
// not all subclasses need to be shared

class UnsharedConcreteFlyweight : public Flyweight {
public:
    UnsharedConcreteFlyweight(int const intrinsicState) : m_unsharedIntrinsicState(intrinsicState) {}

    void operation(int const extrinsicState) override {
        std::cout << "Unshared Flyweight with extrinsicState:" << extrinsicState
                  << " and unsharedIntrinsicState:" << m_unsharedIntrinsicState << "\n";
    }
    // ...

private:
    int m_unsharedIntrinsicState;
    // ...
};

// FlyweightFactory
// creates and manages flyweight objects and ensures
// that flyweights are shared properly

class FlyweightFactory {
public:
    std::unique_ptr<Flyweight> getSharedFlyweight(int const key) {
        auto it = m_keyToSharedValueMap.find(key);
        if (it != m_keyToSharedValueMap.end()) {
            return std::make_unique<SharedConcreteFlyweight>(it->second);
        } else {
            auto iteratorAndFlagPair = m_keyToSharedValueMap.emplace(key, key);  // use key as value
            return std::make_unique<SharedConcreteFlyweight>(iteratorAndFlagPair.first->second);
        }
    }
    std::unique_ptr<Flyweight> getUnsharedFlyweight(int const value) {
        return std::make_unique<UnsharedConcreteFlyweight>(value);
    }
    // ...

private:
    std::map<int, int> m_keyToSharedValueMap;
    // ...
};

}  // namespace Flyweight

// Flyweight discussion:

// ONE LINE NOTE:
// -> Provide a "flyweight object" that can have SHARED data (extrinsic state) or SEPARATED data (intrinsic state)
// -> Provide a "flyweight object" that SEPARATES INTRINSIC/NON-CONTEXT data (can be shared and saved in object) and
// EXTRINSIC/CONTEXT data (can be removed and be sent to object instead)

// Intent:
// Flyweight pattern has has structural purpose, applies to objects and uses sharing to support large numbers of
// fine-grained objects efficiently.
// The pattern can be used to reduce memory usage when you need to create a large number of similar objects.
// Instead of storing the whole data on the object, separate intrinsic and extrinsic data to lessen memory usage.

// When to use (applicability):
// -> when one instance of a class can be used to provide many "virtual instances"
// -> when all of the following are true
// --> an application uses a large number of objects
// --> storage costs are high because of the sheer quantity of objects
// --> most object state can be made extrinsic
// --> many groups of objects may be replaced by relatively few shared objects once extrinsic state is removed
// --> the application doesn't depend on object identity

// Consequences:
// -> Flyweights may introduce run-time cost associated with transferring, funding, and/or computing extrinsic state,
// ---> especially if it was formerly stored as intrinsic state.
// ---> However, such costs are offset by space savings, which increase as more flyweights are shared.
// -> Storage savings are a function of several factors:
// ---> the reduction in the total number of instances that comes from sharing
// ---> the amount of intrinsic state per object
// ---> whether extrinsic state is computed or stored
// -> The more flyweights are shared, the greater storage savings.
// ---> The saving increase with the amount of shared state.
// ---> The greatest saving occur when the objects use substantial quantities of both intrinsic and extrinsic state
// -----> and the extrinsic state can be computed rather than stored.
// -----> Then you save on storage in two ways:
// -------> (1) Sharing reduces the cost of intrinsic state
// -------> (2) and you trade extrinsic state for computation state.
// -> The Flyweight pattern is often combined with the [Composite] pattern to represent a hierarchical structure as a
// graph with shared leaf nodes.
// ---> A consequence of sharing is that flyweight leaf nodes cannot store a pointer to their parent.
// ---> Rather, the parent pointer is passed ot the flyweight as part of its extrinsic state.
// ---> This has a major impact on how the objects in the hierarchy communicate with each other.

// Implementation:
// -> Removing extrinsic state.
// ---> The pattern's applicability is determined largely by how easy it is to identify extrinsic state and remove it
// from shared objects.
// -----> Removing extrinsic state won't help reduce storage cost if there are as many different kinds of extrinsic
// state as there are objects before sharing.
// -----> Ideally, extrinsic state can be computed from a separate object structure, one with far smaller storage
// requirements.
// -> Managing shared objects
// ---> Because objects are shared, clients shouldn't instantiate them directly.
// -----> FlyweightFactory lets clients locate a particular flyweight.
// -----> FlyweightFactory objects often use an associative store to let clients look up flyweight of interest.
// ---> Sharability also implies some form of reference counting or garbage collection to reclaim a flyweights storage
// when its no longer needed.
// -----> However, neither is necessary if the number of flyweights is fixed and small.
// -------> In this case, the flyweights are worth keeping around permanently.

// Related Patterns
// -> The [Flyweight] pattern is often combined with the [Composite] pattern to implement a logically hierarchical
// structure
// ---> in terms of a directed-acyclic-graph with shared leaf nodes.
// -> It's often best to implement [State] and [Strategy] objects as flyweights.
