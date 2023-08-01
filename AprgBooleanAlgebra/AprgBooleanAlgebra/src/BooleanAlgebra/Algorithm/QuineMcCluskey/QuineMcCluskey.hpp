#pragma once

#include <BooleanAlgebra/Algorithm/QuineMcCluskey/ImplicantTemplate.hpp>
#include <BooleanAlgebra/Algorithm/QuineMcCluskey/LogicalValue.hpp>
#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/Print/AlbaPrintFunctions.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/User/DisplayTable.hpp>

#include <map>
#include <queue>
#include <sstream>
#include <vector>

namespace alba {

namespace booleanAlgebra {

template <typename Minterm>
class QuineMcCluskey {
public:
    using Minterms = std::vector<Minterm>;
    using SetOfMinterms = std::set<Minterm>;
    using Implicant = ImplicantTemplate<Minterm>;
    using Implicants = std::set<Implicant>;
    using MintermToImplicantsMap = std::map<Minterm, Implicants>;
    using InputToOutputMap = std::map<Minterm, LogicalValue>;
    using ComputationalTable = std::map<Minterm, MintermToImplicantsMap>;

    QuineMcCluskey() : m_maxCommonalityCount(0) {}

    LogicalValue getOutput(Minterm const input) const {
        LogicalValue result(LogicalValue::False);
        auto it = m_inputToOutputMap.find(input);
        if (it != m_inputToOutputMap.end()) {
            result = it->second;
        }
        return result;
    }

    int getNumberOfOnes(Minterm const value) const { return AlbaBitValueUtilities<Minterm>::getNumberOfOnes(value); }

    Implicants getImplicants(int numberOfOnes, int commonalityCount) const {
        Implicants result;
        auto numberOfOnesIt = m_computationalTable.find(numberOfOnes);
        if (numberOfOnesIt != m_computationalTable.end()) {
            MintermToImplicantsMap const& implicantsMap(numberOfOnesIt->second);
            auto commonalityCountIt = implicantsMap.find(commonalityCount);
            if (commonalityCountIt != implicantsMap.end()) {
                Implicants const& implicants(commonalityCountIt->second);
                for (Implicant const& implicant : implicants) {
                    result.emplace(implicant);
                }
            }
        }
        return result;
    }

    Implicants getAllPrimeImplicants() const {
        Implicants result;
        for (auto it = m_computationalTable.begin(); it != m_computationalTable.end(); it++) {
            MintermToImplicantsMap const& implicantsMap(it->second);
            for (auto reverseIt = implicantsMap.rbegin(); reverseIt != implicantsMap.rend(); reverseIt++) {
                Implicants const& implicantsFromTable(reverseIt->second);
                for (Implicant const& implicantFromTable : implicantsFromTable) {
                    bool isAlreadyCovered(false);
                    for (Implicant const& existingImplicant : result) {
                        if (implicantFromTable.isASubsetOf(existingImplicant)) {
                            isAlreadyCovered = true;
                            break;
                        }
                    }
                    if (!isAlreadyCovered) {
                        result.emplace(implicantFromTable);
                    }
                }
            }
        }
        return result;
    }

    bool doImplicantsExistAt(int numberOfOnes, int commonalityCount) const {
        bool result(false);
        auto numberOfOnesIt = m_computationalTable.find(numberOfOnes);
        if (numberOfOnesIt != m_computationalTable.end()) {
            MintermToImplicantsMap const& implicantsMap(numberOfOnesIt->second);
            result = implicantsMap.find(commonalityCount) != implicantsMap.end();
        }
        return result;
    }

    void setInputOutput(Minterm const input, LogicalValue const output) {
        if (output == LogicalValue::True || output == LogicalValue::DontCare) {
            m_inputToOutputMap.emplace(input, output);
        }
    }

    void findAllCombinations() {
        int commonalityCount = 0;
        bool areAllCombinationsFound(false);
        while (!areAllCombinationsFound) {
            bool isCombinationFound(false);
            for (int numberOfOnes = 0; numberOfOnes + 1 < static_cast<int>(m_computationalTable.size());
                 numberOfOnes++) {
                findCombinationOfImplicants(numberOfOnes, commonalityCount);
                isCombinationFound = isCombinationFound | doImplicantsExistAt(numberOfOnes, commonalityCount + 1);
            }
            areAllCombinationsFound = !isCombinationFound;
            commonalityCount++;
        }
        m_maxCommonalityCount = (commonalityCount > 0) ? commonalityCount - 1 : 0;
    }

    void fillComputationalTableWithMintermsWithZeroCommonalityCount() {
        for (auto const& [input, output] : m_inputToOutputMap) {
            addMintermForZeroCommonalityCount(input);
        }
    }

    void findCombinationOfImplicants(int numberOfOnes, int commonalityCount) {
        if (numberOfOnes + 1 < static_cast<int>(m_computationalTable.size())) {
            Implicants const& implicants1(m_computationalTable[numberOfOnes][commonalityCount]);
            Implicants const& implicants2(m_computationalTable[numberOfOnes + 1][commonalityCount]);
            for (Implicant const& implicant1 : implicants1) {
                for (Implicant const& implicant2 : implicants2) {
                    if (implicant1.isCompatible(implicant2)) {
                        m_computationalTable[numberOfOnes][commonalityCount + 1].emplace(implicant1 + implicant2);
                    }
                }
            }
        }
    }

