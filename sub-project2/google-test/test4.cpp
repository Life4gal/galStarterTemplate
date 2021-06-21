#include <gtest/gtest.h>

namespace {
	// A simple monotonic counter.
	class Counter {
	private:
		int counter_;

	public:
		// Creates a counter that starts at 0.
		Counter() : counter_(0) {}

		// Returns the current counter value, and increments it.
		int Increment() {
			return counter_++;
		}

		// Returns the current counter value, and decrements it.
		// counter can not be less than 0, return 0 in this case
		int Decrement() {
			if (counter_ == 0) {
				return counter_;
			} else {
				return counter_--;
			}
		}

		// Prints the current counter value to STDOUT.
		void Print() const {
			printf("%d", counter_);
		}
	};

	// Tests the Increment() method.

	TEST(Counter, Increment) {
		Counter c;

		// Test that counter 0 returns 0
		EXPECT_EQ(0, c.Decrement());

		// EXPECT_EQ() evaluates its arguments exactly once, so they
		// can have side effects.

		EXPECT_EQ(0, c.Increment());
		EXPECT_EQ(1, c.Increment());
		EXPECT_EQ(2, c.Increment());

		EXPECT_EQ(3, c.Decrement());
	}
}// namespace
