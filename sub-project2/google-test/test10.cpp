#include <gtest/gtest.h>

// This sample shows how to use Google Test listener API to implement
// a primitive leak checker.
namespace {
	using ::testing::EmptyTestEventListener;
	using ::testing::InitGoogleTest;
	using ::testing::Test;
	using ::testing::TestEventListeners;
	using ::testing::TestInfo;
	using ::testing::TestPartResult;
	using ::testing::UnitTest;

	// We will track memory used by this class.
	class Water {
	public:
		// Normal Water declarations go here.

		// operator new and operator delete help us control water allocation.
		void* operator new(size_t allocation_size) {
			allocated_++;
			return malloc(allocation_size);
		}

		void operator delete(void* block, size_t /* allocation_size */) {
			allocated_--;
			free(block);
		}

		static int allocated() { return allocated_; }

	private:
		static int allocated_;
	};

	int Water::allocated_ = 0;

	// This event listener monitors how many Water objects are created and
	// destroyed by each test, and reports a failure if a test leaks some Water
	// objects. It does this by comparing the number of live Water objects at
	// the beginning of a test and at the end of a test.
	class [[maybe_unused]] LeakChecker : public EmptyTestEventListener {
	private:
		// Called before a test starts.
		void OnTestStart(const TestInfo& /* test_info */) override {
			initially_allocated_ = Water::allocated();
		}

		// Called after a test ends.
		void OnTestEnd(const TestInfo& /* test_info */) override {
			int difference = Water::allocated() - initially_allocated_;

			// You can generate a failure in any event handler except
			// OnTestPartResult. Just use an appropriate Google Test assertion to do
			// it.
			EXPECT_LE(difference, 0) << "Leaked " << difference << " unit(s) of Water!";
		}

		int initially_allocated_{};
	};

	TEST(ListenersTest, DoesNotLeak) {
		auto* water = new Water;
		delete water;
	}

	// This should fail when the --check_for_leaks command line flag is
	// specified.
	TEST(ListenersTest, LeaksWater) {
		auto* water = new Water;
		EXPECT_TRUE(water != nullptr);
	}
}// namespace

//int main(int argc, char** argv) {
//	InitGoogleTest(&argc, argv);
//
//	bool check_for_leaks = false;
//	if (argc > 1 && strcmp(argv[1], "--check_for_leaks") == 0)
//		check_for_leaks = true;
//	else
//		printf("%s\n",
//			   "Run this program with --check_for_leaks to enable "
//			   "custom leak checking in the tests.");
//
//	// If we are given the --check_for_leaks command line flag, installs the
//	// leak checker.
//	if (check_for_leaks) {
//		TestEventListeners& listeners = UnitTest::GetInstance()->listeners();
//
//		// Adds the leak checker to the end of the test event listener list,
//		// after the default text output printer and the default XML report
//		// generator.
//		//
//		// The order is important - it ensures that failures generated in the
//		// leak checker's OnTestEnd() method are processed by the text and XML
//		// printers *before* their OnTestEnd() methods are called, such that
//		// they are attributed to the right test. Remember that a listener
//		// receives an OnXyzStart event *after* listeners preceding it in the
//		// list received that event, and receives an OnXyzEnd event *before*
//		// listeners preceding it.
//		//
//		// We don't need to worry about deleting the new listener later, as
//		// Google Test will do it.
//		listeners.Append(new LeakChecker);
//	}
//	return RUN_ALL_TESTS();
//}