    std::string getComputationTableString() const {
        std::stringstream ss;
        for (auto const& [numberOfOnes, commonalityCountImplicantsPairs] : m_computationalTable) {
            ss << "Number of ones = " << numberOfOnes << "\n";
            for (auto const& [commonalityCount, implicants] : commonalityCountImplicantsPairs) {
                ss << "Commonality count = " << commonalityCount << " with ";
                printParameterWithName(ss, "Implicants", implicants);
                ss << "\n";
            }
        }
        return ss.str();
    }

    Implicants getBestPrimeImplicants(Implicants const& primeImplicants) const {
        return getBestPrimeImplicantsPetricksMethod(primeImplicants);
    }

    bool isASubset(std::set<int> const& smaller, std::set<int> const& larger) const {
        bool result(false);
        if (smaller.size() <= larger.size()) {
            result = true;
            for (Minterm const& elementOfSmaller : smaller) {
                auto it = larger.find(elementOfSmaller);
                if (it == larger.cend()) {
                    result = false;
                    break;
                }
            }
        }
        return result;
    }

    Implicants getBestPrimeImplicantsPetricksMethod(Implicants const& primeImplicants) const {
        // Based from this: https://en.wikipedia.org/wiki/Petrick%27s_method
        // Remember this simplifications:  X + XY = X and XX = X and X+X=X

        using Ids = std::set<int>;
        using InnerTerms = std::vector<Ids>;
        using OuterTerms = std::deque<InnerTerms>;

        Implicants result;
        SetOfMinterms mintermsToCover(getSetOfInputMintermsWithTrue());

        // construct equation
        OuterTerms outerTerms;  // outer terms have "AND" logic between them
        for (auto const& mintermToCover : mintermsToCover) {
            InnerTerms innerTerms;  // inner terms have "OR" logic between them
            int id = 0;
            for (auto it = primeImplicants.cbegin(); it != primeImplicants.cend(); ++it, ++id) {
                Implicant const& primeImplicant(*it);
                if (primeImplicant.hasMinterm(mintermToCover)) {
                    // assign ids
                    innerTerms.emplace_back(Ids{id});
                }
            }
            outerTerms.emplace_back(innerTerms);
        }

        // distribute first two terms until theres one outer term left (top operation is OR)
        while (outerTerms.size() > 1) {
            InnerTerms innerTerms1 = outerTerms.front();
            InnerTerms innerTerms2 = *std::next(outerTerms.begin());

            outerTerms.erase(outerTerms.begin(), outerTerms.begin() + 2);

            InnerTerms combinedInnerTerms;
            for (Ids const& ids1 : innerTerms1) {
                for (Ids const& ids2 : innerTerms2) {
                    Ids idsOut(ids1);
                    for (auto const& idIn2 : ids2) {
                        // Uses set for XX = X simplification
                        idsOut.emplace(idIn2);
                    }
                    combinedInnerTerms.emplace_back(idsOut);
                }
            }

            // Simplify X + XY = X  to lessen terms
            for (int i = 0; i < static_cast<int>(combinedInnerTerms.size()); i++) {
                for (int j = 0;  j < static_cast<int>(combinedInnerTerms.size()); j++) {
                    if (i != j && isASubset(combinedInnerTerms[i], combinedInnerTerms[j])) {
                        combinedInnerTerms.erase(combinedInnerTerms.begin() + j);
                        if (i < static_cast<int>(combinedInnerTerms.size())) {
                            continue;
                        } else {
                            break;
                        }
                    }
                }
            }
            // Put the new combined term on the front
            outerTerms.emplace_front(combinedInnerTerms);
        }
        if (!outerTerms.empty()) {
            // Final simplification of X + XY = X.
            InnerTerms& onlyInnerTerms(outerTerms.front());
            for (int i = 0; i < static_cast<int>(onlyInnerTerms.size()); i++) {
                for (int j = 0; j < static_cast<int>(onlyInnerTerms.size()); j++) {
                    if (i != j && isASubset(onlyInnerTerms[i], onlyInnerTerms[j])) {
                        onlyInnerTerms.erase(onlyInnerTerms.begin() + j);
                        continue;
                    }
                }
            }

            // locate the item with least number of ids
            int minSize = std::numeric_limits<int>::max();
            int minSizeIndex = 0;
            for (int i = 0; i < static_cast<int>(onlyInnerTerms.size()); i++) {
                int idsSize = onlyInnerTerms[i].size();
                if (minSize > idsSize) {
                    minSizeIndex = i;
                    minSize = idsSize;
                }
            }
            Ids const& bestIds(onlyInnerTerms[minSizeIndex]);

            // Based from the best ids, get the corresponding implicant and add it to result
            auto itBestIds = bestIds.cbegin();
            int idFromImplicants = 0;
            for (auto itImplicants = primeImplicants.cbegin();
                 itImplicants != primeImplicants.cend() && itBestIds != bestIds.cend();
                 ++itImplicants, ++idFromImplicants) {
                if (*itBestIds == idFromImplicants) {
                    result.emplace(*itImplicants);
                    ++itBestIds;
                }
            }
        }

        return result;
    }

