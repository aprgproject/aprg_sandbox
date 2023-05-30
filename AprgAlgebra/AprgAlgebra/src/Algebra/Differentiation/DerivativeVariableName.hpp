#pragma once

#include <string>

namespace alba {

namespace algebra {

class DerivativeVariableName {
public:
    DerivativeVariableName(
        int const differentiationLevel, std::string const& baseVariable, std::string const& dependentVariable);
    DerivativeVariableName(std::string const& derivativeVariableInLeibnizNotation);

    bool isValid() const;
    int getDifferentiationLevel() const;
    std::string const& getBaseVariable() const;
    std::string const& getDependentVariable() const;
    std::string getNameInLeibnizNotation() const;

    void differentiate();

private:
    void processNumerator(std::string const& numerator);
    void processDenominator(std::string const& denominator);
    bool m_isValid;
    int m_differentiationLevel;
    std::string m_baseVariable;
    std::string m_dependentVariable;
};

}  // namespace algebra

}  // namespace alba
