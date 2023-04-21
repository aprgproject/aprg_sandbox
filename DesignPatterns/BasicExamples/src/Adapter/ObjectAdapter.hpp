#include <iostream>

namespace ObjectAdapter
{

// Target
// defines specific interface that Client uses

class Target
{
public:
    virtual ~Target() = default;
    virtual void request() = 0;
    // ...
};


// Adaptee
// defines an existing interface that needs adapting and thanks
// to Adapter it will get calls that client makes on the Target

class Adaptee
{
public:
    void specificRequest()
    {
        std::cout << "specific request\n";
    }
    // ...
};


// Adapter
// implements the Target interface and when it gets a method call it
// delegates the call to a Adaptee

class Adapter : public Target
{
public:

    void request() override
    {
        adaptee.specificRequest();
        // ...
    }
    // ...

private:
    Adaptee adaptee;
    // ...
};

}