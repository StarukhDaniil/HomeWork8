#pragma once
#include <iostream>
#include <map>

//singletone ���� ��� ���� ��� ��������� �� ��� ��� ��������� shared pointer �� ����� ����� ���������
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