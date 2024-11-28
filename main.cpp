#include <iostream>
#include "sharedPointer.h"
#include "ptrCounter.h"

int main() {
	SharedPointer<int> a(new int(100));
	std::cout << *a << std::endl;
	SharedPointer<int> b = a;
	*a = 200;
	std::cout << *b << std::endl;

	std::cout << std::endl;

	int* x = new int(300);
	SharedPointer<int> xp(x);
	{
		SharedPointer<int> xPtr(x);
	}
	std::cout << *x << std::endl;
	return 0;
}