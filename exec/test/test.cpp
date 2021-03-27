#include <gtest/gtest.h>

namespace {
	/*
	todo: why just msvc error?
    #D:\a\galStarterTemplate\galStarterTemplate\test\test\test.cpp(12): message : see reference to function template instantiation 'auto `anonymous-namespace'::square_nums<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100>(size_t,std::integer_sequence<size_t,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100>)' being compiled [D:\a\galStarterTemplate\galStarterTemplate\build\StarterTemplateTest.vcxproj]
    #D:\a\galStarterTemplate\galStarterTemplate\test\test\test.cpp(47): message : see reference to function template instantiation 'auto `anonymous-namespace'::const_nums<101>(size_t)' being compiled [D:\a\galStarterTemplate\galStarterTemplate\build\StarterTemplateTest.vcxproj]
    #D:\a\galStarterTemplate\galStarterTemplate\test\test\test.cpp(5,2): error C2780: 'std::array<_Ty,_Size> std::array(void)': expects 0 arguments - 101 provided [D:\a\galStarterTemplate\galStarterTemplate\build\StarterTemplateTest.vcxproj]
    #C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Tools\MSVC\14.28.29910\include\tuple(886): message : see declaration of 'std::array' [D:\a\galStarterTemplate\galStarterTemplate\build\StarterTemplateTest.vcxproj]
    #D:\a\galStarterTemplate\galStarterTemplate\test\test\test.cpp(5,2): error C2780: 'std::array<_Ty,_Size> std::array(std::array<_Ty,_Size>)': expects 1 arguments - 101 provided [D:\a\galStarterTemplate\galStarterTemplate\build\StarterTemplateTest.vcxproj]
    #C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Tools\MSVC\14.28.29910\include\tuple(886): message : see declaration of 'std::array' [D:\a\galStarterTemplate\galStarterTemplate\build\StarterTemplateTest.vcxproj]
    #D:\a\galStarterTemplate\galStarterTemplate\test\test\test.cpp(6,18): error C2737: 'nums': 'constexpr' object must be initialized [D:\a\galStarterTemplate\galStarterTemplate\build\StarterTemplateTest.vcxproj]
    #D:\a\galStarterTemplate\galStarterTemplate\test\test\test.cpp(5,2): error C3536: 'nums': cannot be used before it is initialized [D:\a\galStarterTemplate\galStarterTemplate\build\StarterTemplateTest.vcxproj]
    #D:\a\galStarterTemplate\galStarterTemplate\test\test\test.cpp(5,2): error C2109: subscript requires array or pointer type [D:\a\galStarterTemplate\galStarterTemplate\build\StarterTemplateTest.vcxproj]
    #D:\a\galStarterTemplate\galStarterTemplate\test\test\test.cpp(47,38): error C2120: 'void' illegal with all types [D:\a\galStarterTemplate\galStarterTemplate\build\StarterTemplateTest.vcxproj]
    #D:\a\galStarterTemplate\galStarterTemplate\test\test\test.cpp(54,22): error C2079: 'array' uses undefined class 'std::array<int,4>' [D:\a\galStarterTemplate\galStarterTemplate\build\StarterTemplateTest.vcxproj]
    #D:\a\galStarterTemplate\galStarterTemplate\test\test\test.cpp(54,41): error C2440: 'initializing': cannot convert from 'initializer list' to 'int' [D:\a\galStarterTemplate\galStarterTemplate\build\StarterTemplateTest.vcxproj]
    #D:\a\galStarterTemplate\galStarterTemplate\test\test\test.cpp(54,30): message : The initializer contains too many elements [D:\a\galStarterTemplate\galStarterTemplate\build\StarterTemplateTest.vcxproj]
    #D:\a\galStarterTemplate\galStarterTemplate\test\test\test.cpp(56,16): error C2672: '`anonymous-namespace'::a2t': no matching overloaded function found [D:\a\galStarterTemplate\galStarterTemplate\build\StarterTemplateTest.vcxproj]
    #D:\a\galStarterTemplate\galStarterTemplate\test\test\test.cpp(56,25): error C2784: 'auto `anonymous-namespace'::a2t(const std::array<_Ty,_Size> &)': could not deduce template argument for 'const std::array<_Ty,_Size> &' from 'int' [D:\a\galStarterTemplate\galStarterTemplate\build\StarterTemplateTest.vcxproj]
    #D:\a\galStarterTemplate\galStarterTemplate\test\test\test.cpp(28): message : see declaration of '`anonymous-namespace'::a2t' [D:\a\galStarterTemplate\galStarterTemplate\build\StarterTemplateTest.vcxproj]
    #D:\a\galStarterTemplate\galStarterTemplate\test\test\test.cpp(57,44): error C3536: 'tuple': cannot be used before it is initialized [D:\a\galStarterTemplate\galStarterTemplate\build\StarterTemplateTest.vcxproj]
    #D:\a\galStarterTemplate\galStarterTemplate\test\test\test.cpp(57,45): error C3539: a template-argument cannot be a type that contains 'auto' [D:\a\galStarterTemplate\galStarterTemplate\build\StarterTemplateTest.vcxproj]
    #D:\a\galStarterTemplate\galStarterTemplate\test\test\test.cpp(58,45): error C2607: static assertion failed [D:\a\galStarterTemplate\galStarterTemplate\build\StarterTemplateTest.vcxproj]
	 */
	//	template<size_t... N>
	//	static constexpr auto square_nums(size_t index, std::index_sequence<N...>) {
	//		constexpr auto nums = std::array{N * N...};
	//		return nums[index];
	//	}
	//
	//	template<size_t N>
	//	constexpr static auto const_nums(size_t index) {
	//		return square_nums(index, std::make_index_sequence<N>{});
	//	}
	//
	//	template<typename T, T... ints>
	//	void print_sequence(std::integer_sequence<T, ints...> int_seq) {
	//		std::cout << "The sequence of size " << int_seq.size() << ": ";
	//		((std::cout << ints << ' '), ...);
	//		std::cout << '\n';
	//	}
	//
	//	template<typename Array, std::size_t... I>
	//	auto a2t_impl(const Array& a, std::index_sequence<I...>) {
	//		return std::make_tuple(a[I]...);
	//	}
	//
	//	template<typename T, std::size_t N, typename Indices = std::make_index_sequence<N>>
	//	auto a2t(const std::array<T, N>& a) {
	//		return a2t_impl(a, Indices{});
	//	}
	//
	//	template<class Ch, class Tr, class Tuple, std::size_t... Is>
	//	void print_tuple_impl(std::basic_ostream<Ch, Tr>& os,
	//						  const Tuple& t,
	//						  std::index_sequence<Is...>) {
	//		((os << (Is == 0 ? "" : ", ") << std::get<Is>(t)), ...);
	//	}
	//
	//	template<class Ch, class Tr, class... Args>
	//	auto& operator<<(std::basic_ostream<Ch, Tr>& os, const std::tuple<Args...>& t) {
	//		os << "(";
	//		print_tuple_impl(os, t, std::index_sequence_for<Args...>{});
	//		return os << ")";
	//	}
	//
	//	TEST(TestHello, just_do_it) {
	//		static_assert(const_nums<101>(100) == 100 * 100);
	//
	//		print_sequence(std::integer_sequence<unsigned, 9, 2, 5, 1, 9, 1, 6>{});
	//		print_sequence(std::make_integer_sequence<int, 20>{});
	//		print_sequence(std::make_index_sequence<10>{});
	//		print_sequence(std::index_sequence_for<float, std::iostream, char>{});
	//
	//		std::array<int, 4> array = {1, 2, 3, 4};
	//
	//		auto tuple = a2t(array);
	//		static_assert(std::is_same<decltype(tuple),
	//								   std::tuple<int, int, int, int>>::value);
	//
	//		std::cout << tuple << '\n';
	//	}
}// namespace
