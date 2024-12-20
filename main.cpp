#include <iostream>
#include "sharedPointer.h"
#include "resource.h"
#include <unordered_set>
#include <algorithm>
#include <thread>
#include <chrono>

void threadFunction(const SharedPointer<Resource>& p) {
	std::unique_lock<std::shared_mutex> ulock(p->getUniqueLock());
	p->setData(200, ulock);
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
	SharedPointer<Resource> p1(new Resource(100));
	std::thread t1(threadFunction, p1);
	std::cout << p1->getData() << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	for (int i = 0; i < 10; i++) {
		std::cout << p1->getData() << std::endl;
	}
	t1.join();

	return 0;
}