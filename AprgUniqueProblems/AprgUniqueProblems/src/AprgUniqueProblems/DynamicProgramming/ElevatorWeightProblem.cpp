#include "ElevatorWeightProblem.hpp"

using namespace std;

namespace alba
{

ElevatorWeightProblem::ElevatorWeightProblem(
        Weight const maximumElevatorWeight,
        Weights const& peopleWeights)
    : m_maximumElevatorWeight(maximumElevatorWeight)
    , m_peopleWeights(peopleWeights)
    , m_numberOfRidesAndLastWeight(getNumberOfPeopleSubsets(), NumberOfRidesAndWeight{})
{}

unsigned int ElevatorWeightProblem::getNumberOfOptimalRides(){
    unsigned int result(0);
    for(PeopleBits peopleBits=1; peopleBits<getNumberOfPeopleSubsets(); peopleBits++)
    {
        // initial value: n+1 rides are needed
        m_numberOfRidesAndLastWeight[peopleBits]=NumberOfRidesAndWeight{getNumberOfPeople()+1,0};
        for (Person person=0; person<getNumberOfPeople(); person++)
        {
            if(isPersonIncluded(peopleBits, person))
            {
                auto newOption=m_numberOfRidesAndLastWeight[removePerson(peopleBits, person)];
                if(newOption.second + m_peopleWeights.at(person) <= m_maximumElevatorWeight)
                {
                    // add p to an existing ride
                    newOption.second += m_peopleWeights.at(person);
                }
                else
                {
                    // reserve a new ride for p
                    newOption.first++;
                    newOption.second=m_peopleWeights.at(person);
                }
                m_numberOfRidesAndLastWeight[peopleBits]=min(m_numberOfRidesAndLastWeight.at(peopleBits), newOption);
            }
        }
    }
    unsigned int allPeopleBits = getNumberOfPeopleSubsets()-1;
    if(allPeopleBits < m_numberOfRidesAndLastWeight.size())
    {
        result = m_numberOfRidesAndLastWeight.at(allPeopleBits).first + 1;
    }
    return result;
}

bool ElevatorWeightProblem::isPersonIncluded(PeopleBits const peopleBits, Person const person) const{
    return peopleBits & getProductBits(person);
}

ElevatorWeightProblem::Person ElevatorWeightProblem::getNumberOfPeople() const
{
    return m_peopleWeights.size();
}

ElevatorWeightProblem::PeopleBits ElevatorWeightProblem::getNumberOfPeopleSubsets() const
{
    return 1<<getNumberOfPeople();
}

ElevatorWeightProblem::PeopleBits ElevatorWeightProblem::getProductBits(Person const person) const
{
    return 1<<person;
}

ElevatorWeightProblem::PeopleBits ElevatorWeightProblem::removePerson(PeopleBits const peopleBits, Person const person) const
{
    return peopleBits & ~(1 << person);
}

}
