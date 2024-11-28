#include <iostream>
#include "sharedPointer.h"
#include <unordered_set>
#include <algorithm>

int main() {
	SharedPointer<int> a(new int(100));
	std::cout << *a << std::endl;
	SharedPointer<int> b = a;
	*a = 200;
	std::cout << *b << std::endl;

	std::cout << std::endl;

	SharedPointer<int> c = std::move(b);

	if (a == c) {
		std::cout << "Everything works!" << std::endl << std::endl;
	}

	SharedPointer<int> d(new int(1000));

	std::unordered_set<SharedPointer<int>*, SharedPointerHash<int>> uset;
	uset.insert(&a);
	uset.insert(&c);
	uset.insert(&d);

	std::for_each(uset.begin(), uset.end(), [](SharedPointer<int>* const& sharedPointer) {
		if (!*sharedPointer) {
			std::cout << "nullptr" << std::endl;
		}
		else {
			std::cout << **sharedPointer << " ";
		}
		});
	std::cout << std::endl << std::endl;
	return 0;
}