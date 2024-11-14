#pragma once
#include <iostream>
#include "ptrCounter.h"

template <typename T>
class SharedPointer {
private:
	T* ptr = nullptr;
public:
	SharedPointer(T* ptr);
	SharedPointer(const SharedPointer<T>& other);
	SharedPointer<T>& operator=(const SharedPointer<T>& other);
	T& operator*() const;
	T* operator->() const;
	operator bool() const;
	~SharedPointer() noexcept;
};

#include "sharedPointer.cpp"