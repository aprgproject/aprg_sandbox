#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

namespace alba {

template <typename State, typename Input>
class AlbaDfaUsingMatrix {
public:
    using StateMatrix = matrix::AlbaMatrix<State>;

    AlbaDfaUsingMatrix(size_t const maxStateValue, size_t const maxInputValue)
        : m_nextStateMatrix(maxStateValue, maxInputValue) {}

    State getNextState(State const currentState, Input const input) const {
        return m_nextStateMatrix.getEntry(static_cast<size_t>(currentState), static_cast<size_t>(input));
    }

    void setStateTransition(State const currentState, State const nextState, Input const input) {
        m_nextStateMatrix.setEntry(static_cast<size_t>(currentState), static_cast<size_t>(input), nextState);
    }

private:
    StateMatrix m_nextStateMatrix;
};

}  // namespace alba
