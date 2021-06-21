#include <gtest/gtest.h>

#include <cstring>

namespace {
	// A simple string class.
	class MyString {
	private:
		const char* c_string_;

	public:
		const MyString& operator=(const MyString& rhs) = delete;

		// Clones a 0-terminated C string, allocating memory using new.
		static const char* CloneCString(const char* a_c_string) {
			if (a_c_string == nullptr) return nullptr;

			const size_t len = strlen(a_c_string);
			char* const clone = new char[len + 1];
			memcpy(clone, a_c_string, len + 1);

			return clone;
		}

		////////////////////////////////////////////////////////////
		//
		// C'tors

		// The default c'tor constructs a NULL string.
		MyString() : c_string_(nullptr) {}

		// Constructs a MyString by cloning a 0-terminated C string.
		explicit MyString(const char* a_c_string) : c_string_(nullptr) {
			Set(a_c_string);
		}

		// Copy c'tor
		MyString(const MyString& string) : c_string_(nullptr) {
			Set(string.c_string_);
		}

		////////////////////////////////////////////////////////////
		//
		// D'tor.  MyString is intended to be a final class, so the d'tor
		// doesn't need to be virtual.
		~MyString() { delete[] c_string_; }

		// Gets the 0-terminated C string this MyString object represents.
		[[nodiscard]] const char* c_string() const { return c_string_; }

		[[nodiscard]] size_t Length() const { return c_string_ == nullptr ? 0 : strlen(c_string_); }

		// Sets the 0-terminated C string this MyString object represents.
		void Set(const char* c_string) {
			// Makes sure this works when c_string == c_string_
			const char* const temp = MyString::CloneCString(c_string);
			delete[] c_string_;
			c_string_ = temp;
		}
	};

	TEST(MyString, DefaultConstructor) {
		const MyString s;

		// Asserts that s.c_string() returns NULL.
		//
		// <TechnicalDetails>
		//
		// If we write NULL instead of
		//
		//   static_cast<const char *>(NULL)
		//
		// in this assertion, it will generate a warning on gcc 3.4.  The
		// reason is that EXPECT_EQ needs to know the types of its
		// arguments in order to print them when it fails.  Since NULL is
		// #defined as 0, the compiler will use the formatter function for
		// int to print it.  However, gcc thinks that NULL should be used as
		// a pointer, not an int, and therefore complains.
		//
		// The root of the problem is C++'s lack of distinction between the
		// integer number 0 and the null pointer constant.  Unfortunately,
		// we have to live with this fact.
		//
		// </TechnicalDetails>
		EXPECT_STREQ(nullptr, s.c_string());

		EXPECT_EQ(0u, s.Length());
	}

	const char kHelloString[] = "Hello, world!";

	// Tests the c'tor that accepts a C string.
	TEST(MyString, ConstructorFromCString) {
		const MyString s(kHelloString);
		EXPECT_EQ(0, strcmp(s.c_string(), kHelloString));
		EXPECT_EQ(sizeof(kHelloString) / sizeof(kHelloString[0]) - 1,
				  s.Length());
	}

	// Tests the copy c'tor.
	TEST(MyString, CopyConstructor) {
		const MyString s1(kHelloString);
		const MyString s2 = s1;
		EXPECT_EQ(0, strcmp(s2.c_string(), kHelloString));
	}

	// Tests the Set method.
	TEST(MyString, Set) {
		MyString s;

		s.Set(kHelloString);
		EXPECT_EQ(0, strcmp(s.c_string(), kHelloString));

		// Set should work when the input pointer is the same as the one
		// already in the MyString object.
		s.Set(s.c_string());
		EXPECT_EQ(0, strcmp(s.c_string(), kHelloString));

		// Can we set the MyString to NULL?
		s.Set(nullptr);
		EXPECT_STREQ(nullptr, s.c_string());
	}
}// namespace
