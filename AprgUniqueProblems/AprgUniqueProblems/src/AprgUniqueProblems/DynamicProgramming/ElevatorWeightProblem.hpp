#pragma once

#include <vector>

namespace alba
{

class ElevatorWeightProblem
{
public:
    // There is an elevator with maximum weight x, and n people with known weights who want to get from the ground floor to the top floor.
    // What is the minimum number of rides needed if the people enter the elevator in an optimal order?

    using Weight = unsigned int;
    using Person = unsigned int;
    using PeopleBits = unsigned int;
    using People = std::vector<Person>;
    using ListOfPeople = std::vector<People>;
    using Weights = std::vector<Weight>;
    using NumberOfRidesAndWeight = std::pair<unsigned int, Weight>;
    using NumberOfRidesAndWeights = std::vector<NumberOfRidesAndWeight>;

    ElevatorWeightProblem(Weight const maximumElevatorWeight, Weights const& peopleWeights);

    unsigned int getNumberOfOptimalRides();
private:
    bool isPersonIncluded(PeopleBits const peopleBits, Person const person) const;
    Person getNumberOfPeople() const;
    PeopleBits getNumberOfPeopleSubsets() const;
    PeopleBits getProductBits(Person const person) const;
    PeopleBits removePerson(PeopleBits const peopleBits, Person const person) const;
    Weight m_maximumElevatorWeight;
    Weights m_peopleWeights;
    NumberOfRidesAndWeights m_numberOfRidesAndLastWeight;
};

}