    Implicants getBestPrimeImplicantsMyMethod(Implicants const& primeImplicants) const {
        // This is an algorithm I developed on how I would solve it.
        Implicants result;
        SetOfMinterms mintermsToCover(getSetOfInputMintermsWithTrue());
        std::set<Implicant> remainingImplicants(primeImplicants);

        while (!mintermsToCover.empty()) {
            // Process implicants that cover lone minterms first
            while (true) {
                std::vector<Implicant> implicantsWithLoneMinterm;
                for (auto const& mintermToCover : mintermsToCover) {
                    int numberOfImplicantsThatCover = 0;
                    Implicant lastImplicantThatCovers;
                    for (Implicant const& remainingImplicant : remainingImplicants) {
                        if (remainingImplicant.hasMinterm(mintermToCover)) {
                            numberOfImplicantsThatCover++;
                            if (numberOfImplicantsThatCover > 1) {
                                break;
                            }
                            lastImplicantThatCovers = remainingImplicant;
                        }
                    }
                    if (numberOfImplicantsThatCover == 1) {
                        implicantsWithLoneMinterm.emplace_back(lastImplicantThatCovers);
                    }
                }
                if (implicantsWithLoneMinterm.empty()) {
                    break;
                } else {
                    for (auto const& implicant : implicantsWithLoneMinterm) {
                        result.emplace(implicant);
                        remainingImplicants.erase(implicant);
                        for (Minterm const& coveredMinterm : implicant.getMinterms()) {
                            mintermsToCover.erase(coveredMinterm);
                        }
                    }
                }
            }

            // Process an implicant that covers the maximum number of minterms
            if (!mintermsToCover.empty()) {
                std::pair<int, Implicant> mintermCountAndImplicantPair;
                for (Implicant const& remainingImplicant : remainingImplicants) {
                    int mintermCount(0U);
                    for (auto const& mintermToCover : mintermsToCover) {
                        if (remainingImplicant.hasMinterm(mintermToCover)) {
                            mintermCount++;
                        }
                    }
                    if (mintermCountAndImplicantPair.first < mintermCount) {
                        mintermCountAndImplicantPair = std::make_pair(mintermCount, remainingImplicant);
                    }
                }
                Implicant const& implicantWithMaxCount(mintermCountAndImplicantPair.second);
                result.emplace(implicantWithMaxCount);
                remainingImplicants.erase(implicantWithMaxCount);
                for (Minterm const& coveredMinterm : implicantWithMaxCount.getMinterms()) {
                    mintermsToCover.erase(coveredMinterm);
                }
            }
        }

        return result;
    }

    std::string getOutputTable(Implicants const& primeImplicants) const {
        Minterms inputsWithTrue(getInputMintermsWithTrue());
        DisplayTable displayTable;
        displayTable.setBorders("", "|");
        displayTable.addRow();
        displayTable.getLastRow().addCell(" ");
        for (auto const& input : inputsWithTrue) {
            std::stringstream ss;
            ss << input;
            displayTable.getLastRow().addCell(ss.str());
        }
        int maxLength = 0;
        for (Implicant const& implicant : primeImplicants) {
            maxLength = std::max(maxLength, implicant.getMaxLengthOfEquivalentString());
        }
        for (Implicant const& implicant : primeImplicants) {
            displayTable.addRow();
            displayTable.getLastRow().addCell(implicant.getEquivalentString(maxLength));
            for (auto const& input : inputsWithTrue) {
                std::string cell = implicant.hasMinterm(input) ? "X" : " ";
                displayTable.getLastRow().addCell(cell);
            }
        }
        return stringHelper::convertToString(displayTable);
    }

private:
    Minterms getInputMintermsWithTrue() const {
        Minterms result;
        for (auto [input, output] : m_inputToOutputMap) {
            if (output == LogicalValue::True) {
                result.emplace_back(input);
            }
        }
        return result;
    }

    SetOfMinterms getSetOfInputMintermsWithTrue() const {
        SetOfMinterms result;
        for (auto [input, output] : m_inputToOutputMap) {
            if (output == LogicalValue::True) {
                result.emplace(input);
            }
        }
        return result;
    }

    void addMintermForZeroCommonalityCount(Minterm const& minterm) {
        int numberOfOnes(getNumberOfOnes(minterm));
        Implicant implicant;
        implicant.addMinterm(minterm);
        m_computationalTable[numberOfOnes][0].emplace(implicant);
    }

    int m_maxCommonalityCount;
    InputToOutputMap m_inputToOutputMap;
    ComputationalTable m_computationalTable;  // https://en.wikipedia.org/wiki/Quine%E2%80%93McCluskey_algorithm
};

}  // namespace booleanAlgebra

}  // namespace alba
