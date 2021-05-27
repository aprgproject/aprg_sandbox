#pragma once

#include <BaseTermData.hpp>

#include <memory>
#include <vector>

namespace alba
{

namespace equation
{

class Expression : public BaseTermData
{
public:
    Expression();

private:
    std::vector<std::unique_ptr<BaseTermData>> m_terms;
};

}

}
