#pragma once
#include "sharedPointer.h"
#include <iostream>
template <typename T>
SharedPointer<T>::SharedPointer(T* ptr) {
	PtrCounter<T>::getInstance().increaseCount(ptr);
	this->ptr = ptr;
}

template <typename T>
SharedPointer<T>::SharedPointer(const SharedPointer<T>& other) {
	this->ptr = other.ptr;
	PtrCounter<T>::getInstance().increaseCount(other.ptr);
}

template <typename T>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<T>& other) {
	this->ptr = other.ptr;
	PtrCounter<T>::getInstance().increaseCount(other.ptr);
}

template <typename T>
T& SharedPointer<T>::operator*() const {
	return *ptr;
}

template <typename T>
T* SharedPointer<T>::operator->() const {
	return ptr;
}

template <typename T>
SharedPointer<T>::operator bool() const {
	return (ptr != nullptr) || (ptr != NULL);
}

template <typename T>
SharedPointer<T>::~SharedPointer<T>() noexcept {
	PtrCounter<T>::getInstance().decreaseCount(ptr);
	std::cout << ptr << ": " << PtrCounter<T>::getInstance().getCount(ptr) << std::endl;
	if (PtrCounter<T>::getInstance().getCount(ptr) == 0) {
		delete ptr;
	}
}