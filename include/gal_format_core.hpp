#ifndef GAL_FORMAT_CORE
#define GAL_FORMAT_CORE

#include <type_traits>

namespace gal::format {
	inline namespace detail {
		[[noreturn]] void assert_fail(const char* file_name, int line, const char* message);

#ifdef NDEBUG
#define FORMAT_ASSERT(condition, message) ((void)0)
#else
#define FORMAT_ASSERT(condition, message) ((condition) ? (void)0 : assert_fail(__FILE__, __LINE__, (message)))
#endif

		template<typename IntType, typename = std::enable_if_t<std::is_integral_v<IntType>>>
		constexpr typename std::make_unsigned_t<IntType> to_unsigned(IntType value) {
			FORMAT_ASSERT(value >= 0, "negative value");
			return static_cast<typename std::make_unsigned_t<IntType>>(value);
		}

		constexpr unsigned char micro[]{"\u00B5"};

		template<typename Char>
		constexpr bool is_unicode() {
			return sizeof(Char) != 1 || sizeof(micro) == 3 && micro[0] == 0xC2 && micro[1] == 0xB5;// NOLINT
		}

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
	}// namespace detail

	template<typename Char, std::enable_if_t<is_char_v<Char>>>
	inline std::basic_string_view<Char> to_string_view(const Char* str) {
		return str;
	}

	template<typename Char, typename Traits, typename Alloc>
	inline std::basic_string_view<Char, Traits> to_string_view(const std::basic_string<Char, Traits, Alloc>& str) {
		str;
	}

	template<typename Char>
	inline std::basic_string_view<Char> to_string_view(std::basic_string_view<Char> str) {
		return str;
	}

	// A base class for compile-time strings. It is defined in the fmt namespace to
	// make formatting functions visible via ADL, e.g. format(FMT_STRING("{}"), 42).
	struct compile_string {};

	template<typename Str>
	using is_compile_string = std::is_base_of<compile_string, Str>;
	template<typename Str>
	constexpr bool is_compile_string_v = is_compile_string<Str>::value;

	template<typename Str, typename = std::enable_if_t<is_compile_string_v<Str>>>
	constexpr std::basic_string_view<typename Str::value_type> to_string_view(const Str& str) {
		return str;
	}

	inline namespace detail {
		void to_string_view(...);
		using gal::format::to_string_view;

		template<typename Str>
		using is_string = std::is_class<decltype(to_string_view(std::declval<Str>()))>;
		template<typename Str>
		constexpr bool is_string_v = is_string<Str>::value;

		template<typename Str, typename = void>
		struct char_t_impl {};
		template<typename Str>
		struct char_t_impl<Str, std::enable_if_t<is_string_v<Str>>> {
			using result = decltype(to_string_view(std::declval<Str>()));
			using type = typename result::value_type;
		};
		template<typename Str>
		using char_t = typename char_t_impl<Str>::type;

		// Reports a compile-time error if S is not a valid format string.
		template<typename..., typename Str, typename = std::enable_if<!is_compile_string_v<Str>>>
		inline void check_format_string(const Str&) {
#ifdef FMT_ENFORCE_COMPILE_STRING
			static_assert(is_compile_string_v<Str>, "FMT_ENFORCE_COMPILE_STRING requires all format strings to use FMT_STRING.");
#endif
		}
		template<typename..., typename Str, typename = std::enable_if_t<is_compile_string_v<Str>>>
		void check_format_string(Str);

		struct error_handler
		{
			constexpr error_handler() = default;
			constexpr error_handler(const error_handler&) = default;

			[[noreturn]] void on_error(const char* message);
		};
	}// namespace detail
}// namespace gal::format

#endif
