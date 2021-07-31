#include <EnumExtension.hpp>
#include <gtest/gtest.h>

// Enum values
constexpr int EnumFirstValue = -45;
constexpr int EnumNegativeValue = -31;
constexpr int EnumMiddleValue = 0;
constexpr int EnumPositiveValue = -4;
constexpr int EnumLastValue = 42;

// Not enum values
constexpr int FirstNotEnumValue = -32;
constexpr int SecondNotEnumValue = -2;
constexpr int ThirdNotEnumValue = 2;
constexpr int FourthNotEnumValue = 52;

// Out of scope values
constexpr int LowerOutOfScopeValue = -129;
constexpr int UpperOutOfScopeValue = 129;

// Standard enum
enum StandardEnum
{
    FirstValue    = EnumFirstValue,
    NegativeValue = EnumNegativeValue,
    MiddleValue   = EnumMiddleValue,
    PositiveValue = EnumPositiveValue,
    LastValue     = EnumLastValue
};

// Enum class
enum class EnumClass
{
    FirstValue    = EnumFirstValue,
    NegativeValue = EnumNegativeValue,
    MiddleValue   = EnumMiddleValue,
    PositiveValue = EnumPositiveValue,
    LastValue     = EnumLastValue

};

TEST(ValueAsString, StandardEnum_EnumValue)
{
    // StandardEnum::FirstValue
    constexpr std::string_view firstValue = Enum::ValueAsString(StandardEnum::FirstValue);
    EXPECT_EQ("FirstValue", firstValue);
    // StandardEnum::NegativeValue
    constexpr std::string_view negativeValue = Enum::ValueAsString(StandardEnum::NegativeValue);
    EXPECT_EQ("NegativeValue", negativeValue);
    // StandardEnum::MiddleValue
    constexpr std::string_view middleValue = Enum::ValueAsString(StandardEnum::MiddleValue);
    EXPECT_EQ("MiddleValue", middleValue);
    // StandardEnum::PositiveValue
    constexpr std::string_view positiveValue = Enum::ValueAsString(StandardEnum::PositiveValue);
    EXPECT_EQ("PositiveValue", positiveValue);
    // StandardEnum::LastValue
    constexpr std::string_view lastValue = Enum::ValueAsString(StandardEnum::LastValue);
    EXPECT_EQ("LastValue", lastValue);

    // Not enum value
    constexpr std::string_view notEnumValue = Enum::ValueAsString(static_cast<StandardEnum>(12));
    EXPECT_EQ("(StandardEnum)12", notEnumValue);
}

TEST(ValueAsString, StandardEnum_VariableValue)
{
    StandardEnum variable;
    std::string_view valueAsString;

    // StandardEnum::FirstValue
    variable = StandardEnum::FirstValue;
    valueAsString = Enum::ValueAsString(variable);
    EXPECT_EQ("FirstValue", valueAsString);
    // StandardEnum::NegativeValue
    variable = StandardEnum::NegativeValue;
    valueAsString = Enum::ValueAsString(variable);
    EXPECT_EQ("NegativeValue", valueAsString);
    // StandardEnum::MiddleValue
    variable = StandardEnum::MiddleValue;
    valueAsString = Enum::ValueAsString(variable);
    EXPECT_EQ("MiddleValue", valueAsString);
    // StandardEnum::PositiveValue
    variable = StandardEnum::PositiveValue;
    valueAsString = Enum::ValueAsString(variable);
    EXPECT_EQ("PositiveValue", valueAsString);
    // StandardEnum::LastValue
    variable = StandardEnum::LastValue;
    valueAsString = Enum::ValueAsString(variable);
    EXPECT_EQ("LastValue", valueAsString);
}

TEST(ValueAsString, EnumClass_EnumValue)
{
    // EnumClass::FirstValue
    constexpr std::string_view firstValue = Enum::ValueAsString(EnumClass::FirstValue);
    EXPECT_EQ("EnumClass::FirstValue", firstValue);
    // EnumClass::NegativeValue
    constexpr std::string_view negativeValue = Enum::ValueAsString(EnumClass::NegativeValue);
    EXPECT_EQ("EnumClass::NegativeValue", negativeValue);
    // EnumClass::MiddleValue
    constexpr std::string_view middleValue = Enum::ValueAsString(EnumClass::MiddleValue);
    EXPECT_EQ("EnumClass::MiddleValue", middleValue);
    // EnumClass::PositiveValue
    constexpr std::string_view positiveValue = Enum::ValueAsString(EnumClass::PositiveValue);
    EXPECT_EQ("EnumClass::PositiveValue", positiveValue);
    // EnumClass::LastValue
    constexpr std::string_view lastValue = Enum::ValueAsString(EnumClass::LastValue);
    EXPECT_EQ("EnumClass::LastValue", lastValue);
}

