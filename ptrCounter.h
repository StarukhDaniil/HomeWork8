#pragma once
#include <iostream>
#include <map>

//singletone клас для того щоб перевіряти чи був вже зроблений shared pointer на основі цього вказівника
template <typename T>
class PtrCounter {
private:
	PtrCounter() = default;
	std::map<T*, int> ptrCount;
public:
	static PtrCounter<T>& getInstance();
	void increaseCount(T* ptr);
	void decreaseCount(T* ptr);
	int getCount(T* ptr);

	PtrCounter(const PtrCounter&) = delete;
	PtrCounter& operator=(const PtrCounter) = delete;
	~PtrCounter() = default;
};

#include "ptrCounter.cpp"