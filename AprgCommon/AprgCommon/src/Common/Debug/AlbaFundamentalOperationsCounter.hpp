#pragma once

#include <Common/Container/AlbaSingleton.hpp>

#include <sstream>
#include <utility>

namespace alba
{

template <typename TypeToShadow>
struct AlbaFundamentalOperationsCounts : public AlbaSingleton<AlbaFundamentalOperationsCounts<TypeToShadow>>
{
    struct Counts
    {
        unsigned int userConstructionCount;
        unsigned int defaultConstructionCount;
        unsigned int destructionCount;
        unsigned int copyConstructionCount;
        unsigned int copyAssignmentCount;
        unsigned int moveConstructionCount;
        unsigned int moveAssignmentCount;
    };
    void resetCounts()
    {
        counts = {};
    }
    std::string getReport() const
    {
        std::stringstream ss;
        ss << "userConstructionCount: " << counts.userConstructionCount;
        ss << " defaultConstructionCount: " << counts.defaultConstructionCount;
        ss << " destructionCount: " << counts.destructionCount;
        ss << " copyConstructionCount: " << counts.copyConstructionCount;
        ss << " copyAssignmentCount: " << counts.copyAssignmentCount;
        ss << " moveConstructionCount: " << counts.moveConstructionCount;
        ss << " moveAssignmentCount: " << counts.moveAssignmentCount;
        return ss.str();
    }
    Counts counts;
};

template <typename TypeToShadow>
class AlbaFundamentalOperationsCounter : public TypeToShadow
{
public:

#define COUNTS AlbaFundamentalOperationsCounts<TypeToShadow>::getInstance().counts

    // NOTE: COMMENT operation if not needed

    template<typename ...Params>
    AlbaFundamentalOperationsCounter(Params&&... params)
        : TypeToShadow(std::forward<Params>(params)...)
    {
        ++COUNTS.userConstructionCount;
    }

    AlbaFundamentalOperationsCounter()
        : TypeToShadow()
    {
        ++COUNTS.defaultConstructionCount;
    }

    ~AlbaFundamentalOperationsCounter()
    {
        ++COUNTS.destructionCount;
    }

    AlbaFundamentalOperationsCounter(AlbaFundamentalOperationsCounter const& parameter)
        : TypeToShadow(static_cast<TypeToShadow const&>(parameter))
    {
        ++COUNTS.copyConstructionCount;
    }

    AlbaFundamentalOperationsCounter& operator=(AlbaFundamentalOperationsCounter const& parameter)
    {
        static_cast<TypeToShadow &>(*this) = static_cast<TypeToShadow const&>(parameter);
        ++COUNTS.copyAssignmentCount;
        return *this;
    }

    AlbaFundamentalOperationsCounter(AlbaFundamentalOperationsCounter && parameter)
        : TypeToShadow(static_cast<TypeToShadow &&>(parameter))
    {
        ++COUNTS.moveConstructionCount;
    }

    AlbaFundamentalOperationsCounter& operator=(AlbaFundamentalOperationsCounter && parameter)
    {
        static_cast<TypeToShadow &>(*this) = static_cast<TypeToShadow &&>(parameter);
        ++COUNTS.moveAssignmentCount;
        return *this;
    }

#undef COUNTS
};


} // namespace alba
