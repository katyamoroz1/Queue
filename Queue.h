

#ifndef QUEUE_ARRAY_QUEUE_H
#define QUEUE_ARRAY_QUEUE_H

#include <initializer_list>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <tuple>
#include "Visitor.h"

template<typename T>
class Model {
public:

	virtual void Add(const T& element) = 0;

	virtual T& Get(size_t index) const = 0;

	virtual void Delete(size_t index) = 0;

	virtual size_t Size() const = 0;

	virtual bool IsEmpty() const = 0;

	virtual void Clear() = 0;

	virtual void Accept(Visitor<T>& visitor) = 0;

	static std::string str_to_out;

	static std::string str_to_out_iter;

	static std::string str_for_first;

	static std::string str_for_last;
};

template<typename T>
std::string Model<T>::str_to_out = "";

template<typename T>
std::string Model<T>::str_to_out_iter = "";

template<typename T>
std::string Model<T>::str_for_first = "";

template<typename T>
std::string Model<T>::str_for_last = "";



template<typename T>
class Queue : public Model<T> {
public:
	Queue() : size_(0),
		allocated_size_(1),
		data_(new T[allocated_size_]) {}
	Queue(const std::initializer_list<T> list) noexcept :
		size_(list.size()),
		allocated_size_(list.size()),
		data_(new T[allocated_size_]) {
		int i = 0;
		for (auto it = list.begin(); it != list.end(); ++it, ++i) {
			data_[i] = *it;
		}
	}
	Queue(const Queue &other) : size_(other.size_),
		allocated_size_(other.size_),
		data_(new T[allocated_size_]) {
		for (int i = 0; i < other.size_; i++) {
			data_[i] = other.data_[i];
		}
	}
	Queue &operator=(const Queue &other) {
		if (allocated_size_ != other.allocated_size_) {
			delete[] data_;
			allocated_size_ = other.allocated_size_;
			data_ = new T[allocated_size_];
		}
		size_ = other.size_;
	}
		Queue(Queue &&other) noexcept :
			size_(other.size_),
			allocated_size_(other.allocated_size_),
			data_(other.data_) {
			other.size_ = 0;
			other.allocated_size_ = 1;
			other.data_ = new T[other.allocated_size_];
		}
		Queue &operator=(Queue &&other) noexcept {
			delete[] data_;
			allocated_size_ = other.allocated_size_;
			size_ = other.size_;
			data_ = other.data_;
			other.size_ = 0;
			other.allocated_size_ = 1;
			other.data_ = new T[other.allocated_size_];
			return *this;
		}
		~Queue() {
			delete[] data_;
		}
		void Add(const T& element) override {
			Push(element);
		}

		T& Get(size_t index) const override {
			if (index < 0 || index > size_) {
				throw std::out_of_range("Get called with invalid index");
			}
			return data_[index];
		}

		void Delete(size_t index) {
			Pop();
		}

