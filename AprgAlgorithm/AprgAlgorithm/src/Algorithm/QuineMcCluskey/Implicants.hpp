#pragma once

#include <Algorithm/QuineMcCluskey/Implicant.hpp>

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
    using TraverseFunction = std::function<void(Implicant const&)>;

    unsigned int getSize() const
    {
        return m_implicants.size();    }

    std::string getImplicantsString() const
    {        std::stringstream implicantString;
        int index=0;
        for(Implicant const& implicant : m_implicants)
        {
            implicantString << "[" << index << " : " << implicant.getMintermString() << "], ";
            index++;
        }
        return implicantString.str();
    }

    void traverseAllImplicants(TraverseFunction const& traverseFunction) const
    {
        for(Implicant const& implicant : m_implicants)
        {
            traverseFunction(implicant);
        }
    }

    void addImplicant(Implicant const& implicant)
    {
        m_implicants.emplace(implicant);
    }

    void addFinalImplicant(Implicant const& implicant)
    {
        bool isAlreadyRepresented(false);        for(Implicant const& iteratorImplicant : m_implicants)
        {
            if(implicant.isSubset(iteratorImplicant))
            {                isAlreadyRepresented = true;
                break;
            }
        }
        if(!isAlreadyRepresented)
        {
            m_implicants.emplace(implicant);
        }
    }

private:
    std::set<Implicant> m_implicants;
};

}

}
