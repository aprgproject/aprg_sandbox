#include <Common/Container/AlbaUniqueVariant.hpp>

#include <gtest/gtest.h>

namespace alba {

TEST(AlbaUniqueVariantTest, AcquiringVariantTypeInvokesDefaultConstructor) {
    // Given
    struct ExampleStructure1 : public VariantDataType {
        ExampleStructure1() : unsignedField(0), floatField(0.F) {}

        uint8_t unsignedField;
        float floatField;
    };
    struct ExampleStructure2 : public VariantDataType {
        ExampleStructure2() : doubleField(0.0), charField('\0') {}
        double doubleField;
        char charField;
    };

    UniqueVariant<ExampleStructure1, ExampleStructure2> variant;

    // When
    ExampleStructure1& exampleStructure1 = variant.acquire<ExampleStructure1>();
    ExampleStructure2& exampleStructure2 = variant.acquire<ExampleStructure2>();

    // Then
    ASSERT_EQ(0U, exampleStructure1.unsignedField);
    // ASSERT_FLOAT_EQ(0.F, exampleStructure1.floatField); // commented out because of warning: 4th function call
    // argument is an uninitialized value [clang-analyzer-core.CallAndMessage]
    ASSERT_DOUBLE_EQ(0.0, exampleStructure2.doubleField);
    ASSERT_EQ('\0', exampleStructure2.charField);
}

class DestructorClass : public VariantDataType {
public:
    static bool s_destructorInvoked;
    ~DestructorClass() override { s_destructorInvoked = true; }
};
bool DestructorClass::s_destructorInvoked = false;

TEST(AlbaUniqueVariantTest, AcquiringVariantTypeDifferentThanAlreadyInVariantInvokesDestructor) {
    // Given
    UniqueVariant<DestructorClass, VariantDataType> variant;

    // When
    variant.acquire<DestructorClass>();
    variant.acquire<VariantDataType>();

    // Then
    ASSERT_TRUE(DestructorClass::s_destructorInvoked);
}

TEST(AlbaUniqueVariantTest, PolymorphismIsSupportedByUniqueVariant) {
    // Given
    constexpr int valueFromTest = 467;

    class Base : public VariantDataType {
        int m_value;

    public:
        explicit Base(int value) : m_value(value) {}
        ~Base() override = default;  // no need for virtual destructor because base destructor is already virtual

        virtual int getValue() const { return m_value; }
    };

    class Derived : public Base {
    public:
        Derived() : Base(0) {}
        int getValue() const override { return valueFromTest; }
    };

    // When
    UniqueVariant<Derived> variant;
    Base& baseRef = variant.acquire<Derived>();

    // Then
    ASSERT_EQ(valueFromTest, baseRef.getValue());
}

}  // namespace alba
