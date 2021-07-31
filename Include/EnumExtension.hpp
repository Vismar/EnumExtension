#pragma once
#include <utility>
#include <array>
#include <type_traits>
#include <string_view>

#ifndef MIN_VALUE
#define MIN_VALUE -128
#endif
#ifndef MAX_VALUE
#define MAX_VALUE 128
#endif
#define NUMBER_OF_VALUES MAX_VALUE - MIN_VALUE + 1

class Enum
{
private:
    template <auto... Args>
    constexpr static std::string_view GetEnumeratorNamesHelper()
    {
#if defined(__GNUC__) || defined(__clang__)
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
        return GetEnumeratorNamesHelper<static_cast<EnumType>(Args + MIN_VALUE)...>();
    }

    template <typename EnumType>
    constexpr static std::array<EnumType, NUMBER_OF_VALUES> GetEnumValues()
    {
        std::array<EnumType, NUMBER_OF_VALUES> array{};
        for (int i = 0; i < NUMBER_OF_VALUES; ++i)
        {
            array[i] = static_cast<EnumType>(MIN_VALUE + i);
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
            auto substr = str.substr(start, end - start);
            array[i] = substr;
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

#if defined(__GNUC__)
        constexpr auto start_bit = "[with auto ...Args = {"sv;
        constexpr auto end_bit = "};"sv;
#elif defined(__clang__)
        constexpr auto start_bit = "[Args = <"sv;
        constexpr auto end_bit = ">]"sv;
#elif defined(_MSC_VER)
        // TODO: Check what msc compiler returns
        constexpr auto start_bit = "detail::type_name<"sv;
        constexpr auto end_bit = ">("sv;
#else
#error unknown compiler
#endif

        constexpr std::string_view enumValuesAsString =
                GetEnumeratorNames<EnumType>(std::make_index_sequence<NUMBER_OF_VALUES>{});

        constexpr size_t start = enumValuesAsString.find(start_bit);
        constexpr size_t end = enumValuesAsString.rfind(end_bit);
        constexpr bool failed = start == std::string_view::npos || end == std::string_view::npos || end <= start;
        static_assert(!failed);

        constexpr auto trimmedValues =
                enumValuesAsString.substr(start + start_bit.size(), end - start - start_bit.size());
        constexpr std::array<std::string_view, NUMBER_OF_VALUES> valueArray =
                Split<NUMBER_OF_VALUES>(trimmedValues.data());
        constexpr std::array<EnumType, NUMBER_OF_VALUES> enumValues = GetEnumValues<EnumType>();
        for (auto i = 0; i < NUMBER_OF_VALUES; ++i)
        {
            if (value == enumValues[i])
            {
                return valueArray[i];
            }
        }

        return OutOfScopeValue;
    }
};