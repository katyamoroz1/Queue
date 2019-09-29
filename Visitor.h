#pragma once
#include "Model.h"

template <typename T>
class Model;

template <typename T>
class Element;

template <typename T>
class Visitor {
public:
	virtual void visit(Element<T>& element) = 0;
	virtual T& VisitQueue(Model<T>& queue) = 0;
	virtual T& VisitHeap(Model<T>& heap) = 0;
};

template <typename T>
class Element {
public:
	Element(T& v);
	void accept(Visitor<T>& v);
	T& getValue() const;
private:
	T& value_;
};

template <typename T>
class VisitorSum : public Visitor<T> {
public:
	void visit(Element<T>& e) override;
	T& VisitHeap(Model<T>& heap) override;
	T& VisitQueue(Model<T>& queue) override;
	int result() const;
private:
	int result_ = 0;
};

template <typename T>
int VisitorSum<T>::result() const {
	return result_;
}

template <typename T>
void VisitorSum<T>::visit(Element<T>& e) {
	result_ += e.getValue().size();
}

template <typename T>
T& VisitorSum<T>::VisitQueue(Model<T>& queue) {
	T& element = queue.Get(0);
	 queue.Delete(0);
	 return element;
}
template <typename T>
T& VisitorSum<T>::VisitHeap(Model<T>& heap) {
	int index = rand() % heap.Size();
	T& element = heap.Get(index);
	heap.Delete(index);
	return element;
}

template <typename T>
Element<T>::Element(T& v) :
	value_(v) {}

template <typename T>
void Element<T>::accept(Visitor<T>& v) {
	v.visit(*this);
}

template <typename T>
T& Element<T>::getValue() const {
	return value_;
}
