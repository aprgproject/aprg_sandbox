#pragma once

#include <set>
#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Objects>
class PossibilitiesGeneration
{
public:
    using Object = typename Objects::value_type;
    using ProcessedObjects = std::set<Object>;
    using Possibility = Objects;
    using Possibilities = std::vector<Objects>;

    struct RecursionData
    {
        Possibilities & possibilities;
        Possibility currentPossibility;
        unsigned int currentIndex;
        Objects const& objects;
        unsigned int const targetPossibilityLength;
    };

    // rule of five or six
    PossibilitiesGeneration() = delete;
    ~PossibilitiesGeneration() = delete;
    PossibilitiesGeneration(PossibilitiesGeneration const&) = delete;
    PossibilitiesGeneration & operator= (PossibilitiesGeneration const&) = delete;
    PossibilitiesGeneration(PossibilitiesGeneration &&) = delete;
    PossibilitiesGeneration & operator= (PossibilitiesGeneration &&) = delete;

    static Possibilities generatePossibilitiesUsingRecursion(Objects const& objects)
    {
        Possibilities result;
        RecursionData recursionData(createRecursionData(result, objects, objects.size()));
        collectPossibilitiesUsingRecursion(recursionData);
        return result;
    }

    static Possibilities generatePossibilitiesWithLength(Objects const& objects, unsigned int const possibilityLength)
    {
        Possibilities result;
        RecursionData recursionData(createRecursionData(result, objects, std::min(possibilityLength, objects.size())));
        collectPossibilitiesUsingRecursion(recursionData);
        return result;
    }

private:

    static RecursionData createRecursionData(
            Possibilities & possibilities,
            Objects const& objects,
            unsigned int const length)
    {
        return RecursionData{possibilities, Possibility(), 0U, objects, length};
    }

    static void collectPossibilitiesUsingRecursion(RecursionData & recursionData)
    {
        if(recursionData.currentPossibility.size() == recursionData.targetPossibilityLength)
        {
            recursionData.possibilities.emplace_back(recursionData.currentPossibility);
        }
        else
        {
            Objects const& objects(recursionData.objects);
            Possibility & currentPossibility(recursionData.currentPossibility);

            for(unsigned int index=0; index<objects.size(); index++)
            {
                currentPossibility.emplace_back(objects.at(index));
                collectPossibilitiesUsingRecursion(recursionData);
                currentPossibility.pop_back();
            }
        }
    }
};

}

}
