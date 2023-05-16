#pragma once

namespace alba {

namespace chess {

class Exchange {
public:
    Exchange(int const value, int const count);

    bool operator==(Exchange const& exchange) const;
    bool operator!=(Exchange const& exchange) const;

    int getValue() const;
    int getCount() const;

private:
    int m_value;
    int m_count;
};

}  // namespace chess

}  // namespace alba
