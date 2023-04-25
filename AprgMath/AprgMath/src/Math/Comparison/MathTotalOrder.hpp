#pragma once

namespace alba {

namespace math {

template <typename DataType>
bool hasTotalOrder(DataType const& /*value1*/, DataType const& /*value2*/) {
    // Objects in sort must satisfy this
    // Three things must be true:
    // anti-symmetry: if v<=w and w<=v then v=w
    // transitivity: if v<=w and w<=x then v=<x
    // totality: either v<=w or w<=v or both

    // implement this

    return true;
}

}  // namespace math

}  // namespace alba
