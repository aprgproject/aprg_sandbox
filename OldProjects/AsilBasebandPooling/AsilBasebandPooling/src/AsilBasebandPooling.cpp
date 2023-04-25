#include "AsilBasebandPooling.hpp"

#include <algorithm>
#include <iterator>

using namespace std;

namespace alba {

AsilBasebandPooling::AsilBasebandPooling() {}

AsilBasebandPooling::AsilBasebandPooling(
    LcgInitializerList const& lcgs, BasebandCardInitializerList const& basebandCards) {
    copy(lcgs.begin(), lcgs.end(), inserter(m_lcgs, m_lcgs.cbegin()));
    copy(basebandCards.begin(), basebandCards.end(), inserter(m_basebandCards, m_basebandCards.cbegin()));
}

BasebandPoolingResult AsilBasebandPooling::performBasebandPoolingForAsil() const {
    BasebandPoolingResult poolingResult;
    poolingResult.isSuccessful = areLcgAndBasebandCardsValid();
    if (poolingResult.isSuccessful) {
        VectorOfLcgs lcgsInPriorityOrder(getLcgsInPriorityOrder());
        unsigned int numberOfBasebandCardsWithMultipleLcgs(getNumberBasebandCardsWithMultipleLcgs());
        BasebandCardsSplitBasedOnNumberOfLcgs basebandCardsBasedOnNumberOfLcgs(
            getBasebandCardsSplitBetweenOneLcgAndMultipleLcgs(numberOfBasebandCardsWithMultipleLcgs));
        assignBasebandCardsWithOneLcg(
            poolingResult.keplerNidToLcgMap, lcgsInPriorityOrder,
            basebandCardsBasedOnNumberOfLcgs.basebandCardsWithOneLcg);
        assignBasebandCardsWithMultipleLcgs(
            poolingResult.keplerNidToLcgMap, lcgsInPriorityOrder,
            basebandCardsBasedOnNumberOfLcgs.basebandCardsWithMultipleLcgs);
    }
    return poolingResult;
}

bool AsilBasebandPooling::areLcgAndBasebandCardsValid() const {
    return getMaxNumberOfLcgsInAllBasebandCards() >= m_lcgs.size();
}

bool AsilBasebandPooling::canMultipleLcgsBePutOnBasebandCard(BasebandCard const& basebandCard) const {
    return getMaxNumberOfLcgsInBasebandCard(basebandCard) > 1;
}

unsigned int AsilBasebandPooling::getNumberBasebandCardsWithMultipleLcgs() const {
    return m_lcgs.size() - m_basebandCards.size();
}

unsigned int AsilBasebandPooling::getMaxNumberOfLcgsInBasebandCard(BasebandCard const& basebandCard) const {
    return basebandCard.getKeplers().size() / 2;
}

unsigned int AsilBasebandPooling::getMaxNumberOfLcgsInAllBasebandCards() const {
    unsigned int result(0);
    for (BasebandCard const& basebandCard : m_basebandCards) {
        result += getMaxNumberOfLcgsInBasebandCard(basebandCard);
    }
    return result;
}

VectorOfLcgs AsilBasebandPooling::getLcgsInPriorityOrder() const {
    VectorOfLcgs lcgsInPriorityOrder;
    copy(m_lcgs.cbegin(), m_lcgs.cend(), back_inserter(lcgsInPriorityOrder));
    sortAndPrioritizeLcgs(lcgsInPriorityOrder);
    return lcgsInPriorityOrder;
}

BasebandCardsSplitBasedOnNumberOfLcgs AsilBasebandPooling::getBasebandCardsSplitBetweenOneLcgAndMultipleLcgs(
    unsigned int const numberOfBasebandCardsWithMultipleLcgs) const {
    unsigned int numberOfBasebandCardRemaining(numberOfBasebandCardsWithMultipleLcgs);
    BasebandCardsSplitBasedOnNumberOfLcgs basebandCards;
    SetOfBasebandCards::reverse_iterator reverseTraversal = m_basebandCards.crbegin();
    while (reverseTraversal != m_basebandCards.crend()) {
        if (numberOfBasebandCardRemaining > 0 && canMultipleLcgsBePutOnBasebandCard(*reverseTraversal)) {
            basebandCards.basebandCardsWithMultipleLcgs.emplace(*reverseTraversal);
            numberOfBasebandCardRemaining--;
        } else {
            basebandCards.basebandCardsWithOneLcg.emplace(*reverseTraversal);
        }
        reverseTraversal++;
    }
    return basebandCards;
}

void AsilBasebandPooling::sortAndPrioritizeBasebandCards(VectorOfBasebandCards& basebandCardsWithPrioritization) const {
    stable_sort(
        basebandCardsWithPrioritization.begin(), basebandCardsWithPrioritization.end(),
        [](BasebandCard const& basebandCard1, BasebandCard const& basebandCard2) {
            return basebandCard1.getKeplers().size() > basebandCard2.getKeplers().size();
        });
}

void AsilBasebandPooling::sortAndPrioritizeLcgs(VectorOfLcgs& lcgsInPriorityOrder) const {
    stable_sort(lcgsInPriorityOrder.begin(), lcgsInPriorityOrder.end(), [](Lcg const& lcg1, Lcg const& lcg2) {
        return lcg1.getPercentageShare() > lcg2.getPercentageShare();
    });
}

void AsilBasebandPooling::assignBasebandCardsWithOneLcg(
    KeplerNidToLcgMap& poolingMap, VectorOfLcgs& lcgsInPriorityOrder,
    SetOfBasebandCards const& basebandCardsWithOneLcg) const {
    VectorOfBasebandCards basebandCardsWithPrioritization;
    copy(
        basebandCardsWithOneLcg.cbegin(), basebandCardsWithOneLcg.cend(),
        back_inserter(basebandCardsWithPrioritization));
    sortAndPrioritizeBasebandCards(basebandCardsWithPrioritization);

    VectorOfLcgs::const_iterator lcgsIterator = lcgsInPriorityOrder.cbegin();
    for (BasebandCard const& basebandCard : basebandCardsWithPrioritization) {
        if (lcgsIterator != lcgsInPriorityOrder.cend()) {
            unsigned int lcgId(lcgsIterator->getLcgId());
            SetOfKeplers keplersInBasebandCard(basebandCard.getKeplers());
            for (Kepler const& kepler : keplersInBasebandCard) {
                poolingMap[kepler.getNid()] = lcgId;
            }
            lcgsIterator++;
        }
    }
    lcgsInPriorityOrder.erase(lcgsInPriorityOrder.cbegin(), lcgsIterator);
}

void AsilBasebandPooling::assignBasebandCardsWithMultipleLcgs(
    KeplerNidToLcgMap& poolingMap, VectorOfLcgs& lcgsInPriorityOrder,
    SetOfBasebandCards const& basebandCardsWithMultipleLcgs) const {
    VectorOfBasebandCards basebandCardsWithPrioritization;
    copy(
        basebandCardsWithMultipleLcgs.cbegin(), basebandCardsWithMultipleLcgs.cend(),
        back_inserter(basebandCardsWithPrioritization));
    sortAndPrioritizeBasebandCards(basebandCardsWithPrioritization);

    VectorOfLcgs::const_iterator lcgsIterator = lcgsInPriorityOrder.cbegin();
    for (BasebandCard const& basebandCard : basebandCardsWithPrioritization) {
        SetOfKeplers keplersInBasebandCard(basebandCard.getKeplers());
        unsigned int keplerCount = 0;
        for (Kepler const& kepler : keplersInBasebandCard) {
            if (keplerCount % 2 == 0 && keplerCount != 0) {
                lcgsIterator++;
            }
            if (lcgsIterator != lcgsInPriorityOrder.cend()) {
                unsigned int lcgId(lcgsIterator->getLcgId());
                poolingMap[kepler.getNid()] = lcgId;
            }
            keplerCount++;
        }
        lcgsIterator++;
    }
    lcgsInPriorityOrder.erase(lcgsInPriorityOrder.cbegin(), lcgsIterator);
}

}  // namespace alba
