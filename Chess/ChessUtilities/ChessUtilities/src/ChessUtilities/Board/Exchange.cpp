#include "Exchange.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <Common/String/AlbaStringHelper.hpp>

using namespace std;

namespace alba {

namespace chess {

Exchange::Exchange(int const value, int const count) : m_value(value), m_count(count) {}

bool Exchange::operator==(Exchange const& exchange) const {
    return m_value == exchange.m_value && m_count == exchange.m_count;
}

bool Exchange::operator!=(Exchange const& exchange) const { return !operator==(exchange); }

int Exchange::getValue() const { return m_value; }

int Exchange::getCount() const { return m_count; }

}  // namespace chess

}  // namespace alba
