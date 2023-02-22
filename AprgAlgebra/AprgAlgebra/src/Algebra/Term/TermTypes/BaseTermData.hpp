#pragma once

namespace alba
{

namespace algebra
{

class BaseTermData
{
public:
    BaseTermData() = default;
    virtual ~BaseTermData() = default; // virtual destructor because it needs to be polymorphically deleted
};

}

}
