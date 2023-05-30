#pragma once

#include <BooleanAlgebra/Algorithm/QuineMcCluskey/Implicant.hpp>
#include <Common/Print/AlbaPrintFunctions.hpp>

#include <functional>
#include <sstream>

namespace alba {

namespace booleanAlgebra {

template <typename Minterm>
class Implicants {
public:
    using ImplicantWithMinterm = Implicant<Minterm>;
    using ImplicantWithMintermInitializerList = std::initializer_list<ImplicantWithMinterm>;
    using ImplicantWithMintermSet = std::set<ImplicantWithMinterm>;

    Implicants() = default;

    Implicants(ImplicantWithMintermInitializerList const& implicants) : m_implicantsData(implicants) {}

    bool operator==(Implicants const& second) const { return m_implicantsData == second.m_implicantsData; }

    bool operator!=(Implicants const& second) const {
        Implicants const& first(*this);
        return !(first == second);
    }

    int getSize() const { return m_implicantsData.size(); }

    ImplicantWithMintermSet const& getImplicantsData() const& { return m_implicantsData; }

    void addImplicant(ImplicantWithMinterm const& implicant) { m_implicantsData.emplace(implicant); }

    void addFinalImplicant(ImplicantWithMinterm const& implicant) {
        bool isAlreadyRepresented(false);
        for (ImplicantWithMinterm const& iteratorImplicant : m_implicantsData) {
            if (implicant.isSubset(iteratorImplicant)) {
                isAlreadyRepresented = true;
                break;
            }
        }
        if (!isAlreadyRepresented) {
            m_implicantsData.emplace(implicant);
        }
    }

private:
    friend std::ostream& operator<<(std::ostream& out, Implicants<Minterm> const& implicants) {
        printParameterWithName(out, "Implicants", implicants.m_implicantsData);
        return out;
    }

    ImplicantWithMintermSet m_implicantsData;
};

}  // namespace booleanAlgebra

}  // namespace alba
