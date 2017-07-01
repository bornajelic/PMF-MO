/*
 * smartptr.h
 *
 *  Created on: Jun 5, 2015
 *      Author: tomislav
 */

#ifndef SMARTPTR_H_
#define SMARTPTR_H_

#include <utility>
#include <stdexcept>
#include<iostream>

template<typename T>
class SmartPtr {
public:
	SmartPtr();
	SmartPtr(T*);
	SmartPtr(SmartPtr const &);
	SmartPtr& operator=(SmartPtr const &);
	SmartPtr(SmartPtr &&);
	SmartPtr& operator=(SmartPtr &&);

	template<typename T1>
	SmartPtr(SmartPtr<T1> const &);
	template<typename T1>
	SmartPtr& operator=(SmartPtr<T1> const &);
	template<typename T1>
	SmartPtr(SmartPtr<T1> &&);
	template<typename T1>
	SmartPtr& operator=(SmartPtr<T1> &&);

	const T& operator*() const {
		return *data;
	}
	T& operator*() {
		return *data;
	}

	const T* operator->() const {
		return data;
	}
	T* operator->() {
		return data;
	}

	int use_count() const {
		return *counter;
	}

	const T* get() const {
		return data;
	}

	T* get() {
		return data;
	}

	~SmartPtr();

	template<typename T1>
	friend class SmartPtr;
private:
	T * data;
	int * counter;
};

template<typename T>
SmartPtr<T>::SmartPtr() :
		data(nullptr), counter(nullptr) {
}

template<typename T>
SmartPtr<T>::SmartPtr(T* _data) :
		data(_data) {
	if (data == nullptr) {
		throw std::invalid_argument("Data is null pointer!");
	}
	counter = new int(1);
}

template<typename T>
SmartPtr<T>::SmartPtr(SmartPtr const & other) :
		data(other.data), counter(other.counter) {

	if (counter != nullptr) {
		++*counter;
	}
}

template<typename T>
SmartPtr<T>& SmartPtr<T>::operator=(SmartPtr const & other) {
	if (this != &other) {
		if (other.counter != nullptr) {
			++*other.counter;
		}

		if (counter != nullptr && --*counter == 0) {
			delete data;
			delete counter;
		}

		data = other.data;
		counter = other.counter;
	}
	return *this;
}

template<typename T>
SmartPtr<T>::SmartPtr(SmartPtr && other) :
		data(std::move(other.data)), counter(std::move(other.counter)) {

	other.data = nullptr;
	other.counter = nullptr;
}

template<typename T>
SmartPtr<T>& SmartPtr<T>::operator=(SmartPtr && other) {

	if (this != &other) {
		if (counter == other.counter) {
			return *this;
		}
		if (counter != nullptr && --*counter == 0) {
			delete data;
			delete counter;
		}
		data = std::move(other.data);
		counter = std::move(other.counter);
		other.data = nullptr;
		other.counter = nullptr;
	}

	return *this;
}

template<typename T>
SmartPtr<T>::~SmartPtr() {
	if (counter != nullptr && --*counter == 0) {
		delete data;
		delete counter;
	}
}

template<typename T> template<typename T1>
SmartPtr<T>::SmartPtr(SmartPtr<T1> const & other) :
		data(other.data), counter(other.counter) {
	if (counter != nullptr) {
		++*counter;
	}
}

template<typename T> template<typename T1>
SmartPtr<T>& SmartPtr<T>::operator=(SmartPtr<T1> const & other) {
	if (other.counter != nullptr) {
		++*other.counter;
	}

	if (counter != nullptr && --*counter == 0) {
		delete data;
		delete counter;
	}

	data = other.data;
	counter = other.counter;
	return *this;
}

template<typename T> template<typename T1>
SmartPtr<T>::SmartPtr(SmartPtr<T1> && other) :
		data(std::move(other.data)), counter(std::move(other.counter)) {
	other.data = nullptr;
	other.counter = nullptr;
}

template<typename T> template<typename T1>
SmartPtr<T>& SmartPtr<T>::operator=(SmartPtr<T1> && other) {
	if (counter == other.counter) {
		return *this;
	}
	if (counter != nullptr && --*counter == 0) {
		delete data;
		delete counter;
	}
	data = std::move(other.data);
	counter = std::move(other.counter);
	other.data = nullptr;
	other.counter = nullptr;
	return *this;
}

