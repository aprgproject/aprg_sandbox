#pragma once

namespace alba {

class AlbaRatio {
public:
    enum class Type { BothValuesZero, FirstValueIsZero, SecondValueIsZero, WithValidRatio };
    AlbaRatio(double const firstValue, double const secondValue);
    Type getType() const;
    double getValidRatioIfPossible() const;
    bool isBothZero() const;
    bool isOnlyOneValueZero() const;
    bool hasValidRatio() const;

private:
    Type determineTypeFrom2Values(double const firstValue, double const secondValue);
    double calculateValidRatio(double const firstValue, double const secondValue, Type const type);
    Type m_type;
    double m_ratio;
};

}  // namespace alba
