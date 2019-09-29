//
// Created by ekate on 19.09.2019.
//

#include "Queue.h"
#include "stdafx.h"

template <typename T>
Queue<T>::Iterator::Iterator(const Queue<T> *const queue, int index)
	: queue_(queue),
	index_(index) {}

template <typename T>
T* Queue<T>::Iterator::operator->() const {
	return queue_->data_ + index_;
}

template <typename T>
T& Queue<T>::Iterator::operator*() const {
	return queue_->data_[index_];
}

template <typename T>
T& Queue<T>::Iterator::operator[](int n) const {
	return queue_->data_[index_ + n];
}

template <typename T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++() {
	++index_;
	return (*this);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int) {
	auto buff(*this);
	++index_;
	return buff;
}

template <typename T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator--() {
	--index_;
	return (*this);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator--(int) {
	auto buff(*this);
	--index_;
	return buff;
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator+(int n) const {
	return Iterator(queue_, index_ + n);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator-(int n) const {
	return Iterator(queue_, index_ - n);
}

template <typename T>
bool Queue<T>::Iterator::operator==(const Queue<T>::Iterator &other) const {
	return index_ == other.index_;
}

template <typename T>
bool Queue<T>::Iterator::operator!=(const Queue<T>::Iterator &other) const {
	return index_ != other.index_;
}

template <typename T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator=(const Queue<T>::Iterator &other) {
	index_ = other.index_;
	return (*this);
}

//////////////////////////////////////////////////
template <typename T>
Queue<T>::ConstIterator::ConstIterator(const Queue<T> *const queue, int index)
	: queue_(queue),
	index_(index) {}

template <typename T>
const T* Queue<T>::ConstIterator::operator->() const {
	return queue_->data_ + index_;
}

template <typename T>
const T& Queue<T>::ConstIterator::operator*() const {
	return queue_->data_[index_];
}

template <typename T>
const T& Queue<T>::ConstIterator::operator[](int n) const {
	return queue_->data_[index_ + n];
}

template <typename T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++() {
	++index_;
	return (*this);
}

template <typename T>
const typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(int) {
	auto buff(*this);
	++index_;
	return buff;
}

template <typename T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator--() {
	--index_;
	return (*this);
}

template <typename T>
const typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator--(int) {
	auto buff(*this);
	--index_;
	return buff;
}

template <typename T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator+(int n) const {
	return Iterator(queue_, index_ + n);
}

template <typename T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator-(int n) const {
	return Iterator(queue_, index_ - n);
}

template <typename T>
bool Queue<T>::ConstIterator::operator==(const Queue<T>::ConstIterator &other) const {
	return index_ == other.index_;
}

template <typename T>
bool Queue<T>::ConstIterator::operator!=(const Queue<T>::ConstIterator &other) const {
	return index_ != other.index_;
}

template <typename T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator=(const Queue<T>::ConstIterator &other) {
	index_ = other.index_;
	return (*this);
}
///////////////////////////////////////////////////////
template <typename T>
Queue<T>::Queue() : size_(0),
allocated_size_(1),
data_(new T[allocated_size_]) {}

template <typename T>
Queue<T>::Queue(const std::initializer_list<T> list) noexcept :
	size_(list.size()),
	allocated_size_(list.size()),
	data_(new T[allocated_size_]) {
	int i = 0;
	for (auto it = list.begin(); it != list.end(); ++it, ++i) {
		data_[i] = *it;
	}
}
template <typename T>
Queue<T>::Queue(const Queue<T> &other) : size_(other.size_),
allocated_size_(other.size_),
data_(new T[allocated_size_]) {
	for (int i = 0; i < other.size_; i++) {
		data_[i] = other.data_[i];
	}
}
template <typename T>
Queue<T>& Queue<T>::operator=(const Queue &other) {
	if (allocated_size_ != other.allocated_size_) {
		delete[] data_;
		allocated_size_ = other.allocated_size_;
		data_ = new T[allocated_size_];
	}
	size_ = other.size_;
	for (size_t i = 0; i < other.size_; i++) {
		data_[i] = other[i];
	}
	return *this;
}
template <typename T>
Queue<T>::Queue(Queue &&other) noexcept :
	size_(other.size_),
	allocated_size_(other.allocated_size_),
	data_(other.data_) {
	other.size_ = 0;
	other.allocated_size_ = 1;
	other.data_ = new T[other.allocated_size_];
}
template <typename T>
Queue<T>& Queue<T>::operator=(Queue &&other) noexcept {
	delete[] data_;
	allocated_size_ = other.allocated_size_;
	size_ = other.size_;
	data_ = other.data_;
	other.size_ = 0;
	other.allocated_size_ = 1;
	other.data_ = new T[other.allocated_size_];
	return *this;
}
template <typename T>
Queue<T>::~Queue() {
	delete[] data_;
}

template <typename T>
bool Queue<T>::IsEmpty() const {
	return size_ == 0;
}
template <typename T>
size_t Queue<T>::Size() const {
	return size_;
}
template <typename T>
void Queue<T>::Clear() {
	delete[] data_;
	allocated_size_ = 1;
	size_ = 0;
	data_ = new T[allocated_size_];
}
template <typename T>
T Queue<T>::Front() {
	if (!IsEmpty()) {
		return data_[0];
	}
	else {
		throw std::logic_error("Empty queue!");
	}
}
template <typename T>
T Queue<T>::Back() const {
	if (!IsEmpty()) {
		return data_[size_ - 1];
	}
	else {
		throw std::logic_error("Empty queue!");
	}
}
template <typename T>
void Queue<T>::Push(T value) {
	if (size_ == allocated_size_) {
		Relocate(2 * allocated_size_);
	}
	data_[size_] = value;
	size_++;
}
template <typename T>
void Queue<T>::Pop() {
	if (!IsEmpty()) {
		for (int i = 0; i < size_ - 1; i++) {
			data_[i] = data_[i + 1];
		}
		size_--;
		if (size_ <= allocated_size_ / 4) {
			Relocate(allocated_size_ / 2);
		}
	}
	else {
		throw std::logic_error("Empty queue!");
	}
}
template <typename T>
void Queue<T>::Swap(Queue<T> &other) {
	T* array = other.data_;
	size_t s = other.size_;
	size_t alloc = other.allocated_size_;
	other.data_ = data_;
	other.size_ = size_;
	other.allocated_size_ = allocated_size_;
	data_ = array;
	size_ = s;
	allocated_size_ = alloc;
}
template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() {
	return Iterator(this, 0);
};
template <typename T>
typename Queue<T>::Iterator Queue<T>::end() {
	return Iterator(this, this->Size());
};
template <typename T>
typename Queue<T>::ConstIterator Queue<T>::begin() const {
	return ConstIterator(this, 0);
};
template <typename T>
typename Queue<T>::ConstIterator Queue<T>::end() const {
	return ConstIterator(this, this->Size());
};

//template <typename T>
//void Queue<T>::AcceptVisitor(Visitor<T> visitor) {
//	visitor.visitQueue(this);
//}

template <typename T>
Queue<T>& Queue<T>::operator+=(Queue<T> &other) {
	Relocate(size_ + other.size_);
	for (int i = size_; i < other.size_ + size_; i++) {
		data_[i] = other.data_[i];
	}
	return *this;
}
template <typename T>
T Queue<T>::operator[](int n) const {
	return data_[n];
}
template <typename T>
Queue<T> Queue<T>::operator+(const Queue<T> &other) const {
	Queue<T> sum;
	for (int i = 0; i < size_; i++) {
		sum.Push(data_[i]);
	}
	for (int i = 0; i < other.size_; i++) {
		sum.Push(other.data_[i]);
	}
	return sum;
}
template <typename T>
bool Queue<T>::operator==(Queue<T>& other) {
	if (size_ == other.size_) {
		for (int i = 0; i < size_; i++) {
			if (data_[i] == other.data_[i]) {
				return true;
			}
		}
	}
	return false;
}
template <typename T>
bool Queue<T>::operator!=(Queue<T>& other) {
	if (size_ == other.size_) {
		for (int i = 0; i < size_; i++) {
			if (data_[i] == other.data_[i]) {
				return false;
			}
		}
	}
	return true;
}
template <typename T>
void Queue<T>::Relocate(size_t new_size) {
	allocated_size_ = new_size;
	T *old_data_ = data_;
	data_ = new T[allocated_size_];
	for (size_t i = 0; i < size_; ++i) {
		data_[i] = old_data_[i];
	}
	delete[] old_data_;
}
