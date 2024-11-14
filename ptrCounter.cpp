#pragma once
#include "ptrCounter.h"
#include <iostream>

template <typename T>
PtrCounter<T>& PtrCounter<T>::getInstance() {
	static PtrCounter ptrCounter;
	return ptrCounter;
}

template <typename T>
void PtrCounter<T>::increaseCount(T* ptr) {
	if (ptrCount.find(ptr) != ptrCount.end()) {
		++ptrCount[ptr];
	}
	else {
		ptrCount[ptr] = 1;
	}
}

template <typename T>
void PtrCounter<T>::decreaseCount(T* ptr) {
	if (ptrCount.find(ptr) != ptrCount.end()) {
		--ptrCount[ptr];
	}
	else {
		throw std::runtime_error("Trying to decrease ptrCount of a non-written element");
	}
}

template <typename T>
int PtrCounter<T>::getCount(T* ptr) {
	if (ptrCount.find(ptr) != ptrCount.end()) {
		return ptrCount[ptr];
	}
	else {
		throw std::runtime_error("Trying to get value of a non-written element");
	}
}
