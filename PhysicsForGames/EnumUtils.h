#pragma once
#include <type_traits>

template<typename Enum>
inline Enum operator | (Enum lhs, Enum rhs)
{
	static_assert(std::is_enum<Enum>::value, "Template parameter is not an enum type");

	using Underlying = typename std::underlying_type<Enum>::type;

	return static_cast<Enum> (static_cast<Underlying>(lhs) | static_cast<Underlying>(rhs));
}