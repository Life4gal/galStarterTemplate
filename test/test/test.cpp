#include <gtest/gtest.h>

#include <gal_format_core.hpp>

namespace
{
	using namespace gal::format;
	TEST(FormatTest, test_is_char)
	{
		ASSERT_FALSE(is_char_v<int>);
		ASSERT_FALSE(is_char_v<double>);

		ASSERT_TRUE(is_char_v<char>);
		ASSERT_TRUE(is_char_v<wchar_t>);
		ASSERT_TRUE(is_char_v<char8_type>);
		ASSERT_TRUE(is_char_v<char16_t>);
		ASSERT_TRUE(is_char_v<char32_t>);
	}

	TEST(FormatTest, test_to_string_view)
	{
		ASSERT_TRUE((std::is_same_v<decltype(to_string_view(std::string{})), std::basic_string_view<char>>));
		ASSERT_TRUE((std::is_same_v<decltype(to_string_view(std::string_view{})), std::basic_string_view<char>>));
		ASSERT_TRUE((std::is_same_v<decltype(to_string_view(std::basic_string<int>{})), std::basic_string_view<int>>));
		ASSERT_TRUE((std::is_same_v<decltype(to_string_view(std::basic_string_view<int>{})), std::basic_string_view<int>>));

		ASSERT_FALSE((std::is_same_v<decltype(to_string_view("abc")), std::basic_string_view<char>>));
		ASSERT_FALSE((std::is_class_v<decltype(to_string_view("abc"))>));
		ASSERT_TRUE((std::is_same_v<decltype(to_string_view("abc")), void>));

		ASSERT_TRUE((std::is_same_v<char_t_impl<std::string>::result, std::basic_string_view<char>>));
		ASSERT_TRUE((std::is_same_v<char_t_impl<std::string_view>::result, std::basic_string_view<char>>));
		ASSERT_TRUE((std::is_same_v<char_t_impl<std::basic_string<int>>::result, std::basic_string_view<int>>));
		ASSERT_TRUE((std::is_same_v<char_t_impl<std::basic_string_view<int>>::result, std::basic_string_view<int>>));
		ASSERT_TRUE((std::is_same_v<char_t_impl<std::string>::type, char>));
		ASSERT_TRUE((std::is_same_v<char_t_impl<std::string_view>::type, char>));
		ASSERT_TRUE((std::is_same_v<char_t_impl<std::basic_string<int>>::type, int>));
		ASSERT_TRUE((std::is_same_v<char_t_impl<std::basic_string_view<int>>::type, int>));
	}

//	TEST(FormatTest, test_basic_format_parse_context)
//	{
//		std::string_view s{"Hello World"};
//		basic_format_parse_context b{s};
//
//		ASSERT_EQ(s.begin(), b.begin());
//		ASSERT_EQ(s.end(), b.end());
//
//		ASSERT_EQ(b.next_arg_id(), 0);
//		ASSERT_EQ(b.next_arg_id(), 1);
//
//		s.remove_prefix(6);
//		b.advance_to(std::find(b.begin(), b.end(), 'W'));
//		ASSERT_NE(b.begin(), b.end());
//		ASSERT_EQ(s.begin(), b.begin());
//	}

	TEST(FormatTest, test_get_container)
	{
		std::vector<int> vec{1, 2, 3, 4};
		using container_type = decltype(vec);
		using inserter = std::back_insert_iterator<container_type>;
		ASSERT_EQ(get_container(inserter{vec}), vec);
		ASSERT_TRUE((std::is_same_v<inserter::container_type, container_type>));
		ASSERT_TRUE((std::is_same_v<decltype(get_container(inserter{vec})), container_type&>));
	}

//	TEST(FormatTest, test_buffer)
//	{
//		constexpr auto size = 20;
//		char str[size]{};
//		buffer buffer{str, size, size};
//
//		ASSERT_EQ(str, buffer.begin());
//		ASSERT_EQ(str + size, buffer.end());
//		ASSERT_EQ(size, buffer.size());
//		ASSERT_EQ(size, buffer.capacity());
//		ASSERT_EQ(str, buffer.data());
//
//		buffer.clear();
//		ASSERT_EQ(0, buffer.size());
//		buffer.push_back('a');
//		ASSERT_EQ(1, buffer.size());
//		ASSERT_EQ('a', buffer[0]);
//
//		buffer.set(str + 10, 10);
//		ASSERT_EQ(str + 10, buffer.begin());
//		ASSERT_EQ(10, buffer.capacity());
//	}
}
