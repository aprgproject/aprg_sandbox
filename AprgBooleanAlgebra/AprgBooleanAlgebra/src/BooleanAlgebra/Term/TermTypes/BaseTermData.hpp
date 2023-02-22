#pragma once

namespace alba
{

namespace booleanAlgebra
{

class BaseTermData
{
public:
    BaseTermData() = default;
    virtual ~BaseTermData() = default; // virtual destructor because of virtual functions (vtable exists)

};

}

}
