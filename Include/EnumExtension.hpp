#pragma once
#include <utility>
#include <array>
#include <type_traits>
#include <string_view>

#ifndef ENUM_HELPER_MIN_VALUE
#define ENUM_HELPER_MIN_VALUE (-128)
#endif
#ifndef ENUM_HELPER_MAX_VALUE
#define ENUM_HELPER_MAX_VALUE 128
#endif
#ifndef ENUM_HELPER_NUMBER_OF_VALUES
#define ENUM_HELPER_NUMBER_OF_VALUES (ENUM_HELPER_MAX_VALUE - ENUM_HELPER_MIN_VALUE + 1)
#endif

class Enum
{
private:
    template <auto... Args>
    constexpr static std::string_view GetEnumeratorNamesHelper()
    {
#if defined(__clang__) || defined(__GNUC__)
        constexpr std::string_view name{__PRETTY_FUNCTION__};
#elif defined(_MSC_VER)
        constexpr std::string_view name{__FUNCSIG__};
#else
#error unknown compiler
#endif
        return name;
    }

    template <typename EnumType, auto... Args>
    constexpr static std::string_view GetEnumeratorNames(std::index_sequence<Args...>)
    {
        return GetEnumeratorNamesHelper<static_cast<EnumType>(Args + ENUM_HELPER_MIN_VALUE)...>();
    }

    template <typename EnumType>
    constexpr static std::array<EnumType, ENUM_HELPER_NUMBER_OF_VALUES> GetEnumValues()
    {
        std::array<EnumType, ENUM_HELPER_NUMBER_OF_VALUES> array{};
        for (int i = 0; i < ENUM_HELPER_NUMBER_OF_VALUES; ++i)
        {
            array[i] = static_cast<EnumType>(ENUM_HELPER_MIN_VALUE + i);
        }

        return array;
    }

    template <std::size_t N>
    constexpr static std::array<std::string_view, N> Split(std::string_view str)
    {
        std::array<std::string_view, N> array{};
        std::size_t start = 0;
        std::size_t end = 0;

        for (std::size_t i = 0; i < N && end != std::string_view::npos; i++)
        {
            end = str.find_first_of(',', start);
            auto substring = str.substr(start, end - start);
            array[i] = substring;
            start = end + 2;
        }

        return array;
    }

public:
    static constexpr std::string_view OutOfScopeValue = "Out of scope value";

    template <typename EnumType>
    constexpr static std::string_view ValueAsString(EnumType value) noexcept
    {
        using namespace std::literals;

#if defined(__clang__)
        constexpr auto startingPart = "[Args = <"sv;
        constexpr auto endingPart = ">]"sv;
#elif defined(__GNUC__)
        constexpr auto startingPart = "[with auto ...Args = {"sv;
        constexpr auto endingPart = "};"sv;
#elif defined(_MSC_VER)
        constexpr auto startingPart = "__cdecl GetEnumeratorNamesHelper<"sv;
        constexpr auto endingPart = ">("sv;
#else
#error Unknown compiler
#endif

        constexpr std::string_view enumValuesAsString =
            GetEnumeratorNames<EnumType>(std::make_index_sequence<ENUM_HELPER_NUMBER_OF_VALUES>{});

        constexpr size_t start = enumValuesAsString.find(startingPart);
        constexpr size_t end = enumValuesAsString.rfind(endingPart);
        constexpr bool failed = start == std::string_view::npos || end == std::string_view::npos || end <= start;
        static_assert(!failed);

        constexpr auto trimmedValues =
            enumValuesAsString.substr(start + startingPart.size(), end - start - startingPart.size());
        constexpr std::array<std::string_view, ENUM_HELPER_NUMBER_OF_VALUES> valueArray =
            Split<ENUM_HELPER_NUMBER_OF_VALUES>(trimmedValues.data());
        constexpr std::array<EnumType, ENUM_HELPER_NUMBER_OF_VALUES> enumValues = GetEnumValues<EnumType>();
        for (auto i = 0; i < ENUM_HELPER_NUMBER_OF_VALUES; ++i)
        {
            if (value == enumValues[i])
            {
                return valueArray[i];
            }
        }

        return OutOfScopeValue;
    }
};