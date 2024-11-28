#pragma once
#include "sharedPointer.h"
#include <iostream>

template <typename T>
bool SharedPointer<T>::operator==(const T*& ptr) const {
	return this->ptr == ptr;
}

template <typename T>
bool SharedPointer<T>::operator==(const SharedPointer<T>& other) const {
	return this->ptr == other.ptr;
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
	return ptr != nullptr;
}

template <typename T>
SharedPointer<T>::SharedPointer(const T*&& ptr) {
	this->ptr = const_cast<T*>(ptr);
}

template <typename T>
SharedPointer<T>::SharedPointer(const SharedPointer<T>& other) {
	this->ptr = other.ptr;
	this->counter = other.counter;
	if (other.counter) {
		++(*counter);
	}
}

template <typename T>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<T>& other) {
	this->ptr = other.ptr;
	this->counter = other.counter;
	++(*counter);
}

template <typename T>
SharedPointer<T>& SharedPointer<T>::operator=(const T*&& ptr) {
	if (!this->ptr && !this->counter) {
		this->ptr = const_cast<T*>(ptr);
		this->counter = new int(1);
	}
	else if (*counter == 1) {
		this->ptr = ptr;
	}
	else {
		--(*counter);
		this->ptr = ptr;
	}
}

template <typename T>
SharedPointer<T>::SharedPointer(SharedPointer<T>&& other) noexcept {
	if (this == &other) {
		return;
	}

	if (*(this->counter) == 1) {
		delete ptr;
		delete counter;
		this->counter = other.counter;
	}
	else {
		--(*counter);
	}

	this->ptr = other.ptr;
	this->counter = other.counter;
	other.ptr = nullptr;
	other.counter = nullptr;
}

template <typename T>
SharedPointer<T>& SharedPointer<T>::operator=(SharedPointer<T>&& other) noexcept {
	if (this == other) {
		return this;
	}

	if (*(this->counter) == 1) {
		delete ptr;
		delete counter;
		this->counter = other.counter;
	}
	else {
		--(*counter);
	}

	this->ptr = other.ptr;
	this->counter = other.counter;
	other.ptr = nullptr;
	other.counter = nullptr;
}

template <typename T>
SharedPointer<T>::~SharedPointer() noexcept {
	if (!this->ptr && !this->counter) {
		return;
	}

	std::cout << ptr << ": " << *counter << std::endl;
	--(*counter);
	if ((*counter == 0) && (this->ptr != nullptr)) {
		delete ptr;
		delete counter;
	}
	else if (*(counter) == 0) {
		delete counter;
	}
}

template <typename T>
size_t SharedPointerHash<T>::operator()(const SharedPointer<T>& sharedPointer) const noexcept{
	if (!sharedPointer) {
		return 0;
	}
	else {
		return std::hash<T>()(*sharedPointer);
	}
}

template <typename T>
size_t SharedPointerHash<T>::operator()(SharedPointer<T>* const& sharedPointer) const noexcept {
	return operator()(*sharedPointer);
}