#pragma once
#include <iostream>
#include "ptrCounter.h"

template <typename T>
class sharedPointer {
private:
	int* counter = new int(0);
	T* ptr = nullptr;
public:
	sharedPointer(T* ptr) {
		++(*counter);
		this->ptr = ptr;
		
	}
	
	sharedPointer(const sharedPointer<T>& other) {
		this->counter = other.counter;
		this->ptr = other.ptr;
		++(*counter);
	}

	sharedPointer<T>& operator=(const sharedPointer<T>& other) {
		this->counter = other.counter;
		this->ptr = other.ptr;
		++(*counter);
	}

	T& operator*() const {
		return *ptr;
	}

	T* operator->() const {
		return ptr;
	}

	operator bool() const {
		return (ptr != nullptr) || (ptr != NULL);
	}

	~sharedPointer() noexcept {
		--(*counter);
		if (*counter == 0) {
			delete counter;
			delete ptr;
		}
	}
};