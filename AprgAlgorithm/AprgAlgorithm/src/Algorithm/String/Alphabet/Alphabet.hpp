#pragma once

#include <Common/Math/AlbaMathHelper.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>

namespace alba
{
namespace algorithm
{
template <typename Value>
class Alphabet
{
public:
    using Values = std::vector<Value>;

    Alphabet(std::string const& characters)
        : m_characters(characters)
    {}

    bool contains(char const c)
    {
        return stringHelper::isNotNpos(static_cast<int>(m_characters.find_first_of(c)));
    }

    char getCharacter(Value const& value)
    {
        char result{};
        if(value < m_characters.size())
        {
            result = m_characters.at(value) ;
        }
        return result;
    }

    Value getValue(char const c)
    {
        Value result{};
        unsigned int indexOfCharacter = m_characters.find_first_of(c);
        if(stringHelper::isNotNpos(static_cast<int>(indexOfCharacter)))
        {
            result = static_cast<Value>(indexOfCharacter);
        }
        return result;
    }

    unsigned int getRadix()
    {
        return m_characters.size();
    }

    unsigned int getNumbersOfBitsToRepresentCharacters()
    {
        return static_cast<unsigned int>(ceil(mathHelper::getLogarithm(2, getRadix())));
    }

    Values convertStringToValues(std::string const& stringParameter)
    {
        Values result;
        result.reserve(stringParameter.length());
        std::transform(stringParameter.cbegin(), stringParameter.cend(), std::back_inserter(result), [&](char const c)
        {
            return getValue(c);
        });
        return result;
    }

    std::string convertValuesToString(Values const& values)
    {
        std::string result;
        result.reserve(values.size());
        std::transform(values.cbegin(), values.cend(), std::back_inserter(result), [&](Value const& value)
        {
            return getCharacter(value);
        });
        return result;
    }

    std::string const& getCharacters()
    {
        return m_characters;
    }

private:
    std::string m_characters;
};

}

}
