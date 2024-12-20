#pragma once

#include <iostream>
#include "atomic"

template <typename T>
class SharedPointer {
private:
	T* ptr = nullptr;
	std::atomic<int>* counter = new std::atomic<int>(1);
public:
	bool operator==(const T*& ptr) const;
	bool operator==(const SharedPointer<T>& other) const;
	T& operator*() const;
	T* operator->() const;
	explicit operator bool() const;

	SharedPointer(const T*&& ptr);
	SharedPointer(const SharedPointer<T>& other);
	SharedPointer<T>& operator=(const SharedPointer<T>& other);
	SharedPointer<T>& operator=(const T*&& ptr);

	SharedPointer(SharedPointer<T>&& other) noexcept;
	SharedPointer<T>& operator=(SharedPointer<T>&& other) noexcept;

	~SharedPointer() noexcept;
};

template <typename T>
struct SharedPointerHash {
	size_t operator()(const SharedPointer<T>& sharedPointer) const noexcept;
	size_t operator()(SharedPointer<T>* const& sharedPointer) const noexcept;
};

#include "sharedPointer.cpp"