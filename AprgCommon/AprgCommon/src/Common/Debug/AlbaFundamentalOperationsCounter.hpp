#pragma once

#include <Common/Container/AlbaSingleton.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>

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
        // enable_if for isConstructible is not used here, because it still cause compiler error when not used
        ++COUNTS.userConstructionCount;
    }

    AlbaFundamentalOperationsCounter()
        : std::enable_if_t<typeHelper::isDefaultConstructible<TypeToShadow>(), TypeToShadow>()
    {
        ++COUNTS.defaultConstructionCount;
    }

    ~AlbaFundamentalOperationsCounter()
    {
        // enable_if for isConstructible is not used here, because this is just debug tool
        ++COUNTS.destructionCount;
    }

    AlbaFundamentalOperationsCounter(AlbaFundamentalOperationsCounter const& parameter)
        : std::enable_if_t<typeHelper::isCopyConstructible<TypeToShadow>(), TypeToShadow>(static_cast<TypeToShadow const&>(parameter))
    {
        ++COUNTS.copyConstructionCount;
    }

    AlbaFundamentalOperationsCounter& operator=(AlbaFundamentalOperationsCounter const& parameter)
    {
        using EnabledTypeToShadow = std::enable_if_t<typeHelper::isCopyAssignable<TypeToShadow>(), TypeToShadow>;
        static_cast<EnabledTypeToShadow &>(*this) = static_cast<EnabledTypeToShadow const&>(parameter);
        ++COUNTS.copyAssignmentCount;
        return *this;
    }

    AlbaFundamentalOperationsCounter(AlbaFundamentalOperationsCounter && parameter)
        : std::enable_if_t<typeHelper::isMoveConstructible<TypeToShadow>(), TypeToShadow>(static_cast<TypeToShadow &&>(parameter))
    {
        ++COUNTS.moveConstructionCount;
    }

    AlbaFundamentalOperationsCounter& operator=(AlbaFundamentalOperationsCounter && parameter)
    {
        using EnabledTypeToShadow = std::enable_if_t<typeHelper::isMoveAssignable<TypeToShadow>(), TypeToShadow>;
        static_cast<EnabledTypeToShadow &>(*this) = static_cast<EnabledTypeToShadow &&>(parameter);
        ++COUNTS.moveAssignmentCount;
        return *this;
    }

#undef COUNTS
};


} // namespace alba