template<typename T>
class SmartPtr<T[]> {
public:
	SmartPtr();
	SmartPtr(T*);
	SmartPtr(SmartPtr const &);
	SmartPtr& operator=(SmartPtr const &);
	SmartPtr(SmartPtr &&);
	SmartPtr& operator=(SmartPtr &&);

	template<typename T1>
	SmartPtr(SmartPtr<T1[]> const &);
	template<typename T1>
	SmartPtr& operator=(SmartPtr<T1[]> const &);
	template<typename T1>
	SmartPtr(SmartPtr<T1[]> &&);
	template<typename T1>
	SmartPtr& operator=(SmartPtr<T1[]> &&);

	const T& operator*() const {
		return *data;
	}
	T& operator*() {
		return *data;
	}

	const T* operator->() const {
		return data;
	}
	T* operator->() {
		return data;
	}

	const T & operator[](int n) const {
		return data[n];
	}

	T & operator[](int n) {
		return data[n];
	}

	int use_count() const {
		return *counter;
	}

	const T* get() const {
		return data;
	}

	T* get() {
		return data;
	}

	~SmartPtr();

	template<typename T1>
	friend class SmartPtr;
private:
	T * data;
	int * counter;
};

template<typename T>
SmartPtr<T[]>::SmartPtr() :
		data(nullptr), counter(nullptr) {
}

template<typename T>
SmartPtr<T[]>::SmartPtr(T* _data) :
		data(_data) {
	if (_data == nullptr) {
		throw std::invalid_argument("Data is null pointer!");
	}
	counter = new int(1);
}

template<typename T>
SmartPtr<T[]>::SmartPtr(SmartPtr const & other) :
		data(other.data), counter(other.counter) {

	if (counter != nullptr) {
		++*counter;
	}
}

template<typename T>
SmartPtr<T[]>& SmartPtr<T[]>::operator=(SmartPtr const & other) {
	if (this != &other) {
		if (other.counter != nullptr) {
			++*other.counter;
		}

		if (counter != nullptr && --*counter == 0) {
			delete data;
			delete counter;
		}

		data = other.data;
		counter = other.counter;
	}
	return *this;
}

template<typename T>
SmartPtr<T[]>::SmartPtr(SmartPtr && other) :
		data(std::move(other.data)), counter(std::move(other.counter)) {

	other.data = nullptr;
	other.counter = nullptr;
}

template<typename T>
SmartPtr<T[]>& SmartPtr<T[]>::operator=(SmartPtr && other) {
	if (this != &other) {
		if (counter == other.counter) {
			return *this;
		}
		if (counter != nullptr && --*counter == 0) {
			delete[] data;
			delete counter;
		}
		data = std::move(other.data);
		counter = std::move(other.counter);
		other.data = nullptr;
		other.counter = nullptr;
	}
	return *this;
}

template<typename T>
SmartPtr<T[]>::~SmartPtr() {
	if (counter != nullptr && --*counter == 0) {
		delete[] data;
		delete counter;
	}
}

template<typename T> template<typename T1>
SmartPtr<T[]>::SmartPtr(SmartPtr<T1[]> const & other) :
		data(other.data), counter(other.counter) {
	if (counter != nullptr) {
		++*counter;
	}
}

template<typename T> template<typename T1>
SmartPtr<T[]>& SmartPtr<T[]>::operator=(SmartPtr<T1[]> const & other) {
	if (other.counter != nullptr) {
		++*other.counter;
	}

	if (counter != nullptr && --*counter == 0) {
		delete[] data;
		delete counter;
	}

	data = other.data;
	counter = other.counter;
	return *this;

}

template<typename T> template<typename T1>
SmartPtr<T[]>::SmartPtr(SmartPtr<T1[]> && other) :
		data(std::move(other.data)), counter(std::move(other.counter)) {
	other.data = nullptr;
	other.counter = nullptr;
}

template<typename T> template<typename T1>
SmartPtr<T[]>& SmartPtr<T[]>::operator=(SmartPtr<T1[]> && other) {
	if (counter == other.counter) {
		return *this;
	}
	if (counter != nullptr && --*counter == 0) {
		delete[] data;
		delete counter;
	}
	data = std::move(other.data);
	counter = std::move(other.counter);
	other.data = nullptr;
	other.counter = nullptr;

	return *this;
}

template<typename T, typename ... Args>
SmartPtr<T> makeSmartPtr(Args&&... args) {
	return SmartPtr<T>(new T(std::forward<Args>(args)...));
}

#endif /* SMARTPTR_H_ */
