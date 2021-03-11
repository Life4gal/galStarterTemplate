#ifndef GAL_FORMAT_CORE
#define GAL_FORMAT_CORE

#include <exception>
#include <string>
#include <string_view>

namespace gal::format {

	inline namespace support {

#ifdef __cpp_char8_t
		using char8_type = char8_t;
#else
		enum char8_type : unsigned char {};
#endif
		template<typename T>
		struct is_char : std::false_type {};
		template<>
		struct is_char<char> : std::true_type {};
		template<>
		struct is_char<wchar_t> : std::true_type {};
		template<>
		struct is_char<char8_type> : std::true_type {};
		template<>
		struct is_char<char16_t> : std::true_type {};
		template<>
		struct is_char<char32_t> : std::true_type {};

		template<typename T>
		constexpr bool is_char_v = is_char<T>::value;

		template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
		constexpr std::make_unsigned_t<T> to_unsigned(T value) {
			if (value < 0) {
				throw std::runtime_error("negative value");
			}

			return static_cast<std::make_unsigned_t<T>>(value);
		}

		// given a temp string may cause a ub?
		template<typename Char, typename Trait = std::char_traits<Char>, typename Alloc = std::allocator<Char>, typename = std::enable_if_t<is_char_v<Char>>>
		constexpr std::basic_string_view<Char, Trait> to_string_view(const std::basic_string<Char, Trait, Alloc>& str) {
			return {str};
		}

		// copy a string_view
		template<typename Char, typename Trait = std::char_traits<Char>, typename = std::enable_if_t<is_char_v<Char>>>
		constexpr std::basic_string_view<Char, Trait> to_string_view(std::basic_string_view<Char, Trait> str) {
			return {str};
		}

		// use C-Style string init a string_view may cause a ub?
		template<typename Char>
		constexpr std::basic_string_view<Char> to_string_view(const Char* str) {
			return {str};
		}
	}// namespace support

	namespace detail {
		// is given type is not std::basic_string or std::basic_string_view, return type void (which is not a class type)
		void to_string_view(...);

		// why not work?
//		template<typename StrType>
//		struct is_string : std::is_class<decltype(to_string_view(std::declval<StrType>()))> {};
		template<typename T>
		struct is_string : std::is_class<void> {};
		template<typename Char>
		struct is_string<std::basic_string<Char>> : std::is_class<std::basic_string<Char>> {};
		template<typename Char>
		struct is_string<const std::basic_string<Char>> : std::is_class<std::basic_string<Char>> {};
		template<typename Char>
		struct is_string<std::basic_string_view<Char>> : std::is_class<std::basic_string_view<Char>> {};
		template<typename Char>
		struct is_string<const std::basic_string_view<Char>> : std::is_class<std::basic_string_view<Char>> {};
		template<typename Char, size_t N>
		struct is_string<const Char(&)[N]> : std::is_class<std::basic_string_view<Char>> {};
		template<typename Char>
		struct is_string<const Char*> : std::is_class<std::basic_string_view<Char>> {};

		template<typename StrType>
		constexpr bool is_string_v = is_string<StrType>::value;


		// why not work?
//		template<typename, typename>
//		struct char_t_impl {};

		// a valid StrType got a valid char_t_impl
//		template<typename StrType>
//		struct char_t_impl<StrType, std::enable_if_t<is_string_v<StrType>>> {
//			using view_type = decltype(to_string_view(std::declval<StrType>()));
//			// std::basic_string_view<char> got char, std::basic_string_view<wchar_t> got wchar_t
//			using view_value_type = typename view_type::value_type;
//		};

		// invalid char_t_impl
		template<typename T>
		struct char_t_impl {};
		template<typename Char>
		struct char_t_impl<std::basic_string<Char>>{
			using view_type = std::basic_string_view<Char>;
			using view_value_type = typename view_type::value_type;
		};
		template<typename Char>
		struct char_t_impl<const std::basic_string<Char>>{
			using view_type = std::basic_string_view<Char>;
			using view_value_type = typename view_type::value_type;
		};
		template<typename Char>
		struct char_t_impl<std::basic_string_view<Char>>{
			using view_type = std::basic_string_view<Char>;
			using view_value_type = typename view_type::value_type;
		};
		template<typename Char>
		struct char_t_impl<const std::basic_string_view<Char>>{
			using view_type = std::basic_string_view<Char>;
			using view_value_type = typename view_type::value_type;
		};
		template<typename Char, size_t N>
		struct char_t_impl<const Char(&)[N]>{
			using view_type = std::basic_string_view<Char>;
			using view_value_type = typename view_type::value_type;
		};
		template<typename Char>
		struct char_t_impl<const Char*>{
			using view_type = std::basic_string_view<Char>;
			using view_value_type = typename view_type::value_type;
		};


	}// namespace detail

}// namespace gal::format

#endif
