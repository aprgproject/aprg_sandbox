#pragma once

#include <string>

namespace alba
{

namespace equation
{

class BaseTerm
{
public:
    BaseTerm();
    virtual ~BaseTerm();

    virtual std::string getDisplayableString() const;
    virtual std::string getDebugString() const;

private:

};

}

}
