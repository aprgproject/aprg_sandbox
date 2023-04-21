#include <iostream>
#include <memory>

namespace Proxy
{

// Subject
// defines the common interface for RealSubject and Proxy
// so that a Proxy can be used anywhere a RealSubject is expected

class Subject
{
public:
    virtual ~Subject() = default;

    virtual void request() = 0;
    // ...
};


// Real Subject
// defines the real object that the proxy represents

class RealSubject : public Subject
{
public:
    void request() override
    {
        std::cout << "Real Subject request\n";
    }
    // ...
};


// Proxy
// maintains a reference that lets the proxy access the real subject

class Proxy : public Subject
{
public:
    Proxy()
    {
        m_subject = std::make_unique<RealSubject>(); // instantiation might happen elsewhere on other examples
    }

    void request() override
    {
        m_subject->request();
    }
    // ...

private:
    std::unique_ptr<RealSubject> m_subject;
};

}

// Proxy discussion:

// ONE LINE NOTE:
// -> Provide a "proxy object" that LOOKS like a real object but its a PLACEHOLDER ONLY to control ACCESS to the real object

// Intent:
// Proxy pattern provides a surrogate or placeholder for another object to control access to it.
// The pattern has structural purpose and applies to objects.
// Note: The proxy looks like the original subject.
// Note: It both uses the "has a" and "is a" approach.

// When to use (applicability):
// -> whenever there is a need for a more versatile or sophisticated reference to an object than a simple pointer
// -> Here are several common situations in which the Proxy pattern is applicable:
// ---> A "Remote proxy" provides a local representative for an object in a different address space (different server, different project).
// -----> Example: Ambassador type proxies.
// ---> A "Virtual proxy" controls access to objects that are expensive to create or copy.
// -----> This can "create expensive objects on demand".
// -----> It can "copy on write" (only copy when its modified).
// -----> Example: Image proxies.
// ---> A "Protection proxy" controls access to the original object.
// -----> Protection provides are useful when objects should have different access rights.
// -----> Example: Kernel objects/proxies.
// ---> A "Smart reference" is a replacement for a bare pointer that additional actions when an object is accessed. This may include:
// -----> counting the number reference to the real object so that it can be free automatically when there are no more references.
// -----> loading a persistent object into memory when its first referenced.
// -----> checking that the real object is locked before its accessed to ensure that no other object can change it.

// Consequences:
// -> The Proxy pattern introduces a level of indirection when accessing an object.
// ---> The additional indirection has many uses, depending on the kind of proxy:
// -----> A remote proxy can hide the fact that an object resides in a different address space.
// -----> A virtual proxy can perform optimizations such as creating an object on demand.
// -------> It can "copy on write" (if the copy is never modified there;s no need to incur this cost).
// -----> Both protection proxies and smart reference allow additional housekeeping tasks when an object is accessed.

// Implementation:
// -> Overloading the member access operator in C++.
// ---> C++ supports overloading the member access operator(operator->)
// -----> Overloading this operator lets you perform additional work whenever an object is dereferenced.
// -----> This can be helpful for implementing some kinds of proxy and the proxy behaves just like a pointer.
// -----> Overloading the member access operator isn't a good solution for every kind of proxy.
// -------> Some proxies need to know precisely which operation is called and overloading the member access operator doesn't work in those cases.

// Related Patterns
// -> An [Adapter] provides a different interface to the object it adapts.
// ---> In contrast, a proxy provides the same interface as its subject.
// ---> However, a proxy used for access protection might refuse to perform an operation that the subject can perform originally.
// -> Although [Decorators] can have similar implementations as proxies, decorators have a different purpose.
// ---> A decorator adds responsibilities to an object, whereas a proxy controls access to an object.
// ---> Proxies vary in the degree to which they are implemented like a Decorator.
// -----> A protection proxy might be implemented exactly like a decorator.
// -----> A remote proxy will not contain a direct reference to its real subject only an indirect reference (some sort of identifier).
// -----> A virtual proxy will start off with an indirect reference (such as a filename) but will eventually obtain and use a direct reference.