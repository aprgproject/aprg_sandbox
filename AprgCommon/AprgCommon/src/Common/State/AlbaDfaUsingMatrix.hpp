#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

namespace alba {

template <typename State, typename Input>
class AlbaDfaUsingMatrix {
public:
    using StateMatrix = matrix::AlbaMatrix<State>;

    AlbaDfaUsingMatrix(unsigned int const maxStateValue, unsigned int const maxInputValue)
        : m_nextStateMatrix(maxStateValue, maxInputValue) {}

    State getNextState(State const currentState, Input const input) const {
        return m_nextStateMatrix.getEntry(static_cast<unsigned int>(currentState), static_cast<unsigned int>(input));
    }

    void setStateTransition(State const currentState, State const nextState, Input const input) {
        m_nextStateMatrix.setEntry(
            static_cast<unsigned int>(currentState), static_cast<unsigned int>(input), nextState);
    }

private:
    StateMatrix m_nextStateMatrix;
};

}  // namespace alba
