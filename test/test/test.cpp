#include <gtest/gtest.h>

#include <something.hpp>

namespace
{
	TEST(TestHello, say_hello)
	{
		auto what = something::greeter::say();
		ASSERT_STREQ(what.c_str(), "Hello World!");

		something::greeter::hello();
	}

	template<size_t... N>
	static constexpr auto square_nums(size_t index, std::index_sequence<N...>) {
		constexpr auto nums = std::array{N * N...};
		return nums[index];
	}

	template<size_t N>
	constexpr static auto const_nums(size_t index) {
		return square_nums(index, std::make_index_sequence<N>{});
	}

	template<typename T, T... ints>
	void print_sequence(std::integer_sequence<T, ints...> int_seq) {
		std::cout << "The sequence of size " << int_seq.size() << ": ";
		((std::cout << ints << ' '), ...);
		std::cout << '\n';
	}

	template<typename Array, std::size_t... I>
	auto a2t_impl(const Array& a, std::index_sequence<I...>) {
		return std::make_tuple(a[I]...);
	}

	template<typename T, std::size_t N, typename Indices = std::make_index_sequence<N>>
	auto a2t(const std::array<T, N>& a) {
		return a2t_impl(a, Indices{});
	}

	template<class Ch, class Tr, class Tuple, std::size_t... Is>
	void print_tuple_impl(std::basic_ostream<Ch, Tr>& os,
	                      const Tuple& t,
	                      std::index_sequence<Is...>) {
		((os << (Is == 0 ? "" : ", ") << std::get<Is>(t)), ...);
	}

	template<class Ch, class Tr, class... Args>
	auto& operator<<(std::basic_ostream<Ch, Tr>& os, const std::tuple<Args...>& t) {
		os << "(";
		print_tuple_impl(os, t, std::index_sequence_for<Args...>{});
		return os << ")";
	}

	TEST(TestHello, just_do_it)
	{
		static_assert(const_nums<101>(100) == 100 * 100);

		print_sequence(std::integer_sequence<unsigned, 9, 2, 5, 1, 9, 1, 6>{});
		print_sequence(std::make_integer_sequence<int, 20>{});
		print_sequence(std::make_index_sequence<10>{});
		print_sequence(std::index_sequence_for<float, std::iostream, char>{});

		std::array<int, 4> array = {1, 2, 3, 4};

		auto tuple = a2t(array);
		static_assert(std::is_same<decltype(tuple),
				std::tuple<int, int, int, int>>::value);

		std::cout << tuple << '\n';
	}
}
