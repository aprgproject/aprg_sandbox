#pragma once

#include <Algorithm/QuineMcCluskey/Implicant.hpp>
#include <Common/Print/AlbaPrintFunctions.hpp>

#include <functional>
#include <sstream>

namespace alba
{

namespace algorithm
{

template <typename Minterm>
class Implicants
{
public:
    using Implicant = Implicant<Minterm>;
    using ImplicantsInitializerList = std::initializer_list<Implicant>;
    using ImplicantData = std::set<Implicant>;
    using TraverseFunction = std::function<void(Implicant const&)>;

    Implicants()
    {}

    Implicants(ImplicantsInitializerList const& implicants)
        : m_implicantsData(implicants)
    {}

    bool operator==(Implicants const& second) const
    {
        return m_implicantsData == second.m_implicantsData;
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

    std::string getDisplayableString() const
    {
        std::stringstream ss;
        printParameter(ss, "Implicants", m_implicantsData);
        return ss.str();
    }

    void traverseAllImplicants(TraverseFunction const& traverseFunction) const
    {
        for(Implicant const& implicant : m_implicantsData)
        {
            traverseFunction(implicant);
        }
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
    std::set<Implicant> m_implicantsData;
};

template <typename Minterm>
std::ostream & operator<<(std::ostream & out, Implicants<Minterm> const& implicants)
{
    out << implicants.getDisplayableString();
    return out;
}

}

}
