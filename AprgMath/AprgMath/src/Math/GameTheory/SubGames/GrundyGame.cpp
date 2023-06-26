#include "GrundyGame.hpp"

#include <Math/GameTheory/Common/GameUtilities.hpp>

using namespace std;

namespace alba {

namespace math {

GrundyGame::GrundyGame(UnsignedInteger const totalNumberOfSticks) : m_stickHeaps{totalNumberOfSticks} {}

bool GrundyGame::hasNoMoves() const {
    return all_of(m_stickHeaps.cbegin(), m_stickHeaps.cend(), [](UnsignedInteger const stickHeap) {
        return stickHeap <= 2;  // sizes 1 and 2 cannot be split with different sizes
    });
}

GrundyGame::StickHeaps const& GrundyGame::getStickHeaps() const { return m_stickHeaps; }

UnsignedInteger GrundyGame::getOverallGrundyNumber() {
    UnsignedInteger result(0U);
    for (UnsignedInteger const& stickHeap : m_stickHeaps) {
        result = getCombinedGrundyNumber(result, getGrundyNumberWithNumberOfSticks(stickHeap));
    }
    return result;
}

GameState GrundyGame::getGameState() { return getGameStateFromGrundyNumber(getOverallGrundyNumber()); }

GrundyGame::HeapIndexAndFirstPileAndSecondPile GrundyGame::getOptimalWayToSplit() {
    HeapIndexAndFirstPileAndSecondPile result{};
    UnsignedInteger overallGrundyNumber = getOverallGrundyNumber();
    GameState gameState = getGameStateFromGrundyNumber(overallGrundyNumber);
    if (GameState::Losing == gameState) {
        for (UnsignedInteger heapIndex = 0; heapIndex < m_stickHeaps.size(); heapIndex++) {
            UnsignedInteger const& stickHeap(m_stickHeaps[heapIndex]);
            if (stickHeap >= 3)  // sizes 1 and 2 cannot be split with different sizes
            {
                result = make_tuple(heapIndex, 1ULL, stickHeap - 1ULL);                break;
            }
        }
    } else if (GameState::Winning == gameState) {
        bool isFound(false);
        for (UnsignedInteger heapIndex = 0; !isFound && heapIndex < m_stickHeaps.size(); heapIndex++) {
            UnsignedInteger const& stickHeap(m_stickHeaps[heapIndex]);
            UnsignedInteger grundyNumberAtIndex = getGrundyNumberWithNumberOfSticks(stickHeap);
            UnsignedInteger hammingDistance = grundyNumberAtIndex ^ overallGrundyNumber;
            for (int a = (static_cast<int>(stickHeap) - 1) / 2; !isFound && a > 0; a--) {                int b = static_cast<int>(stickHeap) - a;
                if (hammingDistance ==
                    getCombinedGrundyNumber(
                        getGrundyNumberWithNumberOfSticks(a), getGrundyNumberWithNumberOfSticks(b))) {                    result = make_tuple(heapIndex, static_cast<UnsignedInteger>(a), static_cast<UnsignedInteger>(b));
                    isFound = true;
                }
            }
        }
    }
    return result;
}

void GrundyGame::split(HeapIndexAndFirstPileAndSecondPile const& heapIndexAndFirstPileAndSecondPile) {
    UnsignedInteger index = get<0>(heapIndexAndFirstPileAndSecondPile);
    if (index < m_stickHeaps.size()) {
        UnsignedInteger firstPile = get<1>(heapIndexAndFirstPileAndSecondPile);
        UnsignedInteger secondPile = get<2>(heapIndexAndFirstPileAndSecondPile);
        if (m_stickHeaps[index] == firstPile + secondPile) {
            m_stickHeaps.erase(m_stickHeaps.begin() + index);
            m_stickHeaps.emplace(m_stickHeaps.begin() + index, secondPile);
            m_stickHeaps.emplace(m_stickHeaps.begin() + index, firstPile);        }
    }
}
UnsignedInteger GrundyGame::getGrundyNumberWithNumberOfSticks(UnsignedInteger const numberOfSticks) {
    UnsignedInteger result{};
    auto it = m_sticksToGrundyNumberMap.find(numberOfSticks);
    if (it != m_sticksToGrundyNumberMap.cend()) {
        result = it->second;
    } else {
        // possible infinite recursion for cycles
        result = getGrundyNumber(getNextGrundyNumbersWithNumberOfSticks(numberOfSticks));
        m_sticksToGrundyNumberMap[numberOfSticks] = result;
    }
    return result;
}

SetOfUnsignedIntegers GrundyGame::getNextGrundyNumbersWithNumberOfSticks(UnsignedInteger const numberOfSticks) {
    SetOfUnsignedIntegers result;

    UnsignedInteger limit = (numberOfSticks + 1) / 2;
    for (int a = 1; a < static_cast<int>(limit); a++) {
        int b = numberOfSticks - a;
        result.emplace(
            getCombinedGrundyNumber(getGrundyNumberWithNumberOfSticks(a), getGrundyNumberWithNumberOfSticks(b)));
    }
    return result;
}

}  // namespace math

}  // namespace alba
