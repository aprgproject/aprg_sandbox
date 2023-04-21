#include <iostream>
#include <memory>

namespace ChainOfResponsibility
{

// Handler
// defines an interface for handling requests and
// optionally implements the successor link

class Handler
{
public:
    virtual ~Handler() = default;

    virtual void setHandler(std::unique_ptr<Handler> successorPointer)
    {
        m_successorPointer = std::move(successorPointer);
    }

    virtual void handleRequest()
    {
        if(m_successorPointer != 0)
        {
            m_successorPointer->handleRequest();
        }
    }
    // ...

private:
    std::unique_ptr<Handler> m_successorPointer;
};


// Concrete Handlers
// handle requests they are responsible for

class ConcreteHandler1 : public Handler
{
public:
    bool canHandle() const
    {
        // ...
        return false;
    }

    virtual void handleRequest() override
    {
        if(canHandle())
        {
            std::cout << "Handled by Concrete Handler 1\n";
        }
        else
        {
            std::cout << "Cannot be handled by Handler 1\n";
            Handler::handleRequest();
        }
        // ...
    }
    // ...
};

class ConcreteHandler2 : public Handler
{
public:
    bool canHandle() const
    {
        // ...
        return true;
    }

    virtual void handleRequest() override
    {
        if(canHandle())
        {
            std::cout << "Handled by Handler 2\n";
        }
        else
        {
            std::cout << "Cannot be handled by Handler 2\n";
            Handler::handleRequest();
        }
        // ...
    }

    // ...
};

}

// Chain of Responsibility discussion:

// ONE LINE NOTE:
// -> Have a CHAIN of handlers that can process a request and ANY handler is RESPONSIBLE on consuming the request

// Intent:
// Chain of Responsibility pattern avoids coupling the sender of a request to its receiver
// by giving more than one object a chance to handle the request.
// The pattern chains the receiving objects and passes the request along the chain until an object handles it.
// It has a behavioral purpose and deals with relationships between objects.
// Note: It both uses the "has a" and "is a" approach.

// When to use (applicability):
// -> more than one object may handle a request, and the handler should be ascertained automatically
// -> you want to issue a request to one of several objects without specifying the receiver explicitly
// -> the set of objects that can handle a request should be specified dynamically

// Consequences:
// -> Reduced coupling
// ---> The pattern frees an object from knowing which other object handles a request.
// ---> An object only has to know that a request will be handled "appropriately".
// ---> Both receiver and the sender have no explicit knowledge of each other, and an object in the chain doesn't have to know about the chain's structure.
// -----> As a result, Chain of Responsibility can simplify object interconnections.
// -------> Instead of objects maintaining references to all candidate receivers, they keep a single reference to their successor.
// -> Added flexibility in assinging responsibilities to objects
// ---> Chain of Responsibility gives you added flexibility in distributing responsibilities among objects.
// -----> You can add or change responsibilities for handling a request by adding to or otherwise changing the chain at runtime.
// -----> You can combine this with subclassing to specialize handlers statically
// -> Receipt isn't guaranteed or Request can go unhandled
// ---> Since a request has not explicit receiver, there's no guarantee it will be handled. The request can fall off the end of the chain.
// ---> A request can also go unhandled when the chain is not configured properly.

// Implementation:
// -> Implementing the successor chain
// ---> There are two possible ways to implement the successor chain.
// -----> (a) Define new links (usually in the Handler, but ConcreteHandlers could define them instead).
// -------> You can use exisitng object reference to form the successor chain.
// ---------> For example, parent reference in a part-whole hierarchy can define a part's successor.
// ---------> [Composite] discusses parent reference in more detail.
// -----> (b) Use existing links
// -------> This works well when the links support the chain you need.
// -------> It saves you from defining links explicitly and it save space.
// -------> But if the structure doesn't reflect the chain of responsibility your application requires, then you will have to define redundant links.
// -> Connecting successors
// ---> If there are no pre-existing references for defining a chain, then you will have to introduce them yourself.
// ---> In that case, the Handler not only defines the interface for the requests but usually maintains the successor as well.
// ---> That lets the handler provide a default implementation of HandleRequest that forwards the request to the successor (if any).
// ---> If a ConcreteHandler subclass isn't interested in the request,
// -----> it doesn't have to override the forwarding operation,
// -----> since its default implementation forward uncondtionally.
// -> Representing requests
// ---> Different options are available for representing requests.
// ---> In the simplest form, the request is a hard-coded operation invocation.
// -----> This is convenient and safe but you can forward only the fixed set of request that the Handler class defines.
// -----> An alternative is to use a single handler function that takes a request code as a parameter.
// -------> This supports an open-ended set of requests.
// -------> The only requirement is that the sender and receiver agree on how the request should be encoded.
// -------> This approach is more flexible, but it requires conditional statements for dispatching the request based on its code.
// -------> Moreover there is no type-safe way to pass parameters, so they must be packed and unpacked manually.
// ---------> Obviously this is less safe than invoking an operation directly.
// -> Automatic forwarding in small talk
// ---> No need to know.

// Related Patterns
// -> Chain of Responsibility is often applied in conjunction with [Composite].
// ---> This means that a component's parent can act as its successor.
