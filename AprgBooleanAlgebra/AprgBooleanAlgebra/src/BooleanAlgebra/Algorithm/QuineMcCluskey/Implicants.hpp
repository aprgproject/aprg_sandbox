#pragma once

#include <BooleanAlgebra/Algorithm/QuineMcCluskey/Implicant.hpp>
#include <Common/Print/AlbaPrintFunctions.hpp>

#include <functional>
#include <sstream>

namespace alba
{

namespace booleanAlgebra
{

template <typename Minterm>
class Implicants
{
public:
    using Implicant = Implicant<Minterm>;
    using ImplicantsInitializerList = std::initializer_list<Implicant>;
    using ImplicantData = std::set<Implicant>;

    Implicants() = default;

    Implicants(ImplicantsInitializerList const& implicants)
        : m_implicantsData(implicants)    {}

    bool operator==(Implicants const& second) const
    {        return m_implicantsData == second.m_implicantsData;
    }

    bool operator!=(Implicants const& second) const
    {
        Implicants const& first(*this);
        return !(first==second);
    }

    unsigned int getSize() const
    {
        return m_implicantsData.size();
    }

    ImplicantData const& getImplicantsData() const&
    {
        return m_implicantsData;
    }

    std::string getDisplayableString() const
    {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    void addImplicant(Implicant const& implicant)
    {
        m_implicantsData.emplace(implicant);
    }

    void addFinalImplicant(Implicant const& implicant)
    {
        bool isAlreadyRepresented(false);
        for(Implicant const& iteratorImplicant : m_implicantsData)
        {
            if(implicant.isSubset(iteratorImplicant))
            {
                isAlreadyRepresented = true;
                break;
            }
        }
        if(!isAlreadyRepresented)
        {
            m_implicantsData.emplace(implicant);
        }
    }

private:

    friend std::ostream & operator<<(std::ostream & out, Implicants<Minterm> const& implicants)
    {
        printParameterWithName(out, "Implicants", implicants.m_implicantsData);
        return out;
    }

    ImplicantData m_implicantsData;
};

}

}
