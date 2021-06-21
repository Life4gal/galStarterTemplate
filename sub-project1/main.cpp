#include <boost/thread.hpp>

#include "include/project_1.hpp"

int main() {
	boost::thread_group group;
	for (auto i = 0; i < 10; ++i) {
		group.create_thread(
				[i]() {
					project1::say(i);
				});
	}

	group.join_all();
}
