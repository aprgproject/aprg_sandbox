#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace alba
{

enum class LogicalValue
{
    True,
    False,
    DontCare
};


class Implicant
{
public:
    bool operator==(Implicant const& implicant) const;
    bool operator<(Implicant const& implicant) const;
    Implicant operator+(Implicant const& implicant) const;
    bool isCompatible(Implicant const& implicant) const;
    bool isSubset(Implicant const& implicant) const;
    bool isSuperset(unsigned int minterm) const;
    unsigned int getLengthOfEquivalentString() const;
    std::string getEquivalentString() const;
    std::string getEquivalentString(unsigned int length) const;
    std::string getMintermString() const;
    unsigned int getFirstMinterm() const;
    unsigned int getAndResultOfMinterms() const;
    unsigned int getOrResultOfMinterms() const;

    void addMinterm(unsigned int minterm);
private:
    std::set <unsigned int> m_minterms;
};

class Implicants
{
public:
    void loopAllImplicants(std::function<void(Implicant const&)> doFunction) const;
    unsigned int getSize() const;
    std::string getImplicantsString() const;

    void addImplicant(Implicant const& implicant);
    void addFinalImplicant(Implicant const& implicant);
private:
    std::vector<Implicant> m_implicants;
};


struct ImplicantsMap
{
    std::map<unsigned int, Implicants> implicantsMap; // cubeSize, implicants
};

class QuineMcCluskey
{
public:
    QuineMcCluskey();
    LogicalValue getOutput(unsigned int const input) const;
    unsigned int getNumberOfOnes(unsigned int const value) const;
    Implicants getImplicants(unsigned int degree, unsigned int cubeSize) const;
    Implicants getAllFinalImplicants() const;

    void setInputOutput(unsigned int const input, LogicalValue const output);
    void fillComputationalTableWithMintermsForZeroCube();
    void findCombinationOfImplicants(unsigned int degree, unsigned int cubeSize);
    void findAllCombinations();

    std::string getOutputTable(Implicants const& finalImplicants);

private:
    void addMintermForZeroCube(unsigned int minterm);

    unsigned int m_cubeSize;
    std::map<unsigned int, LogicalValue> m_functionMap;
    std::map<unsigned int, ImplicantsMap> m_computationalTable; // https://en.wikipedia.org/wiki/Quine%E2%80%93McCluskey_algorithm
};

}
