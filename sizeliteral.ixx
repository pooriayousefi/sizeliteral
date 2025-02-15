export module sizeliteral;

import <ranges>;

// system size literal type
export template<char FirstDigit, char... RestDigits> struct size_literal
{
	static_assert(
		FirstDigit == '0' ||
		FirstDigit == '1' ||
		FirstDigit == '2' ||
		FirstDigit == '3' ||
		FirstDigit == '4' ||
		FirstDigit == '5' ||
		FirstDigit == '6' ||
		FirstDigit == '7' ||
		FirstDigit == '8' ||
		FirstDigit == '9',
		"Non-numeral character detected.");
	static constexpr inline auto value = static_cast<std::size_t>(FirstDigit - '0') *
		[]() 
		{
			auto power = static_cast<std::size_t>(1);
			for (auto i : std::ranges::views::iota(0ULL, sizeof...(RestDigits)))
				power *= static_cast<std::size_t>(10);
			return power;
		}() +
		size_literal<RestDigits...>::value;
};

// system size type specialization for last character
export template<char LastDigit> struct size_literal<LastDigit>
{
	static_assert(
		LastDigit == '0' ||
		LastDigit == '1' ||
		LastDigit == '2' ||
		LastDigit == '3' ||
		LastDigit == '4' ||
		LastDigit == '5' ||
		LastDigit == '6' ||
		LastDigit == '7' ||
		LastDigit == '8' ||
		LastDigit == '9',
		"Non-numeral character detected.");
	static constexpr inline auto value = static_cast<std::size_t>(LastDigit - '0');
};

// overloaded size literal operator
export template<char... Digits> constexpr std::size_t operator""_z() { return size_literal<Digits...>::value; }