		bool IsEmpty() const override {
			return size_ == 0;
		}
		size_t Size() const override {
			return size_;
		}
		void Clear() override {
			delete[] data_;
			allocated_size_ = 1;
			size_ = 0;
			data_ = new T[allocated_size_];
		}
		T Front() const {
			if (!IsEmpty()) {
				return data_[0];
			}
			else {
				throw std::logic_error("Empty queue!");
			}
		}
		T Back() const {
			if (!IsEmpty()) {
				return data_[size_ - 1];
			}
			else {
				throw std::logic_error("Empty queue!");
			}
		}
		void Push(T value) {
			if (size_ == allocated_size_) {
				Relocate(2 * allocated_size_);
			}
			data_[size_] = value;
			size_++;
		}
		void Pop() {
			if (!IsEmpty()) {
				for (int i = 0; i < size_ - 1; i++) {
					data_[i] = data_[i + 1];
				}
				size_--;
				if (size_ < allocated_size_ / 4) {
					Relocate(allocated_size_ / 2);
				}
			}
			else {
				throw std::logic_error("Empty queue!");
			}
		}
		void Swap(Queue<T> &other) {
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
		void Relocate(std::size_t new_size) {
			allocated_size_ = new_size;
			T *old_data_ = data_;
			data_ = new T[allocated_size_];
			for (size_t i = 0; i < size_; ++i) {
				data_[i] = old_data_[i];
			}
			delete[] old_data_;
		}

		void Accept(Visitor<T>& visitor) override {
			visitor.VisitQueue(*this);
		}

		Queue &operator+=(Queue<T> &other) {
			Relocate(size_ + other.size_);
			for (int i = size_; i < other.size_ + size_; i++) {
				data_[i] = other.data_[i];
			}
			return *this;
		}
		T operator[](int n)const {
			return data_[n];
		}
		Queue operator+(const Queue<T> &other) const {
			Queue<T> sum;
			for (int i = 0; i < size_; i++) {
				sum.Push(data_[i]);
			}
			for (int i = 0; i < other.size_; i++) {
				sum.Push(other.data_[i]);
			}
			return sum;
		}
		bool operator==(Queue<T>& other) {
			if (size_ == other.size_) {
				for (int i = 0; i < size_; i++) {
					if (data_[i] == other.data_[i]) {
						return true;
					}
				}
			}
			return false;
		}
		bool operator!=(Queue<T>& other) {
			if (size_ == other.size_) {
				for (int i = 0; i < size_; i++) {
					if (data_[i] == other.data_[i]) {
						return false;
					}
				}
			}
			return true;
		}

		friend std::ostream &operator<<(std::ostream &out, const Queue<T> &queue) {
			for (int i = 0; i < queue.size_; i++) {
				out << queue.data_[i] << " ";
			}
			return out;
		}
		friend std::istream &operator>>(std::istream &in, Queue<T> &queue) {
			std::cout << "Enter size of queue" << std::endl;
			int size;
			in >> size;
			std::cout << "Enter values" << std::endl;
			for (int i = 0; i < size; i++) {
				T value;
				in >> value;
				queue.Push(value);
			}
			return in;
		}

private:
	size_t size_;
	size_t allocated_size_;
	T* data_;
};

 template <typename T>
 class Heap : public Model<T> {
 public:
	 Heap() : size_(0), allocated_size_(1), data_(new T[allocated_size_]) {}
	 void Add(const T& element) override {
		 if (size_ == allocated_size_) {
			 Relocate(2 * allocated_size_);
		 }
		 data_[size_] = element;
		 size_++;
	 }

	 T& Get(size_t index) const override {
		 if (index < 0 || index > size_) {
			 throw std::out_of_range("Get called with invalid index");
		 }
		 return data_[index];
	 }

	 void Delete(size_t index) override {
		 if (!IsEmpty()) {
			 for (int i = index; i < size_ - 1; i++) {
				 data_[i] = data_[i + 1];
			 }
			 size_--;
			 if (size_ < allocated_size_ / 4) {
				 Relocate(allocated_size_ / 2);
			 }
		 }
		 else {
			 throw std::logic_error("Empty queue!");
		 }
	 }

	 size_t Size() const override {
		 return size_;
	 }

	 bool IsEmpty() const {
		 return size_ == 0;
	 }

	 void Clear() override {
		 delete[] data_;
		 size_ = 0;
	 }

	 //virtual ~Model() = default;

	 virtual void Accept(Visitor<T>& visitor) override {
		 visitor.VisitHeap(*this);
	 }
	 void Relocate(std::size_t new_size) {
		 allocated_size_ = new_size;
		 T *old_data_ = data_;
		 data_ = new T[allocated_size_];
		 for (size_t i = 0; i < size_; ++i) {
			 data_[i] = old_data_[i];
		 }
		 delete[] old_data_;
	 }

private:
	size_t size_;
	size_t allocated_size_;
	T* data_;
 };


#endif //QUEUE_ARRAY_QUEUE_H 
