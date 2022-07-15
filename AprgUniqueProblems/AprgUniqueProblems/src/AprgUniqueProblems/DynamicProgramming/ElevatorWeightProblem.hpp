#pragma once

#include <vector>

namespace alba
{

class ElevatorWeightProblem
{
public:
    // There is an elevator with maximum weight x, and n people with known weights who want to get from the ground floor to the top floor.
    // What is the minimum number of rides needed if the people enter the elevator in an optimal order?

    // Recursive formulation:
    // -> Let numberOfRides(peopleBits) be the number of rides of people in peopleBits
    // -> Let lastWeight(peopleBits) be the last weight of the ride of people in peopleBits (peopleBits includes people from last ride)
    // -> For every person:
    // ---> if lastWeight(peopleBits without the person) + person weight <= maximum elevator weight:
    // -----> Then, add person to current ride
    // -----> So, lastWeight(peopleBits with a person) = lastWeight(peopleBits without a person) + person weight
    // ---> else
    // -----> Then, create a new ride with only the person
    // -----> numberOfRides(peopleBits with a person) = numberOfRides(peopleBits without a person)+1
    // -----> So, lastWeight(peopleBits with a person) = person weight

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
