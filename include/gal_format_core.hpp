#ifndef GAL_FORMAT_CORE
#define GAL_FORMAT_CORE

#include <string_view>
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

		struct error_handler {
			constexpr error_handler() = default;
			constexpr error_handler(const error_handler&) = default;

			[[noreturn]] void on_error(const char* message);
		};
	}// namespace detail

	template<typename Char, typename ErrorHandler = error_handler, typename = std::enable_if_t<is_char_v<Char>>>
	class basic_format_parse_context : private ErrorHandler {
	public:
		using value_type = Char;
		using error_handle_type = ErrorHandler;
		using iterator = typename std::basic_string_view<value_type>::iterator;

		explicit constexpr basic_format_parse_context(std::basic_string_view<value_type> format_str, ErrorHandler error = {}, int next_arg_id = 0)
			: ErrorHandler(error),
			  m_format_str(format_str),
			  m_next_arg_id(next_arg_id) {}


		// Returns an iterator to the beginning of the format string range being parsed.
		[[nodiscard]] constexpr iterator begin() const noexcept {
			return m_format_str.begin();
		}

		// Returns an iterator past the end of the format string range being parsed.
		[[nodiscard]] constexpr iterator end() const noexcept {
			return m_format_str.end();
		}

		// Advances the begin iterator to ``it``.
		constexpr void advance_to(iterator it) {
			m_format_str.remove_prefix(to_unsigned(it - begin()));
		}

		// Reports an error if using the manual argument indexing; otherwise returns
		// the next argument index and switches to the automatic indexing.
		[[nodiscard]] constexpr int next_arg_id() {
			if (m_next_arg_id >= 0) {
				return m_next_arg_id++;
			}
			this->on_error("cannot switch from manual to automatic argument indexing");
			return 0;
		}

		// Reports an error if using the automatic argument indexing; otherwise
		// switches to the manual indexing.
		[[noreturn]] constexpr void check_arg_id(int) {
			if (m_next_arg_id > 0) {
				this->on_error("cannot switch from automatic to manual argument indexing");
			} else {
				m_next_arg_id = -1;
			}
		}

		constexpr void check_arg_id(std::basic_string_view<value_type>) {}

		[[noreturn]] constexpr void on_error(const char* message) {
			ErrorHandler::on_error(message);
		}

		[[nodiscard]] constexpr ErrorHandler error_handler() const {
			return *this;
		}

	private:
		std::basic_string_view<Char>
				m_format_str;
		int m_next_arg_id;
	};

	using format_parse_context = basic_format_parse_context<char>;
	using wformat_parse_context = basic_format_parse_context<wchar_t>;

	template<typename Context>
	class basic_format_arg;
	template<typename Context>
	class basic_format_args;
	template<typename Context>
	class dynamic_format_arg_store;

	template<typename T, typename Char = char, typename = std::enable_if_t<is_char_v<Char>>>
	struct formatter {
		// A deleted default constructor indicates a disabled formatter.
		formatter() = delete;
	};

	// Specifies if T has an enabled formatter specialization. A type can be
	// format able even if it doesn't have a formatter e.g. via a conversion.
	template<typename T, typename Context>
	using has_formatter = std::is_constructible<typename Context::template formatter_type<T>>;
	template<typename T, typename Context>
	constexpr bool has_formatter_v = has_formatter<T, Context>::value;

	// Checks whether T is a container with contiguous storage.
	template<typename T>
	struct is_contiguous : std::false_type {};
	template<typename Char>
	struct is_contiguous<std::basic_string<Char>> : std::true_type {};

	inline namespace detail {
		// Extracts a reference to the container from back_insert_iterator.
		template<typename Container, typename binary_iterator = std::back_insert_iterator<Container>>
		[[nodiscard]] inline Container& get_container(std::back_insert_iterator<Container> it) {
			struct accessor : binary_iterator {
				explicit accessor(binary_iterator it) : binary_iterator(it) {}
				using binary_iterator::container;
			};
			return *accessor(it).container;
		}
	}// namespace detail

	// A contiguous memory buffer with an optional growing ability. It is an internal
	// class and shouldn't be used directly, only via `~fmt::basic_memory_buffer`.
	template<typename T>
	class buffer {
	public:
		using size_type = size_t;
		using value_type = T;
		using pointer_type = T*;
		using const_pointer_type = const T*;
		using reference_type = T&;
		using const_reference_type = const T&;

		template<typename U>
		using other_const_pointer_type = const U*;

		buffer(const buffer&) = delete;
		buffer& operator=(const buffer&) = delete;

		[[nodiscard]] pointer_type begin() noexcept {
			return m_ptr;
		}
		[[nodiscard]] pointer_type end() noexcept {
			return m_ptr + m_size;
		}
		[[nodiscard]] const_pointer_type begin() const noexcept {
			return m_ptr;
		}
		[[nodiscard]] const_pointer_type end() const noexcept {
			return m_ptr + m_size;
		}
		[[nodiscard]] size_type size() const noexcept {
			return m_size;
		}
		[[nodiscard]] size_type capacity() const noexcept {
			return m_capacity;
		}
		[[nodiscard]] pointer_type data() noexcept {
			return m_ptr;
		}
		[[nodiscard]] const_pointer_type data() const noexcept {
			return m_ptr;
		}
		void clear() noexcept {
			m_size = 0;
		}
		// Tries increasing the buffer capacity to *new_capacity*. It can increase the
		// capacity by a smaller amount than requested but guarantees there is space
		// for at least one additional element either by increasing the capacity or by
		// flushing the buffer if it is full.
		void try_reserve(size_type new_capacity) {
			if (new_capacity > m_capacity) {
				grow(new_capacity);
			}
		}
		// Tries resizing the buffer to contain *count* elements. If T is a POD type
		// the new elements may not be initialized.
		void try_resize(size_type new_size) {
			try_reserve(new_size);
			m_size = new_size <= m_capacity ? new_size : m_capacity;
		}
		void push_back(const_reference_type value) {
			try_reserve(m_size + 1);
			m_ptr[m_size++] = value;
		}
		template<typename U>
		void append(other_const_pointer_type<U> begin, other_const_pointer_type<U> end);

		reference_type operator[](size_type index) {
			return m_ptr[index];
		}
		const_reference_type operator[](size_type index) const {
			return m_ptr[index];
		}

	protected:
		explicit buffer(size_type size) noexcept : m_ptr(nullptr),
												   m_size(size),
												   m_capacity(size) {}

		explicit buffer(pointer_type p = nullptr, size_type size = 0, size_type capacity = 0) noexcept
			: m_ptr(p),
			  m_size(size),
			  m_capacity(capacity) {}

		~buffer() = default;

		void set(pointer_type data, size_type capacity) noexcept {
			m_ptr = data;
			m_capacity = capacity;
		}

		virtual void grow(size_type new_capacity) = 0;

	private:
		T* m_ptr;
		size_type m_size;
		size_type m_capacity;
	};

	struct buffer_trait {
		using size_type = size_t;
		explicit buffer_trait(size_type) {}
		[[nodiscard]] size_type count() const { return 0; }			  //NOLINT
		[[nodiscard]] size_type limit(size_type size) { return size; }//NOLINT
	};

	class fixed_buffer_trait {
	public:
		using size_type = size_t;
		explicit fixed_buffer_trait(size_type limit) : m_count(),
													   m_limit(limit) {}
		[[nodiscard]] size_type count() const { return m_count; }
		[[nodiscard]] size_type limit(size_type size) {
			auto n = m_limit - m_count;
			m_count += size;
			return size < n ? size : n;
		}

	private:
		size_type m_count;
		size_type m_limit;
	};



}// namespace gal::format

#endif
