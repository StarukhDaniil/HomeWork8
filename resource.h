#pragma once

#include <shared_mutex>

class Resource {
private:
	int data;
	mutable std::shared_mutex mutex;
public:
	const int& getData(const std::shared_lock<std::shared_mutex>& slock) const {
		if (slock.owns_lock() && slock.mutex() == &this->mutex)
			return data;
		else
			throw std::runtime_error("trying to get data without shared ownership");
	}

	const int& getData() const {
		std::shared_lock<std::shared_mutex> slock(mutex);
		return data;
	}

	void setData(const int& value, const std::unique_lock<std::shared_mutex>& ulock) {
		if (ulock.owns_lock() && ulock.mutex() == &this->mutex)
			data = value;
		else
			throw std::runtime_error("trying to change data without exclusive ownership");
	}

	std::shared_mutex& getMutex() const {
		return mutex;
	}

	std::shared_lock<std::shared_mutex> getSharedLock() const {
		return std::shared_lock<std::shared_mutex>(mutex);
	}

	std::unique_lock<std::shared_mutex> getUniqueLock() const {
		return std::unique_lock<std::shared_mutex> (mutex);
	}

	Resource() : data(0) {}
	Resource(const int& data) : data(data) {}
	Resource(const Resource& other, const std::shared_lock<std::shared_mutex>& slock) : 
		data(other.getData(slock)) {}
	Resource& operator=(const Resource& other) {
		if (this != &other) {
			std::unique_lock<std::shared_mutex> thisLock(this->mutex, std::defer_lock);
			std::shared_lock<std::shared_mutex> otherLock(other.getMutex(), std::defer_lock);
			std::lock(thisLock, otherLock);
			this->data = other.getData(otherLock);
		}
		return *this;
	}
	~Resource() = default;
};