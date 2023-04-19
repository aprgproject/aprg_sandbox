#include <Common/Debug/AlbaFundamentalOperationsCounter.hpp>

#include <gtest/gtest.h>

#include <memory>

using namespace std;

namespace alba
{

namespace original // make an original namespace to avoid collision
{
class SampleClass
{
public:    SampleClass()
        : m_dataPointer()
    {}
    SampleClass(int const data)
        : m_dataPointer(make_unique<int>(data))
    {}
    SampleClass(SampleClass const& parameter)
        : m_dataPointer(make_unique<int>(*parameter.m_dataPointer))
    {}
    SampleClass& operator=(SampleClass const& parameter)
    {
        m_dataPointer = make_unique<int>(*parameter.m_dataPointer);
        return *this;
    }
    SampleClass(SampleClass && parameter)
        : m_dataPointer(move(parameter.m_dataPointer))
    {}
    SampleClass& operator=(SampleClass && parameter)
    {
        m_dataPointer = move(parameter.m_dataPointer);
        return *this;
    }
    unique_ptr<int> m_dataPointer;
};
}

inline namespace WithCounter // inline this namespace to hoist it up and replace the [SampleClass] with the [SampleClass with counter]
{
using SampleClass = AlbaFundamentalOperationsCounter<original::SampleClass>;
using CountsForSampleClass = AlbaFundamentalOperationsCounts<original::SampleClass>;
}

namespace
{
SampleClass getRValue()
{
    SampleClass namedReturnedObject(5678);
    return namedReturnedObject;
}
}

TEST(AlbaFundamentalOperationsCounterTest, UserConstructionIsCounted)
{
    CountsForSampleClass::getInstance().resetCounts();

    SampleClass object(1234);

    EXPECT_EQ("userConstructionCount: 1 defaultConstructionCount: 0 destructionCount: 0 copyConstructionCount: 0 copyAssignmentCount: 0 moveConstructionCount: 0 moveAssignmentCount: 0",
              CountsForSampleClass::getInstance().getReport());
}

TEST(AlbaFundamentalOperationsCounterTest, DefaultConstructionIsCounted)
{
    CountsForSampleClass::getInstance().resetCounts();

    SampleClass object;

    EXPECT_EQ("userConstructionCount: 0 defaultConstructionCount: 1 destructionCount: 0 copyConstructionCount: 0 copyAssignmentCount: 0 moveConstructionCount: 0 moveAssignmentCount: 0",
              CountsForSampleClass::getInstance().getReport());
}

TEST(AlbaFundamentalOperationsCounterTest, DestructionIsCounted)
{
    CountsForSampleClass::getInstance().resetCounts();

    {
        SampleClass object;
    }

    EXPECT_EQ("userConstructionCount: 0 defaultConstructionCount: 1 destructionCount: 1 copyConstructionCount: 0 copyAssignmentCount: 0 moveConstructionCount: 0 moveAssignmentCount: 0",
              CountsForSampleClass::getInstance().getReport());
}

TEST(AlbaFundamentalOperationsCounterTest, CopyConstructionIsCounted)
{
    SampleClass originalObject(1234);
    CountsForSampleClass::getInstance().resetCounts();

    SampleClass object(originalObject);

    EXPECT_EQ("userConstructionCount: 1 defaultConstructionCount: 0 destructionCount: 0 copyConstructionCount: 0 copyAssignmentCount: 0 moveConstructionCount: 0 moveAssignmentCount: 0",
              CountsForSampleClass::getInstance().getReport());
}

TEST(AlbaFundamentalOperationsCounterTest, CopyAssignmentIsCounted)
{
    SampleClass originalObject(1234);
    SampleClass object(5678);
    CountsForSampleClass::getInstance().resetCounts();

    object = originalObject;

    EXPECT_EQ("userConstructionCount: 0 defaultConstructionCount: 0 destructionCount: 0 copyConstructionCount: 0 copyAssignmentCount: 1 moveConstructionCount: 0 moveAssignmentCount: 0",
              CountsForSampleClass::getInstance().getReport());
}

TEST(AlbaFundamentalOperationsCounterTest, MoveConstructionIsCounted)
{
    CountsForSampleClass::getInstance().resetCounts();

    SampleClass object(getRValue());

    EXPECT_EQ("userConstructionCount: 1 defaultConstructionCount: 0 destructionCount: 0 copyConstructionCount: 0 copyAssignmentCount: 0 moveConstructionCount: 0 moveAssignmentCount: 0",
              CountsForSampleClass::getInstance().getReport());
}

TEST(AlbaFundamentalOperationsCounterTest, MoveAssignmentIsCounted)
{
    SampleClass originalObject(1234);
    SampleClass object(5678);
    CountsForSampleClass::getInstance().resetCounts();

    object = getRValue();

    EXPECT_EQ("userConstructionCount: 1 defaultConstructionCount: 0 destructionCount: 1 copyConstructionCount: 0 copyAssignmentCount: 0 moveConstructionCount: 0 moveAssignmentCount: 1",
              CountsForSampleClass::getInstance().getReport());
}

TEST(AlbaFundamentalOperationsCounterTest, ObjectIsConstructedOnceDueToRvo)
{
    CountsForSampleClass::getInstance().resetCounts();

    SampleClass object(getRValue());

    EXPECT_EQ("userConstructionCount: 1 defaultConstructionCount: 0 destructionCount: 0 copyConstructionCount: 0 copyAssignmentCount: 0 moveConstructionCount: 0 moveAssignmentCount: 0",
              CountsForSampleClass::getInstance().getReport());
}

}