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
	static PtrCounter& getInstance() {
		static PtrCounter ptrCounter;
		return ptrCounter;
	}

	void increaseCount(T* ptr) {
		if (ptrCount.find(ptr) != ptrCount.end()) {
			++ptrCount[ptr];
		}
		else {
			ptrCount[ptr] = 1;
		}
	}

	void decreaseCount(T* ptr) {
		if (ptrCount.find(ptr) != ptrCount.end()) {
			--ptrCount[ptr];
		}
		else {
			throw std::runtime_error("Trying to decrease ptrCount of a non-written element");
		}
	}

	int getCount(T* ptr) {
		if (ptrCount.find(ptr) != ptrCount.end()) {
			return ptrCount[ptr];
		}
		else {
			throw std::runtime_error("Trying to get value of a non-written element");
		}
	}

	PtrCounter(const PtrCounter&) = delete;
	PtrCounter& operator=(const PtrCounter) = delete;
	~PtrCounter() = default;
};