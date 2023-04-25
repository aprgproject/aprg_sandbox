#pragma once

#include <string>

namespace alba {

namespace algebra {

class BaseTerm {
public:
    BaseTerm() = default;
    virtual ~BaseTerm() = default;  // virtual destructor because it needs to be polymorphically deleted
};

}  // namespace algebra

}  // namespace alba
