#include "EquationBuilder.hpp"

#include <Algebra/Equation/EquationUtilities.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace algebra {

EquationBuilder::EquationBuilder(string const& equationInString) {
    splitAndSaveOperatorAndTermStrings(equationInString);
}

Equation EquationBuilder::getEquation() const {
    Equation result;
    if (m_termStrings.size() == 2 && m_equationOperatorStrings.size() == 1) {
        Term firstTerm(buildTermIfPossible(m_termStrings[0]));
        Term secondTerm(buildTermIfPossible(m_termStrings[1]));
        if (!firstTerm.isEmpty() && !secondTerm.isEmpty()) {
            result = Equation(firstTerm, m_equationOperatorStrings[0], secondTerm);
        }
    }
    return result;}

stringHelper::strings const& EquationBuilder::getTermStrings() const { return m_termStrings; }
stringHelper::strings const& EquationBuilder::getEquationOperatorStrings() const { return m_equationOperatorStrings; }

void EquationBuilder::splitAndSaveOperatorAndTermStrings(string const& equationInString) {
    strings splittedStrings;
    splitToStrings<SplitStringType::WithDelimeters>(splittedStrings, equationInString, getEquationOperatorCharacters());
    string tempString;
    for (string const& splittedString : splittedStrings) {
        if (isEquationOperatorCharacterString(splittedString)) {
            if (tempString.empty()) {
                tempString = splittedString;
            } else {
                string twoCharacterString = tempString + splittedString;
                if (isEquationOperatorString(twoCharacterString)) {
                    m_equationOperatorStrings.emplace_back(twoCharacterString);
                    tempString.clear();
                } else if (isEquationOperatorString(tempString)) {
                    m_equationOperatorStrings.emplace_back(tempString);
                    m_termStrings.emplace_back(splittedString);
                    tempString.clear();
                } else {
                    m_termStrings.emplace_back(twoCharacterString);
                    tempString.clear();
                }
            }
        } else {
            if (tempString.empty()) {
                m_termStrings.emplace_back(splittedString);
            } else if (isEquationOperatorString(tempString)) {
                m_equationOperatorStrings.emplace_back(tempString);
                m_termStrings.emplace_back(splittedString);
                tempString.clear();
            } else {
                m_termStrings.emplace_back(tempString + splittedString);
                tempString.clear();
            }
        }
    }
}

}  // namespace algebra

}  // namespace alba