TEST(ValueAsString, EnumClass_VariableValue)
{
    EnumClass variable;
    std::string_view valueAsString;

    // EnumClass::FirstValue
    variable = EnumClass::FirstValue;
    valueAsString = Enum::ValueAsString(variable);
    EXPECT_EQ("EnumClass::FirstValue", valueAsString);
    // EnumClass::NegativeValue
    variable = EnumClass::NegativeValue;
    valueAsString = Enum::ValueAsString(variable);
    EXPECT_EQ("EnumClass::NegativeValue", valueAsString);
    // EnumClass::MiddleValue
    variable = EnumClass::MiddleValue;
    valueAsString = Enum::ValueAsString(variable);
    EXPECT_EQ("EnumClass::MiddleValue", valueAsString);
    // EnumClass::PositiveValue
    variable = EnumClass::PositiveValue;
    valueAsString = Enum::ValueAsString(variable);
    EXPECT_EQ("EnumClass::PositiveValue", valueAsString);
    // EnumClass::LastValue
    variable = EnumClass::LastValue;
    valueAsString = Enum::ValueAsString(variable);
    EXPECT_EQ("EnumClass::LastValue", valueAsString);
}

TEST(ValueAsString, NotEnumValue)
{
    std::string_view notStandardEnumValue;

    // Standard enum
    {
        // FirstNotEnumValue
        notStandardEnumValue = Enum::ValueAsString(static_cast<StandardEnum>(FirstNotEnumValue));
        EXPECT_EQ("(StandardEnum)" + std::to_string(FirstNotEnumValue), notStandardEnumValue);
        // SecondNotEnumValue
        notStandardEnumValue = Enum::ValueAsString(static_cast<StandardEnum>(SecondNotEnumValue));
        EXPECT_EQ("(StandardEnum)" + std::to_string(SecondNotEnumValue), notStandardEnumValue);
        // ThirdNotEnumValue
        notStandardEnumValue = Enum::ValueAsString(static_cast<StandardEnum>(ThirdNotEnumValue));
        EXPECT_EQ("(StandardEnum)" + std::to_string(ThirdNotEnumValue), notStandardEnumValue);
        // FourthNotEnumValue
        notStandardEnumValue = Enum::ValueAsString(static_cast<StandardEnum>(FourthNotEnumValue));
        EXPECT_EQ("(StandardEnum)" + std::to_string(FourthNotEnumValue), notStandardEnumValue);
    }

    // Enum class
    {
        // FirstNotEnumValue
        notStandardEnumValue = Enum::ValueAsString(static_cast<EnumClass>(FirstNotEnumValue));
        EXPECT_EQ("(EnumClass)" + std::to_string(FirstNotEnumValue), notStandardEnumValue);
        // SecondNotEnumValue
        notStandardEnumValue = Enum::ValueAsString(static_cast<EnumClass>(SecondNotEnumValue));
        EXPECT_EQ("(EnumClass)" + std::to_string(SecondNotEnumValue), notStandardEnumValue);
        // ThirdNotEnumValue
        notStandardEnumValue = Enum::ValueAsString(static_cast<EnumClass>(ThirdNotEnumValue));
        EXPECT_EQ("(EnumClass)" + std::to_string(ThirdNotEnumValue), notStandardEnumValue);
        // FourthNotEnumValue
        notStandardEnumValue = Enum::ValueAsString(static_cast<EnumClass>(FourthNotEnumValue));
        EXPECT_EQ("(EnumClass)" + std::to_string(FourthNotEnumValue), notStandardEnumValue);
    }
}

TEST(ValueAsString, OutOfScopeValue)
{
    std::string_view outOfScopeEnumValue;
    // Standard enum
    {
        // LowerOutOfScopeValue
        outOfScopeEnumValue = Enum::ValueAsString(static_cast<StandardEnum>(LowerOutOfScopeValue));
        EXPECT_EQ(Enum::OutOfScopeValue, outOfScopeEnumValue);
        // UpperOutOfScopeValue
        outOfScopeEnumValue = Enum::ValueAsString(static_cast<StandardEnum>(UpperOutOfScopeValue));
        EXPECT_EQ(Enum::OutOfScopeValue, outOfScopeEnumValue);
    }

    // Enum class
    {
        // LowerOutOfScopeValue
        outOfScopeEnumValue = Enum::ValueAsString(static_cast<EnumClass>(LowerOutOfScopeValue));
        EXPECT_EQ(Enum::OutOfScopeValue, outOfScopeEnumValue);
        // UpperOutOfScopeValue
        outOfScopeEnumValue = Enum::ValueAsString(static_cast<EnumClass>(UpperOutOfScopeValue));
        EXPECT_EQ(Enum::OutOfScopeValue, outOfScopeEnumValue);
    }
}