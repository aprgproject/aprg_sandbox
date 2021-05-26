#pragma once

#include <BaseTerm.hpp>

#include <memory>
#include <vector>

namespace alba
{
namespace equation
{

class Expression : public BaseTerm
{
public:
    Expression();

private:
    std::vector<std::unique_ptr<BaseTerm>> m_terms;
};

}
}